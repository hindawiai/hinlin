<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Extensible Firmware Interface
 *
 * Based on Extensible Firmware Interface Specअगरication version 2.4
 *
 * Copyright (C) 2013, 2014 Linaro Ltd.
 */

#समावेश <linux/efi.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/efi.h>

/*
 * Only regions of type EFI_RUNTIME_SERVICES_CODE need to be
 * executable, everything अन्यथा can be mapped with the XN bits
 * set. Also take the new (optional) RO/XP bits पूर्णांकo account.
 */
अटल __init pteval_t create_mapping_protection(efi_memory_desc_t *md)
अणु
	u64 attr = md->attribute;
	u32 type = md->type;

	अगर (type == EFI_MEMORY_MAPPED_IO)
		वापस PROT_DEVICE_nGnRE;

	अगर (WARN_ONCE(!PAGE_ALIGNED(md->phys_addr),
		      "UEFI Runtime regions are not aligned to 64 KB -- buggy firmware?"))
		/*
		 * If the region is not aligned to the page size of the OS, we
		 * can not use strict permissions, since that would also affect
		 * the mapping attributes of the adjacent regions.
		 */
		वापस pgprot_val(PAGE_KERNEL_EXEC);

	/* R-- */
	अगर ((attr & (EFI_MEMORY_XP | EFI_MEMORY_RO)) ==
	    (EFI_MEMORY_XP | EFI_MEMORY_RO))
		वापस pgprot_val(PAGE_KERNEL_RO);

	/* R-X */
	अगर (attr & EFI_MEMORY_RO)
		वापस pgprot_val(PAGE_KERNEL_ROX);

	/* RW- */
	अगर (((attr & (EFI_MEMORY_RP | EFI_MEMORY_WP | EFI_MEMORY_XP)) ==
	     EFI_MEMORY_XP) ||
	    type != EFI_RUNTIME_SERVICES_CODE)
		वापस pgprot_val(PAGE_KERNEL);

	/* RWX */
	वापस pgprot_val(PAGE_KERNEL_EXEC);
पूर्ण

/* we will fill this काष्ठाure from the stub, so करोn't put it in .bss */
काष्ठा screen_info screen_info __section(".data");

पूर्णांक __init efi_create_mapping(काष्ठा mm_काष्ठा *mm, efi_memory_desc_t *md)
अणु
	pteval_t prot_val = create_mapping_protection(md);
	bool page_mappings_only = (md->type == EFI_RUNTIME_SERVICES_CODE ||
				   md->type == EFI_RUNTIME_SERVICES_DATA);

	अगर (!PAGE_ALIGNED(md->phys_addr) ||
	    !PAGE_ALIGNED(md->num_pages << EFI_PAGE_SHIFT)) अणु
		/*
		 * If the end address of this region is not aligned to page
		 * size, the mapping is rounded up, and may end up sharing a
		 * page frame with the next UEFI memory region. If we create
		 * a block entry now, we may need to split it again when mapping
		 * the next region, and support क्रम that is going to be हटाओd
		 * from the MMU routines. So aव्योम block mappings altogether in
		 * that हाल.
		 */
		page_mappings_only = true;
	पूर्ण

	create_pgd_mapping(mm, md->phys_addr, md->virt_addr,
			   md->num_pages << EFI_PAGE_SHIFT,
			   __pgprot(prot_val | PTE_NG), page_mappings_only);
	वापस 0;
पूर्ण

अटल पूर्णांक __init set_permissions(pte_t *ptep, अचिन्हित दीर्घ addr, व्योम *data)
अणु
	efi_memory_desc_t *md = data;
	pte_t pte = READ_ONCE(*ptep);

	अगर (md->attribute & EFI_MEMORY_RO)
		pte = set_pte_bit(pte, __pgprot(PTE_RDONLY));
	अगर (md->attribute & EFI_MEMORY_XP)
		pte = set_pte_bit(pte, __pgprot(PTE_PXN));
	set_pte(ptep, pte);
	वापस 0;
पूर्ण

पूर्णांक __init efi_set_mapping_permissions(काष्ठा mm_काष्ठा *mm,
				       efi_memory_desc_t *md)
अणु
	BUG_ON(md->type != EFI_RUNTIME_SERVICES_CODE &&
	       md->type != EFI_RUNTIME_SERVICES_DATA);

	/*
	 * Calling apply_to_page_range() is only safe on regions that are
	 * guaranteed to be mapped करोwn to pages. Since we are only called
	 * क्रम regions that have been mapped using efi_create_mapping() above
	 * (and this is checked by the generic Memory Attributes table parsing
	 * routines), there is no need to check that again here.
	 */
	वापस apply_to_page_range(mm, md->virt_addr,
				   md->num_pages << EFI_PAGE_SHIFT,
				   set_permissions, md);
पूर्ण

/*
 * UpdateCapsule() depends on the प्रणाली being shutकरोwn via
 * ResetSystem().
 */
bool efi_घातeroff_required(व्योम)
अणु
	वापस efi_enabled(EFI_RUNTIME_SERVICES);
पूर्ण

यंत्रlinkage efi_status_t efi_handle_corrupted_x18(efi_status_t s, स्थिर अक्षर *f)
अणु
	pr_err_ratelimited(FW_BUG "register x18 corrupted by EFI %s\n", f);
	वापस s;
पूर्ण
