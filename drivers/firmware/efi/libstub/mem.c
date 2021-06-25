<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/efi.h>
#समावेश <यंत्र/efi.h>

#समावेश "efistub.h"

अटल अंतरभूत bool mmap_has_headroom(अचिन्हित दीर्घ buff_size,
				     अचिन्हित दीर्घ map_size,
				     अचिन्हित दीर्घ desc_size)
अणु
	अचिन्हित दीर्घ slack = buff_size - map_size;

	वापस slack / desc_size >= EFI_MMAP_NR_SLACK_SLOTS;
पूर्ण

/**
 * efi_get_memory_map() - get memory map
 * @map:	on वापस poपूर्णांकer to memory map
 *
 * Retrieve the UEFI memory map. The allocated memory leaves room क्रम
 * up to EFI_MMAP_NR_SLACK_SLOTS additional memory map entries.
 *
 * Return:	status code
 */
efi_status_t efi_get_memory_map(काष्ठा efi_boot_memmap *map)
अणु
	efi_memory_desc_t *m = शून्य;
	efi_status_t status;
	अचिन्हित दीर्घ key;
	u32 desc_version;

	*map->desc_size =	माप(*m);
	*map->map_size =	*map->desc_size * 32;
	*map->buff_size =	*map->map_size;
again:
	status = efi_bs_call(allocate_pool, EFI_LOADER_DATA,
			     *map->map_size, (व्योम **)&m);
	अगर (status != EFI_SUCCESS)
		जाओ fail;

	*map->desc_size = 0;
	key = 0;
	status = efi_bs_call(get_memory_map, map->map_size, m,
			     &key, map->desc_size, &desc_version);
	अगर (status == EFI_BUFFER_TOO_SMALL ||
	    !mmap_has_headroom(*map->buff_size, *map->map_size,
			       *map->desc_size)) अणु
		efi_bs_call(मुक्त_pool, m);
		/*
		 * Make sure there is some entries of headroom so that the
		 * buffer can be reused क्रम a new map after allocations are
		 * no दीर्घer permitted.  Its unlikely that the map will grow to
		 * exceed this headroom once we are पढ़ोy to trigger
		 * ExitBootServices()
		 */
		*map->map_size += *map->desc_size * EFI_MMAP_NR_SLACK_SLOTS;
		*map->buff_size = *map->map_size;
		जाओ again;
	पूर्ण

	अगर (status == EFI_SUCCESS) अणु
		अगर (map->key_ptr)
			*map->key_ptr = key;
		अगर (map->desc_ver)
			*map->desc_ver = desc_version;
	पूर्ण अन्यथा अणु
		efi_bs_call(मुक्त_pool, m);
	पूर्ण

fail:
	*map->map = m;
	वापस status;
पूर्ण

/**
 * efi_allocate_pages() - Allocate memory pages
 * @size:	minimum number of bytes to allocate
 * @addr:	On वापस the address of the first allocated page. The first
 *		allocated page has alignment EFI_ALLOC_ALIGN which is an
 *		architecture dependent multiple of the page size.
 * @max:	the address that the last allocated memory page shall not
 *		exceed
 *
 * Allocate pages as EFI_LOADER_DATA. The allocated pages are aligned according
 * to EFI_ALLOC_ALIGN. The last allocated page will not exceed the address
 * given by @max.
 *
 * Return:	status code
 */
efi_status_t efi_allocate_pages(अचिन्हित दीर्घ size, अचिन्हित दीर्घ *addr,
				अचिन्हित दीर्घ max)
अणु
	efi_physical_addr_t alloc_addr;
	efi_status_t status;

	अगर (EFI_ALLOC_ALIGN > EFI_PAGE_SIZE)
		वापस efi_allocate_pages_aligned(size, addr, max,
						  EFI_ALLOC_ALIGN);

	alloc_addr = ALIGN_DOWN(max + 1, EFI_ALLOC_ALIGN) - 1;
	status = efi_bs_call(allocate_pages, EFI_ALLOCATE_MAX_ADDRESS,
			     EFI_LOADER_DATA, DIV_ROUND_UP(size, EFI_PAGE_SIZE),
			     &alloc_addr);
	अगर (status != EFI_SUCCESS)
		वापस status;

	*addr = alloc_addr;
	वापस EFI_SUCCESS;
पूर्ण

/**
 * efi_मुक्त() - मुक्त memory pages
 * @size:	size of the memory area to मुक्त in bytes
 * @addr:	start of the memory area to मुक्त (must be EFI_PAGE_SIZE
 *		aligned)
 *
 * @size is rounded up to a multiple of EFI_ALLOC_ALIGN which is an
 * architecture specअगरic multiple of EFI_PAGE_SIZE. So this function should
 * only be used to वापस pages allocated with efi_allocate_pages() or
 * efi_low_alloc_above().
 */
व्योम efi_मुक्त(अचिन्हित दीर्घ size, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ nr_pages;

	अगर (!size)
		वापस;

	nr_pages = round_up(size, EFI_ALLOC_ALIGN) / EFI_PAGE_SIZE;
	efi_bs_call(मुक्त_pages, addr, nr_pages);
पूर्ण
