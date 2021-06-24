<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright तऊ 2006-2014 Intel Corporation.
 *
 * Authors: David Woodhouse <dwmw2@infradead.org>,
 *          Ashok Raj <ashok.raj@पूर्णांकel.com>,
 *          Shaohua Li <shaohua.li@पूर्णांकel.com>,
 *          Anil S Keshavamurthy <anil.s.keshavamurthy@पूर्णांकel.com>,
 *          Fenghua Yu <fenghua.yu@पूर्णांकel.com>
 *          Joerg Roedel <jroedel@suse.de>
 */

#घोषणा pr_fmt(fmt)     "DMAR: " fmt
#घोषणा dev_fmt(fmt)    pr_fmt(fmt)

#समावेश <linux/init.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pci.h>
#समावेश <linux/dmar.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/mempool.h>
#समावेश <linux/memory.h>
#समावेश <linux/cpu.h>
#समावेश <linux/समयr.h>
#समावेश <linux/पन.स>
#समावेश <linux/iova.h>
#समावेश <linux/iommu.h>
#समावेश <linux/dma-iommu.h>
#समावेश <linux/पूर्णांकel-iommu.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/tboot.h>
#समावेश <linux/dmi.h>
#समावेश <linux/pci-ats.h>
#समावेश <linux/memblock.h>
#समावेश <linux/dma-direct.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/numa.h>
#समावेश <यंत्र/irq_remapping.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/iommu.h>

#समावेश "../irq_remapping.h"
#समावेश "pasid.h"
#समावेश "cap_audit.h"

#घोषणा ROOT_SIZE		VTD_PAGE_SIZE
#घोषणा CONTEXT_SIZE		VTD_PAGE_SIZE

#घोषणा IS_GFX_DEVICE(pdev) ((pdev->class >> 16) == PCI_BASE_CLASS_DISPLAY)
#घोषणा IS_USB_DEVICE(pdev) ((pdev->class >> 8) == PCI_CLASS_SERIAL_USB)
#घोषणा IS_ISA_DEVICE(pdev) ((pdev->class >> 8) == PCI_CLASS_BRIDGE_ISA)
#घोषणा IS_AZALIA(pdev) ((pdev)->venकरोr == 0x8086 && (pdev)->device == 0x3a3e)

#घोषणा IOAPIC_RANGE_START	(0xfee00000)
#घोषणा IOAPIC_RANGE_END	(0xfeefffff)
#घोषणा IOVA_START_ADDR		(0x1000)

#घोषणा DEFAULT_DOMAIN_ADDRESS_WIDTH 57

#घोषणा MAX_AGAW_WIDTH 64
#घोषणा MAX_AGAW_PFN_WIDTH	(MAX_AGAW_WIDTH - VTD_PAGE_SHIFT)

#घोषणा __DOMAIN_MAX_PFN(gaw)  ((((uपूर्णांक64_t)1) << ((gaw) - VTD_PAGE_SHIFT)) - 1)
#घोषणा __DOMAIN_MAX_ADDR(gaw) ((((uपूर्णांक64_t)1) << (gaw)) - 1)

/* We limit DOMAIN_MAX_PFN to fit in an अचिन्हित दीर्घ, and DOMAIN_MAX_ADDR
   to match. That way, we can use 'unsigned long' क्रम PFNs with impunity. */
#घोषणा DOMAIN_MAX_PFN(gaw)	((अचिन्हित दीर्घ) min_t(uपूर्णांक64_t, \
				__DOMAIN_MAX_PFN(gaw), (अचिन्हित दीर्घ)-1))
#घोषणा DOMAIN_MAX_ADDR(gaw)	(((uपूर्णांक64_t)__DOMAIN_MAX_PFN(gaw)) << VTD_PAGE_SHIFT)

/* IO भव address start page frame number */
#घोषणा IOVA_START_PFN		(1)

#घोषणा IOVA_PFN(addr)		((addr) >> PAGE_SHIFT)

/* page table handling */
#घोषणा LEVEL_STRIDE		(9)
#घोषणा LEVEL_MASK		(((u64)1 << LEVEL_STRIDE) - 1)

/*
 * This biपंचांगap is used to advertise the page sizes our hardware support
 * to the IOMMU core, which will then use this inक्रमmation to split
 * physically contiguous memory regions it is mapping पूर्णांकo page sizes
 * that we support.
 *
 * Traditionally the IOMMU core just handed us the mappings directly,
 * after making sure the size is an order of a 4KiB page and that the
 * mapping has natural alignment.
 *
 * To retain this behavior, we currently advertise that we support
 * all page sizes that are an order of 4KiB.
 *
 * If at some poपूर्णांक we'd like to utilize the IOMMU core's new behavior,
 * we could change this to advertise the real page sizes we support.
 */
#घोषणा INTEL_IOMMU_PGSIZES	(~0xFFFUL)

अटल अंतरभूत पूर्णांक agaw_to_level(पूर्णांक agaw)
अणु
	वापस agaw + 2;
पूर्ण

अटल अंतरभूत पूर्णांक agaw_to_width(पूर्णांक agaw)
अणु
	वापस min_t(पूर्णांक, 30 + agaw * LEVEL_STRIDE, MAX_AGAW_WIDTH);
पूर्ण

अटल अंतरभूत पूर्णांक width_to_agaw(पूर्णांक width)
अणु
	वापस DIV_ROUND_UP(width - 30, LEVEL_STRIDE);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक level_to_offset_bits(पूर्णांक level)
अणु
	वापस (level - 1) * LEVEL_STRIDE;
पूर्ण

अटल अंतरभूत पूर्णांक pfn_level_offset(u64 pfn, पूर्णांक level)
अणु
	वापस (pfn >> level_to_offset_bits(level)) & LEVEL_MASK;
पूर्ण

अटल अंतरभूत u64 level_mask(पूर्णांक level)
अणु
	वापस -1ULL << level_to_offset_bits(level);
पूर्ण

अटल अंतरभूत u64 level_size(पूर्णांक level)
अणु
	वापस 1ULL << level_to_offset_bits(level);
पूर्ण

अटल अंतरभूत u64 align_to_level(u64 pfn, पूर्णांक level)
अणु
	वापस (pfn + level_size(level) - 1) & level_mask(level);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ lvl_to_nr_pages(अचिन्हित पूर्णांक lvl)
अणु
	वापस 1UL << min_t(पूर्णांक, (lvl - 1) * LEVEL_STRIDE, MAX_AGAW_PFN_WIDTH);
पूर्ण

/* VT-d pages must always be _smaller_ than MM pages. Otherwise things
   are never going to work. */
अटल अंतरभूत अचिन्हित दीर्घ dma_to_mm_pfn(अचिन्हित दीर्घ dma_pfn)
अणु
	वापस dma_pfn >> (PAGE_SHIFT - VTD_PAGE_SHIFT);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ mm_to_dma_pfn(अचिन्हित दीर्घ mm_pfn)
अणु
	वापस mm_pfn << (PAGE_SHIFT - VTD_PAGE_SHIFT);
पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ page_to_dma_pfn(काष्ठा page *pg)
अणु
	वापस mm_to_dma_pfn(page_to_pfn(pg));
पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ virt_to_dma_pfn(व्योम *p)
अणु
	वापस page_to_dma_pfn(virt_to_page(p));
पूर्ण

/* global iommu list, set शून्य क्रम ignored DMAR units */
अटल काष्ठा पूर्णांकel_iommu **g_iommus;

अटल व्योम __init check_tylersburg_isoch(व्योम);
अटल पूर्णांक rwbf_quirk;

/*
 * set to 1 to panic kernel अगर can't successfully enable VT-d
 * (used when kernel is launched w/ TXT)
 */
अटल पूर्णांक क्रमce_on = 0;
अटल पूर्णांक पूर्णांकel_iommu_tboot_noक्रमce;
अटल पूर्णांक no_platक्रमm_optin;

#घोषणा ROOT_ENTRY_NR (VTD_PAGE_SIZE/माप(काष्ठा root_entry))

/*
 * Take a root_entry and वापस the Lower Context Table Poपूर्णांकer (LCTP)
 * अगर marked present.
 */
अटल phys_addr_t root_entry_lctp(काष्ठा root_entry *re)
अणु
	अगर (!(re->lo & 1))
		वापस 0;

	वापस re->lo & VTD_PAGE_MASK;
पूर्ण

/*
 * Take a root_entry and वापस the Upper Context Table Poपूर्णांकer (UCTP)
 * अगर marked present.
 */
अटल phys_addr_t root_entry_uctp(काष्ठा root_entry *re)
अणु
	अगर (!(re->hi & 1))
		वापस 0;

	वापस re->hi & VTD_PAGE_MASK;
पूर्ण

अटल अंतरभूत व्योम context_clear_pasid_enable(काष्ठा context_entry *context)
अणु
	context->lo &= ~(1ULL << 11);
पूर्ण

अटल अंतरभूत bool context_pasid_enabled(काष्ठा context_entry *context)
अणु
	वापस !!(context->lo & (1ULL << 11));
पूर्ण

अटल अंतरभूत व्योम context_set_copied(काष्ठा context_entry *context)
अणु
	context->hi |= (1ull << 3);
पूर्ण

अटल अंतरभूत bool context_copied(काष्ठा context_entry *context)
अणु
	वापस !!(context->hi & (1ULL << 3));
पूर्ण

अटल अंतरभूत bool __context_present(काष्ठा context_entry *context)
अणु
	वापस (context->lo & 1);
पूर्ण

bool context_present(काष्ठा context_entry *context)
अणु
	वापस context_pasid_enabled(context) ?
	     __context_present(context) :
	     __context_present(context) && !context_copied(context);
पूर्ण

अटल अंतरभूत व्योम context_set_present(काष्ठा context_entry *context)
अणु
	context->lo |= 1;
पूर्ण

अटल अंतरभूत व्योम context_set_fault_enable(काष्ठा context_entry *context)
अणु
	context->lo &= (((u64)-1) << 2) | 1;
पूर्ण

अटल अंतरभूत व्योम context_set_translation_type(काष्ठा context_entry *context,
						अचिन्हित दीर्घ value)
अणु
	context->lo &= (((u64)-1) << 4) | 3;
	context->lo |= (value & 3) << 2;
पूर्ण

अटल अंतरभूत व्योम context_set_address_root(काष्ठा context_entry *context,
					    अचिन्हित दीर्घ value)
अणु
	context->lo &= ~VTD_PAGE_MASK;
	context->lo |= value & VTD_PAGE_MASK;
पूर्ण

अटल अंतरभूत व्योम context_set_address_width(काष्ठा context_entry *context,
					     अचिन्हित दीर्घ value)
अणु
	context->hi |= value & 7;
पूर्ण

अटल अंतरभूत व्योम context_set_करोमुख्य_id(काष्ठा context_entry *context,
					 अचिन्हित दीर्घ value)
अणु
	context->hi |= (value & ((1 << 16) - 1)) << 8;
पूर्ण

अटल अंतरभूत पूर्णांक context_करोमुख्य_id(काष्ठा context_entry *c)
अणु
	वापस((c->hi >> 8) & 0xffff);
पूर्ण

अटल अंतरभूत व्योम context_clear_entry(काष्ठा context_entry *context)
अणु
	context->lo = 0;
	context->hi = 0;
पूर्ण

/*
 * This करोमुख्य is a अटलally identity mapping करोमुख्य.
 *	1. This करोमुख्य creats a अटल 1:1 mapping to all usable memory.
 * 	2. It maps to each iommu अगर successful.
 *	3. Each iommu mapps to this करोमुख्य अगर successful.
 */
अटल काष्ठा dmar_करोमुख्य *si_करोमुख्य;
अटल पूर्णांक hw_pass_through = 1;

#घोषणा क्रम_each_करोमुख्य_iommu(idx, करोमुख्य)			\
	क्रम (idx = 0; idx < g_num_of_iommus; idx++)		\
		अगर (करोमुख्य->iommu_refcnt[idx])

काष्ठा dmar_rmrr_unit अणु
	काष्ठा list_head list;		/* list of rmrr units	*/
	काष्ठा acpi_dmar_header *hdr;	/* ACPI header		*/
	u64	base_address;		/* reserved base address*/
	u64	end_address;		/* reserved end address */
	काष्ठा dmar_dev_scope *devices;	/* target devices */
	पूर्णांक	devices_cnt;		/* target device count */
पूर्ण;

काष्ठा dmar_atsr_unit अणु
	काष्ठा list_head list;		/* list of ATSR units */
	काष्ठा acpi_dmar_header *hdr;	/* ACPI header */
	काष्ठा dmar_dev_scope *devices;	/* target devices */
	पूर्णांक devices_cnt;		/* target device count */
	u8 include_all:1;		/* include all ports */
पूर्ण;

काष्ठा dmar_satc_unit अणु
	काष्ठा list_head list;		/* list of SATC units */
	काष्ठा acpi_dmar_header *hdr;	/* ACPI header */
	काष्ठा dmar_dev_scope *devices;	/* target devices */
	काष्ठा पूर्णांकel_iommu *iommu;	/* the corresponding iommu */
	पूर्णांक devices_cnt;		/* target device count */
	u8 atc_required:1;		/* ATS is required */
पूर्ण;

अटल LIST_HEAD(dmar_atsr_units);
अटल LIST_HEAD(dmar_rmrr_units);
अटल LIST_HEAD(dmar_satc_units);

#घोषणा क्रम_each_rmrr_units(rmrr) \
	list_क्रम_each_entry(rmrr, &dmar_rmrr_units, list)

/* biपंचांगap क्रम indexing पूर्णांकel_iommus */
अटल पूर्णांक g_num_of_iommus;

अटल व्योम करोमुख्य_निकास(काष्ठा dmar_करोमुख्य *करोमुख्य);
अटल व्योम करोमुख्य_हटाओ_dev_info(काष्ठा dmar_करोमुख्य *करोमुख्य);
अटल व्योम dmar_हटाओ_one_dev_info(काष्ठा device *dev);
अटल व्योम __dmar_हटाओ_one_dev_info(काष्ठा device_करोमुख्य_info *info);
अटल पूर्णांक पूर्णांकel_iommu_attach_device(काष्ठा iommu_करोमुख्य *करोमुख्य,
				     काष्ठा device *dev);
अटल phys_addr_t पूर्णांकel_iommu_iova_to_phys(काष्ठा iommu_करोमुख्य *करोमुख्य,
					    dma_addr_t iova);

#अगर_घोषित CONFIG_INTEL_IOMMU_DEFAULT_ON
पूर्णांक dmar_disabled = 0;
#अन्यथा
पूर्णांक dmar_disabled = 1;
#पूर्ण_अगर /* CONFIG_INTEL_IOMMU_DEFAULT_ON */

#अगर_घोषित CONFIG_INTEL_IOMMU_SCALABLE_MODE_DEFAULT_ON
पूर्णांक पूर्णांकel_iommu_sm = 1;
#अन्यथा
पूर्णांक पूर्णांकel_iommu_sm;
#पूर्ण_अगर /* CONFIG_INTEL_IOMMU_SCALABLE_MODE_DEFAULT_ON */

पूर्णांक पूर्णांकel_iommu_enabled = 0;
EXPORT_SYMBOL_GPL(पूर्णांकel_iommu_enabled);

अटल पूर्णांक dmar_map_gfx = 1;
अटल पूर्णांक पूर्णांकel_iommu_strict;
अटल पूर्णांक पूर्णांकel_iommu_superpage = 1;
अटल पूर्णांक iommu_identity_mapping;
अटल पूर्णांक iommu_skip_te_disable;

#घोषणा IDENTMAP_GFX		2
#घोषणा IDENTMAP_AZALIA		4

पूर्णांक पूर्णांकel_iommu_gfx_mapped;
EXPORT_SYMBOL_GPL(पूर्णांकel_iommu_gfx_mapped);

#घोषणा DEFER_DEVICE_DOMAIN_INFO ((काष्ठा device_करोमुख्य_info *)(-2))
काष्ठा device_करोमुख्य_info *get_करोमुख्य_info(काष्ठा device *dev)
अणु
	काष्ठा device_करोमुख्य_info *info;

	अगर (!dev)
		वापस शून्य;

	info = dev_iommu_priv_get(dev);
	अगर (unlikely(info == DEFER_DEVICE_DOMAIN_INFO))
		वापस शून्य;

	वापस info;
पूर्ण

DEFINE_SPINLOCK(device_करोमुख्य_lock);
अटल LIST_HEAD(device_करोमुख्य_list);

/*
 * Iterate over elements in device_करोमुख्य_list and call the specअगरied
 * callback @fn against each element.
 */
पूर्णांक क्रम_each_device_करोमुख्य(पूर्णांक (*fn)(काष्ठा device_करोमुख्य_info *info,
				     व्योम *data), व्योम *data)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा device_करोमुख्य_info *info;

	spin_lock_irqsave(&device_करोमुख्य_lock, flags);
	list_क्रम_each_entry(info, &device_करोमुख्य_list, global) अणु
		ret = fn(info, data);
		अगर (ret) अणु
			spin_unlock_irqrestore(&device_करोमुख्य_lock, flags);
			वापस ret;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&device_करोमुख्य_lock, flags);

	वापस 0;
पूर्ण

स्थिर काष्ठा iommu_ops पूर्णांकel_iommu_ops;

