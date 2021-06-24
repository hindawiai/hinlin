<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Linaro Ltd <ard.biesheuvel@linaro.org>
 */

#समावेश <linux/efi.h>
#समावेश <यंत्र/efi.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mmu_context.h>

अटल पूर्णांक __init set_permissions(pte_t *ptep, अचिन्हित दीर्घ addr, व्योम *data)
अणु
	efi_memory_desc_t *md = data;
	pte_t pte = *ptep;

	अगर (md->attribute & EFI_MEMORY_RO)
		pte = set_pte_bit(pte, __pgprot(L_PTE_RDONLY));
	अगर (md->attribute & EFI_MEMORY_XP)
		pte = set_pte_bit(pte, __pgprot(L_PTE_XN));
	set_pte_ext(ptep, pte, PTE_EXT_NG);
	वापस 0;
पूर्ण

पूर्णांक __init efi_set_mapping_permissions(काष्ठा mm_काष्ठा *mm,
				       efi_memory_desc_t *md)
अणु
	अचिन्हित दीर्घ base, size;

	base = md->virt_addr;
	size = md->num_pages << EFI_PAGE_SHIFT;

	/*
	 * We can only use apply_to_page_range() अगर we can guarantee that the
	 * entire region was mapped using pages. This should be the हाल अगर the
	 * region करोes not cover any naturally aligned SECTION_SIZE sized
	 * blocks.
	 */
	अगर (round_करोwn(base + size, SECTION_SIZE) <
	    round_up(base, SECTION_SIZE) + SECTION_SIZE)
		वापस apply_to_page_range(mm, base, size, set_permissions, md);

	वापस 0;
पूर्ण

पूर्णांक __init efi_create_mapping(काष्ठा mm_काष्ठा *mm, efi_memory_desc_t *md)
अणु
	काष्ठा map_desc desc = अणु
		.भव	= md->virt_addr,
		.pfn		= __phys_to_pfn(md->phys_addr),
		.length		= md->num_pages * EFI_PAGE_SIZE,
	पूर्ण;

	/*
	 * Order is important here: memory regions may have all of the
	 * bits below set (and usually करो), so we check them in order of
	 * preference.
	 */
	अगर (md->attribute & EFI_MEMORY_WB)
		desc.type = MT_MEMORY_RWX;
	अन्यथा अगर (md->attribute & EFI_MEMORY_WT)
		desc.type = MT_MEMORY_RWX_NONCACHED;
	अन्यथा अगर (md->attribute & EFI_MEMORY_WC)
		desc.type = MT_DEVICE_WC;
	अन्यथा
		desc.type = MT_DEVICE;

	create_mapping_late(mm, &desc, true);

	/*
	 * If stricter permissions were specअगरied, apply them now.
	 */
	अगर (md->attribute & (EFI_MEMORY_RO | EFI_MEMORY_XP))
		वापस efi_set_mapping_permissions(mm, md);
	वापस 0;
पूर्ण
