<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 Western Digital Corporation or its affiliates.
 * Adapted from arch/arm64/kernel/efi.c
 */

#समावेश <linux/efi.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/efi.h>
#समावेश <यंत्र/pgtable.h>
#समावेश <यंत्र/pgtable-bits.h>

/*
 * Only regions of type EFI_RUNTIME_SERVICES_CODE need to be
 * executable, everything अन्यथा can be mapped with the XN bits
 * set. Also take the new (optional) RO/XP bits पूर्णांकo account.
 */
अटल __init pgprot_t efimem_to_pgprot_map(efi_memory_desc_t *md)
अणु
	u64 attr = md->attribute;
	u32 type = md->type;

	अगर (type == EFI_MEMORY_MAPPED_IO)
		वापस PAGE_KERNEL;

	/* R-- */
	अगर ((attr & (EFI_MEMORY_XP | EFI_MEMORY_RO)) ==
	    (EFI_MEMORY_XP | EFI_MEMORY_RO))
		वापस PAGE_KERNEL_READ;

	/* R-X */
	अगर (attr & EFI_MEMORY_RO)
		वापस PAGE_KERNEL_READ_EXEC;

	/* RW- */
	अगर (((attr & (EFI_MEMORY_RP | EFI_MEMORY_WP | EFI_MEMORY_XP)) ==
	     EFI_MEMORY_XP) ||
	    type != EFI_RUNTIME_SERVICES_CODE)
		वापस PAGE_KERNEL;

	/* RWX */
	वापस PAGE_KERNEL_EXEC;
पूर्ण

पूर्णांक __init efi_create_mapping(काष्ठा mm_काष्ठा *mm, efi_memory_desc_t *md)
अणु
	pgprot_t prot = __pgprot(pgprot_val(efimem_to_pgprot_map(md)) &
				~(_PAGE_GLOBAL));
	पूर्णांक i;

	/* RISC-V maps one page at a समय */
	क्रम (i = 0; i < md->num_pages; i++)
		create_pgd_mapping(mm->pgd, md->virt_addr + i * PAGE_SIZE,
				   md->phys_addr + i * PAGE_SIZE,
				   PAGE_SIZE, prot);
	वापस 0;
पूर्ण

अटल पूर्णांक __init set_permissions(pte_t *ptep, अचिन्हित दीर्घ addr, व्योम *data)
अणु
	efi_memory_desc_t *md = data;
	pte_t pte = READ_ONCE(*ptep);
	अचिन्हित दीर्घ val;

	अगर (md->attribute & EFI_MEMORY_RO) अणु
		val = pte_val(pte) & ~_PAGE_WRITE;
		val = pte_val(pte) | _PAGE_READ;
		pte = __pte(val);
	पूर्ण
	अगर (md->attribute & EFI_MEMORY_XP) अणु
		val = pte_val(pte) & ~_PAGE_EXEC;
		pte = __pte(val);
	पूर्ण
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
