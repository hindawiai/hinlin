<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2019 Intel Corporation. All rights reserved. */
#समावेश <linux/efi.h>
#समावेश <यंत्र/e820/api.h>
#समावेश "fake_mem.h"

व्योम __init efi_fake_memmap_early(व्योम)
अणु
	पूर्णांक i;

	/*
	 * The late efi_fake_mem() call can handle all requests अगर
	 * EFI_MEMORY_SP support is disabled.
	 */
	अगर (!efi_soft_reserve_enabled())
		वापस;

	अगर (!efi_enabled(EFI_MEMMAP) || !nr_fake_mem)
		वापस;

	/*
	 * Given that efi_fake_memmap() needs to perक्रमm memblock
	 * allocations it needs to run after e820__memblock_setup().
	 * However, अगर efi_fake_mem specअगरies EFI_MEMORY_SP क्रम a given
	 * address range that potentially needs to mark the memory as
	 * reserved prior to e820__memblock_setup(). Update e820
	 * directly अगर EFI_MEMORY_SP is specअगरied क्रम an
	 * EFI_CONVENTIONAL_MEMORY descriptor.
	 */
	क्रम (i = 0; i < nr_fake_mem; i++) अणु
		काष्ठा efi_mem_range *mem = &efi_fake_mems[i];
		efi_memory_desc_t *md;
		u64 m_start, m_end;

		अगर ((mem->attribute & EFI_MEMORY_SP) == 0)
			जारी;

		m_start = mem->range.start;
		m_end = mem->range.end;
		क्रम_each_efi_memory_desc(md) अणु
			u64 start, end, size;

			अगर (md->type != EFI_CONVENTIONAL_MEMORY)
				जारी;

			start = md->phys_addr;
			end = md->phys_addr + (md->num_pages << EFI_PAGE_SHIFT) - 1;

			अगर (m_start <= end && m_end >= start)
				/* fake range overlaps descriptor */;
			अन्यथा
				जारी;

			/*
			 * Trim the boundary of the e820 update to the
			 * descriptor in हाल the fake range overlaps
			 * !EFI_CONVENTIONAL_MEMORY
			 */
			start = max(start, m_start);
			end = min(end, m_end);
			size = end - start + 1;

			अगर (end <= start)
				जारी;

			/*
			 * Ensure each efi_fake_mem instance results in
			 * a unique e820 resource
			 */
			e820__range_हटाओ(start, size, E820_TYPE_RAM, 1);
			e820__range_add(start, size, E820_TYPE_SOFT_RESERVED);
			e820__update_table(e820_table);
		पूर्ण
	पूर्ण
पूर्ण
