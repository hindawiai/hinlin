<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/efi.h>
#समावेश <यंत्र/efi.h>

#समावेश "efistub.h"

/**
 * efi_low_alloc_above() - allocate pages at or above given address
 * @size:	size of the memory area to allocate
 * @align:	minimum alignment of the allocated memory area. It should
 *		a घातer of two.
 * @addr:	on निकास the address of the allocated memory
 * @min:	minimum address to used क्रम the memory allocation
 *
 * Allocate at the lowest possible address that is not below @min as
 * EFI_LOADER_DATA. The allocated pages are aligned according to @align but at
 * least EFI_ALLOC_ALIGN. The first allocated page will not below the address
 * given by @min.
 *
 * Return:	status code
 */
efi_status_t efi_low_alloc_above(अचिन्हित दीर्घ size, अचिन्हित दीर्घ align,
				 अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ min)
अणु
	अचिन्हित दीर्घ map_size, desc_size, buff_size;
	efi_memory_desc_t *map;
	efi_status_t status;
	अचिन्हित दीर्घ nr_pages;
	पूर्णांक i;
	काष्ठा efi_boot_memmap boot_map;

	boot_map.map		= &map;
	boot_map.map_size	= &map_size;
	boot_map.desc_size	= &desc_size;
	boot_map.desc_ver	= शून्य;
	boot_map.key_ptr	= शून्य;
	boot_map.buff_size	= &buff_size;

	status = efi_get_memory_map(&boot_map);
	अगर (status != EFI_SUCCESS)
		जाओ fail;

	/*
	 * Enक्रमce minimum alignment that EFI or Linux requires when
	 * requesting a specअगरic address.  We are करोing page-based (or
	 * larger) allocations, and both the address and size must meet
	 * alignment स्थिरraपूर्णांकs.
	 */
	अगर (align < EFI_ALLOC_ALIGN)
		align = EFI_ALLOC_ALIGN;

	size = round_up(size, EFI_ALLOC_ALIGN);
	nr_pages = size / EFI_PAGE_SIZE;
	क्रम (i = 0; i < map_size / desc_size; i++) अणु
		efi_memory_desc_t *desc;
		अचिन्हित दीर्घ m = (अचिन्हित दीर्घ)map;
		u64 start, end;

		desc = efi_early_memdesc_ptr(m, desc_size, i);

		अगर (desc->type != EFI_CONVENTIONAL_MEMORY)
			जारी;

		अगर (efi_soft_reserve_enabled() &&
		    (desc->attribute & EFI_MEMORY_SP))
			जारी;

		अगर (desc->num_pages < nr_pages)
			जारी;

		start = desc->phys_addr;
		end = start + desc->num_pages * EFI_PAGE_SIZE;

		अगर (start < min)
			start = min;

		start = round_up(start, align);
		अगर ((start + size) > end)
			जारी;

		status = efi_bs_call(allocate_pages, EFI_ALLOCATE_ADDRESS,
				     EFI_LOADER_DATA, nr_pages, &start);
		अगर (status == EFI_SUCCESS) अणु
			*addr = start;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == map_size / desc_size)
		status = EFI_NOT_FOUND;

	efi_bs_call(मुक्त_pool, map);
fail:
	वापस status;
पूर्ण

/**
 * efi_relocate_kernel() - copy memory area
 * @image_addr:		poपूर्णांकer to address of memory area to copy
 * @image_size:		size of memory area to copy
 * @alloc_size:		minimum size of memory to allocate, must be greater or
 *			equal to image_size
 * @preferred_addr:	preferred target address
 * @alignment:		minimum alignment of the allocated memory area. It
 *			should be a घातer of two.
 * @min_addr:		minimum target address
 *
 * Copy a memory area to a newly allocated memory area aligned according
 * to @alignment but at least EFI_ALLOC_ALIGN. If the preferred address
 * is not available, the allocated address will not be below @min_addr.
 * On निकास, @image_addr is updated to the target copy address that was used.
 *
 * This function is used to copy the Linux kernel verbatim. It करोes not apply
 * any relocation changes.
 *
 * Return:		status code
 */
efi_status_t efi_relocate_kernel(अचिन्हित दीर्घ *image_addr,
				 अचिन्हित दीर्घ image_size,
				 अचिन्हित दीर्घ alloc_size,
				 अचिन्हित दीर्घ preferred_addr,
				 अचिन्हित दीर्घ alignment,
				 अचिन्हित दीर्घ min_addr)
अणु
	अचिन्हित दीर्घ cur_image_addr;
	अचिन्हित दीर्घ new_addr = 0;
	efi_status_t status;
	अचिन्हित दीर्घ nr_pages;
	efi_physical_addr_t efi_addr = preferred_addr;

	अगर (!image_addr || !image_size || !alloc_size)
		वापस EFI_INVALID_PARAMETER;
	अगर (alloc_size < image_size)
		वापस EFI_INVALID_PARAMETER;

	cur_image_addr = *image_addr;

	/*
	 * The EFI firmware loader could have placed the kernel image
	 * anywhere in memory, but the kernel has restrictions on the
	 * max physical address it can run at.  Some architectures
	 * also have a preferred address, so first try to relocate
	 * to the preferred address.  If that fails, allocate as low
	 * as possible जबतक respecting the required alignment.
	 */
	nr_pages = round_up(alloc_size, EFI_ALLOC_ALIGN) / EFI_PAGE_SIZE;
	status = efi_bs_call(allocate_pages, EFI_ALLOCATE_ADDRESS,
			     EFI_LOADER_DATA, nr_pages, &efi_addr);
	new_addr = efi_addr;
	/*
	 * If preferred address allocation failed allocate as low as
	 * possible.
	 */
	अगर (status != EFI_SUCCESS) अणु
		status = efi_low_alloc_above(alloc_size, alignment, &new_addr,
					     min_addr);
	पूर्ण
	अगर (status != EFI_SUCCESS) अणु
		efi_err("Failed to allocate usable memory for kernel.\n");
		वापस status;
	पूर्ण

	/*
	 * We know source/dest won't overlap since both memory ranges
	 * have been allocated by UEFI, so we can safely use स_नकल.
	 */
	स_नकल((व्योम *)new_addr, (व्योम *)cur_image_addr, image_size);

	/* Return the new address of the relocated image. */
	*image_addr = new_addr;

	वापस status;
पूर्ण