अटल bool translation_pre_enabled(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	वापस (iommu->flags & VTD_FLAG_TRANS_PRE_ENABLED);
पूर्ण

अटल व्योम clear_translation_pre_enabled(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	iommu->flags &= ~VTD_FLAG_TRANS_PRE_ENABLED;
पूर्ण

अटल व्योम init_translation_status(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	u32 gsts;

	gsts = पढ़ोl(iommu->reg + DMAR_GSTS_REG);
	अगर (gsts & DMA_GSTS_TES)
		iommu->flags |= VTD_FLAG_TRANS_PRE_ENABLED;
पूर्ण

अटल पूर्णांक __init पूर्णांकel_iommu_setup(अक्षर *str)
अणु
	अगर (!str)
		वापस -EINVAL;
	जबतक (*str) अणु
		अगर (!म_भेदन(str, "on", 2)) अणु
			dmar_disabled = 0;
			pr_info("IOMMU enabled\n");
		पूर्ण अन्यथा अगर (!म_भेदन(str, "off", 3)) अणु
			dmar_disabled = 1;
			no_platक्रमm_optin = 1;
			pr_info("IOMMU disabled\n");
		पूर्ण अन्यथा अगर (!म_भेदन(str, "igfx_off", 8)) अणु
			dmar_map_gfx = 0;
			pr_info("Disable GFX device mapping\n");
		पूर्ण अन्यथा अगर (!म_भेदन(str, "forcedac", 8)) अणु
			pr_warn("intel_iommu=forcedac deprecated; use iommu.forcedac instead\n");
			iommu_dma_क्रमcedac = true;
		पूर्ण अन्यथा अगर (!म_भेदन(str, "strict", 6)) अणु
			pr_info("Disable batched IOTLB flush\n");
			पूर्णांकel_iommu_strict = 1;
		पूर्ण अन्यथा अगर (!म_भेदन(str, "sp_off", 6)) अणु
			pr_info("Disable supported super page\n");
			पूर्णांकel_iommu_superpage = 0;
		पूर्ण अन्यथा अगर (!म_भेदन(str, "sm_on", 5)) अणु
			pr_info("Intel-IOMMU: scalable mode supported\n");
			पूर्णांकel_iommu_sm = 1;
		पूर्ण अन्यथा अगर (!म_भेदन(str, "tboot_noforce", 13)) अणु
			pr_info("Intel-IOMMU: not forcing on after tboot. This could expose security risk for tboot\n");
			पूर्णांकel_iommu_tboot_noक्रमce = 1;
		पूर्ण

		str += म_खोज(str, ",");
		जबतक (*str == ',')
			str++;
	पूर्ण
	वापस 0;
पूर्ण
__setup("intel_iommu=", पूर्णांकel_iommu_setup);

अटल काष्ठा kmem_cache *iommu_करोमुख्य_cache;
अटल काष्ठा kmem_cache *iommu_devinfo_cache;

अटल काष्ठा dmar_करोमुख्य* get_iommu_करोमुख्य(काष्ठा पूर्णांकel_iommu *iommu, u16 did)
अणु
	काष्ठा dmar_करोमुख्य **करोमुख्यs;
	पूर्णांक idx = did >> 8;

	करोमुख्यs = iommu->करोमुख्यs[idx];
	अगर (!करोमुख्यs)
		वापस शून्य;

	वापस करोमुख्यs[did & 0xff];
पूर्ण

अटल व्योम set_iommu_करोमुख्य(काष्ठा पूर्णांकel_iommu *iommu, u16 did,
			     काष्ठा dmar_करोमुख्य *करोमुख्य)
अणु
	काष्ठा dmar_करोमुख्य **करोमुख्यs;
	पूर्णांक idx = did >> 8;

	अगर (!iommu->करोमुख्यs[idx]) अणु
		माप_प्रकार size = 256 * माप(काष्ठा dmar_करोमुख्य *);
		iommu->करोमुख्यs[idx] = kzalloc(size, GFP_ATOMIC);
	पूर्ण

	करोमुख्यs = iommu->करोमुख्यs[idx];
	अगर (WARN_ON(!करोमुख्यs))
		वापस;
	अन्यथा
		करोमुख्यs[did & 0xff] = करोमुख्य;
पूर्ण

व्योम *alloc_pgtable_page(पूर्णांक node)
अणु
	काष्ठा page *page;
	व्योम *vaddr = शून्य;

	page = alloc_pages_node(node, GFP_ATOMIC | __GFP_ZERO, 0);
	अगर (page)
		vaddr = page_address(page);
	वापस vaddr;
पूर्ण

व्योम मुक्त_pgtable_page(व्योम *vaddr)
अणु
	मुक्त_page((अचिन्हित दीर्घ)vaddr);
पूर्ण

अटल अंतरभूत व्योम *alloc_करोमुख्य_mem(व्योम)
अणु
	वापस kmem_cache_alloc(iommu_करोमुख्य_cache, GFP_ATOMIC);
पूर्ण

अटल व्योम मुक्त_करोमुख्य_mem(व्योम *vaddr)
अणु
	kmem_cache_मुक्त(iommu_करोमुख्य_cache, vaddr);
पूर्ण

अटल अंतरभूत व्योम * alloc_devinfo_mem(व्योम)
अणु
	वापस kmem_cache_alloc(iommu_devinfo_cache, GFP_ATOMIC);
पूर्ण

अटल अंतरभूत व्योम मुक्त_devinfo_mem(व्योम *vaddr)
अणु
	kmem_cache_मुक्त(iommu_devinfo_cache, vaddr);
पूर्ण

अटल अंतरभूत पूर्णांक करोमुख्य_type_is_si(काष्ठा dmar_करोमुख्य *करोमुख्य)
अणु
	वापस करोमुख्य->flags & DOMAIN_FLAG_STATIC_IDENTITY;
पूर्ण

अटल अंतरभूत bool करोमुख्य_use_first_level(काष्ठा dmar_करोमुख्य *करोमुख्य)
अणु
	वापस करोमुख्य->flags & DOMAIN_FLAG_USE_FIRST_LEVEL;
पूर्ण

अटल अंतरभूत पूर्णांक करोमुख्य_pfn_supported(काष्ठा dmar_करोमुख्य *करोमुख्य,
				       अचिन्हित दीर्घ pfn)
अणु
	पूर्णांक addr_width = agaw_to_width(करोमुख्य->agaw) - VTD_PAGE_SHIFT;

	वापस !(addr_width < BITS_PER_LONG && pfn >> addr_width);
पूर्ण

अटल पूर्णांक __iommu_calculate_agaw(काष्ठा पूर्णांकel_iommu *iommu, पूर्णांक max_gaw)
अणु
	अचिन्हित दीर्घ sagaw;
	पूर्णांक agaw = -1;

	sagaw = cap_sagaw(iommu->cap);
	क्रम (agaw = width_to_agaw(max_gaw);
	     agaw >= 0; agaw--) अणु
		अगर (test_bit(agaw, &sagaw))
			अवरोध;
	पूर्ण

	वापस agaw;
पूर्ण

/*
 * Calculate max SAGAW क्रम each iommu.
 */
पूर्णांक iommu_calculate_max_sagaw(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	वापस __iommu_calculate_agaw(iommu, MAX_AGAW_WIDTH);
पूर्ण

/*
 * calculate agaw क्रम each iommu.
 * "SAGAW" may be dअगरferent across iommus, use a शेष agaw, and
 * get a supported less agaw क्रम iommus that करोn't support the शेष agaw.
 */
पूर्णांक iommu_calculate_agaw(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	वापस __iommu_calculate_agaw(iommu, DEFAULT_DOMAIN_ADDRESS_WIDTH);
पूर्ण

/* This functionin only वापसs single iommu in a करोमुख्य */
काष्ठा पूर्णांकel_iommu *करोमुख्य_get_iommu(काष्ठा dmar_करोमुख्य *करोमुख्य)
अणु
	पूर्णांक iommu_id;

	/* si_करोमुख्य and vm करोमुख्य should not get here. */
	अगर (WARN_ON(करोमुख्य->करोमुख्य.type != IOMMU_DOMAIN_DMA))
		वापस शून्य;

	क्रम_each_करोमुख्य_iommu(iommu_id, करोमुख्य)
		अवरोध;

	अगर (iommu_id < 0 || iommu_id >= g_num_of_iommus)
		वापस शून्य;

	वापस g_iommus[iommu_id];
पूर्ण

अटल अंतरभूत bool iommu_paging_काष्ठाure_coherency(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	वापस sm_supported(iommu) ?
			ecap_smpwc(iommu->ecap) : ecap_coherent(iommu->ecap);
पूर्ण

अटल व्योम करोमुख्य_update_iommu_coherency(काष्ठा dmar_करोमुख्य *करोमुख्य)
अणु
	काष्ठा dmar_drhd_unit *drhd;
	काष्ठा पूर्णांकel_iommu *iommu;
	bool found = false;
	पूर्णांक i;

	करोमुख्य->iommu_coherency = 1;

	क्रम_each_करोमुख्य_iommu(i, करोमुख्य) अणु
		found = true;
		अगर (!iommu_paging_काष्ठाure_coherency(g_iommus[i])) अणु
			करोमुख्य->iommu_coherency = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (found)
		वापस;

	/* No hardware attached; use lowest common denominator */
	rcu_पढ़ो_lock();
	क्रम_each_active_iommu(iommu, drhd) अणु
		अगर (!iommu_paging_काष्ठाure_coherency(iommu)) अणु
			करोमुख्य->iommu_coherency = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक करोमुख्य_update_iommu_snooping(काष्ठा पूर्णांकel_iommu *skip)
अणु
	काष्ठा dmar_drhd_unit *drhd;
	काष्ठा पूर्णांकel_iommu *iommu;
	पूर्णांक ret = 1;

	rcu_पढ़ो_lock();
	क्रम_each_active_iommu(iommu, drhd) अणु
		अगर (iommu != skip) अणु
			/*
			 * If the hardware is operating in the scalable mode,
			 * the snooping control is always supported since we
			 * always set PASID-table-entry.PGSNP bit अगर the करोमुख्य
			 * is managed outside (UNMANAGED).
			 */
			अगर (!sm_supported(iommu) &&
			    !ecap_sc_support(iommu->ecap)) अणु
				ret = 0;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल पूर्णांक करोमुख्य_update_iommu_superpage(काष्ठा dmar_करोमुख्य *करोमुख्य,
					 काष्ठा पूर्णांकel_iommu *skip)
अणु
	काष्ठा dmar_drhd_unit *drhd;
	काष्ठा पूर्णांकel_iommu *iommu;
	पूर्णांक mask = 0x3;

	अगर (!पूर्णांकel_iommu_superpage) अणु
		वापस 0;
	पूर्ण

	/* set iommu_superpage to the smallest common denominator */
	rcu_पढ़ो_lock();
	क्रम_each_active_iommu(iommu, drhd) अणु
		अगर (iommu != skip) अणु
			अगर (करोमुख्य && करोमुख्य_use_first_level(करोमुख्य)) अणु
				अगर (!cap_fl1gp_support(iommu->cap))
					mask = 0x1;
			पूर्ण अन्यथा अणु
				mask &= cap_super_page_val(iommu->cap);
			पूर्ण

			अगर (!mask)
				अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस fls(mask);
पूर्ण

अटल पूर्णांक करोमुख्य_update_device_node(काष्ठा dmar_करोमुख्य *करोमुख्य)
अणु
	काष्ठा device_करोमुख्य_info *info;
	पूर्णांक nid = NUMA_NO_NODE;

	निश्चित_spin_locked(&device_करोमुख्य_lock);

	अगर (list_empty(&करोमुख्य->devices))
		वापस NUMA_NO_NODE;

	list_क्रम_each_entry(info, &करोमुख्य->devices, link) अणु
		अगर (!info->dev)
			जारी;

		/*
		 * There could possibly be multiple device numa nodes as devices
		 * within the same करोमुख्य may sit behind dअगरferent IOMMUs. There
		 * isn't perfect answer in such situation, so we select first
		 * come first served policy.
		 */
		nid = dev_to_node(info->dev);
		अगर (nid != NUMA_NO_NODE)
			अवरोध;
	पूर्ण

	वापस nid;
पूर्ण

अटल व्योम करोमुख्य_update_iotlb(काष्ठा dmar_करोमुख्य *करोमुख्य);

/* Some capabilities may be dअगरferent across iommus */
अटल व्योम करोमुख्य_update_iommu_cap(काष्ठा dmar_करोमुख्य *करोमुख्य)
अणु
	करोमुख्य_update_iommu_coherency(करोमुख्य);
	करोमुख्य->iommu_snooping = करोमुख्य_update_iommu_snooping(शून्य);
	करोमुख्य->iommu_superpage = करोमुख्य_update_iommu_superpage(करोमुख्य, शून्य);

	/*
	 * If RHSA is missing, we should शेष to the device numa करोमुख्य
	 * as fall back.
	 */
	अगर (करोमुख्य->nid == NUMA_NO_NODE)
		करोमुख्य->nid = करोमुख्य_update_device_node(करोमुख्य);

	/*
	 * First-level translation restricts the input-address to a
	 * canonical address (i.e., address bits 63:N have the same
	 * value as address bit [N-1], where N is 48-bits with 4-level
	 * paging and 57-bits with 5-level paging). Hence, skip bit
	 * [N-1].
	 */
	अगर (करोमुख्य_use_first_level(करोमुख्य))
		करोमुख्य->करोमुख्य.geometry.aperture_end = __DOMAIN_MAX_ADDR(करोमुख्य->gaw - 1);
	अन्यथा
		करोमुख्य->करोमुख्य.geometry.aperture_end = __DOMAIN_MAX_ADDR(करोमुख्य->gaw);

	करोमुख्य_update_iotlb(करोमुख्य);
पूर्ण

काष्ठा context_entry *iommu_context_addr(काष्ठा पूर्णांकel_iommu *iommu, u8 bus,
					 u8 devfn, पूर्णांक alloc)
अणु
	काष्ठा root_entry *root = &iommu->root_entry[bus];
	काष्ठा context_entry *context;
	u64 *entry;

	entry = &root->lo;
	अगर (sm_supported(iommu)) अणु
		अगर (devfn >= 0x80) अणु
			devfn -= 0x80;
			entry = &root->hi;
		पूर्ण
		devfn *= 2;
	पूर्ण
	अगर (*entry & 1)
		context = phys_to_virt(*entry & VTD_PAGE_MASK);
	अन्यथा अणु
		अचिन्हित दीर्घ phy_addr;
		अगर (!alloc)
			वापस शून्य;

		context = alloc_pgtable_page(iommu->node);
		अगर (!context)
			वापस शून्य;

		__iommu_flush_cache(iommu, (व्योम *)context, CONTEXT_SIZE);
		phy_addr = virt_to_phys((व्योम *)context);
		*entry = phy_addr | 1;
		__iommu_flush_cache(iommu, entry, माप(*entry));
	पूर्ण
	वापस &context[devfn];
पूर्ण

अटल bool attach_deferred(काष्ठा device *dev)
अणु
	वापस dev_iommu_priv_get(dev) == DEFER_DEVICE_DOMAIN_INFO;
पूर्ण

/**
 * is_करोwnstream_to_pci_bridge - test अगर a device beदीर्घs to the PCI
 *				 sub-hierarchy of a candidate PCI-PCI bridge
 * @dev: candidate PCI device beदीर्घing to @bridge PCI sub-hierarchy
 * @bridge: the candidate PCI-PCI bridge
 *
 * Return: true अगर @dev beदीर्घs to @bridge PCI sub-hierarchy, अन्यथा false.
 */
अटल bool
is_करोwnstream_to_pci_bridge(काष्ठा device *dev, काष्ठा device *bridge)
अणु
	काष्ठा pci_dev *pdev, *pbridge;

	अगर (!dev_is_pci(dev) || !dev_is_pci(bridge))
		वापस false;

	pdev = to_pci_dev(dev);
	pbridge = to_pci_dev(bridge);

	अगर (pbridge->subordinate &&
	    pbridge->subordinate->number <= pdev->bus->number &&
	    pbridge->subordinate->busn_res.end >= pdev->bus->number)
		वापस true;

	वापस false;
पूर्ण

अटल bool quirk_ioat_snb_local_iommu(काष्ठा pci_dev *pdev)
अणु
	काष्ठा dmar_drhd_unit *drhd;
	u32 vtbar;
	पूर्णांक rc;

	/* We know that this device on this chipset has its own IOMMU.
	 * If we find it under a dअगरferent IOMMU, then the BIOS is lying
	 * to us. Hope that the IOMMU क्रम this device is actually
	 * disabled, and it needs no translation...
	 */
	rc = pci_bus_पढ़ो_config_dword(pdev->bus, PCI_DEVFN(0, 0), 0xb0, &vtbar);
	अगर (rc) अणु
		/* "can't" happen */
		dev_info(&pdev->dev, "failed to run vt-d quirk\n");
		वापस false;
	पूर्ण
	vtbar &= 0xffff0000;

	/* we know that the this iommu should be at offset 0xa000 from vtbar */
	drhd = dmar_find_matched_drhd_unit(pdev);
	अगर (!drhd || drhd->reg_base_addr - vtbar != 0xa000) अणु
		pr_warn_once(FW_BUG "BIOS assigned incorrect VT-d unit for Intel(R) QuickData Technology device\n");
		add_taपूर्णांक(TAINT_FIRMWARE_WORKAROUND, LOCKDEP_STILL_OK);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool iommu_is_dummy(काष्ठा पूर्णांकel_iommu *iommu, काष्ठा device *dev)
अणु
	अगर (!iommu || iommu->drhd->ignored)
		वापस true;

	अगर (dev_is_pci(dev)) अणु
		काष्ठा pci_dev *pdev = to_pci_dev(dev);

		अगर (pdev->venकरोr == PCI_VENDOR_ID_INTEL &&
		    pdev->device == PCI_DEVICE_ID_INTEL_IOAT_SNB &&
		    quirk_ioat_snb_local_iommu(pdev))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

काष्ठा पूर्णांकel_iommu *device_to_iommu(काष्ठा device *dev, u8 *bus, u8 *devfn)
अणु
	काष्ठा dmar_drhd_unit *drhd = शून्य;
	काष्ठा pci_dev *pdev = शून्य;
	काष्ठा पूर्णांकel_iommu *iommu;
	काष्ठा device *पंचांगp;
	u16 segment = 0;
	पूर्णांक i;

	अगर (!dev)
		वापस शून्य;

	अगर (dev_is_pci(dev)) अणु
		काष्ठा pci_dev *pf_pdev;

		pdev = pci_real_dma_dev(to_pci_dev(dev));

		/* VFs aren't listed in scope tables; we need to look up
		 * the PF instead to find the IOMMU. */
		pf_pdev = pci_physfn(pdev);
		dev = &pf_pdev->dev;
		segment = pci_करोमुख्य_nr(pdev->bus);
	पूर्ण अन्यथा अगर (has_acpi_companion(dev))
		dev = &ACPI_COMPANION(dev)->dev;

	rcu_पढ़ो_lock();
	क्रम_each_iommu(iommu, drhd) अणु
		अगर (pdev && segment != drhd->segment)
			जारी;

		क्रम_each_active_dev_scope(drhd->devices,
					  drhd->devices_cnt, i, पंचांगp) अणु
			अगर (पंचांगp == dev) अणु
				/* For a VF use its original BDF# not that of the PF
				 * which we used क्रम the IOMMU lookup. Strictly speaking
				 * we could करो this क्रम all PCI devices; we only need to
				 * get the BDF# from the scope table क्रम ACPI matches. */
				अगर (pdev && pdev->is_virtfn)
					जाओ got_pdev;

				अगर (bus && devfn) अणु
					*bus = drhd->devices[i].bus;
					*devfn = drhd->devices[i].devfn;
				पूर्ण
				जाओ out;
			पूर्ण

			अगर (is_करोwnstream_to_pci_bridge(dev, पंचांगp))
				जाओ got_pdev;
		पूर्ण

		अगर (pdev && drhd->include_all) अणु
		got_pdev:
			अगर (bus && devfn) अणु
				*bus = pdev->bus->number;
				*devfn = pdev->devfn;
			पूर्ण
			जाओ out;
		पूर्ण
	पूर्ण
	iommu = शून्य;
 out:
	अगर (iommu_is_dummy(iommu, dev))
		iommu = शून्य;

	rcu_पढ़ो_unlock();

	वापस iommu;
पूर्ण

अटल व्योम करोमुख्य_flush_cache(काष्ठा dmar_करोमुख्य *करोमुख्य,
			       व्योम *addr, पूर्णांक size)
अणु
	अगर (!करोमुख्य->iommu_coherency)
		clflush_cache_range(addr, size);
पूर्ण

अटल पूर्णांक device_context_mapped(काष्ठा पूर्णांकel_iommu *iommu, u8 bus, u8 devfn)
अणु
	काष्ठा context_entry *context;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&iommu->lock, flags);
	context = iommu_context_addr(iommu, bus, devfn, 0);
	अगर (context)
		ret = context_present(context);
	spin_unlock_irqrestore(&iommu->lock, flags);
	वापस ret;
पूर्ण

अटल व्योम मुक्त_context_table(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;
	काष्ठा context_entry *context;

	spin_lock_irqsave(&iommu->lock, flags);
	अगर (!iommu->root_entry) अणु
		जाओ out;
	पूर्ण
	क्रम (i = 0; i < ROOT_ENTRY_NR; i++) अणु
		context = iommu_context_addr(iommu, i, 0, 0);
		अगर (context)
			मुक्त_pgtable_page(context);

		अगर (!sm_supported(iommu))
			जारी;

		context = iommu_context_addr(iommu, i, 0x80, 0);
		अगर (context)
			मुक्त_pgtable_page(context);

	पूर्ण
	मुक्त_pgtable_page(iommu->root_entry);
	iommu->root_entry = शून्य;
out:
	spin_unlock_irqrestore(&iommu->lock, flags);
पूर्ण

अटल काष्ठा dma_pte *pfn_to_dma_pte(काष्ठा dmar_करोमुख्य *करोमुख्य,
				      अचिन्हित दीर्घ pfn, पूर्णांक *target_level)
अणु
	काष्ठा dma_pte *parent, *pte;
	पूर्णांक level = agaw_to_level(करोमुख्य->agaw);
	पूर्णांक offset;

	BUG_ON(!करोमुख्य->pgd);

	अगर (!करोमुख्य_pfn_supported(करोमुख्य, pfn))
		/* Address beyond IOMMU's addressing capabilities. */
		वापस शून्य;

	parent = करोमुख्य->pgd;

	जबतक (1) अणु
		व्योम *पंचांगp_page;

		offset = pfn_level_offset(pfn, level);
		pte = &parent[offset];
		अगर (!*target_level && (dma_pte_superpage(pte) || !dma_pte_present(pte)))
			अवरोध;
		अगर (level == *target_level)
			अवरोध;

		अगर (!dma_pte_present(pte)) अणु
			uपूर्णांक64_t pteval;

			पंचांगp_page = alloc_pgtable_page(करोमुख्य->nid);

			अगर (!पंचांगp_page)
				वापस शून्य;

			करोमुख्य_flush_cache(करोमुख्य, पंचांगp_page, VTD_PAGE_SIZE);
			pteval = ((uपूर्णांक64_t)virt_to_dma_pfn(पंचांगp_page) << VTD_PAGE_SHIFT) | DMA_PTE_READ | DMA_PTE_WRITE;
			अगर (करोमुख्य_use_first_level(करोमुख्य)) अणु
				pteval |= DMA_FL_PTE_XD | DMA_FL_PTE_US;
				अगर (करोमुख्य->करोमुख्य.type == IOMMU_DOMAIN_DMA)
					pteval |= DMA_FL_PTE_ACCESS;
			पूर्ण
			अगर (cmpxchg64(&pte->val, 0ULL, pteval))
				/* Someone अन्यथा set it जबतक we were thinking; use theirs. */
				मुक्त_pgtable_page(पंचांगp_page);
			अन्यथा
				करोमुख्य_flush_cache(करोमुख्य, pte, माप(*pte));
		पूर्ण
		अगर (level == 1)
			अवरोध;

		parent = phys_to_virt(dma_pte_addr(pte));
		level--;
	पूर्ण

	अगर (!*target_level)
		*target_level = level;

	वापस pte;
पूर्ण

/* वापस address's pte at specअगरic level */
अटल काष्ठा dma_pte *dma_pfn_level_pte(काष्ठा dmar_करोमुख्य *करोमुख्य,
					 अचिन्हित दीर्घ pfn,
					 पूर्णांक level, पूर्णांक *large_page)
अणु
	काष्ठा dma_pte *parent, *pte;
	पूर्णांक total = agaw_to_level(करोमुख्य->agaw);
	पूर्णांक offset;

	parent = करोमुख्य->pgd;
	जबतक (level <= total) अणु
		offset = pfn_level_offset(pfn, total);
		pte = &parent[offset];
		अगर (level == total)
			वापस pte;

		अगर (!dma_pte_present(pte)) अणु
			*large_page = total;
			अवरोध;
		पूर्ण

		अगर (dma_pte_superpage(pte)) अणु
			*large_page = total;
			वापस pte;
		पूर्ण

		parent = phys_to_virt(dma_pte_addr(pte));
		total--;
	पूर्ण
	वापस शून्य;
पूर्ण

/* clear last level pte, a tlb flush should be followed */
अटल व्योम dma_pte_clear_range(काष्ठा dmar_करोमुख्य *करोमुख्य,
				अचिन्हित दीर्घ start_pfn,
				अचिन्हित दीर्घ last_pfn)
अणु
	अचिन्हित पूर्णांक large_page;
	काष्ठा dma_pte *first_pte, *pte;

	BUG_ON(!करोमुख्य_pfn_supported(करोमुख्य, start_pfn));
	BUG_ON(!करोमुख्य_pfn_supported(करोमुख्य, last_pfn));
	BUG_ON(start_pfn > last_pfn);

	/* we करोn't need lock here; nobody अन्यथा touches the iova range */
	करो अणु
		large_page = 1;
		first_pte = pte = dma_pfn_level_pte(करोमुख्य, start_pfn, 1, &large_page);
		अगर (!pte) अणु
			start_pfn = align_to_level(start_pfn + 1, large_page + 1);
			जारी;
		पूर्ण
		करो अणु
			dma_clear_pte(pte);
			start_pfn += lvl_to_nr_pages(large_page);
			pte++;
		पूर्ण जबतक (start_pfn <= last_pfn && !first_pte_in_page(pte));

		करोमुख्य_flush_cache(करोमुख्य, first_pte,
				   (व्योम *)pte - (व्योम *)first_pte);

	पूर्ण जबतक (start_pfn && start_pfn <= last_pfn);
पूर्ण

अटल व्योम dma_pte_मुक्त_level(काष्ठा dmar_करोमुख्य *करोमुख्य, पूर्णांक level,
			       पूर्णांक retain_level, काष्ठा dma_pte *pte,
			       अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ start_pfn,
			       अचिन्हित दीर्घ last_pfn)
अणु
	pfn = max(start_pfn, pfn);
	pte = &pte[pfn_level_offset(pfn, level)];

	करो अणु
		अचिन्हित दीर्घ level_pfn;
		काष्ठा dma_pte *level_pte;

		अगर (!dma_pte_present(pte) || dma_pte_superpage(pte))
			जाओ next;

		level_pfn = pfn & level_mask(level);
		level_pte = phys_to_virt(dma_pte_addr(pte));

		अगर (level > 2) अणु
			dma_pte_मुक्त_level(करोमुख्य, level - 1, retain_level,
					   level_pte, level_pfn, start_pfn,
					   last_pfn);
		पूर्ण

		/*
		 * Free the page table अगर we're below the level we want to
		 * retain and the range covers the entire table.
		 */
		अगर (level < retain_level && !(start_pfn > level_pfn ||
		      last_pfn < level_pfn + level_size(level) - 1)) अणु
			dma_clear_pte(pte);
			करोमुख्य_flush_cache(करोमुख्य, pte, माप(*pte));
			मुक्त_pgtable_page(level_pte);
		पूर्ण
next:
		pfn += level_size(level);
	पूर्ण जबतक (!first_pte_in_page(++pte) && pfn <= last_pfn);
पूर्ण

/*
 * clear last level (leaf) ptes and मुक्त page table pages below the
 * level we wish to keep पूर्णांकact.
 */
अटल व्योम dma_pte_मुक्त_pagetable(काष्ठा dmar_करोमुख्य *करोमुख्य,
				   अचिन्हित दीर्घ start_pfn,
				   अचिन्हित दीर्घ last_pfn,
				   पूर्णांक retain_level)
अणु
	BUG_ON(!करोमुख्य_pfn_supported(करोमुख्य, start_pfn));
	BUG_ON(!करोमुख्य_pfn_supported(करोमुख्य, last_pfn));
	BUG_ON(start_pfn > last_pfn);

	dma_pte_clear_range(करोमुख्य, start_pfn, last_pfn);

	/* We करोn't need lock here; nobody अन्यथा touches the iova range */
	dma_pte_मुक्त_level(करोमुख्य, agaw_to_level(करोमुख्य->agaw), retain_level,
			   करोमुख्य->pgd, 0, start_pfn, last_pfn);

	/* मुक्त pgd */
	अगर (start_pfn == 0 && last_pfn == DOMAIN_MAX_PFN(करोमुख्य->gaw)) अणु
		मुक्त_pgtable_page(करोमुख्य->pgd);
		करोमुख्य->pgd = शून्य;
	पूर्ण
पूर्ण

/* When a page at a given level is being unlinked from its parent, we करोn't
   need to *modअगरy* it at all. All we need to करो is make a list of all the
   pages which can be मुक्तd just as soon as we've flushed the IOTLB and we
   know the hardware page-walk will no दीर्घer touch them.
   The 'pte' argument is the *parent* PTE, poपूर्णांकing to the page that is to
   be मुक्तd. */
अटल काष्ठा page *dma_pte_list_pagetables(काष्ठा dmar_करोमुख्य *करोमुख्य,
					    पूर्णांक level, काष्ठा dma_pte *pte,
					    काष्ठा page *मुक्तlist)
अणु
	काष्ठा page *pg;

	pg = pfn_to_page(dma_pte_addr(pte) >> PAGE_SHIFT);
	pg->मुक्तlist = मुक्तlist;
	मुक्तlist = pg;

	अगर (level == 1)
		वापस मुक्तlist;

	pte = page_address(pg);
	करो अणु
		अगर (dma_pte_present(pte) && !dma_pte_superpage(pte))
			मुक्तlist = dma_pte_list_pagetables(करोमुख्य, level - 1,
							   pte, मुक्तlist);
		pte++;
	पूर्ण जबतक (!first_pte_in_page(pte));

	वापस मुक्तlist;
पूर्ण

अटल काष्ठा page *dma_pte_clear_level(काष्ठा dmar_करोमुख्य *करोमुख्य, पूर्णांक level,
					काष्ठा dma_pte *pte, अचिन्हित दीर्घ pfn,
					अचिन्हित दीर्घ start_pfn,
					अचिन्हित दीर्घ last_pfn,
					काष्ठा page *मुक्तlist)
अणु
	काष्ठा dma_pte *first_pte = शून्य, *last_pte = शून्य;

	pfn = max(start_pfn, pfn);
	pte = &pte[pfn_level_offset(pfn, level)];

	करो अणु
		अचिन्हित दीर्घ level_pfn;

		अगर (!dma_pte_present(pte))
			जाओ next;

		level_pfn = pfn & level_mask(level);

		/* If range covers entire pagetable, मुक्त it */
		अगर (start_pfn <= level_pfn &&
		    last_pfn >= level_pfn + level_size(level) - 1) अणु
			/* These suborbinate page tables are going away entirely. Don't
			   bother to clear them; we're just going to *मुक्त* them. */
			अगर (level > 1 && !dma_pte_superpage(pte))
				मुक्तlist = dma_pte_list_pagetables(करोमुख्य, level - 1, pte, मुक्तlist);

			dma_clear_pte(pte);
			अगर (!first_pte)
				first_pte = pte;
			last_pte = pte;
		पूर्ण अन्यथा अगर (level > 1) अणु
			/* Recurse करोwn पूर्णांकo a level that isn't *entirely* obsolete */
			मुक्तlist = dma_pte_clear_level(करोमुख्य, level - 1,
						       phys_to_virt(dma_pte_addr(pte)),
						       level_pfn, start_pfn, last_pfn,
						       मुक्तlist);
		पूर्ण
next:
		pfn += level_size(level);
	पूर्ण जबतक (!first_pte_in_page(++pte) && pfn <= last_pfn);

	अगर (first_pte)
		करोमुख्य_flush_cache(करोमुख्य, first_pte,
				   (व्योम *)++last_pte - (व्योम *)first_pte);

	वापस मुक्तlist;
पूर्ण

/* We can't just मुक्त the pages because the IOMMU may still be walking
   the page tables, and may have cached the पूर्णांकermediate levels. The
   pages can only be मुक्तd after the IOTLB flush has been करोne. */
अटल काष्ठा page *करोमुख्य_unmap(काष्ठा dmar_करोमुख्य *करोमुख्य,
				 अचिन्हित दीर्घ start_pfn,
				 अचिन्हित दीर्घ last_pfn,
				 काष्ठा page *मुक्तlist)
अणु
	BUG_ON(!करोमुख्य_pfn_supported(करोमुख्य, start_pfn));
	BUG_ON(!करोमुख्य_pfn_supported(करोमुख्य, last_pfn));
	BUG_ON(start_pfn > last_pfn);

	/* we करोn't need lock here; nobody अन्यथा touches the iova range */
	मुक्तlist = dma_pte_clear_level(करोमुख्य, agaw_to_level(करोमुख्य->agaw),
				       करोमुख्य->pgd, 0, start_pfn, last_pfn,
				       मुक्तlist);

	/* मुक्त pgd */
	अगर (start_pfn == 0 && last_pfn == DOMAIN_MAX_PFN(करोमुख्य->gaw)) अणु
		काष्ठा page *pgd_page = virt_to_page(करोमुख्य->pgd);
		pgd_page->मुक्तlist = मुक्तlist;
		मुक्तlist = pgd_page;

		करोमुख्य->pgd = शून्य;
	पूर्ण

	वापस मुक्तlist;
पूर्ण

अटल व्योम dma_मुक्त_pagelist(काष्ठा page *मुक्तlist)
अणु
	काष्ठा page *pg;

	जबतक ((pg = मुक्तlist)) अणु
		मुक्तlist = pg->मुक्तlist;
		मुक्त_pgtable_page(page_address(pg));
	पूर्ण
पूर्ण

/* iommu handling */
अटल पूर्णांक iommu_alloc_root_entry(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	काष्ठा root_entry *root;
	अचिन्हित दीर्घ flags;

	root = (काष्ठा root_entry *)alloc_pgtable_page(iommu->node);
	अगर (!root) अणु
		pr_err("Allocating root entry for %s failed\n",
			iommu->name);
		वापस -ENOMEM;
	पूर्ण

	__iommu_flush_cache(iommu, root, ROOT_SIZE);

	spin_lock_irqsave(&iommu->lock, flags);
	iommu->root_entry = root;
	spin_unlock_irqrestore(&iommu->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम iommu_set_root_entry(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	u64 addr;
	u32 sts;
	अचिन्हित दीर्घ flag;

	addr = virt_to_phys(iommu->root_entry);
	अगर (sm_supported(iommu))
		addr |= DMA_RTADDR_SMT;

	raw_spin_lock_irqsave(&iommu->रेजिस्टर_lock, flag);
	dmar_ग_लिखोq(iommu->reg + DMAR_RTADDR_REG, addr);

	ग_लिखोl(iommu->gcmd | DMA_GCMD_SRTP, iommu->reg + DMAR_GCMD_REG);

	/* Make sure hardware complete it */
	IOMMU_WAIT_OP(iommu, DMAR_GSTS_REG,
		      पढ़ोl, (sts & DMA_GSTS_RTPS), sts);

	raw_spin_unlock_irqrestore(&iommu->रेजिस्टर_lock, flag);

	iommu->flush.flush_context(iommu, 0, 0, 0, DMA_CCMD_GLOBAL_INVL);
	अगर (sm_supported(iommu))
		qi_flush_pasid_cache(iommu, 0, QI_PC_GLOBAL, 0);
	iommu->flush.flush_iotlb(iommu, 0, 0, 0, DMA_TLB_GLOBAL_FLUSH);
पूर्ण

व्योम iommu_flush_ग_लिखो_buffer(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	u32 val;
	अचिन्हित दीर्घ flag;

	अगर (!rwbf_quirk && !cap_rwbf(iommu->cap))
		वापस;

	raw_spin_lock_irqsave(&iommu->रेजिस्टर_lock, flag);
	ग_लिखोl(iommu->gcmd | DMA_GCMD_WBF, iommu->reg + DMAR_GCMD_REG);

	/* Make sure hardware complete it */
	IOMMU_WAIT_OP(iommu, DMAR_GSTS_REG,
		      पढ़ोl, (!(val & DMA_GSTS_WBFS)), val);

	raw_spin_unlock_irqrestore(&iommu->रेजिस्टर_lock, flag);
पूर्ण

/* वापस value determine अगर we need a ग_लिखो buffer flush */
अटल व्योम __iommu_flush_context(काष्ठा पूर्णांकel_iommu *iommu,
				  u16 did, u16 source_id, u8 function_mask,
				  u64 type)
अणु
	u64 val = 0;
	अचिन्हित दीर्घ flag;

	चयन (type) अणु
	हाल DMA_CCMD_GLOBAL_INVL:
		val = DMA_CCMD_GLOBAL_INVL;
		अवरोध;
	हाल DMA_CCMD_DOMAIN_INVL:
		val = DMA_CCMD_DOMAIN_INVL|DMA_CCMD_DID(did);
		अवरोध;
	हाल DMA_CCMD_DEVICE_INVL:
		val = DMA_CCMD_DEVICE_INVL|DMA_CCMD_DID(did)
			| DMA_CCMD_SID(source_id) | DMA_CCMD_FM(function_mask);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	val |= DMA_CCMD_ICC;

	raw_spin_lock_irqsave(&iommu->रेजिस्टर_lock, flag);
	dmar_ग_लिखोq(iommu->reg + DMAR_CCMD_REG, val);

	/* Make sure hardware complete it */
	IOMMU_WAIT_OP(iommu, DMAR_CCMD_REG,
		dmar_पढ़ोq, (!(val & DMA_CCMD_ICC)), val);

	raw_spin_unlock_irqrestore(&iommu->रेजिस्टर_lock, flag);
पूर्ण

/* वापस value determine अगर we need a ग_लिखो buffer flush */
अटल व्योम __iommu_flush_iotlb(काष्ठा पूर्णांकel_iommu *iommu, u16 did,
				u64 addr, अचिन्हित पूर्णांक size_order, u64 type)
अणु
	पूर्णांक tlb_offset = ecap_iotlb_offset(iommu->ecap);
	u64 val = 0, val_iva = 0;
	अचिन्हित दीर्घ flag;

	चयन (type) अणु
	हाल DMA_TLB_GLOBAL_FLUSH:
		/* global flush करोesn't need set IVA_REG */
		val = DMA_TLB_GLOBAL_FLUSH|DMA_TLB_IVT;
		अवरोध;
	हाल DMA_TLB_DSI_FLUSH:
		val = DMA_TLB_DSI_FLUSH|DMA_TLB_IVT|DMA_TLB_DID(did);
		अवरोध;
	हाल DMA_TLB_PSI_FLUSH:
		val = DMA_TLB_PSI_FLUSH|DMA_TLB_IVT|DMA_TLB_DID(did);
		/* IH bit is passed in as part of address */
		val_iva = size_order | addr;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	/* Note: set drain पढ़ो/ग_लिखो */
#अगर 0
	/*
	 * This is probably to be super secure.. Looks like we can
	 * ignore it without any impact.
	 */
	अगर (cap_पढ़ो_drain(iommu->cap))
		val |= DMA_TLB_READ_DRAIN;
#पूर्ण_अगर
	अगर (cap_ग_लिखो_drain(iommu->cap))
		val |= DMA_TLB_WRITE_DRAIN;

	raw_spin_lock_irqsave(&iommu->रेजिस्टर_lock, flag);
	/* Note: Only uses first TLB reg currently */
	अगर (val_iva)
		dmar_ग_लिखोq(iommu->reg + tlb_offset, val_iva);
	dmar_ग_लिखोq(iommu->reg + tlb_offset + 8, val);

	/* Make sure hardware complete it */
	IOMMU_WAIT_OP(iommu, tlb_offset + 8,
		dmar_पढ़ोq, (!(val & DMA_TLB_IVT)), val);

	raw_spin_unlock_irqrestore(&iommu->रेजिस्टर_lock, flag);

	/* check IOTLB invalidation granularity */
	अगर (DMA_TLB_IAIG(val) == 0)
		pr_err("Flush IOTLB failed\n");
	अगर (DMA_TLB_IAIG(val) != DMA_TLB_IIRG(type))
		pr_debug("TLB flush request %Lx, actual %Lx\n",
			(अचिन्हित दीर्घ दीर्घ)DMA_TLB_IIRG(type),
			(अचिन्हित दीर्घ दीर्घ)DMA_TLB_IAIG(val));
पूर्ण

अटल काष्ठा device_करोमुख्य_info *
iommu_support_dev_iotlb (काष्ठा dmar_करोमुख्य *करोमुख्य, काष्ठा पूर्णांकel_iommu *iommu,
			 u8 bus, u8 devfn)
अणु
	काष्ठा device_करोमुख्य_info *info;

	निश्चित_spin_locked(&device_करोमुख्य_lock);

	अगर (!iommu->qi)
		वापस शून्य;

	list_क्रम_each_entry(info, &करोमुख्य->devices, link)
		अगर (info->iommu == iommu && info->bus == bus &&
		    info->devfn == devfn) अणु
			अगर (info->ats_supported && info->dev)
				वापस info;
			अवरोध;
		पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम करोमुख्य_update_iotlb(काष्ठा dmar_करोमुख्य *करोमुख्य)
अणु
	काष्ठा device_करोमुख्य_info *info;
	bool has_iotlb_device = false;

	निश्चित_spin_locked(&device_करोमुख्य_lock);

	list_क्रम_each_entry(info, &करोमुख्य->devices, link)
		अगर (info->ats_enabled) अणु
			has_iotlb_device = true;
			अवरोध;
		पूर्ण

	अगर (!has_iotlb_device) अणु
		काष्ठा subdev_करोमुख्य_info *sinfo;

		list_क्रम_each_entry(sinfo, &करोमुख्य->subdevices, link_करोमुख्य) अणु
			info = get_करोमुख्य_info(sinfo->pdev);
			अगर (info && info->ats_enabled) अणु
				has_iotlb_device = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	करोमुख्य->has_iotlb_device = has_iotlb_device;
पूर्ण

अटल व्योम iommu_enable_dev_iotlb(काष्ठा device_करोमुख्य_info *info)
अणु
	काष्ठा pci_dev *pdev;

	निश्चित_spin_locked(&device_करोमुख्य_lock);

	अगर (!info || !dev_is_pci(info->dev))
		वापस;

	pdev = to_pci_dev(info->dev);
	/* For IOMMU that supports device IOTLB throttling (DIT), we assign
	 * PFSID to the invalidation desc of a VF such that IOMMU HW can gauge
	 * queue depth at PF level. If DIT is not set, PFSID will be treated as
	 * reserved, which should be set to 0.
	 */
	अगर (!ecap_dit(info->iommu->ecap))
		info->pfsid = 0;
	अन्यथा अणु
		काष्ठा pci_dev *pf_pdev;

		/* pdev will be वापसed अगर device is not a vf */
		pf_pdev = pci_physfn(pdev);
		info->pfsid = pci_dev_id(pf_pdev);
	पूर्ण

#अगर_घोषित CONFIG_INTEL_IOMMU_SVM
	/* The PCIe spec, in its wisकरोm, declares that the behaviour of
	   the device अगर you enable PASID support after ATS support is
	   undefined. So always enable PASID support on devices which
	   have it, even अगर we can't yet know if we're ever going to
	   use it. */
	अगर (info->pasid_supported && !pci_enable_pasid(pdev, info->pasid_supported & ~1))
		info->pasid_enabled = 1;

	अगर (info->pri_supported &&
	    (info->pasid_enabled ? pci_prg_resp_pasid_required(pdev) : 1)  &&
	    !pci_reset_pri(pdev) && !pci_enable_pri(pdev, 32))
		info->pri_enabled = 1;
#पूर्ण_अगर
	अगर (info->ats_supported && pci_ats_page_aligned(pdev) &&
	    !pci_enable_ats(pdev, VTD_PAGE_SHIFT)) अणु
		info->ats_enabled = 1;
		करोमुख्य_update_iotlb(info->करोमुख्य);
		info->ats_qdep = pci_ats_queue_depth(pdev);
	पूर्ण
पूर्ण

अटल व्योम iommu_disable_dev_iotlb(काष्ठा device_करोमुख्य_info *info)
अणु
	काष्ठा pci_dev *pdev;

	निश्चित_spin_locked(&device_करोमुख्य_lock);

	अगर (!dev_is_pci(info->dev))
		वापस;

	pdev = to_pci_dev(info->dev);

	अगर (info->ats_enabled) अणु
		pci_disable_ats(pdev);
		info->ats_enabled = 0;
		करोमुख्य_update_iotlb(info->करोमुख्य);
	पूर्ण
#अगर_घोषित CONFIG_INTEL_IOMMU_SVM
	अगर (info->pri_enabled) अणु
		pci_disable_pri(pdev);
		info->pri_enabled = 0;
	पूर्ण
	अगर (info->pasid_enabled) अणु
		pci_disable_pasid(pdev);
		info->pasid_enabled = 0;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम __iommu_flush_dev_iotlb(काष्ठा device_करोमुख्य_info *info,
				    u64 addr, अचिन्हित पूर्णांक mask)
अणु
	u16 sid, qdep;

	अगर (!info || !info->ats_enabled)
		वापस;

	sid = info->bus << 8 | info->devfn;
	qdep = info->ats_qdep;
	qi_flush_dev_iotlb(info->iommu, sid, info->pfsid,
			   qdep, addr, mask);
पूर्ण

अटल व्योम iommu_flush_dev_iotlb(काष्ठा dmar_करोमुख्य *करोमुख्य,
				  u64 addr, अचिन्हित mask)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा device_करोमुख्य_info *info;
	काष्ठा subdev_करोमुख्य_info *sinfo;

	अगर (!करोमुख्य->has_iotlb_device)
		वापस;

	spin_lock_irqsave(&device_करोमुख्य_lock, flags);
	list_क्रम_each_entry(info, &करोमुख्य->devices, link)
		__iommu_flush_dev_iotlb(info, addr, mask);

	list_क्रम_each_entry(sinfo, &करोमुख्य->subdevices, link_करोमुख्य) अणु
		info = get_करोमुख्य_info(sinfo->pdev);
		__iommu_flush_dev_iotlb(info, addr, mask);
	पूर्ण
	spin_unlock_irqrestore(&device_करोमुख्य_lock, flags);
पूर्ण

अटल व्योम करोमुख्य_flush_piotlb(काष्ठा पूर्णांकel_iommu *iommu,
				काष्ठा dmar_करोमुख्य *करोमुख्य,
				u64 addr, अचिन्हित दीर्घ npages, bool ih)
अणु
	u16 did = करोमुख्य->iommu_did[iommu->seq_id];

	अगर (करोमुख्य->शेष_pasid)
		qi_flush_piotlb(iommu, did, करोमुख्य->शेष_pasid,
				addr, npages, ih);

	अगर (!list_empty(&करोमुख्य->devices))
		qi_flush_piotlb(iommu, did, PASID_RID2PASID, addr, npages, ih);
पूर्ण

अटल व्योम iommu_flush_iotlb_psi(काष्ठा पूर्णांकel_iommu *iommu,
				  काष्ठा dmar_करोमुख्य *करोमुख्य,
				  अचिन्हित दीर्घ pfn, अचिन्हित पूर्णांक pages,
				  पूर्णांक ih, पूर्णांक map)
अणु
	अचिन्हित पूर्णांक mask = ilog2(__roundup_घात_of_two(pages));
	uपूर्णांक64_t addr = (uपूर्णांक64_t)pfn << VTD_PAGE_SHIFT;
	u16 did = करोमुख्य->iommu_did[iommu->seq_id];

	BUG_ON(pages == 0);

	अगर (ih)
		ih = 1 << 6;

	अगर (करोमुख्य_use_first_level(करोमुख्य)) अणु
		करोमुख्य_flush_piotlb(iommu, करोमुख्य, addr, pages, ih);
	पूर्ण अन्यथा अणु
		/*
		 * Fallback to करोमुख्य selective flush अगर no PSI support or
		 * the size is too big. PSI requires page size to be 2 ^ x,
		 * and the base address is naturally aligned to the size.
		 */
		अगर (!cap_pgsel_inv(iommu->cap) ||
		    mask > cap_max_amask_val(iommu->cap))
			iommu->flush.flush_iotlb(iommu, did, 0, 0,
							DMA_TLB_DSI_FLUSH);
		अन्यथा
			iommu->flush.flush_iotlb(iommu, did, addr | ih, mask,
							DMA_TLB_PSI_FLUSH);
	पूर्ण

	/*
	 * In caching mode, changes of pages from non-present to present require
	 * flush. However, device IOTLB करोesn't need to be flushed in this हाल.
	 */
	अगर (!cap_caching_mode(iommu->cap) || !map)
		iommu_flush_dev_iotlb(करोमुख्य, addr, mask);
पूर्ण

/* Notअगरication क्रम newly created mappings */
अटल अंतरभूत व्योम __mapping_notअगरy_one(काष्ठा पूर्णांकel_iommu *iommu,
					काष्ठा dmar_करोमुख्य *करोमुख्य,
					अचिन्हित दीर्घ pfn, अचिन्हित पूर्णांक pages)
अणु
	/*
	 * It's a non-present to present mapping. Only flush अगर caching mode
	 * and second level.
	 */
	अगर (cap_caching_mode(iommu->cap) && !करोमुख्य_use_first_level(करोमुख्य))
		iommu_flush_iotlb_psi(iommu, करोमुख्य, pfn, pages, 0, 1);
	अन्यथा
		iommu_flush_ग_लिखो_buffer(iommu);
पूर्ण

अटल व्योम पूर्णांकel_flush_iotlb_all(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा dmar_करोमुख्य *dmar_करोमुख्य = to_dmar_करोमुख्य(करोमुख्य);
	पूर्णांक idx;

	क्रम_each_करोमुख्य_iommu(idx, dmar_करोमुख्य) अणु
		काष्ठा पूर्णांकel_iommu *iommu = g_iommus[idx];
		u16 did = dmar_करोमुख्य->iommu_did[iommu->seq_id];

		अगर (करोमुख्य_use_first_level(dmar_करोमुख्य))
			करोमुख्य_flush_piotlb(iommu, dmar_करोमुख्य, 0, -1, 0);
		अन्यथा
			iommu->flush.flush_iotlb(iommu, did, 0, 0,
						 DMA_TLB_DSI_FLUSH);

		अगर (!cap_caching_mode(iommu->cap))
			iommu_flush_dev_iotlb(get_iommu_करोमुख्य(iommu, did),
					      0, MAX_AGAW_PFN_WIDTH);
	पूर्ण
पूर्ण

अटल व्योम iommu_disable_protect_mem_regions(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	u32 pmen;
	अचिन्हित दीर्घ flags;

	अगर (!cap_plmr(iommu->cap) && !cap_phmr(iommu->cap))
		वापस;

	raw_spin_lock_irqsave(&iommu->रेजिस्टर_lock, flags);
	pmen = पढ़ोl(iommu->reg + DMAR_PMEN_REG);
	pmen &= ~DMA_PMEN_EPM;
	ग_लिखोl(pmen, iommu->reg + DMAR_PMEN_REG);

	/* रुको क्रम the रक्षित region status bit to clear */
	IOMMU_WAIT_OP(iommu, DMAR_PMEN_REG,
		पढ़ोl, !(pmen & DMA_PMEN_PRS), pmen);

	raw_spin_unlock_irqrestore(&iommu->रेजिस्टर_lock, flags);
पूर्ण

अटल व्योम iommu_enable_translation(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	u32 sts;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&iommu->रेजिस्टर_lock, flags);
	iommu->gcmd |= DMA_GCMD_TE;
	ग_लिखोl(iommu->gcmd, iommu->reg + DMAR_GCMD_REG);

	/* Make sure hardware complete it */
	IOMMU_WAIT_OP(iommu, DMAR_GSTS_REG,
		      पढ़ोl, (sts & DMA_GSTS_TES), sts);

	raw_spin_unlock_irqrestore(&iommu->रेजिस्टर_lock, flags);
पूर्ण

अटल व्योम iommu_disable_translation(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	u32 sts;
	अचिन्हित दीर्घ flag;

	अगर (iommu_skip_te_disable && iommu->drhd->gfx_dedicated &&
	    (cap_पढ़ो_drain(iommu->cap) || cap_ग_लिखो_drain(iommu->cap)))
		वापस;

	raw_spin_lock_irqsave(&iommu->रेजिस्टर_lock, flag);
	iommu->gcmd &= ~DMA_GCMD_TE;
	ग_लिखोl(iommu->gcmd, iommu->reg + DMAR_GCMD_REG);

	/* Make sure hardware complete it */
	IOMMU_WAIT_OP(iommu, DMAR_GSTS_REG,
		      पढ़ोl, (!(sts & DMA_GSTS_TES)), sts);

	raw_spin_unlock_irqrestore(&iommu->रेजिस्टर_lock, flag);
पूर्ण

अटल पूर्णांक iommu_init_करोमुख्यs(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	u32 nकरोमुख्यs, nदीर्घs;
	माप_प्रकार size;

	nकरोमुख्यs = cap_nकरोms(iommu->cap);
	pr_debug("%s: Number of Domains supported <%d>\n",
		 iommu->name, nकरोमुख्यs);
	nदीर्घs = BITS_TO_LONGS(nकरोमुख्यs);

	spin_lock_init(&iommu->lock);

	iommu->करोमुख्य_ids = kसुस्मृति(nदीर्घs, माप(अचिन्हित दीर्घ), GFP_KERNEL);
	अगर (!iommu->करोमुख्य_ids) अणु
		pr_err("%s: Allocating domain id array failed\n",
		       iommu->name);
		वापस -ENOMEM;
	पूर्ण

	size = (ALIGN(nकरोमुख्यs, 256) >> 8) * माप(काष्ठा dmar_करोमुख्य **);
	iommu->करोमुख्यs = kzalloc(size, GFP_KERNEL);

	अगर (iommu->करोमुख्यs) अणु
		size = 256 * माप(काष्ठा dmar_करोमुख्य *);
		iommu->करोमुख्यs[0] = kzalloc(size, GFP_KERNEL);
	पूर्ण

	अगर (!iommu->करोमुख्यs || !iommu->करोमुख्यs[0]) अणु
		pr_err("%s: Allocating domain array failed\n",
		       iommu->name);
		kमुक्त(iommu->करोमुख्य_ids);
		kमुक्त(iommu->करोमुख्यs);
		iommu->करोमुख्य_ids = शून्य;
		iommu->करोमुख्यs    = शून्य;
		वापस -ENOMEM;
	पूर्ण

	/*
	 * If Caching mode is set, then invalid translations are tagged
	 * with करोमुख्य-id 0, hence we need to pre-allocate it. We also
	 * use करोमुख्य-id 0 as a marker क्रम non-allocated करोमुख्य-id, so
	 * make sure it is not used क्रम a real करोमुख्य.
	 */
	set_bit(0, iommu->करोमुख्य_ids);

	/*
	 * Vt-d spec rev3.0 (section 6.2.3.1) requires that each pasid
	 * entry क्रम first-level or pass-through translation modes should
	 * be programmed with a करोमुख्य id dअगरferent from those used क्रम
	 * second-level or nested translation. We reserve a करोमुख्य id क्रम
	 * this purpose.
	 */
	अगर (sm_supported(iommu))
		set_bit(FLPT_DEFAULT_DID, iommu->करोमुख्य_ids);

	वापस 0;
पूर्ण

अटल व्योम disable_dmar_iommu(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	काष्ठा device_करोमुख्य_info *info, *पंचांगp;
	अचिन्हित दीर्घ flags;

	अगर (!iommu->करोमुख्यs || !iommu->करोमुख्य_ids)
		वापस;

	spin_lock_irqsave(&device_करोमुख्य_lock, flags);
	list_क्रम_each_entry_safe(info, पंचांगp, &device_करोमुख्य_list, global) अणु
		अगर (info->iommu != iommu)
			जारी;

		अगर (!info->dev || !info->करोमुख्य)
			जारी;

		__dmar_हटाओ_one_dev_info(info);
	पूर्ण
	spin_unlock_irqrestore(&device_करोमुख्य_lock, flags);

	अगर (iommu->gcmd & DMA_GCMD_TE)
		iommu_disable_translation(iommu);
पूर्ण

अटल व्योम मुक्त_dmar_iommu(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	अगर ((iommu->करोमुख्यs) && (iommu->करोमुख्य_ids)) अणु
		पूर्णांक elems = ALIGN(cap_nकरोms(iommu->cap), 256) >> 8;
		पूर्णांक i;

		क्रम (i = 0; i < elems; i++)
			kमुक्त(iommu->करोमुख्यs[i]);
		kमुक्त(iommu->करोमुख्यs);
		kमुक्त(iommu->करोमुख्य_ids);
		iommu->करोमुख्यs = शून्य;
		iommu->करोमुख्य_ids = शून्य;
	पूर्ण

	g_iommus[iommu->seq_id] = शून्य;

	/* मुक्त context mapping */
	मुक्त_context_table(iommu);

#अगर_घोषित CONFIG_INTEL_IOMMU_SVM
	अगर (pasid_supported(iommu)) अणु
		अगर (ecap_prs(iommu->ecap))
			पूर्णांकel_svm_finish_prq(iommu);
	पूर्ण
	अगर (vccap_pasid(iommu->vccap))
		ioasid_unरेजिस्टर_allocator(&iommu->pasid_allocator);

#पूर्ण_अगर
पूर्ण

/*
 * Check and वापस whether first level is used by शेष क्रम
 * DMA translation.
 */
अटल bool first_level_by_शेष(व्योम)
अणु
	वापस scalable_mode_support() && पूर्णांकel_cap_flts_sanity();
पूर्ण

अटल काष्ठा dmar_करोमुख्य *alloc_करोमुख्य(पूर्णांक flags)
अणु
	काष्ठा dmar_करोमुख्य *करोमुख्य;

	करोमुख्य = alloc_करोमुख्य_mem();
	अगर (!करोमुख्य)
		वापस शून्य;

	स_रखो(करोमुख्य, 0, माप(*करोमुख्य));
	करोमुख्य->nid = NUMA_NO_NODE;
	करोमुख्य->flags = flags;
	अगर (first_level_by_शेष())
		करोमुख्य->flags |= DOMAIN_FLAG_USE_FIRST_LEVEL;
	करोमुख्य->has_iotlb_device = false;
	INIT_LIST_HEAD(&करोमुख्य->devices);
	INIT_LIST_HEAD(&करोमुख्य->subdevices);

	वापस करोमुख्य;
पूर्ण

/* Must be called with iommu->lock */
अटल पूर्णांक करोमुख्य_attach_iommu(काष्ठा dmar_करोमुख्य *करोमुख्य,
			       काष्ठा पूर्णांकel_iommu *iommu)
अणु
	अचिन्हित दीर्घ nकरोमुख्यs;
	पूर्णांक num;

	निश्चित_spin_locked(&device_करोमुख्य_lock);
	निश्चित_spin_locked(&iommu->lock);

	करोमुख्य->iommu_refcnt[iommu->seq_id] += 1;
	करोमुख्य->iommu_count += 1;
	अगर (करोमुख्य->iommu_refcnt[iommu->seq_id] == 1) अणु
		nकरोमुख्यs = cap_nकरोms(iommu->cap);
		num      = find_first_zero_bit(iommu->करोमुख्य_ids, nकरोमुख्यs);

		अगर (num >= nकरोमुख्यs) अणु
			pr_err("%s: No free domain ids\n", iommu->name);
			करोमुख्य->iommu_refcnt[iommu->seq_id] -= 1;
			करोमुख्य->iommu_count -= 1;
			वापस -ENOSPC;
		पूर्ण

		set_bit(num, iommu->करोमुख्य_ids);
		set_iommu_करोमुख्य(iommu, num, करोमुख्य);

		करोमुख्य->iommu_did[iommu->seq_id] = num;
		करोमुख्य->nid			 = iommu->node;

		करोमुख्य_update_iommu_cap(करोमुख्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक करोमुख्य_detach_iommu(काष्ठा dmar_करोमुख्य *करोमुख्य,
			       काष्ठा पूर्णांकel_iommu *iommu)
अणु
	पूर्णांक num, count;

	निश्चित_spin_locked(&device_करोमुख्य_lock);
	निश्चित_spin_locked(&iommu->lock);

	करोमुख्य->iommu_refcnt[iommu->seq_id] -= 1;
	count = --करोमुख्य->iommu_count;
	अगर (करोमुख्य->iommu_refcnt[iommu->seq_id] == 0) अणु
		num = करोमुख्य->iommu_did[iommu->seq_id];
		clear_bit(num, iommu->करोमुख्य_ids);
		set_iommu_करोमुख्य(iommu, num, शून्य);

		करोमुख्य_update_iommu_cap(करोमुख्य);
		करोमुख्य->iommu_did[iommu->seq_id] = 0;
	पूर्ण

	वापस count;
पूर्ण

अटल अंतरभूत पूर्णांक guestwidth_to_adjustwidth(पूर्णांक gaw)
अणु
	पूर्णांक agaw;
	पूर्णांक r = (gaw - 12) % 9;

	अगर (r == 0)
		agaw = gaw;
	अन्यथा
		agaw = gaw + 9 - r;
	अगर (agaw > 64)
		agaw = 64;
	वापस agaw;
पूर्ण

अटल व्योम करोमुख्य_निकास(काष्ठा dmar_करोमुख्य *करोमुख्य)
अणु

	/* Remove associated devices and clear attached or cached करोमुख्यs */
	करोमुख्य_हटाओ_dev_info(करोमुख्य);

	/* destroy iovas */
	अगर (करोमुख्य->करोमुख्य.type == IOMMU_DOMAIN_DMA)
		iommu_put_dma_cookie(&करोमुख्य->करोमुख्य);

	अगर (करोमुख्य->pgd) अणु
		काष्ठा page *मुक्तlist;

		मुक्तlist = करोमुख्य_unmap(करोमुख्य, 0,
					DOMAIN_MAX_PFN(करोमुख्य->gaw), शून्य);
		dma_मुक्त_pagelist(मुक्तlist);
	पूर्ण

	मुक्त_करोमुख्य_mem(करोमुख्य);
पूर्ण

/*
 * Get the PASID directory size क्रम scalable mode context entry.
 * Value of X in the PDTS field of a scalable mode context entry
 * indicates PASID directory with 2^(X + 7) entries.
 */
अटल अंतरभूत अचिन्हित दीर्घ context_get_sm_pds(काष्ठा pasid_table *table)
अणु
	पूर्णांक pds, max_pde;

	max_pde = table->max_pasid >> PASID_PDE_SHIFT;
	pds = find_first_bit((अचिन्हित दीर्घ *)&max_pde, MAX_NR_PASID_BITS);
	अगर (pds < 7)
		वापस 0;

	वापस pds - 7;
पूर्ण

/*
 * Set the RID_PASID field of a scalable mode context entry. The
 * IOMMU hardware will use the PASID value set in this field क्रम
 * DMA translations of DMA requests without PASID.
 */
अटल अंतरभूत व्योम
context_set_sm_rid2pasid(काष्ठा context_entry *context, अचिन्हित दीर्घ pasid)
अणु
	context->hi |= pasid & ((1 << 20) - 1);
पूर्ण

/*
 * Set the DTE(Device-TLB Enable) field of a scalable mode context
 * entry.
 */
अटल अंतरभूत व्योम context_set_sm_dte(काष्ठा context_entry *context)
अणु
	context->lo |= (1 << 2);
पूर्ण

/*
 * Set the PRE(Page Request Enable) field of a scalable mode context
 * entry.
 */
अटल अंतरभूत व्योम context_set_sm_pre(काष्ठा context_entry *context)
अणु
	context->lo |= (1 << 4);
पूर्ण

/* Convert value to context PASID directory size field coding. */
#घोषणा context_pdts(pds)	(((pds) & 0x7) << 9)

अटल पूर्णांक करोमुख्य_context_mapping_one(काष्ठा dmar_करोमुख्य *करोमुख्य,
				      काष्ठा पूर्णांकel_iommu *iommu,
				      काष्ठा pasid_table *table,
				      u8 bus, u8 devfn)
अणु
	u16 did = करोमुख्य->iommu_did[iommu->seq_id];
	पूर्णांक translation = CONTEXT_TT_MULTI_LEVEL;
	काष्ठा device_करोमुख्य_info *info = शून्य;
	काष्ठा context_entry *context;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	WARN_ON(did == 0);

	अगर (hw_pass_through && करोमुख्य_type_is_si(करोमुख्य))
		translation = CONTEXT_TT_PASS_THROUGH;

	pr_debug("Set context mapping for %02x:%02x.%d\n",
		bus, PCI_SLOT(devfn), PCI_FUNC(devfn));

	BUG_ON(!करोमुख्य->pgd);

	spin_lock_irqsave(&device_करोमुख्य_lock, flags);
	spin_lock(&iommu->lock);

	ret = -ENOMEM;
	context = iommu_context_addr(iommu, bus, devfn, 1);
	अगर (!context)
		जाओ out_unlock;

	ret = 0;
	अगर (context_present(context))
		जाओ out_unlock;

	/*
	 * For kdump हालs, old valid entries may be cached due to the
	 * in-flight DMA and copied pgtable, but there is no unmapping
	 * behaviour क्रम them, thus we need an explicit cache flush क्रम
	 * the newly-mapped device. For kdump, at this poपूर्णांक, the device
	 * is supposed to finish reset at its driver probe stage, so no
	 * in-flight DMA will exist, and we करोn't need to worry anymore
	 * hereafter.
	 */
	अगर (context_copied(context)) अणु
		u16 did_old = context_करोमुख्य_id(context);

		अगर (did_old < cap_nकरोms(iommu->cap)) अणु
			iommu->flush.flush_context(iommu, did_old,
						   (((u16)bus) << 8) | devfn,
						   DMA_CCMD_MASK_NOBIT,
						   DMA_CCMD_DEVICE_INVL);
			iommu->flush.flush_iotlb(iommu, did_old, 0, 0,
						 DMA_TLB_DSI_FLUSH);
		पूर्ण
	पूर्ण

	context_clear_entry(context);

	अगर (sm_supported(iommu)) अणु
		अचिन्हित दीर्घ pds;

		WARN_ON(!table);

		/* Setup the PASID सूची poपूर्णांकer: */
		pds = context_get_sm_pds(table);
		context->lo = (u64)virt_to_phys(table->table) |
				context_pdts(pds);

		/* Setup the RID_PASID field: */
		context_set_sm_rid2pasid(context, PASID_RID2PASID);

		/*
		 * Setup the Device-TLB enable bit and Page request
		 * Enable bit:
		 */
		info = iommu_support_dev_iotlb(करोमुख्य, iommu, bus, devfn);
		अगर (info && info->ats_supported)
			context_set_sm_dte(context);
		अगर (info && info->pri_supported)
			context_set_sm_pre(context);
	पूर्ण अन्यथा अणु
		काष्ठा dma_pte *pgd = करोमुख्य->pgd;
		पूर्णांक agaw;

		context_set_करोमुख्य_id(context, did);

		अगर (translation != CONTEXT_TT_PASS_THROUGH) अणु
			/*
			 * Skip top levels of page tables क्रम iommu which has
			 * less agaw than शेष. Unnecessary क्रम PT mode.
			 */
			क्रम (agaw = करोमुख्य->agaw; agaw > iommu->agaw; agaw--) अणु
				ret = -ENOMEM;
				pgd = phys_to_virt(dma_pte_addr(pgd));
				अगर (!dma_pte_present(pgd))
					जाओ out_unlock;
			पूर्ण

			info = iommu_support_dev_iotlb(करोमुख्य, iommu, bus, devfn);
			अगर (info && info->ats_supported)
				translation = CONTEXT_TT_DEV_IOTLB;
			अन्यथा
				translation = CONTEXT_TT_MULTI_LEVEL;

			context_set_address_root(context, virt_to_phys(pgd));
			context_set_address_width(context, agaw);
		पूर्ण अन्यथा अणु
			/*
			 * In pass through mode, AW must be programmed to
			 * indicate the largest AGAW value supported by
			 * hardware. And ASR is ignored by hardware.
			 */
			context_set_address_width(context, iommu->msagaw);
		पूर्ण

		context_set_translation_type(context, translation);
	पूर्ण

	context_set_fault_enable(context);
	context_set_present(context);
	अगर (!ecap_coherent(iommu->ecap))
		clflush_cache_range(context, माप(*context));

	/*
	 * It's a non-present to present mapping. If hardware doesn't cache
	 * non-present entry we only need to flush the ग_लिखो-buffer. If the
	 * _करोes_ cache non-present entries, then it करोes so in the special
	 * करोमुख्य #0, which we have to flush:
	 */
	अगर (cap_caching_mode(iommu->cap)) अणु
		iommu->flush.flush_context(iommu, 0,
					   (((u16)bus) << 8) | devfn,
					   DMA_CCMD_MASK_NOBIT,
					   DMA_CCMD_DEVICE_INVL);
		iommu->flush.flush_iotlb(iommu, did, 0, 0, DMA_TLB_DSI_FLUSH);
	पूर्ण अन्यथा अणु
		iommu_flush_ग_लिखो_buffer(iommu);
	पूर्ण
	iommu_enable_dev_iotlb(info);

	ret = 0;

out_unlock:
	spin_unlock(&iommu->lock);
	spin_unlock_irqrestore(&device_करोमुख्य_lock, flags);

	वापस ret;
पूर्ण

काष्ठा करोमुख्य_context_mapping_data अणु
	काष्ठा dmar_करोमुख्य *करोमुख्य;
	काष्ठा पूर्णांकel_iommu *iommu;
	काष्ठा pasid_table *table;
पूर्ण;

अटल पूर्णांक करोमुख्य_context_mapping_cb(काष्ठा pci_dev *pdev,
				     u16 alias, व्योम *opaque)
अणु
	काष्ठा करोमुख्य_context_mapping_data *data = opaque;

	वापस करोमुख्य_context_mapping_one(data->करोमुख्य, data->iommu,
					  data->table, PCI_BUS_NUM(alias),
					  alias & 0xff);
पूर्ण

अटल पूर्णांक
करोमुख्य_context_mapping(काष्ठा dmar_करोमुख्य *करोमुख्य, काष्ठा device *dev)
अणु
	काष्ठा करोमुख्य_context_mapping_data data;
	काष्ठा pasid_table *table;
	काष्ठा पूर्णांकel_iommu *iommu;
	u8 bus, devfn;

	iommu = device_to_iommu(dev, &bus, &devfn);
	अगर (!iommu)
		वापस -ENODEV;

	table = पूर्णांकel_pasid_get_table(dev);

	अगर (!dev_is_pci(dev))
		वापस करोमुख्य_context_mapping_one(करोमुख्य, iommu, table,
						  bus, devfn);

	data.करोमुख्य = करोमुख्य;
	data.iommu = iommu;
	data.table = table;

	वापस pci_क्रम_each_dma_alias(to_pci_dev(dev),
				      &करोमुख्य_context_mapping_cb, &data);
पूर्ण

अटल पूर्णांक करोमुख्य_context_mapped_cb(काष्ठा pci_dev *pdev,
				    u16 alias, व्योम *opaque)
अणु
	काष्ठा पूर्णांकel_iommu *iommu = opaque;

	वापस !device_context_mapped(iommu, PCI_BUS_NUM(alias), alias & 0xff);
पूर्ण

अटल पूर्णांक करोमुख्य_context_mapped(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_iommu *iommu;
	u8 bus, devfn;

	iommu = device_to_iommu(dev, &bus, &devfn);
	अगर (!iommu)
		वापस -ENODEV;

	अगर (!dev_is_pci(dev))
		वापस device_context_mapped(iommu, bus, devfn);

	वापस !pci_क्रम_each_dma_alias(to_pci_dev(dev),
				       करोमुख्य_context_mapped_cb, iommu);
पूर्ण

/* Returns a number of VTD pages, but aligned to MM page size */
अटल अंतरभूत अचिन्हित दीर्घ aligned_nrpages(अचिन्हित दीर्घ host_addr,
					    माप_प्रकार size)
अणु
	host_addr &= ~PAGE_MASK;
	वापस PAGE_ALIGN(host_addr + size) >> VTD_PAGE_SHIFT;
पूर्ण

/* Return largest possible superpage level क्रम a given mapping */
अटल अंतरभूत पूर्णांक hardware_largepage_caps(काष्ठा dmar_करोमुख्य *करोमुख्य,
					  अचिन्हित दीर्घ iov_pfn,
					  अचिन्हित दीर्घ phy_pfn,
					  अचिन्हित दीर्घ pages)
अणु
	पूर्णांक support, level = 1;
	अचिन्हित दीर्घ pfnmerge;

	support = करोमुख्य->iommu_superpage;

	/* To use a large page, the भव *and* physical addresses
	   must be aligned to 2MiB/1GiB/etc. Lower bits set in either
	   of them will mean we have to use smaller pages. So just
	   merge them and check both at once. */
	pfnmerge = iov_pfn | phy_pfn;

	जबतक (support && !(pfnmerge & ~VTD_STRIDE_MASK)) अणु
		pages >>= VTD_STRIDE_SHIFT;
		अगर (!pages)
			अवरोध;
		pfnmerge >>= VTD_STRIDE_SHIFT;
		level++;
		support--;
	पूर्ण
	वापस level;
पूर्ण

/*
 * Ensure that old small page tables are हटाओd to make room क्रम superpage(s).
 * We're going to add new large pages, so make sure we don't हटाओ their parent
 * tables. The IOTLB/devTLBs should be flushed अगर any PDE/PTEs are cleared.
 */
अटल व्योम चयन_to_super_page(काष्ठा dmar_करोमुख्य *करोमुख्य,
				 अचिन्हित दीर्घ start_pfn,
				 अचिन्हित दीर्घ end_pfn, पूर्णांक level)
अणु
	अचिन्हित दीर्घ lvl_pages = lvl_to_nr_pages(level);
	काष्ठा dma_pte *pte = शून्य;
	पूर्णांक i;

	जबतक (start_pfn <= end_pfn) अणु
		अगर (!pte)
			pte = pfn_to_dma_pte(करोमुख्य, start_pfn, &level);

		अगर (dma_pte_present(pte)) अणु
			dma_pte_मुक्त_pagetable(करोमुख्य, start_pfn,
					       start_pfn + lvl_pages - 1,
					       level + 1);

			क्रम_each_करोमुख्य_iommu(i, करोमुख्य)
				iommu_flush_iotlb_psi(g_iommus[i], करोमुख्य,
						      start_pfn, lvl_pages,
						      0, 0);
		पूर्ण

		pte++;
		start_pfn += lvl_pages;
		अगर (first_pte_in_page(pte))
			pte = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक
__करोमुख्य_mapping(काष्ठा dmar_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iov_pfn,
		 अचिन्हित दीर्घ phys_pfn, अचिन्हित दीर्घ nr_pages, पूर्णांक prot)
अणु
	अचिन्हित पूर्णांक largepage_lvl = 0;
	अचिन्हित दीर्घ lvl_pages = 0;
	काष्ठा dma_pte *pte = शून्य;
	phys_addr_t pteval;
	u64 attr;

	BUG_ON(!करोमुख्य_pfn_supported(करोमुख्य, iov_pfn + nr_pages - 1));

	अगर ((prot & (DMA_PTE_READ|DMA_PTE_WRITE)) == 0)
		वापस -EINVAL;

	attr = prot & (DMA_PTE_READ | DMA_PTE_WRITE | DMA_PTE_SNP);
	attr |= DMA_FL_PTE_PRESENT;
	अगर (करोमुख्य_use_first_level(करोमुख्य)) अणु
		attr |= DMA_FL_PTE_XD | DMA_FL_PTE_US;

		अगर (करोमुख्य->करोमुख्य.type == IOMMU_DOMAIN_DMA) अणु
			attr |= DMA_FL_PTE_ACCESS;
			अगर (prot & DMA_PTE_WRITE)
				attr |= DMA_FL_PTE_सूचीTY;
		पूर्ण
	पूर्ण

	pteval = ((phys_addr_t)phys_pfn << VTD_PAGE_SHIFT) | attr;

	जबतक (nr_pages > 0) अणु
		uपूर्णांक64_t पंचांगp;

		अगर (!pte) अणु
			largepage_lvl = hardware_largepage_caps(करोमुख्य, iov_pfn,
					phys_pfn, nr_pages);

			pte = pfn_to_dma_pte(करोमुख्य, iov_pfn, &largepage_lvl);
			अगर (!pte)
				वापस -ENOMEM;
			/* It is large page*/
			अगर (largepage_lvl > 1) अणु
				अचिन्हित दीर्घ end_pfn;

				pteval |= DMA_PTE_LARGE_PAGE;
				end_pfn = ((iov_pfn + nr_pages) & level_mask(largepage_lvl)) - 1;
				चयन_to_super_page(करोमुख्य, iov_pfn, end_pfn, largepage_lvl);
			पूर्ण अन्यथा अणु
				pteval &= ~(uपूर्णांक64_t)DMA_PTE_LARGE_PAGE;
			पूर्ण

		पूर्ण
		/* We करोn't need lock here, nobody अन्यथा
		 * touches the iova range
		 */
		पंचांगp = cmpxchg64_local(&pte->val, 0ULL, pteval);
		अगर (पंचांगp) अणु
			अटल पूर्णांक dumps = 5;
			pr_crit("ERROR: DMA PTE for vPFN 0x%lx already set (to %llx not %llx)\n",
				iov_pfn, पंचांगp, (अचिन्हित दीर्घ दीर्घ)pteval);
			अगर (dumps) अणु
				dumps--;
				debug_dma_dump_mappings(शून्य);
			पूर्ण
			WARN_ON(1);
		पूर्ण

		lvl_pages = lvl_to_nr_pages(largepage_lvl);

		BUG_ON(nr_pages < lvl_pages);

		nr_pages -= lvl_pages;
		iov_pfn += lvl_pages;
		phys_pfn += lvl_pages;
		pteval += lvl_pages * VTD_PAGE_SIZE;

		/* If the next PTE would be the first in a new page, then we
		 * need to flush the cache on the entries we've just written.
		 * And then we'll need to recalculate 'pte', so clear it and
		 * let it get set again in the अगर (!pte) block above.
		 *
		 * If we're करोne (!nr_pages) we need to flush the cache too.
		 *
		 * Also अगर we've been setting superpages, we may need to
		 * recalculate 'pte' and चयन back to smaller pages क्रम the
		 * end of the mapping, अगर the trailing size is not enough to
		 * use another superpage (i.e. nr_pages < lvl_pages).
		 *
		 * We leave clflush क्रम the leaf pte changes to iotlb_sync_map()
		 * callback.
		 */
		pte++;
		अगर (!nr_pages || first_pte_in_page(pte) ||
		    (largepage_lvl > 1 && nr_pages < lvl_pages))
			pte = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम करोमुख्य_context_clear_one(काष्ठा पूर्णांकel_iommu *iommu, u8 bus, u8 devfn)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा context_entry *context;
	u16 did_old;

	अगर (!iommu)
		वापस;

	spin_lock_irqsave(&iommu->lock, flags);
	context = iommu_context_addr(iommu, bus, devfn, 0);
	अगर (!context) अणु
		spin_unlock_irqrestore(&iommu->lock, flags);
		वापस;
	पूर्ण
	did_old = context_करोमुख्य_id(context);
	context_clear_entry(context);
	__iommu_flush_cache(iommu, context, माप(*context));
	spin_unlock_irqrestore(&iommu->lock, flags);
	iommu->flush.flush_context(iommu,
				   did_old,
				   (((u16)bus) << 8) | devfn,
				   DMA_CCMD_MASK_NOBIT,
				   DMA_CCMD_DEVICE_INVL);

	अगर (sm_supported(iommu))
		qi_flush_pasid_cache(iommu, did_old, QI_PC_ALL_PASIDS, 0);

	iommu->flush.flush_iotlb(iommu,
				 did_old,
				 0,
				 0,
				 DMA_TLB_DSI_FLUSH);
पूर्ण

अटल अंतरभूत व्योम unlink_करोमुख्य_info(काष्ठा device_करोमुख्य_info *info)
अणु
	निश्चित_spin_locked(&device_करोमुख्य_lock);
	list_del(&info->link);
	list_del(&info->global);
	अगर (info->dev)
		dev_iommu_priv_set(info->dev, शून्य);
पूर्ण

अटल व्योम करोमुख्य_हटाओ_dev_info(काष्ठा dmar_करोमुख्य *करोमुख्य)
अणु
	काष्ठा device_करोमुख्य_info *info, *पंचांगp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&device_करोमुख्य_lock, flags);
	list_क्रम_each_entry_safe(info, पंचांगp, &करोमुख्य->devices, link)
		__dmar_हटाओ_one_dev_info(info);
	spin_unlock_irqrestore(&device_करोमुख्य_lock, flags);
पूर्ण

काष्ठा dmar_करोमुख्य *find_करोमुख्य(काष्ठा device *dev)
अणु
	काष्ठा device_करोमुख्य_info *info;

	अगर (unlikely(!dev || !dev->iommu))
		वापस शून्य;

	अगर (unlikely(attach_deferred(dev)))
		वापस शून्य;

	/* No lock here, assumes no करोमुख्य निकास in normal हाल */
	info = get_करोमुख्य_info(dev);
	अगर (likely(info))
		वापस info->करोमुख्य;

	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा device_करोमुख्य_info *
dmar_search_करोमुख्य_by_dev_info(पूर्णांक segment, पूर्णांक bus, पूर्णांक devfn)
अणु
	काष्ठा device_करोमुख्य_info *info;

	list_क्रम_each_entry(info, &device_करोमुख्य_list, global)
		अगर (info->segment == segment && info->bus == bus &&
		    info->devfn == devfn)
			वापस info;

	वापस शून्य;
पूर्ण

अटल पूर्णांक करोमुख्य_setup_first_level(काष्ठा पूर्णांकel_iommu *iommu,
				    काष्ठा dmar_करोमुख्य *करोमुख्य,
				    काष्ठा device *dev,
				    u32 pasid)
अणु
	काष्ठा dma_pte *pgd = करोमुख्य->pgd;
	पूर्णांक agaw, level;
	पूर्णांक flags = 0;

	/*
	 * Skip top levels of page tables क्रम iommu which has
	 * less agaw than शेष. Unnecessary क्रम PT mode.
	 */
	क्रम (agaw = करोमुख्य->agaw; agaw > iommu->agaw; agaw--) अणु
		pgd = phys_to_virt(dma_pte_addr(pgd));
		अगर (!dma_pte_present(pgd))
			वापस -ENOMEM;
	पूर्ण

	level = agaw_to_level(agaw);
	अगर (level != 4 && level != 5)
		वापस -EINVAL;

	अगर (pasid != PASID_RID2PASID)
		flags |= PASID_FLAG_SUPERVISOR_MODE;
	अगर (level == 5)
		flags |= PASID_FLAG_FL5LP;

	अगर (करोमुख्य->करोमुख्य.type == IOMMU_DOMAIN_UNMANAGED)
		flags |= PASID_FLAG_PAGE_SNOOP;

	वापस पूर्णांकel_pasid_setup_first_level(iommu, dev, (pgd_t *)pgd, pasid,
					     करोमुख्य->iommu_did[iommu->seq_id],
					     flags);
पूर्ण

अटल bool dev_is_real_dma_subdevice(काष्ठा device *dev)
अणु
	वापस dev && dev_is_pci(dev) &&
	       pci_real_dma_dev(to_pci_dev(dev)) != to_pci_dev(dev);
पूर्ण

अटल काष्ठा dmar_करोमुख्य *dmar_insert_one_dev_info(काष्ठा पूर्णांकel_iommu *iommu,
						    पूर्णांक bus, पूर्णांक devfn,
						    काष्ठा device *dev,
						    काष्ठा dmar_करोमुख्य *करोमुख्य)
अणु
	काष्ठा dmar_करोमुख्य *found = शून्य;
	काष्ठा device_करोमुख्य_info *info;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	info = alloc_devinfo_mem();
	अगर (!info)
		वापस शून्य;

	अगर (!dev_is_real_dma_subdevice(dev)) अणु
		info->bus = bus;
		info->devfn = devfn;
		info->segment = iommu->segment;
	पूर्ण अन्यथा अणु
		काष्ठा pci_dev *pdev = to_pci_dev(dev);

		info->bus = pdev->bus->number;
		info->devfn = pdev->devfn;
		info->segment = pci_करोमुख्य_nr(pdev->bus);
	पूर्ण

	info->ats_supported = info->pasid_supported = info->pri_supported = 0;
	info->ats_enabled = info->pasid_enabled = info->pri_enabled = 0;
	info->ats_qdep = 0;
	info->dev = dev;
	info->करोमुख्य = करोमुख्य;
	info->iommu = iommu;
	info->pasid_table = शून्य;
	info->auxd_enabled = 0;
	INIT_LIST_HEAD(&info->subdevices);

	अगर (dev && dev_is_pci(dev)) अणु
		काष्ठा pci_dev *pdev = to_pci_dev(info->dev);

		अगर (ecap_dev_iotlb_support(iommu->ecap) &&
		    pci_ats_supported(pdev) &&
		    dmar_find_matched_atsr_unit(pdev))
			info->ats_supported = 1;

		अगर (sm_supported(iommu)) अणु
			अगर (pasid_supported(iommu)) अणु
				पूर्णांक features = pci_pasid_features(pdev);
				अगर (features >= 0)
					info->pasid_supported = features | 1;
			पूर्ण

			अगर (info->ats_supported && ecap_prs(iommu->ecap) &&
			    pci_pri_supported(pdev))
				info->pri_supported = 1;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&device_करोमुख्य_lock, flags);
	अगर (dev)
		found = find_करोमुख्य(dev);

	अगर (!found) अणु
		काष्ठा device_करोमुख्य_info *info2;
		info2 = dmar_search_करोमुख्य_by_dev_info(info->segment, info->bus,
						       info->devfn);
		अगर (info2) अणु
			found      = info2->करोमुख्य;
			info2->dev = dev;
		पूर्ण
	पूर्ण

	अगर (found) अणु
		spin_unlock_irqrestore(&device_करोमुख्य_lock, flags);
		मुक्त_devinfo_mem(info);
		/* Caller must मुक्त the original करोमुख्य */
		वापस found;
	पूर्ण

	spin_lock(&iommu->lock);
	ret = करोमुख्य_attach_iommu(करोमुख्य, iommu);
	spin_unlock(&iommu->lock);

	अगर (ret) अणु
		spin_unlock_irqrestore(&device_करोमुख्य_lock, flags);
		मुक्त_devinfo_mem(info);
		वापस शून्य;
	पूर्ण

	list_add(&info->link, &करोमुख्य->devices);
	list_add(&info->global, &device_करोमुख्य_list);
	अगर (dev)
		dev_iommu_priv_set(dev, info);
	spin_unlock_irqrestore(&device_करोमुख्य_lock, flags);

	/* PASID table is mandatory क्रम a PCI device in scalable mode. */
	अगर (dev && dev_is_pci(dev) && sm_supported(iommu)) अणु
		ret = पूर्णांकel_pasid_alloc_table(dev);
		अगर (ret) अणु
			dev_err(dev, "PASID table allocation failed\n");
			dmar_हटाओ_one_dev_info(dev);
			वापस शून्य;
		पूर्ण

		/* Setup the PASID entry क्रम requests without PASID: */
		spin_lock_irqsave(&iommu->lock, flags);
		अगर (hw_pass_through && करोमुख्य_type_is_si(करोमुख्य))
			ret = पूर्णांकel_pasid_setup_pass_through(iommu, करोमुख्य,
					dev, PASID_RID2PASID);
		अन्यथा अगर (करोमुख्य_use_first_level(करोमुख्य))
			ret = करोमुख्य_setup_first_level(iommu, करोमुख्य, dev,
					PASID_RID2PASID);
		अन्यथा
			ret = पूर्णांकel_pasid_setup_second_level(iommu, करोमुख्य,
					dev, PASID_RID2PASID);
		spin_unlock_irqrestore(&iommu->lock, flags);
		अगर (ret) अणु
			dev_err(dev, "Setup RID2PASID failed\n");
			dmar_हटाओ_one_dev_info(dev);
			वापस शून्य;
		पूर्ण
	पूर्ण

	अगर (dev && करोमुख्य_context_mapping(करोमुख्य, dev)) अणु
		dev_err(dev, "Domain context map failed\n");
		dmar_हटाओ_one_dev_info(dev);
		वापस शून्य;
	पूर्ण

	वापस करोमुख्य;
पूर्ण

अटल पूर्णांक iommu_करोमुख्य_identity_map(काष्ठा dmar_करोमुख्य *करोमुख्य,
				     अचिन्हित दीर्घ first_vpfn,
				     अचिन्हित दीर्घ last_vpfn)
अणु
	/*
	 * RMRR range might have overlap with physical memory range,
	 * clear it first
	 */
	dma_pte_clear_range(करोमुख्य, first_vpfn, last_vpfn);

	वापस __करोमुख्य_mapping(करोमुख्य, first_vpfn,
				first_vpfn, last_vpfn - first_vpfn + 1,
				DMA_PTE_READ|DMA_PTE_WRITE);
पूर्ण

अटल पूर्णांक md_करोमुख्य_init(काष्ठा dmar_करोमुख्य *करोमुख्य, पूर्णांक guest_width);

अटल पूर्णांक __init si_करोमुख्य_init(पूर्णांक hw)
अणु
	काष्ठा dmar_rmrr_unit *rmrr;
	काष्ठा device *dev;
	पूर्णांक i, nid, ret;

	si_करोमुख्य = alloc_करोमुख्य(DOMAIN_FLAG_STATIC_IDENTITY);
	अगर (!si_करोमुख्य)
		वापस -EFAULT;

	अगर (md_करोमुख्य_init(si_करोमुख्य, DEFAULT_DOMAIN_ADDRESS_WIDTH)) अणु
		करोमुख्य_निकास(si_करोमुख्य);
		वापस -EFAULT;
	पूर्ण

	अगर (hw)
		वापस 0;

	क्रम_each_online_node(nid) अणु
		अचिन्हित दीर्घ start_pfn, end_pfn;
		पूर्णांक i;

		क्रम_each_mem_pfn_range(i, nid, &start_pfn, &end_pfn, शून्य) अणु
			ret = iommu_करोमुख्य_identity_map(si_करोमुख्य,
					mm_to_dma_pfn(start_pfn),
					mm_to_dma_pfn(end_pfn));
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * Identity map the RMRRs so that devices with RMRRs could also use
	 * the si_करोमुख्य.
	 */
	क्रम_each_rmrr_units(rmrr) अणु
		क्रम_each_active_dev_scope(rmrr->devices, rmrr->devices_cnt,
					  i, dev) अणु
			अचिन्हित दीर्घ दीर्घ start = rmrr->base_address;
			अचिन्हित दीर्घ दीर्घ end = rmrr->end_address;

			अगर (WARN_ON(end < start ||
				    end >> agaw_to_width(si_करोमुख्य->agaw)))
				जारी;

			ret = iommu_करोमुख्य_identity_map(si_करोमुख्य,
					mm_to_dma_pfn(start >> PAGE_SHIFT),
					mm_to_dma_pfn(end >> PAGE_SHIFT));
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक करोमुख्य_add_dev_info(काष्ठा dmar_करोमुख्य *करोमुख्य, काष्ठा device *dev)
अणु
	काष्ठा dmar_करोमुख्य *nकरोमुख्य;
	काष्ठा पूर्णांकel_iommu *iommu;
	u8 bus, devfn;

	iommu = device_to_iommu(dev, &bus, &devfn);
	अगर (!iommu)
		वापस -ENODEV;

	nकरोमुख्य = dmar_insert_one_dev_info(iommu, bus, devfn, dev, करोमुख्य);
	अगर (nकरोमुख्य != करोमुख्य)
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल bool device_has_rmrr(काष्ठा device *dev)
अणु
	काष्ठा dmar_rmrr_unit *rmrr;
	काष्ठा device *पंचांगp;
	पूर्णांक i;

	rcu_पढ़ो_lock();
	क्रम_each_rmrr_units(rmrr) अणु
		/*
		 * Return TRUE अगर this RMRR contains the device that
		 * is passed in.
		 */
		क्रम_each_active_dev_scope(rmrr->devices,
					  rmrr->devices_cnt, i, पंचांगp)
			अगर (पंचांगp == dev ||
			    is_करोwnstream_to_pci_bridge(dev, पंचांगp)) अणु
				rcu_पढ़ो_unlock();
				वापस true;
			पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस false;
पूर्ण

/**
 * device_rmrr_is_relaxable - Test whether the RMRR of this device
 * is relaxable (ie. is allowed to be not enक्रमced under some conditions)
 * @dev: device handle
 *
 * We assume that PCI USB devices with RMRRs have them largely
 * क्रम historical reasons and that the RMRR space is not actively used post
 * boot.  This exclusion may change अगर venकरोrs begin to abuse it.
 *
 * The same exception is made क्रम graphics devices, with the requirement that
 * any use of the RMRR regions will be torn करोwn beक्रमe assigning the device
 * to a guest.
 *
 * Return: true अगर the RMRR is relaxable, false otherwise
 */
अटल bool device_rmrr_is_relaxable(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev;

	अगर (!dev_is_pci(dev))
		वापस false;

	pdev = to_pci_dev(dev);
	अगर (IS_USB_DEVICE(pdev) || IS_GFX_DEVICE(pdev))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

/*
 * There are a couple हालs where we need to restrict the functionality of
 * devices associated with RMRRs.  The first is when evaluating a device क्रम
 * identity mapping because problems exist when devices are moved in and out
 * of करोमुख्यs and their respective RMRR inक्रमmation is lost.  This means that
 * a device with associated RMRRs will never be in a "passthrough" करोमुख्य.
 * The second is use of the device through the IOMMU API.  This पूर्णांकerface
 * expects to have full control of the IOVA space क्रम the device.  We cannot
 * satisfy both the requirement that RMRR access is मुख्यtained and have an
 * unencumbered IOVA space.  We also have no ability to quiesce the device's
 * use of the RMRR space or even inक्रमm the IOMMU API user of the restriction.
 * We thereक्रमe prevent devices associated with an RMRR from participating in
 * the IOMMU API, which eliminates them from device assignment.
 *
 * In both हालs, devices which have relaxable RMRRs are not concerned by this
 * restriction. See device_rmrr_is_relaxable comment.
 */
अटल bool device_is_rmrr_locked(काष्ठा device *dev)
अणु
	अगर (!device_has_rmrr(dev))
		वापस false;

	अगर (device_rmrr_is_relaxable(dev))
		वापस false;

	वापस true;
पूर्ण

/*
 * Return the required शेष करोमुख्य type क्रम a specअगरic device.
 *
 * @dev: the device in query
 * @startup: true अगर this is during early boot
 *
 * Returns:
 *  - IOMMU_DOMAIN_DMA: device requires a dynamic mapping करोमुख्य
 *  - IOMMU_DOMAIN_IDENTITY: device requires an identical mapping करोमुख्य
 *  - 0: both identity and dynamic करोमुख्यs work क्रम this device
 */
अटल पूर्णांक device_def_करोमुख्य_type(काष्ठा device *dev)
अणु
	अगर (dev_is_pci(dev)) अणु
		काष्ठा pci_dev *pdev = to_pci_dev(dev);

		अगर ((iommu_identity_mapping & IDENTMAP_AZALIA) && IS_AZALIA(pdev))
			वापस IOMMU_DOMAIN_IDENTITY;

		अगर ((iommu_identity_mapping & IDENTMAP_GFX) && IS_GFX_DEVICE(pdev))
			वापस IOMMU_DOMAIN_IDENTITY;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_iommu_init_qi(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	/*
	 * Start from the sane iommu hardware state.
	 * If the queued invalidation is alपढ़ोy initialized by us
	 * (क्रम example, जबतक enabling पूर्णांकerrupt-remapping) then
	 * we got the things alपढ़ोy rolling from a sane state.
	 */
	अगर (!iommu->qi) अणु
		/*
		 * Clear any previous faults.
		 */
		dmar_fault(-1, iommu);
		/*
		 * Disable queued invalidation अगर supported and alपढ़ोy enabled
		 * beक्रमe OS hanकरोver.
		 */
		dmar_disable_qi(iommu);
	पूर्ण

	अगर (dmar_enable_qi(iommu)) अणु
		/*
		 * Queued Invalidate not enabled, use Register Based Invalidate
		 */
		iommu->flush.flush_context = __iommu_flush_context;
		iommu->flush.flush_iotlb = __iommu_flush_iotlb;
		pr_info("%s: Using Register based invalidation\n",
			iommu->name);
	पूर्ण अन्यथा अणु
		iommu->flush.flush_context = qi_flush_context;
		iommu->flush.flush_iotlb = qi_flush_iotlb;
		pr_info("%s: Using Queued invalidation\n", iommu->name);
	पूर्ण
पूर्ण

अटल पूर्णांक copy_context_table(काष्ठा पूर्णांकel_iommu *iommu,
			      काष्ठा root_entry *old_re,
			      काष्ठा context_entry **tbl,
			      पूर्णांक bus, bool ext)
अणु
	पूर्णांक tbl_idx, pos = 0, idx, devfn, ret = 0, did;
	काष्ठा context_entry *new_ce = शून्य, ce;
	काष्ठा context_entry *old_ce = शून्य;
	काष्ठा root_entry re;
	phys_addr_t old_ce_phys;

	tbl_idx = ext ? bus * 2 : bus;
	स_नकल(&re, old_re, माप(re));

	क्रम (devfn = 0; devfn < 256; devfn++) अणु
		/* First calculate the correct index */
		idx = (ext ? devfn * 2 : devfn) % 256;

		अगर (idx == 0) अणु
			/* First save what we may have and clean up */
			अगर (new_ce) अणु
				tbl[tbl_idx] = new_ce;
				__iommu_flush_cache(iommu, new_ce,
						    VTD_PAGE_SIZE);
				pos = 1;
			पूर्ण

			अगर (old_ce)
				memunmap(old_ce);

			ret = 0;
			अगर (devfn < 0x80)
				old_ce_phys = root_entry_lctp(&re);
			अन्यथा
				old_ce_phys = root_entry_uctp(&re);

			अगर (!old_ce_phys) अणु
				अगर (ext && devfn == 0) अणु
					/* No LCTP, try UCTP */
					devfn = 0x7f;
					जारी;
				पूर्ण अन्यथा अणु
					जाओ out;
				पूर्ण
			पूर्ण

			ret = -ENOMEM;
			old_ce = memremap(old_ce_phys, PAGE_SIZE,
					MEMREMAP_WB);
			अगर (!old_ce)
				जाओ out;

			new_ce = alloc_pgtable_page(iommu->node);
			अगर (!new_ce)
				जाओ out_unmap;

			ret = 0;
		पूर्ण

		/* Now copy the context entry */
		स_नकल(&ce, old_ce + idx, माप(ce));

		अगर (!__context_present(&ce))
			जारी;

		did = context_करोमुख्य_id(&ce);
		अगर (did >= 0 && did < cap_nकरोms(iommu->cap))
			set_bit(did, iommu->करोमुख्य_ids);

		/*
		 * We need a marker क्रम copied context entries. This
		 * marker needs to work क्रम the old क्रमmat as well as
		 * क्रम extended context entries.
		 *
		 * Bit 67 of the context entry is used. In the old
		 * क्रमmat this bit is available to software, in the
		 * extended क्रमmat it is the PGE bit, but PGE is ignored
		 * by HW अगर PASIDs are disabled (and thus still
		 * available).
		 *
		 * So disable PASIDs first and then mark the entry
		 * copied. This means that we करोn't copy PASID
		 * translations from the old kernel, but this is fine as
		 * faults there are not fatal.
		 */
		context_clear_pasid_enable(&ce);
		context_set_copied(&ce);

		new_ce[idx] = ce;
	पूर्ण

	tbl[tbl_idx + pos] = new_ce;

	__iommu_flush_cache(iommu, new_ce, VTD_PAGE_SIZE);

out_unmap:
	memunmap(old_ce);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक copy_translation_tables(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	काष्ठा context_entry **ctxt_tbls;
	काष्ठा root_entry *old_rt;
	phys_addr_t old_rt_phys;
	पूर्णांक ctxt_table_entries;
	अचिन्हित दीर्घ flags;
	u64 rtaddr_reg;
	पूर्णांक bus, ret;
	bool new_ext, ext;

	rtaddr_reg = dmar_पढ़ोq(iommu->reg + DMAR_RTADDR_REG);
	ext        = !!(rtaddr_reg & DMA_RTADDR_RTT);
	new_ext    = !!ecap_ecs(iommu->ecap);

	/*
	 * The RTT bit can only be changed when translation is disabled,
	 * but disabling translation means to खोलो a winकरोw क्रम data
	 * corruption. So bail out and करोn't copy anything अगर we would
	 * have to change the bit.
	 */
	अगर (new_ext != ext)
		वापस -EINVAL;

	old_rt_phys = rtaddr_reg & VTD_PAGE_MASK;
	अगर (!old_rt_phys)
		वापस -EINVAL;

	old_rt = memremap(old_rt_phys, PAGE_SIZE, MEMREMAP_WB);
	अगर (!old_rt)
		वापस -ENOMEM;

	/* This is too big क्रम the stack - allocate it from slab */
	ctxt_table_entries = ext ? 512 : 256;
	ret = -ENOMEM;
	ctxt_tbls = kसुस्मृति(ctxt_table_entries, माप(व्योम *), GFP_KERNEL);
	अगर (!ctxt_tbls)
		जाओ out_unmap;

	क्रम (bus = 0; bus < 256; bus++) अणु
		ret = copy_context_table(iommu, &old_rt[bus],
					 ctxt_tbls, bus, ext);
		अगर (ret) अणु
			pr_err("%s: Failed to copy context table for bus %d\n",
				iommu->name, bus);
			जारी;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&iommu->lock, flags);

	/* Context tables are copied, now ग_लिखो them to the root_entry table */
	क्रम (bus = 0; bus < 256; bus++) अणु
		पूर्णांक idx = ext ? bus * 2 : bus;
		u64 val;

		अगर (ctxt_tbls[idx]) अणु
			val = virt_to_phys(ctxt_tbls[idx]) | 1;
			iommu->root_entry[bus].lo = val;
		पूर्ण

		अगर (!ext || !ctxt_tbls[idx + 1])
			जारी;

		val = virt_to_phys(ctxt_tbls[idx + 1]) | 1;
		iommu->root_entry[bus].hi = val;
	पूर्ण

	spin_unlock_irqrestore(&iommu->lock, flags);

	kमुक्त(ctxt_tbls);

	__iommu_flush_cache(iommu, iommu->root_entry, PAGE_SIZE);

	ret = 0;

out_unmap:
	memunmap(old_rt);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_INTEL_IOMMU_SVM
अटल ioasid_t पूर्णांकel_vcmd_ioasid_alloc(ioasid_t min, ioasid_t max, व्योम *data)
अणु
	काष्ठा पूर्णांकel_iommu *iommu = data;
	ioasid_t ioasid;

	अगर (!iommu)
		वापस INVALID_IOASID;
	/*
	 * VT-d भव command पूर्णांकerface always uses the full 20 bit
	 * PASID range. Host can partition guest PASID range based on
	 * policies but it is out of guest's control.
	 */
	अगर (min < PASID_MIN || max > पूर्णांकel_pasid_max_id)
		वापस INVALID_IOASID;

	अगर (vcmd_alloc_pasid(iommu, &ioasid))
		वापस INVALID_IOASID;

	वापस ioasid;
पूर्ण

अटल व्योम पूर्णांकel_vcmd_ioasid_मुक्त(ioasid_t ioasid, व्योम *data)
अणु
	काष्ठा पूर्णांकel_iommu *iommu = data;

	अगर (!iommu)
		वापस;
	/*
	 * Sanity check the ioasid owner is करोne at upper layer, e.g. VFIO
	 * We can only मुक्त the PASID when all the devices are unbound.
	 */
	अगर (ioasid_find(शून्य, ioasid, शून्य)) अणु
		pr_alert("Cannot free active IOASID %d\n", ioasid);
		वापस;
	पूर्ण
	vcmd_मुक्त_pasid(iommu, ioasid);
पूर्ण

अटल व्योम रेजिस्टर_pasid_allocator(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	/*
	 * If we are running in the host, no need क्रम custom allocator
	 * in that PASIDs are allocated from the host प्रणाली-wide.
	 */
	अगर (!cap_caching_mode(iommu->cap))
		वापस;

	अगर (!sm_supported(iommu)) अणु
		pr_warn("VT-d Scalable Mode not enabled, no PASID allocation\n");
		वापस;
	पूर्ण

	/*
	 * Register a custom PASID allocator अगर we are running in a guest,
	 * guest PASID must be obtained via भव command पूर्णांकerface.
	 * There can be multiple vIOMMUs in each guest but only one allocator
	 * is active. All vIOMMU allocators will eventually be calling the same
	 * host allocator.
	 */
	अगर (!vccap_pasid(iommu->vccap))
		वापस;

	pr_info("Register custom PASID allocator\n");
	iommu->pasid_allocator.alloc = पूर्णांकel_vcmd_ioasid_alloc;
	iommu->pasid_allocator.मुक्त = पूर्णांकel_vcmd_ioasid_मुक्त;
	iommu->pasid_allocator.pdata = (व्योम *)iommu;
	अगर (ioasid_रेजिस्टर_allocator(&iommu->pasid_allocator)) अणु
		pr_warn("Custom PASID allocator failed, scalable mode disabled\n");
		/*
		 * Disable scalable mode on this IOMMU अगर there
		 * is no custom allocator. Mixing SM capable vIOMMU
		 * and non-SM vIOMMU are not supported.
		 */
		पूर्णांकel_iommu_sm = 0;
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init init_dmars(व्योम)
अणु
	काष्ठा dmar_drhd_unit *drhd;
	काष्ठा पूर्णांकel_iommu *iommu;
	पूर्णांक ret;

	/*
	 * क्रम each drhd
	 *    allocate root
	 *    initialize and program root entry to not present
	 * endक्रम
	 */
	क्रम_each_drhd_unit(drhd) अणु
		/*
		 * lock not needed as this is only incremented in the single
		 * thपढ़ोed kernel __init code path all other access are पढ़ो
		 * only
		 */
		अगर (g_num_of_iommus < DMAR_UNITS_SUPPORTED) अणु
			g_num_of_iommus++;
			जारी;
		पूर्ण
		pr_err_once("Exceeded %d IOMMUs\n", DMAR_UNITS_SUPPORTED);
	पूर्ण

	/* Pपुनः_स्मृतिate enough resources क्रम IOMMU hot-addition */
	अगर (g_num_of_iommus < DMAR_UNITS_SUPPORTED)
		g_num_of_iommus = DMAR_UNITS_SUPPORTED;

	g_iommus = kसुस्मृति(g_num_of_iommus, माप(काष्ठा पूर्णांकel_iommu *),
			GFP_KERNEL);
	अगर (!g_iommus) अणु
		pr_err("Allocating global iommu array failed\n");
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	ret = पूर्णांकel_cap_audit(CAP_AUDIT_STATIC_DMAR, शून्य);
	अगर (ret)
		जाओ मुक्त_iommu;

	क्रम_each_iommu(iommu, drhd) अणु
		अगर (drhd->ignored) अणु
			iommu_disable_translation(iommu);
			जारी;
		पूर्ण

		/*
		 * Find the max pasid size of all IOMMU's in the प्रणाली.
		 * We need to ensure the प्रणाली pasid table is no bigger
		 * than the smallest supported.
		 */
		अगर (pasid_supported(iommu)) अणु
			u32 temp = 2 << ecap_pss(iommu->ecap);

			पूर्णांकel_pasid_max_id = min_t(u32, temp,
						   पूर्णांकel_pasid_max_id);
		पूर्ण

		g_iommus[iommu->seq_id] = iommu;

		पूर्णांकel_iommu_init_qi(iommu);

		ret = iommu_init_करोमुख्यs(iommu);
		अगर (ret)
			जाओ मुक्त_iommu;

		init_translation_status(iommu);

		अगर (translation_pre_enabled(iommu) && !is_kdump_kernel()) अणु
			iommu_disable_translation(iommu);
			clear_translation_pre_enabled(iommu);
			pr_warn("Translation was enabled for %s but we are not in kdump mode\n",
				iommu->name);
		पूर्ण

		/*
		 * TBD:
		 * we could share the same root & context tables
		 * among all IOMMU's. Need to Split it later.
		 */
		ret = iommu_alloc_root_entry(iommu);
		अगर (ret)
			जाओ मुक्त_iommu;

		अगर (translation_pre_enabled(iommu)) अणु
			pr_info("Translation already enabled - trying to copy translation structures\n");

			ret = copy_translation_tables(iommu);
			अगर (ret) अणु
				/*
				 * We found the IOMMU with translation
				 * enabled - but failed to copy over the
				 * old root-entry table. Try to proceed
				 * by disabling translation now and
				 * allocating a clean root-entry table.
				 * This might cause DMAR faults, but
				 * probably the dump will still succeed.
				 */
				pr_err("Failed to copy translation tables from previous kernel for %s\n",
				       iommu->name);
				iommu_disable_translation(iommu);
				clear_translation_pre_enabled(iommu);
			पूर्ण अन्यथा अणु
				pr_info("Copied translation tables from previous kernel for %s\n",
					iommu->name);
			पूर्ण
		पूर्ण

		अगर (!ecap_pass_through(iommu->ecap))
			hw_pass_through = 0;
		पूर्णांकel_svm_check(iommu);
	पूर्ण

	/*
	 * Now that qi is enabled on all iommus, set the root entry and flush
	 * caches. This is required on some Intel X58 chipsets, otherwise the
	 * flush_context function will loop क्रमever and the boot hangs.
	 */
	क्रम_each_active_iommu(iommu, drhd) अणु
		iommu_flush_ग_लिखो_buffer(iommu);
#अगर_घोषित CONFIG_INTEL_IOMMU_SVM
		रेजिस्टर_pasid_allocator(iommu);
#पूर्ण_अगर
		iommu_set_root_entry(iommu);
	पूर्ण

#अगर_घोषित CONFIG_INTEL_IOMMU_BROKEN_GFX_WA
	dmar_map_gfx = 0;
#पूर्ण_अगर

	अगर (!dmar_map_gfx)
		iommu_identity_mapping |= IDENTMAP_GFX;

	check_tylersburg_isoch();

	ret = si_करोमुख्य_init(hw_pass_through);
	अगर (ret)
		जाओ मुक्त_iommu;

	/*
	 * क्रम each drhd
	 *   enable fault log
	 *   global invalidate context cache
	 *   global invalidate iotlb
	 *   enable translation
	 */
	क्रम_each_iommu(iommu, drhd) अणु
		अगर (drhd->ignored) अणु
			/*
			 * we always have to disable PMRs or DMA may fail on
			 * this device
			 */
			अगर (क्रमce_on)
				iommu_disable_protect_mem_regions(iommu);
			जारी;
		पूर्ण

		iommu_flush_ग_लिखो_buffer(iommu);

#अगर_घोषित CONFIG_INTEL_IOMMU_SVM
		अगर (pasid_supported(iommu) && ecap_prs(iommu->ecap)) अणु
			/*
			 * Call dmar_alloc_hwirq() with dmar_global_lock held,
			 * could cause possible lock race condition.
			 */
			up_ग_लिखो(&dmar_global_lock);
			ret = पूर्णांकel_svm_enable_prq(iommu);
			करोwn_ग_लिखो(&dmar_global_lock);
			अगर (ret)
				जाओ मुक्त_iommu;
		पूर्ण
#पूर्ण_अगर
		ret = dmar_set_पूर्णांकerrupt(iommu);
		अगर (ret)
			जाओ मुक्त_iommu;
	पूर्ण

	वापस 0;

मुक्त_iommu:
	क्रम_each_active_iommu(iommu, drhd) अणु
		disable_dmar_iommu(iommu);
		मुक्त_dmar_iommu(iommu);
	पूर्ण

	kमुक्त(g_iommus);

error:
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक iommu_करोमुख्य_cache_init(व्योम)
अणु
	पूर्णांक ret = 0;

	iommu_करोमुख्य_cache = kmem_cache_create("iommu_domain",
					 माप(काष्ठा dmar_करोमुख्य),
					 0,
					 SLAB_HWCACHE_ALIGN,

					 शून्य);
	अगर (!iommu_करोमुख्य_cache) अणु
		pr_err("Couldn't create iommu_domain cache\n");
		ret = -ENOMEM;
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक iommu_devinfo_cache_init(व्योम)
अणु
	पूर्णांक ret = 0;

	iommu_devinfo_cache = kmem_cache_create("iommu_devinfo",
					 माप(काष्ठा device_करोमुख्य_info),
					 0,
					 SLAB_HWCACHE_ALIGN,
					 शून्य);
	अगर (!iommu_devinfo_cache) अणु
		pr_err("Couldn't create devinfo cache\n");
		ret = -ENOMEM;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __init iommu_init_mempool(व्योम)
अणु
	पूर्णांक ret;
	ret = iova_cache_get();
	अगर (ret)
		वापस ret;

	ret = iommu_करोमुख्य_cache_init();
	अगर (ret)
		जाओ करोमुख्य_error;

	ret = iommu_devinfo_cache_init();
	अगर (!ret)
		वापस ret;

	kmem_cache_destroy(iommu_करोमुख्य_cache);
करोमुख्य_error:
	iova_cache_put();

	वापस -ENOMEM;
पूर्ण

अटल व्योम __init iommu_निकास_mempool(व्योम)
अणु
	kmem_cache_destroy(iommu_devinfo_cache);
	kmem_cache_destroy(iommu_करोमुख्य_cache);
	iova_cache_put();
पूर्ण

अटल व्योम __init init_no_remapping_devices(व्योम)
अणु
	काष्ठा dmar_drhd_unit *drhd;
	काष्ठा device *dev;
	पूर्णांक i;

	क्रम_each_drhd_unit(drhd) अणु
		अगर (!drhd->include_all) अणु
			क्रम_each_active_dev_scope(drhd->devices,
						  drhd->devices_cnt, i, dev)
				अवरोध;
			/* ignore DMAR unit अगर no devices exist */
			अगर (i == drhd->devices_cnt)
				drhd->ignored = 1;
		पूर्ण
	पूर्ण

	क्रम_each_active_drhd_unit(drhd) अणु
		अगर (drhd->include_all)
			जारी;

		क्रम_each_active_dev_scope(drhd->devices,
					  drhd->devices_cnt, i, dev)
			अगर (!dev_is_pci(dev) || !IS_GFX_DEVICE(to_pci_dev(dev)))
				अवरोध;
		अगर (i < drhd->devices_cnt)
			जारी;

		/* This IOMMU has *only* gfx devices. Either bypass it or
		   set the gfx_mapped flag, as appropriate */
		drhd->gfx_dedicated = 1;
		अगर (!dmar_map_gfx)
			drhd->ignored = 1;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SUSPEND
अटल पूर्णांक init_iommu_hw(व्योम)
अणु
	काष्ठा dmar_drhd_unit *drhd;
	काष्ठा पूर्णांकel_iommu *iommu = शून्य;

	क्रम_each_active_iommu(iommu, drhd)
		अगर (iommu->qi)
			dmar_reenable_qi(iommu);

	क्रम_each_iommu(iommu, drhd) अणु
		अगर (drhd->ignored) अणु
			/*
			 * we always have to disable PMRs or DMA may fail on
			 * this device
			 */
			अगर (क्रमce_on)
				iommu_disable_protect_mem_regions(iommu);
			जारी;
		पूर्ण

		iommu_flush_ग_लिखो_buffer(iommu);
		iommu_set_root_entry(iommu);
		iommu_enable_translation(iommu);
		iommu_disable_protect_mem_regions(iommu);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम iommu_flush_all(व्योम)
अणु
	काष्ठा dmar_drhd_unit *drhd;
	काष्ठा पूर्णांकel_iommu *iommu;

	क्रम_each_active_iommu(iommu, drhd) अणु
		iommu->flush.flush_context(iommu, 0, 0, 0,
					   DMA_CCMD_GLOBAL_INVL);
		iommu->flush.flush_iotlb(iommu, 0, 0, 0,
					 DMA_TLB_GLOBAL_FLUSH);
	पूर्ण
पूर्ण

अटल पूर्णांक iommu_suspend(व्योम)
अणु
	काष्ठा dmar_drhd_unit *drhd;
	काष्ठा पूर्णांकel_iommu *iommu = शून्य;
	अचिन्हित दीर्घ flag;

	क्रम_each_active_iommu(iommu, drhd) अणु
		iommu->iommu_state = kसुस्मृति(MAX_SR_DMAR_REGS, माप(u32),
					     GFP_KERNEL);
		अगर (!iommu->iommu_state)
			जाओ nomem;
	पूर्ण

	iommu_flush_all();

	क्रम_each_active_iommu(iommu, drhd) अणु
		iommu_disable_translation(iommu);

		raw_spin_lock_irqsave(&iommu->रेजिस्टर_lock, flag);

		iommu->iommu_state[SR_DMAR_FECTL_REG] =
			पढ़ोl(iommu->reg + DMAR_FECTL_REG);
		iommu->iommu_state[SR_DMAR_FEDATA_REG] =
			पढ़ोl(iommu->reg + DMAR_FEDATA_REG);
		iommu->iommu_state[SR_DMAR_FEADDR_REG] =
			पढ़ोl(iommu->reg + DMAR_FEADDR_REG);
		iommu->iommu_state[SR_DMAR_FEUADDR_REG] =
			पढ़ोl(iommu->reg + DMAR_FEUADDR_REG);

		raw_spin_unlock_irqrestore(&iommu->रेजिस्टर_lock, flag);
	पूर्ण
	वापस 0;

nomem:
	क्रम_each_active_iommu(iommu, drhd)
		kमुक्त(iommu->iommu_state);

	वापस -ENOMEM;
पूर्ण

अटल व्योम iommu_resume(व्योम)
अणु
	काष्ठा dmar_drhd_unit *drhd;
	काष्ठा पूर्णांकel_iommu *iommu = शून्य;
	अचिन्हित दीर्घ flag;

	अगर (init_iommu_hw()) अणु
		अगर (क्रमce_on)
			panic("tboot: IOMMU setup failed, DMAR can not resume!\n");
		अन्यथा
			WARN(1, "IOMMU setup failed, DMAR can not resume!\n");
		वापस;
	पूर्ण

	क्रम_each_active_iommu(iommu, drhd) अणु

		raw_spin_lock_irqsave(&iommu->रेजिस्टर_lock, flag);

		ग_लिखोl(iommu->iommu_state[SR_DMAR_FECTL_REG],
			iommu->reg + DMAR_FECTL_REG);
		ग_लिखोl(iommu->iommu_state[SR_DMAR_FEDATA_REG],
			iommu->reg + DMAR_FEDATA_REG);
		ग_लिखोl(iommu->iommu_state[SR_DMAR_FEADDR_REG],
			iommu->reg + DMAR_FEADDR_REG);
		ग_लिखोl(iommu->iommu_state[SR_DMAR_FEUADDR_REG],
			iommu->reg + DMAR_FEUADDR_REG);

		raw_spin_unlock_irqrestore(&iommu->रेजिस्टर_lock, flag);
	पूर्ण

	क्रम_each_active_iommu(iommu, drhd)
		kमुक्त(iommu->iommu_state);
पूर्ण

अटल काष्ठा syscore_ops iommu_syscore_ops = अणु
	.resume		= iommu_resume,
	.suspend	= iommu_suspend,
पूर्ण;

अटल व्योम __init init_iommu_pm_ops(व्योम)
अणु
	रेजिस्टर_syscore_ops(&iommu_syscore_ops);
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम init_iommu_pm_ops(व्योम) अणुपूर्ण
#पूर्ण_अगर	/* CONFIG_PM */

अटल पूर्णांक rmrr_sanity_check(काष्ठा acpi_dmar_reserved_memory *rmrr)
अणु
	अगर (!IS_ALIGNED(rmrr->base_address, PAGE_SIZE) ||
	    !IS_ALIGNED(rmrr->end_address + 1, PAGE_SIZE) ||
	    rmrr->end_address <= rmrr->base_address ||
	    arch_rmrr_sanity_check(rmrr))
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक __init dmar_parse_one_rmrr(काष्ठा acpi_dmar_header *header, व्योम *arg)
अणु
	काष्ठा acpi_dmar_reserved_memory *rmrr;
	काष्ठा dmar_rmrr_unit *rmrru;

	rmrr = (काष्ठा acpi_dmar_reserved_memory *)header;
	अगर (rmrr_sanity_check(rmrr)) अणु
		pr_warn(FW_BUG
			   "Your BIOS is broken; bad RMRR [%#018Lx-%#018Lx]\n"
			   "BIOS vendor: %s; Ver: %s; Product Version: %s\n",
			   rmrr->base_address, rmrr->end_address,
			   dmi_get_प्रणाली_info(DMI_BIOS_VENDOR),
			   dmi_get_प्रणाली_info(DMI_BIOS_VERSION),
			   dmi_get_प्रणाली_info(DMI_PRODUCT_VERSION));
		add_taपूर्णांक(TAINT_FIRMWARE_WORKAROUND, LOCKDEP_STILL_OK);
	पूर्ण

	rmrru = kzalloc(माप(*rmrru), GFP_KERNEL);
	अगर (!rmrru)
		जाओ out;

	rmrru->hdr = header;

	rmrru->base_address = rmrr->base_address;
	rmrru->end_address = rmrr->end_address;

	rmrru->devices = dmar_alloc_dev_scope((व्योम *)(rmrr + 1),
				((व्योम *)rmrr) + rmrr->header.length,
				&rmrru->devices_cnt);
	अगर (rmrru->devices_cnt && rmrru->devices == शून्य)
		जाओ मुक्त_rmrru;

	list_add(&rmrru->list, &dmar_rmrr_units);

	वापस 0;
मुक्त_rmrru:
	kमुक्त(rmrru);
out:
	वापस -ENOMEM;
पूर्ण

अटल काष्ठा dmar_atsr_unit *dmar_find_atsr(काष्ठा acpi_dmar_atsr *atsr)
अणु
	काष्ठा dmar_atsr_unit *atsru;
	काष्ठा acpi_dmar_atsr *पंचांगp;

	list_क्रम_each_entry_rcu(atsru, &dmar_atsr_units, list,
				dmar_rcu_check()) अणु
		पंचांगp = (काष्ठा acpi_dmar_atsr *)atsru->hdr;
		अगर (atsr->segment != पंचांगp->segment)
			जारी;
		अगर (atsr->header.length != पंचांगp->header.length)
			जारी;
		अगर (स_भेद(atsr, पंचांगp, atsr->header.length) == 0)
			वापस atsru;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक dmar_parse_one_atsr(काष्ठा acpi_dmar_header *hdr, व्योम *arg)
अणु
	काष्ठा acpi_dmar_atsr *atsr;
	काष्ठा dmar_atsr_unit *atsru;

	अगर (प्रणाली_state >= SYSTEM_RUNNING && !पूर्णांकel_iommu_enabled)
		वापस 0;

	atsr = container_of(hdr, काष्ठा acpi_dmar_atsr, header);
	atsru = dmar_find_atsr(atsr);
	अगर (atsru)
		वापस 0;

	atsru = kzalloc(माप(*atsru) + hdr->length, GFP_KERNEL);
	अगर (!atsru)
		वापस -ENOMEM;

	/*
	 * If memory is allocated from slab by ACPI _DSM method, we need to
	 * copy the memory content because the memory buffer will be मुक्तd
	 * on वापस.
	 */
	atsru->hdr = (व्योम *)(atsru + 1);
	स_नकल(atsru->hdr, hdr, hdr->length);
	atsru->include_all = atsr->flags & 0x1;
	अगर (!atsru->include_all) अणु
		atsru->devices = dmar_alloc_dev_scope((व्योम *)(atsr + 1),
				(व्योम *)atsr + atsr->header.length,
				&atsru->devices_cnt);
		अगर (atsru->devices_cnt && atsru->devices == शून्य) अणु
			kमुक्त(atsru);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	list_add_rcu(&atsru->list, &dmar_atsr_units);

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_iommu_मुक्त_atsr(काष्ठा dmar_atsr_unit *atsru)
अणु
	dmar_मुक्त_dev_scope(&atsru->devices, &atsru->devices_cnt);
	kमुक्त(atsru);
पूर्ण

पूर्णांक dmar_release_one_atsr(काष्ठा acpi_dmar_header *hdr, व्योम *arg)
अणु
	काष्ठा acpi_dmar_atsr *atsr;
	काष्ठा dmar_atsr_unit *atsru;

	atsr = container_of(hdr, काष्ठा acpi_dmar_atsr, header);
	atsru = dmar_find_atsr(atsr);
	अगर (atsru) अणु
		list_del_rcu(&atsru->list);
		synchronize_rcu();
		पूर्णांकel_iommu_मुक्त_atsr(atsru);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dmar_check_one_atsr(काष्ठा acpi_dmar_header *hdr, व्योम *arg)
अणु
	पूर्णांक i;
	काष्ठा device *dev;
	काष्ठा acpi_dmar_atsr *atsr;
	काष्ठा dmar_atsr_unit *atsru;

	atsr = container_of(hdr, काष्ठा acpi_dmar_atsr, header);
	atsru = dmar_find_atsr(atsr);
	अगर (!atsru)
		वापस 0;

	अगर (!atsru->include_all && atsru->devices && atsru->devices_cnt) अणु
		क्रम_each_active_dev_scope(atsru->devices, atsru->devices_cnt,
					  i, dev)
			वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा dmar_satc_unit *dmar_find_satc(काष्ठा acpi_dmar_satc *satc)
अणु
	काष्ठा dmar_satc_unit *satcu;
	काष्ठा acpi_dmar_satc *पंचांगp;

	list_क्रम_each_entry_rcu(satcu, &dmar_satc_units, list,
				dmar_rcu_check()) अणु
		पंचांगp = (काष्ठा acpi_dmar_satc *)satcu->hdr;
		अगर (satc->segment != पंचांगp->segment)
			जारी;
		अगर (satc->header.length != पंचांगp->header.length)
			जारी;
		अगर (स_भेद(satc, पंचांगp, satc->header.length) == 0)
			वापस satcu;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक dmar_parse_one_satc(काष्ठा acpi_dmar_header *hdr, व्योम *arg)
अणु
	काष्ठा acpi_dmar_satc *satc;
	काष्ठा dmar_satc_unit *satcu;

	अगर (प्रणाली_state >= SYSTEM_RUNNING && !पूर्णांकel_iommu_enabled)
		वापस 0;

	satc = container_of(hdr, काष्ठा acpi_dmar_satc, header);
	satcu = dmar_find_satc(satc);
	अगर (satcu)
		वापस 0;

	satcu = kzalloc(माप(*satcu) + hdr->length, GFP_KERNEL);
	अगर (!satcu)
		वापस -ENOMEM;

	satcu->hdr = (व्योम *)(satcu + 1);
	स_नकल(satcu->hdr, hdr, hdr->length);
	satcu->atc_required = satc->flags & 0x1;
	satcu->devices = dmar_alloc_dev_scope((व्योम *)(satc + 1),
					      (व्योम *)satc + satc->header.length,
					      &satcu->devices_cnt);
	अगर (satcu->devices_cnt && !satcu->devices) अणु
		kमुक्त(satcu);
		वापस -ENOMEM;
	पूर्ण
	list_add_rcu(&satcu->list, &dmar_satc_units);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_iommu_add(काष्ठा dmar_drhd_unit *dmaru)
अणु
	पूर्णांक sp, ret;
	काष्ठा पूर्णांकel_iommu *iommu = dmaru->iommu;

	अगर (g_iommus[iommu->seq_id])
		वापस 0;

	ret = पूर्णांकel_cap_audit(CAP_AUDIT_HOTPLUG_DMAR, iommu);
	अगर (ret)
		जाओ out;

	अगर (hw_pass_through && !ecap_pass_through(iommu->ecap)) अणु
		pr_warn("%s: Doesn't support hardware pass through.\n",
			iommu->name);
		वापस -ENXIO;
	पूर्ण
	अगर (!ecap_sc_support(iommu->ecap) &&
	    करोमुख्य_update_iommu_snooping(iommu)) अणु
		pr_warn("%s: Doesn't support snooping.\n",
			iommu->name);
		वापस -ENXIO;
	पूर्ण
	sp = करोमुख्य_update_iommu_superpage(शून्य, iommu) - 1;
	अगर (sp >= 0 && !(cap_super_page_val(iommu->cap) & (1 << sp))) अणु
		pr_warn("%s: Doesn't support large page.\n",
			iommu->name);
		वापस -ENXIO;
	पूर्ण

	/*
	 * Disable translation अगर alपढ़ोy enabled prior to OS hanकरोver.
	 */
	अगर (iommu->gcmd & DMA_GCMD_TE)
		iommu_disable_translation(iommu);

	g_iommus[iommu->seq_id] = iommu;
	ret = iommu_init_करोमुख्यs(iommu);
	अगर (ret == 0)
		ret = iommu_alloc_root_entry(iommu);
	अगर (ret)
		जाओ out;

	पूर्णांकel_svm_check(iommu);

	अगर (dmaru->ignored) अणु
		/*
		 * we always have to disable PMRs or DMA may fail on this device
		 */
		अगर (क्रमce_on)
			iommu_disable_protect_mem_regions(iommu);
		वापस 0;
	पूर्ण

	पूर्णांकel_iommu_init_qi(iommu);
	iommu_flush_ग_लिखो_buffer(iommu);

#अगर_घोषित CONFIG_INTEL_IOMMU_SVM
	अगर (pasid_supported(iommu) && ecap_prs(iommu->ecap)) अणु
		ret = पूर्णांकel_svm_enable_prq(iommu);
		अगर (ret)
			जाओ disable_iommu;
	पूर्ण
#पूर्ण_अगर
	ret = dmar_set_पूर्णांकerrupt(iommu);
	अगर (ret)
		जाओ disable_iommu;

	iommu_set_root_entry(iommu);
	iommu_enable_translation(iommu);

	iommu_disable_protect_mem_regions(iommu);
	वापस 0;

disable_iommu:
	disable_dmar_iommu(iommu);
out:
	मुक्त_dmar_iommu(iommu);
	वापस ret;
पूर्ण

पूर्णांक dmar_iommu_hotplug(काष्ठा dmar_drhd_unit *dmaru, bool insert)
अणु
	पूर्णांक ret = 0;
	काष्ठा पूर्णांकel_iommu *iommu = dmaru->iommu;

	अगर (!पूर्णांकel_iommu_enabled)
		वापस 0;
	अगर (iommu == शून्य)
		वापस -EINVAL;

	अगर (insert) अणु
		ret = पूर्णांकel_iommu_add(dmaru);
	पूर्ण अन्यथा अणु
		disable_dmar_iommu(iommu);
		मुक्त_dmar_iommu(iommu);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम पूर्णांकel_iommu_मुक्त_dmars(व्योम)
अणु
	काष्ठा dmar_rmrr_unit *rmrru, *rmrr_n;
	काष्ठा dmar_atsr_unit *atsru, *atsr_n;
	काष्ठा dmar_satc_unit *satcu, *satc_n;

	list_क्रम_each_entry_safe(rmrru, rmrr_n, &dmar_rmrr_units, list) अणु
		list_del(&rmrru->list);
		dmar_मुक्त_dev_scope(&rmrru->devices, &rmrru->devices_cnt);
		kमुक्त(rmrru);
	पूर्ण

	list_क्रम_each_entry_safe(atsru, atsr_n, &dmar_atsr_units, list) अणु
		list_del(&atsru->list);
		पूर्णांकel_iommu_मुक्त_atsr(atsru);
	पूर्ण
	list_क्रम_each_entry_safe(satcu, satc_n, &dmar_satc_units, list) अणु
		list_del(&satcu->list);
		dmar_मुक्त_dev_scope(&satcu->devices, &satcu->devices_cnt);
		kमुक्त(satcu);
	पूर्ण
पूर्ण

पूर्णांक dmar_find_matched_atsr_unit(काष्ठा pci_dev *dev)
अणु
	पूर्णांक i, ret = 1;
	काष्ठा pci_bus *bus;
	काष्ठा pci_dev *bridge = शून्य;
	काष्ठा device *पंचांगp;
	काष्ठा acpi_dmar_atsr *atsr;
	काष्ठा dmar_atsr_unit *atsru;

	dev = pci_physfn(dev);
	क्रम (bus = dev->bus; bus; bus = bus->parent) अणु
		bridge = bus->self;
		/* If it's an पूर्णांकegrated device, allow ATS */
		अगर (!bridge)
			वापस 1;
		/* Connected via non-PCIe: no ATS */
		अगर (!pci_is_pcie(bridge) ||
		    pci_pcie_type(bridge) == PCI_EXP_TYPE_PCI_BRIDGE)
			वापस 0;
		/* If we found the root port, look it up in the ATSR */
		अगर (pci_pcie_type(bridge) == PCI_EXP_TYPE_ROOT_PORT)
			अवरोध;
	पूर्ण

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(atsru, &dmar_atsr_units, list) अणु
		atsr = container_of(atsru->hdr, काष्ठा acpi_dmar_atsr, header);
		अगर (atsr->segment != pci_करोमुख्य_nr(dev->bus))
			जारी;

		क्रम_each_dev_scope(atsru->devices, atsru->devices_cnt, i, पंचांगp)
			अगर (पंचांगp == &bridge->dev)
				जाओ out;

		अगर (atsru->include_all)
			जाओ out;
	पूर्ण
	ret = 0;
out:
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

पूर्णांक dmar_iommu_notअगरy_scope_dev(काष्ठा dmar_pci_notअगरy_info *info)
अणु
	पूर्णांक ret;
	काष्ठा dmar_rmrr_unit *rmrru;
	काष्ठा dmar_atsr_unit *atsru;
	काष्ठा dmar_satc_unit *satcu;
	काष्ठा acpi_dmar_atsr *atsr;
	काष्ठा acpi_dmar_reserved_memory *rmrr;
	काष्ठा acpi_dmar_satc *satc;

	अगर (!पूर्णांकel_iommu_enabled && प्रणाली_state >= SYSTEM_RUNNING)
		वापस 0;

	list_क्रम_each_entry(rmrru, &dmar_rmrr_units, list) अणु
		rmrr = container_of(rmrru->hdr,
				    काष्ठा acpi_dmar_reserved_memory, header);
		अगर (info->event == BUS_NOTIFY_ADD_DEVICE) अणु
			ret = dmar_insert_dev_scope(info, (व्योम *)(rmrr + 1),
				((व्योम *)rmrr) + rmrr->header.length,
				rmrr->segment, rmrru->devices,
				rmrru->devices_cnt);
			अगर (ret < 0)
				वापस ret;
		पूर्ण अन्यथा अगर (info->event == BUS_NOTIFY_REMOVED_DEVICE) अणु
			dmar_हटाओ_dev_scope(info, rmrr->segment,
				rmrru->devices, rmrru->devices_cnt);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(atsru, &dmar_atsr_units, list) अणु
		अगर (atsru->include_all)
			जारी;

		atsr = container_of(atsru->hdr, काष्ठा acpi_dmar_atsr, header);
		अगर (info->event == BUS_NOTIFY_ADD_DEVICE) अणु
			ret = dmar_insert_dev_scope(info, (व्योम *)(atsr + 1),
					(व्योम *)atsr + atsr->header.length,
					atsr->segment, atsru->devices,
					atsru->devices_cnt);
			अगर (ret > 0)
				अवरोध;
			अन्यथा अगर (ret < 0)
				वापस ret;
		पूर्ण अन्यथा अगर (info->event == BUS_NOTIFY_REMOVED_DEVICE) अणु
			अगर (dmar_हटाओ_dev_scope(info, atsr->segment,
					atsru->devices, atsru->devices_cnt))
				अवरोध;
		पूर्ण
	पूर्ण
	list_क्रम_each_entry(satcu, &dmar_satc_units, list) अणु
		satc = container_of(satcu->hdr, काष्ठा acpi_dmar_satc, header);
		अगर (info->event == BUS_NOTIFY_ADD_DEVICE) अणु
			ret = dmar_insert_dev_scope(info, (व्योम *)(satc + 1),
					(व्योम *)satc + satc->header.length,
					satc->segment, satcu->devices,
					satcu->devices_cnt);
			अगर (ret > 0)
				अवरोध;
			अन्यथा अगर (ret < 0)
				वापस ret;
		पूर्ण अन्यथा अगर (info->event == BUS_NOTIFY_REMOVED_DEVICE) अणु
			अगर (dmar_हटाओ_dev_scope(info, satc->segment,
					satcu->devices, satcu->devices_cnt))
				अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_iommu_memory_notअगरier(काष्ठा notअगरier_block *nb,
				       अचिन्हित दीर्घ val, व्योम *v)
अणु
	काष्ठा memory_notअगरy *mhp = v;
	अचिन्हित दीर्घ start_vpfn = mm_to_dma_pfn(mhp->start_pfn);
	अचिन्हित दीर्घ last_vpfn = mm_to_dma_pfn(mhp->start_pfn +
			mhp->nr_pages - 1);

	चयन (val) अणु
	हाल MEM_GOING_ONLINE:
		अगर (iommu_करोमुख्य_identity_map(si_करोमुख्य,
					      start_vpfn, last_vpfn)) अणु
			pr_warn("Failed to build identity map for [%lx-%lx]\n",
				start_vpfn, last_vpfn);
			वापस NOTIFY_BAD;
		पूर्ण
		अवरोध;

	हाल MEM_OFFLINE:
	हाल MEM_CANCEL_ONLINE:
		अणु
			काष्ठा dmar_drhd_unit *drhd;
			काष्ठा पूर्णांकel_iommu *iommu;
			काष्ठा page *मुक्तlist;

			मुक्तlist = करोमुख्य_unmap(si_करोमुख्य,
						start_vpfn, last_vpfn,
						शून्य);

			rcu_पढ़ो_lock();
			क्रम_each_active_iommu(iommu, drhd)
				iommu_flush_iotlb_psi(iommu, si_करोमुख्य,
					start_vpfn, mhp->nr_pages,
					!मुक्तlist, 0);
			rcu_पढ़ो_unlock();
			dma_मुक्त_pagelist(मुक्तlist);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block पूर्णांकel_iommu_memory_nb = अणु
	.notअगरier_call = पूर्णांकel_iommu_memory_notअगरier,
	.priority = 0
पूर्ण;

अटल व्योम पूर्णांकel_disable_iommus(व्योम)
अणु
	काष्ठा पूर्णांकel_iommu *iommu = शून्य;
	काष्ठा dmar_drhd_unit *drhd;

	क्रम_each_iommu(iommu, drhd)
		iommu_disable_translation(iommu);
पूर्ण

व्योम पूर्णांकel_iommu_shutकरोwn(व्योम)
अणु
	काष्ठा dmar_drhd_unit *drhd;
	काष्ठा पूर्णांकel_iommu *iommu = शून्य;

	अगर (no_iommu || dmar_disabled)
		वापस;

	करोwn_ग_लिखो(&dmar_global_lock);

	/* Disable PMRs explicitly here. */
	क्रम_each_iommu(iommu, drhd)
		iommu_disable_protect_mem_regions(iommu);

	/* Make sure the IOMMUs are चयनed off */
	पूर्णांकel_disable_iommus();

	up_ग_लिखो(&dmar_global_lock);
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_iommu *dev_to_पूर्णांकel_iommu(काष्ठा device *dev)
अणु
	काष्ठा iommu_device *iommu_dev = dev_to_iommu_device(dev);

	वापस container_of(iommu_dev, काष्ठा पूर्णांकel_iommu, iommu);
पूर्ण

अटल sमाप_प्रकार पूर्णांकel_iommu_show_version(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_iommu *iommu = dev_to_पूर्णांकel_iommu(dev);
	u32 ver = पढ़ोl(iommu->reg + DMAR_VER_REG);
	वापस प्र_लिखो(buf, "%d:%d\n",
		       DMAR_VER_MAJOR(ver), DMAR_VER_MINOR(ver));
पूर्ण
अटल DEVICE_ATTR(version, S_IRUGO, पूर्णांकel_iommu_show_version, शून्य);

अटल sमाप_प्रकार पूर्णांकel_iommu_show_address(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_iommu *iommu = dev_to_पूर्णांकel_iommu(dev);
	वापस प्र_लिखो(buf, "%llx\n", iommu->reg_phys);
पूर्ण
अटल DEVICE_ATTR(address, S_IRUGO, पूर्णांकel_iommu_show_address, शून्य);

अटल sमाप_प्रकार पूर्णांकel_iommu_show_cap(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_iommu *iommu = dev_to_पूर्णांकel_iommu(dev);
	वापस प्र_लिखो(buf, "%llx\n", iommu->cap);
पूर्ण
अटल DEVICE_ATTR(cap, S_IRUGO, पूर्णांकel_iommu_show_cap, शून्य);

अटल sमाप_प्रकार पूर्णांकel_iommu_show_ecap(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_iommu *iommu = dev_to_पूर्णांकel_iommu(dev);
	वापस प्र_लिखो(buf, "%llx\n", iommu->ecap);
पूर्ण
अटल DEVICE_ATTR(ecap, S_IRUGO, पूर्णांकel_iommu_show_ecap, शून्य);

अटल sमाप_प्रकार पूर्णांकel_iommu_show_nकरोms(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_iommu *iommu = dev_to_पूर्णांकel_iommu(dev);
	वापस प्र_लिखो(buf, "%ld\n", cap_nकरोms(iommu->cap));
पूर्ण
अटल DEVICE_ATTR(करोमुख्यs_supported, S_IRUGO, पूर्णांकel_iommu_show_nकरोms, शून्य);

अटल sमाप_प्रकार पूर्णांकel_iommu_show_nकरोms_used(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_iommu *iommu = dev_to_पूर्णांकel_iommu(dev);
	वापस प्र_लिखो(buf, "%d\n", biपंचांगap_weight(iommu->करोमुख्य_ids,
						  cap_nकरोms(iommu->cap)));
पूर्ण
अटल DEVICE_ATTR(करोमुख्यs_used, S_IRUGO, पूर्णांकel_iommu_show_nकरोms_used, शून्य);

अटल काष्ठा attribute *पूर्णांकel_iommu_attrs[] = अणु
	&dev_attr_version.attr,
	&dev_attr_address.attr,
	&dev_attr_cap.attr,
	&dev_attr_ecap.attr,
	&dev_attr_करोमुख्यs_supported.attr,
	&dev_attr_करोमुख्यs_used.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group पूर्णांकel_iommu_group = अणु
	.name = "intel-iommu",
	.attrs = पूर्णांकel_iommu_attrs,
पूर्ण;

स्थिर काष्ठा attribute_group *पूर्णांकel_iommu_groups[] = अणु
	&पूर्णांकel_iommu_group,
	शून्य,
पूर्ण;

अटल अंतरभूत bool has_बाह्यal_pci(व्योम)
अणु
	काष्ठा pci_dev *pdev = शून्य;

	क्रम_each_pci_dev(pdev)
		अगर (pdev->बाह्यal_facing)
			वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक __init platक्रमm_optin_क्रमce_iommu(व्योम)
अणु
	अगर (!dmar_platक्रमm_optin() || no_platक्रमm_optin || !has_बाह्यal_pci())
		वापस 0;

	अगर (no_iommu || dmar_disabled)
		pr_info("Intel-IOMMU force enabled due to platform opt in\n");

	/*
	 * If Intel-IOMMU is disabled by शेष, we will apply identity
	 * map क्रम all devices except those marked as being untrusted.
	 */
	अगर (dmar_disabled)
		iommu_set_शेष_passthrough(false);

	dmar_disabled = 0;
	no_iommu = 0;

	वापस 1;
पूर्ण

अटल पूर्णांक __init probe_acpi_namespace_devices(व्योम)
अणु
	काष्ठा dmar_drhd_unit *drhd;
	/* To aव्योम a -Wunused-but-set-variable warning. */
	काष्ठा पूर्णांकel_iommu *iommu __maybe_unused;
	काष्ठा device *dev;
	पूर्णांक i, ret = 0;

	क्रम_each_active_iommu(iommu, drhd) अणु
		क्रम_each_active_dev_scope(drhd->devices,
					  drhd->devices_cnt, i, dev) अणु
			काष्ठा acpi_device_physical_node *pn;
			काष्ठा iommu_group *group;
			काष्ठा acpi_device *adev;

			अगर (dev->bus != &acpi_bus_type)
				जारी;

			adev = to_acpi_device(dev);
			mutex_lock(&adev->physical_node_lock);
			list_क्रम_each_entry(pn,
					    &adev->physical_node_list, node) अणु
				group = iommu_group_get(pn->dev);
				अगर (group) अणु
					iommu_group_put(group);
					जारी;
				पूर्ण

				pn->dev->bus->iommu_ops = &पूर्णांकel_iommu_ops;
				ret = iommu_probe_device(pn->dev);
				अगर (ret)
					अवरोध;
			पूर्ण
			mutex_unlock(&adev->physical_node_lock);

			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक __init पूर्णांकel_iommu_init(व्योम)
अणु
	पूर्णांक ret = -ENODEV;
	काष्ठा dmar_drhd_unit *drhd;
	काष्ठा पूर्णांकel_iommu *iommu;

	/*
	 * Intel IOMMU is required क्रम a TXT/tboot launch or platक्रमm
	 * opt in, so enक्रमce that.
	 */
	क्रमce_on = (!पूर्णांकel_iommu_tboot_noक्रमce && tboot_क्रमce_iommu()) ||
		    platक्रमm_optin_क्रमce_iommu();

	अगर (iommu_init_mempool()) अणु
		अगर (क्रमce_on)
			panic("tboot: Failed to initialize iommu memory\n");
		वापस -ENOMEM;
	पूर्ण

	करोwn_ग_लिखो(&dmar_global_lock);
	अगर (dmar_table_init()) अणु
		अगर (क्रमce_on)
			panic("tboot: Failed to initialize DMAR table\n");
		जाओ out_मुक्त_dmar;
	पूर्ण

	अगर (dmar_dev_scope_init() < 0) अणु
		अगर (क्रमce_on)
			panic("tboot: Failed to initialize DMAR device scope\n");
		जाओ out_मुक्त_dmar;
	पूर्ण

	up_ग_लिखो(&dmar_global_lock);

	/*
	 * The bus notअगरier takes the dmar_global_lock, so lockdep will
	 * complain later when we रेजिस्टर it under the lock.
	 */
	dmar_रेजिस्टर_bus_notअगरier();

	करोwn_ग_लिखो(&dmar_global_lock);

	अगर (!no_iommu)
		पूर्णांकel_iommu_debugfs_init();

	अगर (no_iommu || dmar_disabled) अणु
		/*
		 * We निकास the function here to ensure IOMMU's remapping and
		 * mempool aren't setup, which means that the IOMMU's PMRs
		 * won't be disabled via the call to init_dmars(). So disable
		 * it explicitly here. The PMRs were setup by tboot prior to
		 * calling SENTER, but the kernel is expected to reset/tear
		 * करोwn the PMRs.
		 */
		अगर (पूर्णांकel_iommu_tboot_noक्रमce) अणु
			क्रम_each_iommu(iommu, drhd)
				iommu_disable_protect_mem_regions(iommu);
		पूर्ण

		/*
		 * Make sure the IOMMUs are चयनed off, even when we
		 * boot पूर्णांकo a kexec kernel and the previous kernel left
		 * them enabled
		 */
		पूर्णांकel_disable_iommus();
		जाओ out_मुक्त_dmar;
	पूर्ण

	अगर (list_empty(&dmar_rmrr_units))
		pr_info("No RMRR found\n");

	अगर (list_empty(&dmar_atsr_units))
		pr_info("No ATSR found\n");

	अगर (list_empty(&dmar_satc_units))
		pr_info("No SATC found\n");

	अगर (dmar_map_gfx)
		पूर्णांकel_iommu_gfx_mapped = 1;

	init_no_remapping_devices();

	ret = init_dmars();
	अगर (ret) अणु
		अगर (क्रमce_on)
			panic("tboot: Failed to initialize DMARs\n");
		pr_err("Initialization failed\n");
		जाओ out_मुक्त_dmar;
	पूर्ण
	up_ग_लिखो(&dmar_global_lock);

	init_iommu_pm_ops();

	करोwn_पढ़ो(&dmar_global_lock);
	क्रम_each_active_iommu(iommu, drhd) अणु
		/*
		 * The flush queue implementation करोes not perक्रमm
		 * page-selective invalidations that are required क्रम efficient
		 * TLB flushes in भव environments.  The benefit of batching
		 * is likely to be much lower than the overhead of synchronizing
		 * the भव and physical IOMMU page-tables.
		 */
		अगर (!पूर्णांकel_iommu_strict && cap_caching_mode(iommu->cap)) अणु
			pr_warn("IOMMU batching is disabled due to virtualization");
			पूर्णांकel_iommu_strict = 1;
		पूर्ण
		iommu_device_sysfs_add(&iommu->iommu, शून्य,
				       पूर्णांकel_iommu_groups,
				       "%s", iommu->name);
		iommu_device_रेजिस्टर(&iommu->iommu, &पूर्णांकel_iommu_ops, शून्य);
	पूर्ण
	up_पढ़ो(&dmar_global_lock);

	iommu_set_dma_strict(पूर्णांकel_iommu_strict);
	bus_set_iommu(&pci_bus_type, &पूर्णांकel_iommu_ops);
	अगर (si_करोमुख्य && !hw_pass_through)
		रेजिस्टर_memory_notअगरier(&पूर्णांकel_iommu_memory_nb);

	करोwn_पढ़ो(&dmar_global_lock);
	अगर (probe_acpi_namespace_devices())
		pr_warn("ACPI name space devices didn't probe correctly\n");

	/* Finally, we enable the DMA remapping hardware. */
	क्रम_each_iommu(iommu, drhd) अणु
		अगर (!drhd->ignored && !translation_pre_enabled(iommu))
			iommu_enable_translation(iommu);

		iommu_disable_protect_mem_regions(iommu);
	पूर्ण
	up_पढ़ो(&dmar_global_lock);

	pr_info("Intel(R) Virtualization Technology for Directed I/O\n");

	पूर्णांकel_iommu_enabled = 1;

	वापस 0;

out_मुक्त_dmar:
	पूर्णांकel_iommu_मुक्त_dmars();
	up_ग_लिखो(&dmar_global_lock);
	iommu_निकास_mempool();
	वापस ret;
पूर्ण

अटल पूर्णांक करोमुख्य_context_clear_one_cb(काष्ठा pci_dev *pdev, u16 alias, व्योम *opaque)
अणु
	काष्ठा पूर्णांकel_iommu *iommu = opaque;

	करोमुख्य_context_clear_one(iommu, PCI_BUS_NUM(alias), alias & 0xff);
	वापस 0;
पूर्ण

/*
 * NB - पूर्णांकel-iommu lacks any sort of reference counting क्रम the users of
 * dependent devices.  If multiple endpoपूर्णांकs have पूर्णांकersecting dependent
 * devices, unbinding the driver from any one of them will possibly leave
 * the others unable to operate.
 */
अटल व्योम करोमुख्य_context_clear(काष्ठा पूर्णांकel_iommu *iommu, काष्ठा device *dev)
अणु
	अगर (!iommu || !dev || !dev_is_pci(dev))
		वापस;

	pci_क्रम_each_dma_alias(to_pci_dev(dev), &करोमुख्य_context_clear_one_cb, iommu);
पूर्ण

अटल व्योम __dmar_हटाओ_one_dev_info(काष्ठा device_करोमुख्य_info *info)
अणु
	काष्ठा dmar_करोमुख्य *करोमुख्य;
	काष्ठा पूर्णांकel_iommu *iommu;
	अचिन्हित दीर्घ flags;

	निश्चित_spin_locked(&device_करोमुख्य_lock);

	अगर (WARN_ON(!info))
		वापस;

	iommu = info->iommu;
	करोमुख्य = info->करोमुख्य;

	अगर (info->dev) अणु
		अगर (dev_is_pci(info->dev) && sm_supported(iommu))
			पूर्णांकel_pasid_tear_करोwn_entry(iommu, info->dev,
					PASID_RID2PASID, false);

		iommu_disable_dev_iotlb(info);
		अगर (!dev_is_real_dma_subdevice(info->dev))
			करोमुख्य_context_clear(iommu, info->dev);
		पूर्णांकel_pasid_मुक्त_table(info->dev);
	पूर्ण

	unlink_करोमुख्य_info(info);

	spin_lock_irqsave(&iommu->lock, flags);
	करोमुख्य_detach_iommu(करोमुख्य, iommu);
	spin_unlock_irqrestore(&iommu->lock, flags);

	मुक्त_devinfo_mem(info);
पूर्ण

अटल व्योम dmar_हटाओ_one_dev_info(काष्ठा device *dev)
अणु
	काष्ठा device_करोमुख्य_info *info;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&device_करोमुख्य_lock, flags);
	info = get_करोमुख्य_info(dev);
	अगर (info)
		__dmar_हटाओ_one_dev_info(info);
	spin_unlock_irqrestore(&device_करोमुख्य_lock, flags);
पूर्ण

अटल पूर्णांक md_करोमुख्य_init(काष्ठा dmar_करोमुख्य *करोमुख्य, पूर्णांक guest_width)
अणु
	पूर्णांक adjust_width;

	/* calculate AGAW */
	करोमुख्य->gaw = guest_width;
	adjust_width = guestwidth_to_adjustwidth(guest_width);
	करोमुख्य->agaw = width_to_agaw(adjust_width);

	करोमुख्य->iommu_coherency = 0;
	करोमुख्य->iommu_snooping = 0;
	करोमुख्य->iommu_superpage = 0;
	करोमुख्य->max_addr = 0;

	/* always allocate the top pgd */
	करोमुख्य->pgd = (काष्ठा dma_pte *)alloc_pgtable_page(करोमुख्य->nid);
	अगर (!करोमुख्य->pgd)
		वापस -ENOMEM;
	करोमुख्य_flush_cache(करोमुख्य, करोमुख्य->pgd, PAGE_SIZE);
	वापस 0;
पूर्ण

अटल काष्ठा iommu_करोमुख्य *पूर्णांकel_iommu_करोमुख्य_alloc(अचिन्हित type)
अणु
	काष्ठा dmar_करोमुख्य *dmar_करोमुख्य;
	काष्ठा iommu_करोमुख्य *करोमुख्य;

	चयन (type) अणु
	हाल IOMMU_DOMAIN_DMA:
	हाल IOMMU_DOMAIN_UNMANAGED:
		dmar_करोमुख्य = alloc_करोमुख्य(0);
		अगर (!dmar_करोमुख्य) अणु
			pr_err("Can't allocate dmar_domain\n");
			वापस शून्य;
		पूर्ण
		अगर (md_करोमुख्य_init(dmar_करोमुख्य, DEFAULT_DOMAIN_ADDRESS_WIDTH)) अणु
			pr_err("Domain initialization failed\n");
			करोमुख्य_निकास(dmar_करोमुख्य);
			वापस शून्य;
		पूर्ण

		अगर (type == IOMMU_DOMAIN_DMA &&
		    iommu_get_dma_cookie(&dmar_करोमुख्य->करोमुख्य))
			वापस शून्य;

		करोमुख्य = &dmar_करोमुख्य->करोमुख्य;
		करोमुख्य->geometry.aperture_start = 0;
		करोमुख्य->geometry.aperture_end   =
				__DOMAIN_MAX_ADDR(dmar_करोमुख्य->gaw);
		करोमुख्य->geometry.क्रमce_aperture = true;

		वापस करोमुख्य;
	हाल IOMMU_DOMAIN_IDENTITY:
		वापस &si_करोमुख्य->करोमुख्य;
	शेष:
		वापस शून्य;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम पूर्णांकel_iommu_करोमुख्य_मुक्त(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	अगर (करोमुख्य != &si_करोमुख्य->करोमुख्य)
		करोमुख्य_निकास(to_dmar_करोमुख्य(करोमुख्य));
पूर्ण

/*
 * Check whether a @करोमुख्य could be attached to the @dev through the
 * aux-करोमुख्य attach/detach APIs.
 */
अटल अंतरभूत bool
is_aux_करोमुख्य(काष्ठा device *dev, काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा device_करोमुख्य_info *info = get_करोमुख्य_info(dev);

	वापस info && info->auxd_enabled &&
			करोमुख्य->type == IOMMU_DOMAIN_UNMANAGED;
पूर्ण

अटल अंतरभूत काष्ठा subdev_करोमुख्य_info *
lookup_subdev_info(काष्ठा dmar_करोमुख्य *करोमुख्य, काष्ठा device *dev)
अणु
	काष्ठा subdev_करोमुख्य_info *sinfo;

	अगर (!list_empty(&करोमुख्य->subdevices)) अणु
		list_क्रम_each_entry(sinfo, &करोमुख्य->subdevices, link_करोमुख्य) अणु
			अगर (sinfo->pdev == dev)
				वापस sinfo;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक auxiliary_link_device(काष्ठा dmar_करोमुख्य *करोमुख्य,
				 काष्ठा device *dev)
अणु
	काष्ठा device_करोमुख्य_info *info = get_करोमुख्य_info(dev);
	काष्ठा subdev_करोमुख्य_info *sinfo = lookup_subdev_info(करोमुख्य, dev);

	निश्चित_spin_locked(&device_करोमुख्य_lock);
	अगर (WARN_ON(!info))
		वापस -EINVAL;

	अगर (!sinfo) अणु
		sinfo = kzalloc(माप(*sinfo), GFP_ATOMIC);
		अगर (!sinfo)
			वापस -ENOMEM;
		sinfo->करोमुख्य = करोमुख्य;
		sinfo->pdev = dev;
		list_add(&sinfo->link_phys, &info->subdevices);
		list_add(&sinfo->link_करोमुख्य, &करोमुख्य->subdevices);
	पूर्ण

	वापस ++sinfo->users;
पूर्ण

अटल पूर्णांक auxiliary_unlink_device(काष्ठा dmar_करोमुख्य *करोमुख्य,
				   काष्ठा device *dev)
अणु
	काष्ठा device_करोमुख्य_info *info = get_करोमुख्य_info(dev);
	काष्ठा subdev_करोमुख्य_info *sinfo = lookup_subdev_info(करोमुख्य, dev);
	पूर्णांक ret;

	निश्चित_spin_locked(&device_करोमुख्य_lock);
	अगर (WARN_ON(!info || !sinfo || sinfo->users <= 0))
		वापस -EINVAL;

	ret = --sinfo->users;
	अगर (!ret) अणु
		list_del(&sinfo->link_phys);
		list_del(&sinfo->link_करोमुख्य);
		kमुक्त(sinfo);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक aux_करोमुख्य_add_dev(काष्ठा dmar_करोमुख्य *करोमुख्य,
			      काष्ठा device *dev)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	काष्ठा पूर्णांकel_iommu *iommu;

	iommu = device_to_iommu(dev, शून्य, शून्य);
	अगर (!iommu)
		वापस -ENODEV;

	अगर (करोमुख्य->शेष_pasid <= 0) अणु
		u32 pasid;

		/* No निजी data needed क्रम the शेष pasid */
		pasid = ioasid_alloc(शून्य, PASID_MIN,
				     pci_max_pasids(to_pci_dev(dev)) - 1,
				     शून्य);
		अगर (pasid == INVALID_IOASID) अणु
			pr_err("Can't allocate default pasid\n");
			वापस -ENODEV;
		पूर्ण
		करोमुख्य->शेष_pasid = pasid;
	पूर्ण

	spin_lock_irqsave(&device_करोमुख्य_lock, flags);
	ret = auxiliary_link_device(करोमुख्य, dev);
	अगर (ret <= 0)
		जाओ link_failed;

	/*
	 * Subdevices from the same physical device can be attached to the
	 * same करोमुख्य. For such हालs, only the first subdevice attachment
	 * needs to go through the full steps in this function. So अगर ret >
	 * 1, just जाओ out.
	 */
	अगर (ret > 1)
		जाओ out;

	/*
	 * iommu->lock must be held to attach करोमुख्य to iommu and setup the
	 * pasid entry क्रम second level translation.
	 */
	spin_lock(&iommu->lock);
	ret = करोमुख्य_attach_iommu(करोमुख्य, iommu);
	अगर (ret)
		जाओ attach_failed;

	/* Setup the PASID entry क्रम mediated devices: */
	अगर (करोमुख्य_use_first_level(करोमुख्य))
		ret = करोमुख्य_setup_first_level(iommu, करोमुख्य, dev,
					       करोमुख्य->शेष_pasid);
	अन्यथा
		ret = पूर्णांकel_pasid_setup_second_level(iommu, करोमुख्य, dev,
						     करोमुख्य->शेष_pasid);
	अगर (ret)
		जाओ table_failed;

	spin_unlock(&iommu->lock);
out:
	spin_unlock_irqrestore(&device_करोमुख्य_lock, flags);

	वापस 0;

table_failed:
	करोमुख्य_detach_iommu(करोमुख्य, iommu);
attach_failed:
	spin_unlock(&iommu->lock);
	auxiliary_unlink_device(करोमुख्य, dev);
link_failed:
	spin_unlock_irqrestore(&device_करोमुख्य_lock, flags);
	अगर (list_empty(&करोमुख्य->subdevices) && करोमुख्य->शेष_pasid > 0)
		ioasid_put(करोमुख्य->शेष_pasid);

	वापस ret;
पूर्ण

अटल व्योम aux_करोमुख्य_हटाओ_dev(काष्ठा dmar_करोमुख्य *करोमुख्य,
				  काष्ठा device *dev)
अणु
	काष्ठा device_करोमुख्य_info *info;
	काष्ठा पूर्णांकel_iommu *iommu;
	अचिन्हित दीर्घ flags;

	अगर (!is_aux_करोमुख्य(dev, &करोमुख्य->करोमुख्य))
		वापस;

	spin_lock_irqsave(&device_करोमुख्य_lock, flags);
	info = get_करोमुख्य_info(dev);
	iommu = info->iommu;

	अगर (!auxiliary_unlink_device(करोमुख्य, dev)) अणु
		spin_lock(&iommu->lock);
		पूर्णांकel_pasid_tear_करोwn_entry(iommu, dev,
					    करोमुख्य->शेष_pasid, false);
		करोमुख्य_detach_iommu(करोमुख्य, iommu);
		spin_unlock(&iommu->lock);
	पूर्ण

	spin_unlock_irqrestore(&device_करोमुख्य_lock, flags);

	अगर (list_empty(&करोमुख्य->subdevices) && करोमुख्य->शेष_pasid > 0)
		ioasid_put(करोमुख्य->शेष_pasid);
पूर्ण

अटल पूर्णांक prepare_करोमुख्य_attach_device(काष्ठा iommu_करोमुख्य *करोमुख्य,
					काष्ठा device *dev)
अणु
	काष्ठा dmar_करोमुख्य *dmar_करोमुख्य = to_dmar_करोमुख्य(करोमुख्य);
	काष्ठा पूर्णांकel_iommu *iommu;
	पूर्णांक addr_width;

	iommu = device_to_iommu(dev, शून्य, शून्य);
	अगर (!iommu)
		वापस -ENODEV;

	/* check अगर this iommu agaw is sufficient क्रम max mapped address */
	addr_width = agaw_to_width(iommu->agaw);
	अगर (addr_width > cap_mgaw(iommu->cap))
		addr_width = cap_mgaw(iommu->cap);

	अगर (dmar_करोमुख्य->max_addr > (1LL << addr_width)) अणु
		dev_err(dev, "%s: iommu width (%d) is not "
		        "sufficient for the mapped address (%llx)\n",
		        __func__, addr_width, dmar_करोमुख्य->max_addr);
		वापस -EFAULT;
	पूर्ण
	dmar_करोमुख्य->gaw = addr_width;

	/*
	 * Knock out extra levels of page tables अगर necessary
	 */
	जबतक (iommu->agaw < dmar_करोमुख्य->agaw) अणु
		काष्ठा dma_pte *pte;

		pte = dmar_करोमुख्य->pgd;
		अगर (dma_pte_present(pte)) अणु
			dmar_करोमुख्य->pgd = (काष्ठा dma_pte *)
				phys_to_virt(dma_pte_addr(pte));
			मुक्त_pgtable_page(pte);
		पूर्ण
		dmar_करोमुख्य->agaw--;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_iommu_attach_device(काष्ठा iommu_करोमुख्य *करोमुख्य,
				     काष्ठा device *dev)
अणु
	पूर्णांक ret;

	अगर (करोमुख्य->type == IOMMU_DOMAIN_UNMANAGED &&
	    device_is_rmrr_locked(dev)) अणु
		dev_warn(dev, "Device is ineligible for IOMMU domain attach due to platform RMRR requirement.  Contact your platform vendor.\n");
		वापस -EPERM;
	पूर्ण

	अगर (is_aux_करोमुख्य(dev, करोमुख्य))
		वापस -EPERM;

	/* normally dev is not mapped */
	अगर (unlikely(करोमुख्य_context_mapped(dev))) अणु
		काष्ठा dmar_करोमुख्य *old_करोमुख्य;

		old_करोमुख्य = find_करोमुख्य(dev);
		अगर (old_करोमुख्य)
			dmar_हटाओ_one_dev_info(dev);
	पूर्ण

	ret = prepare_करोमुख्य_attach_device(करोमुख्य, dev);
	अगर (ret)
		वापस ret;

	वापस करोमुख्य_add_dev_info(to_dmar_करोमुख्य(करोमुख्य), dev);
पूर्ण

अटल पूर्णांक पूर्णांकel_iommu_aux_attach_device(काष्ठा iommu_करोमुख्य *करोमुख्य,
					 काष्ठा device *dev)
अणु
	पूर्णांक ret;

	अगर (!is_aux_करोमुख्य(dev, करोमुख्य))
		वापस -EPERM;

	ret = prepare_करोमुख्य_attach_device(करोमुख्य, dev);
	अगर (ret)
		वापस ret;

	वापस aux_करोमुख्य_add_dev(to_dmar_करोमुख्य(करोमुख्य), dev);
पूर्ण

अटल व्योम पूर्णांकel_iommu_detach_device(काष्ठा iommu_करोमुख्य *करोमुख्य,
				      काष्ठा device *dev)
अणु
	dmar_हटाओ_one_dev_info(dev);
पूर्ण

अटल व्योम पूर्णांकel_iommu_aux_detach_device(काष्ठा iommu_करोमुख्य *करोमुख्य,
					  काष्ठा device *dev)
अणु
	aux_करोमुख्य_हटाओ_dev(to_dmar_करोमुख्य(करोमुख्य), dev);
पूर्ण

#अगर_घोषित CONFIG_INTEL_IOMMU_SVM
/*
 * 2D array क्रम converting and sanitizing IOMMU generic TLB granularity to
 * VT-d granularity. Invalidation is typically included in the unmap operation
 * as a result of DMA or VFIO unmap. However, क्रम asचिन्हित devices guest
 * owns the first level page tables. Invalidations of translation caches in the
 * guest are trapped and passed करोwn to the host.
 *
 * vIOMMU in the guest will only expose first level page tables, thereक्रमe
 * we करो not support IOTLB granularity क्रम request without PASID (second level).
 *
 * For example, to find the VT-d granularity encoding क्रम IOTLB
 * type and page selective granularity within PASID:
 * X: indexed by iommu cache type
 * Y: indexed by क्रमागत iommu_inv_granularity
 * [IOMMU_CACHE_INV_TYPE_IOTLB][IOMMU_INV_GRANU_ADDR]
 */

अटल स्थिर पूर्णांक
inv_type_granu_table[IOMMU_CACHE_INV_TYPE_NR][IOMMU_INV_GRANU_NR] = अणु
	/*
	 * PASID based IOTLB invalidation: PASID selective (per PASID),
	 * page selective (address granularity)
	 */
	अणु-EINVAL, QI_GRAN_NONG_PASID, QI_GRAN_PSI_PASIDपूर्ण,
	/* PASID based dev TLBs */
	अणु-EINVAL, -EINVAL, QI_DEV_IOTLB_GRAN_PASID_SELपूर्ण,
	/* PASID cache */
	अणु-EINVAL, -EINVAL, -EINVALपूर्ण
पूर्ण;

अटल अंतरभूत पूर्णांक to_vtd_granularity(पूर्णांक type, पूर्णांक granu)
अणु
	वापस inv_type_granu_table[type][granu];
पूर्ण

अटल अंतरभूत u64 to_vtd_size(u64 granu_size, u64 nr_granules)
अणु
	u64 nr_pages = (granu_size * nr_granules) >> VTD_PAGE_SHIFT;

	/* VT-d size is encoded as 2^size of 4K pages, 0 क्रम 4k, 9 क्रम 2MB, etc.
	 * IOMMU cache invalidate API passes granu_size in bytes, and number of
	 * granu size in contiguous memory.
	 */
	वापस order_base_2(nr_pages);
पूर्ण

अटल पूर्णांक
पूर्णांकel_iommu_sva_invalidate(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev,
			   काष्ठा iommu_cache_invalidate_info *inv_info)
अणु
	काष्ठा dmar_करोमुख्य *dmar_करोमुख्य = to_dmar_करोमुख्य(करोमुख्य);
	काष्ठा device_करोमुख्य_info *info;
	काष्ठा पूर्णांकel_iommu *iommu;
	अचिन्हित दीर्घ flags;
	पूर्णांक cache_type;
	u8 bus, devfn;
	u16 did, sid;
	पूर्णांक ret = 0;
	u64 size = 0;

	अगर (!inv_info || !dmar_करोमुख्य)
		वापस -EINVAL;

	अगर (!dev || !dev_is_pci(dev))
		वापस -ENODEV;

	iommu = device_to_iommu(dev, &bus, &devfn);
	अगर (!iommu)
		वापस -ENODEV;

	अगर (!(dmar_करोमुख्य->flags & DOMAIN_FLAG_NESTING_MODE))
		वापस -EINVAL;

	spin_lock_irqsave(&device_करोमुख्य_lock, flags);
	spin_lock(&iommu->lock);
	info = get_करोमुख्य_info(dev);
	अगर (!info) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण
	did = dmar_करोमुख्य->iommu_did[iommu->seq_id];
	sid = PCI_DEVID(bus, devfn);

	/* Size is only valid in address selective invalidation */
	अगर (inv_info->granularity == IOMMU_INV_GRANU_ADDR)
		size = to_vtd_size(inv_info->granu.addr_info.granule_size,
				   inv_info->granu.addr_info.nb_granules);

	क्रम_each_set_bit(cache_type,
			 (अचिन्हित दीर्घ *)&inv_info->cache,
			 IOMMU_CACHE_INV_TYPE_NR) अणु
		पूर्णांक granu = 0;
		u64 pasid = 0;
		u64 addr = 0;

		granu = to_vtd_granularity(cache_type, inv_info->granularity);
		अगर (granu == -EINVAL) अणु
			pr_err_ratelimited("Invalid cache type and granu combination %d/%d\n",
					   cache_type, inv_info->granularity);
			अवरोध;
		पूर्ण

		/*
		 * PASID is stored in dअगरferent locations based on the
		 * granularity.
		 */
		अगर (inv_info->granularity == IOMMU_INV_GRANU_PASID &&
		    (inv_info->granu.pasid_info.flags & IOMMU_INV_PASID_FLAGS_PASID))
			pasid = inv_info->granu.pasid_info.pasid;
		अन्यथा अगर (inv_info->granularity == IOMMU_INV_GRANU_ADDR &&
			 (inv_info->granu.addr_info.flags & IOMMU_INV_ADDR_FLAGS_PASID))
			pasid = inv_info->granu.addr_info.pasid;

		चयन (BIT(cache_type)) अणु
		हाल IOMMU_CACHE_INV_TYPE_IOTLB:
			/* HW will ignore LSB bits based on address mask */
			अगर (inv_info->granularity == IOMMU_INV_GRANU_ADDR &&
			    size &&
			    (inv_info->granu.addr_info.addr & ((BIT(VTD_PAGE_SHIFT + size)) - 1))) अणु
				pr_err_ratelimited("User address not aligned, 0x%llx, size order %llu\n",
						   inv_info->granu.addr_info.addr, size);
			पूर्ण

			/*
			 * If granu is PASID-selective, address is ignored.
			 * We use npages = -1 to indicate that.
			 */
			qi_flush_piotlb(iommu, did, pasid,
					mm_to_dma_pfn(inv_info->granu.addr_info.addr),
					(granu == QI_GRAN_NONG_PASID) ? -1 : 1 << size,
					inv_info->granu.addr_info.flags & IOMMU_INV_ADDR_FLAGS_LEAF);

			अगर (!info->ats_enabled)
				अवरोध;
			/*
			 * Always flush device IOTLB अगर ATS is enabled. vIOMMU
			 * in the guest may assume IOTLB flush is inclusive,
			 * which is more efficient.
			 */
			fallthrough;
		हाल IOMMU_CACHE_INV_TYPE_DEV_IOTLB:
			/*
			 * PASID based device TLB invalidation करोes not support
			 * IOMMU_INV_GRANU_PASID granularity but only supports
			 * IOMMU_INV_GRANU_ADDR.
			 * The equivalent of that is we set the size to be the
			 * entire range of 64 bit. User only provides PASID info
			 * without address info. So we set addr to 0.
			 */
			अगर (inv_info->granularity == IOMMU_INV_GRANU_PASID) अणु
				size = 64 - VTD_PAGE_SHIFT;
				addr = 0;
			पूर्ण अन्यथा अगर (inv_info->granularity == IOMMU_INV_GRANU_ADDR) अणु
				addr = inv_info->granu.addr_info.addr;
			पूर्ण

			अगर (info->ats_enabled)
				qi_flush_dev_iotlb_pasid(iommu, sid,
						info->pfsid, pasid,
						info->ats_qdep, addr,
						size);
			अन्यथा
				pr_warn_ratelimited("Passdown device IOTLB flush w/o ATS!\n");
			अवरोध;
		शेष:
			dev_err_ratelimited(dev, "Unsupported IOMMU invalidation type %d\n",
					    cache_type);
			ret = -EINVAL;
		पूर्ण
	पूर्ण
out_unlock:
	spin_unlock(&iommu->lock);
	spin_unlock_irqrestore(&device_करोमुख्य_lock, flags);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक पूर्णांकel_iommu_map(काष्ठा iommu_करोमुख्य *करोमुख्य,
			   अचिन्हित दीर्घ iova, phys_addr_t hpa,
			   माप_प्रकार size, पूर्णांक iommu_prot, gfp_t gfp)
अणु
	काष्ठा dmar_करोमुख्य *dmar_करोमुख्य = to_dmar_करोमुख्य(करोमुख्य);
	u64 max_addr;
	पूर्णांक prot = 0;

	अगर (iommu_prot & IOMMU_READ)
		prot |= DMA_PTE_READ;
	अगर (iommu_prot & IOMMU_WRITE)
		prot |= DMA_PTE_WRITE;
	अगर ((iommu_prot & IOMMU_CACHE) && dmar_करोमुख्य->iommu_snooping)
		prot |= DMA_PTE_SNP;

	max_addr = iova + size;
	अगर (dmar_करोमुख्य->max_addr < max_addr) अणु
		u64 end;

		/* check अगर minimum agaw is sufficient क्रम mapped address */
		end = __DOMAIN_MAX_ADDR(dmar_करोमुख्य->gaw) + 1;
		अगर (end < max_addr) अणु
			pr_err("%s: iommu width (%d) is not "
			       "sufficient for the mapped address (%llx)\n",
			       __func__, dmar_करोमुख्य->gaw, max_addr);
			वापस -EFAULT;
		पूर्ण
		dmar_करोमुख्य->max_addr = max_addr;
	पूर्ण
	/* Round up size to next multiple of PAGE_SIZE, अगर it and
	   the low bits of hpa would take us onto the next page */
	size = aligned_nrpages(hpa, size);
	वापस __करोमुख्य_mapping(dmar_करोमुख्य, iova >> VTD_PAGE_SHIFT,
				hpa >> VTD_PAGE_SHIFT, size, prot);
पूर्ण

अटल माप_प्रकार पूर्णांकel_iommu_unmap(काष्ठा iommu_करोमुख्य *करोमुख्य,
				अचिन्हित दीर्घ iova, माप_प्रकार size,
				काष्ठा iommu_iotlb_gather *gather)
अणु
	काष्ठा dmar_करोमुख्य *dmar_करोमुख्य = to_dmar_करोमुख्य(करोमुख्य);
	अचिन्हित दीर्घ start_pfn, last_pfn;
	पूर्णांक level = 0;

	/* Cope with horrid API which requires us to unmap more than the
	   size argument अगर it happens to be a large-page mapping. */
	BUG_ON(!pfn_to_dma_pte(dmar_करोमुख्य, iova >> VTD_PAGE_SHIFT, &level));

	अगर (size < VTD_PAGE_SIZE << level_to_offset_bits(level))
		size = VTD_PAGE_SIZE << level_to_offset_bits(level);

	start_pfn = iova >> VTD_PAGE_SHIFT;
	last_pfn = (iova + size - 1) >> VTD_PAGE_SHIFT;

	gather->मुक्तlist = करोमुख्य_unmap(dmar_करोमुख्य, start_pfn,
					last_pfn, gather->मुक्तlist);

	अगर (dmar_करोमुख्य->max_addr == iova + size)
		dmar_करोमुख्य->max_addr = iova;

	iommu_iotlb_gather_add_page(करोमुख्य, gather, iova, size);

	वापस size;
पूर्ण

अटल व्योम पूर्णांकel_iommu_tlb_sync(काष्ठा iommu_करोमुख्य *करोमुख्य,
				 काष्ठा iommu_iotlb_gather *gather)
अणु
	काष्ठा dmar_करोमुख्य *dmar_करोमुख्य = to_dmar_करोमुख्य(करोमुख्य);
	अचिन्हित दीर्घ iova_pfn = IOVA_PFN(gather->start);
	माप_प्रकार size = gather->end - gather->start;
	अचिन्हित दीर्घ start_pfn;
	अचिन्हित दीर्घ nrpages;
	पूर्णांक iommu_id;

	nrpages = aligned_nrpages(gather->start, size);
	start_pfn = mm_to_dma_pfn(iova_pfn);

	क्रम_each_करोमुख्य_iommu(iommu_id, dmar_करोमुख्य)
		iommu_flush_iotlb_psi(g_iommus[iommu_id], dmar_करोमुख्य,
				      start_pfn, nrpages, !gather->मुक्तlist, 0);

	dma_मुक्त_pagelist(gather->मुक्तlist);
पूर्ण

अटल phys_addr_t पूर्णांकel_iommu_iova_to_phys(काष्ठा iommu_करोमुख्य *करोमुख्य,
					    dma_addr_t iova)
अणु
	काष्ठा dmar_करोमुख्य *dmar_करोमुख्य = to_dmar_करोमुख्य(करोमुख्य);
	काष्ठा dma_pte *pte;
	पूर्णांक level = 0;
	u64 phys = 0;

	pte = pfn_to_dma_pte(dmar_करोमुख्य, iova >> VTD_PAGE_SHIFT, &level);
	अगर (pte && dma_pte_present(pte))
		phys = dma_pte_addr(pte) +
			(iova & (BIT_MASK(level_to_offset_bits(level) +
						VTD_PAGE_SHIFT) - 1));

	वापस phys;
पूर्ण

अटल bool पूर्णांकel_iommu_capable(क्रमागत iommu_cap cap)
अणु
	अगर (cap == IOMMU_CAP_CACHE_COHERENCY)
		वापस करोमुख्य_update_iommu_snooping(शून्य) == 1;
	अगर (cap == IOMMU_CAP_INTR_REMAP)
		वापस irq_remapping_enabled == 1;

	वापस false;
पूर्ण

अटल काष्ठा iommu_device *पूर्णांकel_iommu_probe_device(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_iommu *iommu;

	iommu = device_to_iommu(dev, शून्य, शून्य);
	अगर (!iommu)
		वापस ERR_PTR(-ENODEV);

	अगर (translation_pre_enabled(iommu))
		dev_iommu_priv_set(dev, DEFER_DEVICE_DOMAIN_INFO);

	वापस &iommu->iommu;
पूर्ण

अटल व्योम पूर्णांकel_iommu_release_device(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_iommu *iommu;

	iommu = device_to_iommu(dev, शून्य, शून्य);
	अगर (!iommu)
		वापस;

	dmar_हटाओ_one_dev_info(dev);

	set_dma_ops(dev, शून्य);
पूर्ण

अटल व्योम पूर्णांकel_iommu_probe_finalize(काष्ठा device *dev)
अणु
	dma_addr_t base = IOVA_START_PFN << VTD_PAGE_SHIFT;
	काष्ठा iommu_करोमुख्य *करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(dev);
	काष्ठा dmar_करोमुख्य *dmar_करोमुख्य = to_dmar_करोमुख्य(करोमुख्य);

	अगर (करोमुख्य && करोमुख्य->type == IOMMU_DOMAIN_DMA)
		iommu_setup_dma_ops(dev, base,
				    __DOMAIN_MAX_ADDR(dmar_करोमुख्य->gaw) - base);
	अन्यथा
		set_dma_ops(dev, शून्य);
पूर्ण

अटल व्योम पूर्णांकel_iommu_get_resv_regions(काष्ठा device *device,
					 काष्ठा list_head *head)
अणु
	पूर्णांक prot = DMA_PTE_READ | DMA_PTE_WRITE;
	काष्ठा iommu_resv_region *reg;
	काष्ठा dmar_rmrr_unit *rmrr;
	काष्ठा device *i_dev;
	पूर्णांक i;

	करोwn_पढ़ो(&dmar_global_lock);
	क्रम_each_rmrr_units(rmrr) अणु
		क्रम_each_active_dev_scope(rmrr->devices, rmrr->devices_cnt,
					  i, i_dev) अणु
			काष्ठा iommu_resv_region *resv;
			क्रमागत iommu_resv_type type;
			माप_प्रकार length;

			अगर (i_dev != device &&
			    !is_करोwnstream_to_pci_bridge(device, i_dev))
				जारी;

			length = rmrr->end_address - rmrr->base_address + 1;

			type = device_rmrr_is_relaxable(device) ?
				IOMMU_RESV_सूचीECT_RELAXABLE : IOMMU_RESV_सूचीECT;

			resv = iommu_alloc_resv_region(rmrr->base_address,
						       length, prot, type);
			अगर (!resv)
				अवरोध;

			list_add_tail(&resv->list, head);
		पूर्ण
	पूर्ण
	up_पढ़ो(&dmar_global_lock);

#अगर_घोषित CONFIG_INTEL_IOMMU_FLOPPY_WA
	अगर (dev_is_pci(device)) अणु
		काष्ठा pci_dev *pdev = to_pci_dev(device);

		अगर ((pdev->class >> 8) == PCI_CLASS_BRIDGE_ISA) अणु
			reg = iommu_alloc_resv_region(0, 1UL << 24, prot,
						   IOMMU_RESV_सूचीECT_RELAXABLE);
			अगर (reg)
				list_add_tail(&reg->list, head);
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_INTEL_IOMMU_FLOPPY_WA */

	reg = iommu_alloc_resv_region(IOAPIC_RANGE_START,
				      IOAPIC_RANGE_END - IOAPIC_RANGE_START + 1,
				      0, IOMMU_RESV_MSI);
	अगर (!reg)
		वापस;
	list_add_tail(&reg->list, head);
पूर्ण

पूर्णांक पूर्णांकel_iommu_enable_pasid(काष्ठा पूर्णांकel_iommu *iommu, काष्ठा device *dev)
अणु
	काष्ठा device_करोमुख्य_info *info;
	काष्ठा context_entry *context;
	काष्ठा dmar_करोमुख्य *करोमुख्य;
	अचिन्हित दीर्घ flags;
	u64 ctx_lo;
	पूर्णांक ret;

	करोमुख्य = find_करोमुख्य(dev);
	अगर (!करोमुख्य)
		वापस -EINVAL;

	spin_lock_irqsave(&device_करोमुख्य_lock, flags);
	spin_lock(&iommu->lock);

	ret = -EINVAL;
	info = get_करोमुख्य_info(dev);
	अगर (!info || !info->pasid_supported)
		जाओ out;

	context = iommu_context_addr(iommu, info->bus, info->devfn, 0);
	अगर (WARN_ON(!context))
		जाओ out;

	ctx_lo = context[0].lo;

	अगर (!(ctx_lo & CONTEXT_PASIDE)) अणु
		ctx_lo |= CONTEXT_PASIDE;
		context[0].lo = ctx_lo;
		wmb();
		iommu->flush.flush_context(iommu,
					   करोमुख्य->iommu_did[iommu->seq_id],
					   PCI_DEVID(info->bus, info->devfn),
					   DMA_CCMD_MASK_NOBIT,
					   DMA_CCMD_DEVICE_INVL);
	पूर्ण

	/* Enable PASID support in the device, अगर it wasn't alपढ़ोy */
	अगर (!info->pasid_enabled)
		iommu_enable_dev_iotlb(info);

	ret = 0;

 out:
	spin_unlock(&iommu->lock);
	spin_unlock_irqrestore(&device_करोमुख्य_lock, flags);

	वापस ret;
पूर्ण

अटल काष्ठा iommu_group *पूर्णांकel_iommu_device_group(काष्ठा device *dev)
अणु
	अगर (dev_is_pci(dev))
		वापस pci_device_group(dev);
	वापस generic_device_group(dev);
पूर्ण

अटल पूर्णांक पूर्णांकel_iommu_enable_auxd(काष्ठा device *dev)
अणु
	काष्ठा device_करोमुख्य_info *info;
	काष्ठा पूर्णांकel_iommu *iommu;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	iommu = device_to_iommu(dev, शून्य, शून्य);
	अगर (!iommu || dmar_disabled)
		वापस -EINVAL;

	अगर (!sm_supported(iommu) || !pasid_supported(iommu))
		वापस -EINVAL;

	ret = पूर्णांकel_iommu_enable_pasid(iommu, dev);
	अगर (ret)
		वापस -ENODEV;

	spin_lock_irqsave(&device_करोमुख्य_lock, flags);
	info = get_करोमुख्य_info(dev);
	info->auxd_enabled = 1;
	spin_unlock_irqrestore(&device_करोमुख्य_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_iommu_disable_auxd(काष्ठा device *dev)
अणु
	काष्ठा device_करोमुख्य_info *info;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&device_करोमुख्य_lock, flags);
	info = get_करोमुख्य_info(dev);
	अगर (!WARN_ON(!info))
		info->auxd_enabled = 0;
	spin_unlock_irqrestore(&device_करोमुख्य_lock, flags);

	वापस 0;
पूर्ण

/*
 * A PCI express designated venकरोr specअगरic extended capability is defined
 * in the section 3.7 of Intel scalable I/O भवization technical spec
 * क्रम प्रणाली software and tools to detect endpoपूर्णांक devices supporting the
 * Intel scalable IO भवization without host driver dependency.
 *
 * Returns the address of the matching extended capability काष्ठाure within
 * the device's PCI configuration space or 0 अगर the device करोes not support
 * it.
 */
अटल पूर्णांक siov_find_pci_dvsec(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक pos;
	u16 venकरोr, id;

	pos = pci_find_next_ext_capability(pdev, 0, 0x23);
	जबतक (pos) अणु
		pci_पढ़ो_config_word(pdev, pos + 4, &venकरोr);
		pci_पढ़ो_config_word(pdev, pos + 8, &id);
		अगर (venकरोr == PCI_VENDOR_ID_INTEL && id == 5)
			वापस pos;

		pos = pci_find_next_ext_capability(pdev, pos, 0x23);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool
पूर्णांकel_iommu_dev_has_feat(काष्ठा device *dev, क्रमागत iommu_dev_features feat)
अणु
	काष्ठा device_करोमुख्य_info *info = get_करोमुख्य_info(dev);

	अगर (feat == IOMMU_DEV_FEAT_AUX) अणु
		पूर्णांक ret;

		अगर (!dev_is_pci(dev) || dmar_disabled ||
		    !scalable_mode_support() || !pasid_mode_support())
			वापस false;

		ret = pci_pasid_features(to_pci_dev(dev));
		अगर (ret < 0)
			वापस false;

		वापस !!siov_find_pci_dvsec(to_pci_dev(dev));
	पूर्ण

	अगर (feat == IOMMU_DEV_FEAT_IOPF)
		वापस info && info->pri_supported;

	अगर (feat == IOMMU_DEV_FEAT_SVA)
		वापस info && (info->iommu->flags & VTD_FLAG_SVM_CAPABLE) &&
			info->pasid_supported && info->pri_supported &&
			info->ats_supported;

	वापस false;
पूर्ण

अटल पूर्णांक
पूर्णांकel_iommu_dev_enable_feat(काष्ठा device *dev, क्रमागत iommu_dev_features feat)
अणु
	अगर (feat == IOMMU_DEV_FEAT_AUX)
		वापस पूर्णांकel_iommu_enable_auxd(dev);

	अगर (feat == IOMMU_DEV_FEAT_IOPF)
		वापस पूर्णांकel_iommu_dev_has_feat(dev, feat) ? 0 : -ENODEV;

	अगर (feat == IOMMU_DEV_FEAT_SVA) अणु
		काष्ठा device_करोमुख्य_info *info = get_करोमुख्य_info(dev);

		अगर (!info)
			वापस -EINVAL;

		अगर (!info->pasid_enabled || !info->pri_enabled || !info->ats_enabled)
			वापस -EINVAL;

		अगर (info->iommu->flags & VTD_FLAG_SVM_CAPABLE)
			वापस 0;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक
पूर्णांकel_iommu_dev_disable_feat(काष्ठा device *dev, क्रमागत iommu_dev_features feat)
अणु
	अगर (feat == IOMMU_DEV_FEAT_AUX)
		वापस पूर्णांकel_iommu_disable_auxd(dev);

	वापस -ENODEV;
पूर्ण

अटल bool
पूर्णांकel_iommu_dev_feat_enabled(काष्ठा device *dev, क्रमागत iommu_dev_features feat)
अणु
	काष्ठा device_करोमुख्य_info *info = get_करोमुख्य_info(dev);

	अगर (feat == IOMMU_DEV_FEAT_AUX)
		वापस scalable_mode_support() && info && info->auxd_enabled;

	वापस false;
पूर्ण

अटल पूर्णांक
पूर्णांकel_iommu_aux_get_pasid(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev)
अणु
	काष्ठा dmar_करोमुख्य *dmar_करोमुख्य = to_dmar_करोमुख्य(करोमुख्य);

	वापस dmar_करोमुख्य->शेष_pasid > 0 ?
			dmar_करोमुख्य->शेष_pasid : -EINVAL;
पूर्ण

अटल bool पूर्णांकel_iommu_is_attach_deferred(काष्ठा iommu_करोमुख्य *करोमुख्य,
					   काष्ठा device *dev)
अणु
	वापस attach_deferred(dev);
पूर्ण

अटल पूर्णांक
पूर्णांकel_iommu_enable_nesting(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा dmar_करोमुख्य *dmar_करोमुख्य = to_dmar_करोमुख्य(करोमुख्य);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -ENODEV;

	spin_lock_irqsave(&device_करोमुख्य_lock, flags);
	अगर (nested_mode_support() && list_empty(&dmar_करोमुख्य->devices)) अणु
		dmar_करोमुख्य->flags |= DOMAIN_FLAG_NESTING_MODE;
		dmar_करोमुख्य->flags &= ~DOMAIN_FLAG_USE_FIRST_LEVEL;
		ret = 0;
	पूर्ण
	spin_unlock_irqrestore(&device_करोमुख्य_lock, flags);

	वापस ret;
पूर्ण

/*
 * Check that the device करोes not live on an बाह्यal facing PCI port that is
 * marked as untrusted. Such devices should not be able to apply quirks and
 * thus not be able to bypass the IOMMU restrictions.
 */
अटल bool risky_device(काष्ठा pci_dev *pdev)
अणु
	अगर (pdev->untrusted) अणु
		pci_info(pdev,
			 "Skipping IOMMU quirk for dev [%04X:%04X] on untrusted PCI link\n",
			 pdev->venकरोr, pdev->device);
		pci_info(pdev, "Please check with your BIOS/Platform vendor about this\n");
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम clflush_sync_map(काष्ठा dmar_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ clf_pfn,
			     अचिन्हित दीर्घ clf_pages)
अणु
	काष्ठा dma_pte *first_pte = शून्य, *pte = शून्य;
	अचिन्हित दीर्घ lvl_pages = 0;
	पूर्णांक level = 0;

	जबतक (clf_pages > 0) अणु
		अगर (!pte) अणु
			level = 0;
			pte = pfn_to_dma_pte(करोमुख्य, clf_pfn, &level);
			अगर (WARN_ON(!pte))
				वापस;
			first_pte = pte;
			lvl_pages = lvl_to_nr_pages(level);
		पूर्ण

		अगर (WARN_ON(!lvl_pages || clf_pages < lvl_pages))
			वापस;

		clf_pages -= lvl_pages;
		clf_pfn += lvl_pages;
		pte++;

		अगर (!clf_pages || first_pte_in_page(pte) ||
		    (level > 1 && clf_pages < lvl_pages)) अणु
			करोमुख्य_flush_cache(करोमुख्य, first_pte,
					   (व्योम *)pte - (व्योम *)first_pte);
			pte = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_iommu_iotlb_sync_map(काष्ठा iommu_करोमुख्य *करोमुख्य,
				       अचिन्हित दीर्घ iova, माप_प्रकार size)
अणु
	काष्ठा dmar_करोमुख्य *dmar_करोमुख्य = to_dmar_करोमुख्य(करोमुख्य);
	अचिन्हित दीर्घ pages = aligned_nrpages(iova, size);
	अचिन्हित दीर्घ pfn = iova >> VTD_PAGE_SHIFT;
	काष्ठा पूर्णांकel_iommu *iommu;
	पूर्णांक iommu_id;

	अगर (!dmar_करोमुख्य->iommu_coherency)
		clflush_sync_map(dmar_करोमुख्य, pfn, pages);

	क्रम_each_करोमुख्य_iommu(iommu_id, dmar_करोमुख्य) अणु
		iommu = g_iommus[iommu_id];
		__mapping_notअगरy_one(iommu, dmar_करोमुख्य, pfn, pages);
	पूर्ण
पूर्ण

स्थिर काष्ठा iommu_ops पूर्णांकel_iommu_ops = अणु
	.capable		= पूर्णांकel_iommu_capable,
	.करोमुख्य_alloc		= पूर्णांकel_iommu_करोमुख्य_alloc,
	.करोमुख्य_मुक्त		= पूर्णांकel_iommu_करोमुख्य_मुक्त,
	.enable_nesting		= पूर्णांकel_iommu_enable_nesting,
	.attach_dev		= पूर्णांकel_iommu_attach_device,
	.detach_dev		= पूर्णांकel_iommu_detach_device,
	.aux_attach_dev		= पूर्णांकel_iommu_aux_attach_device,
	.aux_detach_dev		= पूर्णांकel_iommu_aux_detach_device,
	.aux_get_pasid		= पूर्णांकel_iommu_aux_get_pasid,
	.map			= पूर्णांकel_iommu_map,
	.iotlb_sync_map		= पूर्णांकel_iommu_iotlb_sync_map,
	.unmap			= पूर्णांकel_iommu_unmap,
	.flush_iotlb_all        = पूर्णांकel_flush_iotlb_all,
	.iotlb_sync		= पूर्णांकel_iommu_tlb_sync,
	.iova_to_phys		= पूर्णांकel_iommu_iova_to_phys,
	.probe_device		= पूर्णांकel_iommu_probe_device,
	.probe_finalize		= पूर्णांकel_iommu_probe_finalize,
	.release_device		= पूर्णांकel_iommu_release_device,
	.get_resv_regions	= पूर्णांकel_iommu_get_resv_regions,
	.put_resv_regions	= generic_iommu_put_resv_regions,
	.device_group		= पूर्णांकel_iommu_device_group,
	.dev_has_feat		= पूर्णांकel_iommu_dev_has_feat,
	.dev_feat_enabled	= पूर्णांकel_iommu_dev_feat_enabled,
	.dev_enable_feat	= पूर्णांकel_iommu_dev_enable_feat,
	.dev_disable_feat	= पूर्णांकel_iommu_dev_disable_feat,
	.is_attach_deferred	= पूर्णांकel_iommu_is_attach_deferred,
	.def_करोमुख्य_type	= device_def_करोमुख्य_type,
	.pgsize_biपंचांगap		= INTEL_IOMMU_PGSIZES,
#अगर_घोषित CONFIG_INTEL_IOMMU_SVM
	.cache_invalidate	= पूर्णांकel_iommu_sva_invalidate,
	.sva_bind_gpasid	= पूर्णांकel_svm_bind_gpasid,
	.sva_unbind_gpasid	= पूर्णांकel_svm_unbind_gpasid,
	.sva_bind		= पूर्णांकel_svm_bind,
	.sva_unbind		= पूर्णांकel_svm_unbind,
	.sva_get_pasid		= पूर्णांकel_svm_get_pasid,
	.page_response		= पूर्णांकel_svm_page_response,
#पूर्ण_अगर
पूर्ण;

अटल व्योम quirk_iommu_igfx(काष्ठा pci_dev *dev)
अणु
	अगर (risky_device(dev))
		वापस;

	pci_info(dev, "Disabling IOMMU for graphics on this chipset\n");
	dmar_map_gfx = 0;
पूर्ण

/* G4x/GM45 पूर्णांकegrated gfx dmar support is totally busted. */
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x2a40, quirk_iommu_igfx);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x2e00, quirk_iommu_igfx);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x2e10, quirk_iommu_igfx);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x2e20, quirk_iommu_igfx);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x2e30, quirk_iommu_igfx);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x2e40, quirk_iommu_igfx);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x2e90, quirk_iommu_igfx);

/* Broadwell igfx malfunctions with dmar */
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x1606, quirk_iommu_igfx);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x160B, quirk_iommu_igfx);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x160E, quirk_iommu_igfx);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x1602, quirk_iommu_igfx);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x160A, quirk_iommu_igfx);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x160D, quirk_iommu_igfx);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x1616, quirk_iommu_igfx);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x161B, quirk_iommu_igfx);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x161E, quirk_iommu_igfx);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x1612, quirk_iommu_igfx);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x161A, quirk_iommu_igfx);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x161D, quirk_iommu_igfx);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x1626, quirk_iommu_igfx);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x162B, quirk_iommu_igfx);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x162E, quirk_iommu_igfx);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x1622, quirk_iommu_igfx);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x162A, quirk_iommu_igfx);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x162D, quirk_iommu_igfx);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x1636, quirk_iommu_igfx);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x163B, quirk_iommu_igfx);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x163E, quirk_iommu_igfx);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x1632, quirk_iommu_igfx);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x163A, quirk_iommu_igfx);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x163D, quirk_iommu_igfx);

