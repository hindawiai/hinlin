<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2016 Linaro Ltd;  <ard.biesheuvel@linaro.org>
 */

#समावेश <linux/efi.h>
#समावेश <linux/log2.h>
#समावेश <यंत्र/efi.h>

#समावेश "efistub.h"

/*
 * Return the number of slots covered by this entry, i.e., the number of
 * addresses it covers that are suitably aligned and supply enough room
 * क्रम the allocation.
 */
अटल अचिन्हित दीर्घ get_entry_num_slots(efi_memory_desc_t *md,
					 अचिन्हित दीर्घ size,
					 अचिन्हित दीर्घ align_shअगरt)
अणु
	अचिन्हित दीर्घ align = 1UL << align_shअगरt;
	u64 first_slot, last_slot, region_end;

	अगर (md->type != EFI_CONVENTIONAL_MEMORY)
		वापस 0;

	अगर (efi_soft_reserve_enabled() &&
	    (md->attribute & EFI_MEMORY_SP))
		वापस 0;

	region_end = min(md->phys_addr + md->num_pages * EFI_PAGE_SIZE - 1,
			 (u64)अच_दीर्घ_उच्च);

	first_slot = round_up(md->phys_addr, align);
	last_slot = round_करोwn(region_end - size + 1, align);

	अगर (first_slot > last_slot)
		वापस 0;

	वापस ((अचिन्हित दीर्घ)(last_slot - first_slot) >> align_shअगरt) + 1;
पूर्ण

/*
 * The UEFI memory descriptors have a भव address field that is only used
 * when installing the भव mapping using SetVirtualAddressMap(). Since it
 * is unused here, we can reuse it to keep track of each descriptor's slot
 * count.
 */
#घोषणा MD_NUM_SLOTS(md)	((md)->virt_addr)

efi_status_t efi_अक्रमom_alloc(अचिन्हित दीर्घ size,
			      अचिन्हित दीर्घ align,
			      अचिन्हित दीर्घ *addr,
			      अचिन्हित दीर्घ अक्रमom_seed)
अणु
	अचिन्हित दीर्घ map_size, desc_size, total_slots = 0, target_slot;
	अचिन्हित दीर्घ buff_size;
	efi_status_t status;
	efi_memory_desc_t *memory_map;
	पूर्णांक map_offset;
	काष्ठा efi_boot_memmap map;

	map.map =	&memory_map;
	map.map_size =	&map_size;
	map.desc_size =	&desc_size;
	map.desc_ver =	शून्य;
	map.key_ptr =	शून्य;
	map.buff_size =	&buff_size;

	status = efi_get_memory_map(&map);
	अगर (status != EFI_SUCCESS)
		वापस status;

	अगर (align < EFI_ALLOC_ALIGN)
		align = EFI_ALLOC_ALIGN;

	size = round_up(size, EFI_ALLOC_ALIGN);

	/* count the suitable slots in each memory map entry */
	क्रम (map_offset = 0; map_offset < map_size; map_offset += desc_size) अणु
		efi_memory_desc_t *md = (व्योम *)memory_map + map_offset;
		अचिन्हित दीर्घ slots;

		slots = get_entry_num_slots(md, size, ilog2(align));
		MD_NUM_SLOTS(md) = slots;
		total_slots += slots;
	पूर्ण

	/* find a अक्रमom number between 0 and total_slots */
	target_slot = (total_slots * (u64)(अक्रमom_seed & U32_MAX)) >> 32;

	/*
	 * target_slot is now a value in the range [0, total_slots), and so
	 * it corresponds with exactly one of the suitable slots we recorded
	 * when iterating over the memory map the first समय around.
	 *
	 * So iterate over the memory map again, subtracting the number of
	 * slots of each entry at each iteration, until we have found the entry
	 * that covers our chosen slot. Use the residual value of target_slot
	 * to calculate the अक्रमomly chosen address, and allocate it directly
	 * using EFI_ALLOCATE_ADDRESS.
	 */
	क्रम (map_offset = 0; map_offset < map_size; map_offset += desc_size) अणु
		efi_memory_desc_t *md = (व्योम *)memory_map + map_offset;
		efi_physical_addr_t target;
		अचिन्हित दीर्घ pages;

		अगर (target_slot >= MD_NUM_SLOTS(md)) अणु
			target_slot -= MD_NUM_SLOTS(md);
			जारी;
		पूर्ण

		target = round_up(md->phys_addr, align) + target_slot * align;
		pages = size / EFI_PAGE_SIZE;

		status = efi_bs_call(allocate_pages, EFI_ALLOCATE_ADDRESS,
				     EFI_LOADER_DATA, pages, &target);
		अगर (status == EFI_SUCCESS)
			*addr = target;
		अवरोध;
	पूर्ण

	efi_bs_call(मुक्त_pool, memory_map);

	वापस status;
पूर्ण