अटल व्योम quirk_iommu_rwbf(काष्ठा pci_dev *dev)
अणु
	अगर (risky_device(dev))
		वापस;

	/*
	 * Mobile 4 Series Chipset neglects to set RWBF capability,
	 * but needs it. Same seems to hold क्रम the desktop versions.
	 */
	pci_info(dev, "Forcing write-buffer flush capability\n");
	rwbf_quirk = 1;
पूर्ण

DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x2a40, quirk_iommu_rwbf);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x2e00, quirk_iommu_rwbf);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x2e10, quirk_iommu_rwbf);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x2e20, quirk_iommu_rwbf);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x2e30, quirk_iommu_rwbf);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x2e40, quirk_iommu_rwbf);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x2e90, quirk_iommu_rwbf);

#घोषणा GGC 0x52
#घोषणा GGC_MEMORY_SIZE_MASK	(0xf << 8)
#घोषणा GGC_MEMORY_SIZE_NONE	(0x0 << 8)
#घोषणा GGC_MEMORY_SIZE_1M	(0x1 << 8)
#घोषणा GGC_MEMORY_SIZE_2M	(0x3 << 8)
#घोषणा GGC_MEMORY_VT_ENABLED	(0x8 << 8)
#घोषणा GGC_MEMORY_SIZE_2M_VT	(0x9 << 8)
#घोषणा GGC_MEMORY_SIZE_3M_VT	(0xa << 8)
#घोषणा GGC_MEMORY_SIZE_4M_VT	(0xb << 8)

अटल व्योम quirk_calpella_no_shaकरोw_gtt(काष्ठा pci_dev *dev)
अणु
	अचिन्हित लघु ggc;

	अगर (risky_device(dev))
		वापस;

	अगर (pci_पढ़ो_config_word(dev, GGC, &ggc))
		वापस;

	अगर (!(ggc & GGC_MEMORY_VT_ENABLED)) अणु
		pci_info(dev, "BIOS has allocated no shadow GTT; disabling IOMMU for graphics\n");
		dmar_map_gfx = 0;
	पूर्ण अन्यथा अगर (dmar_map_gfx) अणु
		/* we have to ensure the gfx device is idle beक्रमe we flush */
		pci_info(dev, "Disabling batched IOTLB flush on Ironlake\n");
		पूर्णांकel_iommu_strict = 1;
       पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x0040, quirk_calpella_no_shaकरोw_gtt);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x0044, quirk_calpella_no_shaकरोw_gtt);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x0062, quirk_calpella_no_shaकरोw_gtt);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x006a, quirk_calpella_no_shaकरोw_gtt);

अटल व्योम quirk_igfx_skip_te_disable(काष्ठा pci_dev *dev)
अणु
	अचिन्हित लघु ver;

	अगर (!IS_GFX_DEVICE(dev))
		वापस;

	ver = (dev->device >> 8) & 0xff;
	अगर (ver != 0x45 && ver != 0x46 && ver != 0x4c &&
	    ver != 0x4e && ver != 0x8a && ver != 0x98 &&
	    ver != 0x9a)
		वापस;

	अगर (risky_device(dev))
		वापस;

	pci_info(dev, "Skip IOMMU disabling for graphics\n");
	iommu_skip_te_disable = 1;
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, PCI_ANY_ID, quirk_igfx_skip_te_disable);

/* On Tylersburg chipsets, some BIOSes have been known to enable the
   ISOCH DMAR unit क्रम the Azalia sound device, but not give it any
   TLB entries, which causes it to deadlock. Check क्रम that.  We करो
   this in a function called from init_dmars(), instead of in a PCI
   quirk, because we करोn't want to prपूर्णांक the obnoxious "BIOS broken"
   message अगर VT-d is actually disabled.
*/
अटल व्योम __init check_tylersburg_isoch(व्योम)
अणु
	काष्ठा pci_dev *pdev;
	uपूर्णांक32_t vtisochctrl;

	/* If there's no Azalia in the प्रणाली anyway, क्रमget it. */
	pdev = pci_get_device(PCI_VENDOR_ID_INTEL, 0x3a3e, शून्य);
	अगर (!pdev)
		वापस;

	अगर (risky_device(pdev)) अणु
		pci_dev_put(pdev);
		वापस;
	पूर्ण

	pci_dev_put(pdev);

	/* System Management Registers. Might be hidden, in which हाल
	   we can't do the sanity check. But that's OK, because the
	   known-broken BIOSes _करोn't_ actually hide it, so far. */
	pdev = pci_get_device(PCI_VENDOR_ID_INTEL, 0x342e, शून्य);
	अगर (!pdev)
		वापस;

	अगर (risky_device(pdev)) अणु
		pci_dev_put(pdev);
		वापस;
	पूर्ण

	अगर (pci_पढ़ो_config_dword(pdev, 0x188, &vtisochctrl)) अणु
		pci_dev_put(pdev);
		वापस;
	पूर्ण

	pci_dev_put(pdev);

	/* If Azalia DMA is routed to the non-isoch DMAR unit, fine. */
	अगर (vtisochctrl & 1)
		वापस;

	/* Drop all bits other than the number of TLB entries */
	vtisochctrl &= 0x1c;

	/* If we have the recommended number of TLB entries (16), fine. */
	अगर (vtisochctrl == 0x10)
		वापस;

	/* Zero TLB entries? You get to ride the लघु bus to school. */
	अगर (!vtisochctrl) अणु
		WARN(1, "Your BIOS is broken; DMA routed to ISOCH DMAR unit but no TLB space.\n"
		     "BIOS vendor: %s; Ver: %s; Product Version: %s\n",
		     dmi_get_प्रणाली_info(DMI_BIOS_VENDOR),
		     dmi_get_प्रणाली_info(DMI_BIOS_VERSION),
		     dmi_get_प्रणाली_info(DMI_PRODUCT_VERSION));
		iommu_identity_mapping |= IDENTMAP_AZALIA;
		वापस;
	पूर्ण

	pr_warn("Recommended TLB entries for ISOCH unit is 16; your BIOS set %d\n",
	       vtisochctrl);
पूर्ण
