<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/efi.h>
#समावेश <यंत्र/efi.h>

#समावेश "efistub.h"

/**
 * efi_allocate_pages_aligned() - Allocate memory pages
 * @size:	minimum number of bytes to allocate
 * @addr:	On वापस the address of the first allocated page. The first
 *		allocated page has alignment EFI_ALLOC_ALIGN which is an
 *		architecture dependent multiple of the page size.
 * @max:	the address that the last allocated memory page shall not
 *		exceed
 * @align:	minimum alignment of the base of the allocation
 *
 * Allocate pages as EFI_LOADER_DATA. The allocated pages are aligned according
 * to @align, which should be >= EFI_ALLOC_ALIGN. The last allocated page will
 * not exceed the address given by @max.
 *
 * Return:	status code
 */
efi_status_t efi_allocate_pages_aligned(अचिन्हित दीर्घ size, अचिन्हित दीर्घ *addr,
					अचिन्हित दीर्घ max, अचिन्हित दीर्घ align)
अणु
	efi_physical_addr_t alloc_addr;
	efi_status_t status;
	पूर्णांक slack;

	अगर (align < EFI_ALLOC_ALIGN)
		align = EFI_ALLOC_ALIGN;

	alloc_addr = ALIGN_DOWN(max + 1, align) - 1;
	size = round_up(size, EFI_ALLOC_ALIGN);
	slack = align / EFI_PAGE_SIZE - 1;

	status = efi_bs_call(allocate_pages, EFI_ALLOCATE_MAX_ADDRESS,
			     EFI_LOADER_DATA, size / EFI_PAGE_SIZE + slack,
			     &alloc_addr);
	अगर (status != EFI_SUCCESS)
		वापस status;

	*addr = ALIGN((अचिन्हित दीर्घ)alloc_addr, align);

	अगर (slack > 0) अणु
		पूर्णांक l = (alloc_addr & (align - 1)) / EFI_PAGE_SIZE;

		अगर (l) अणु
			efi_bs_call(मुक्त_pages, alloc_addr, slack - l + 1);
			slack = l - 1;
		पूर्ण
		अगर (slack)
			efi_bs_call(मुक्त_pages, *addr + size, slack);
	पूर्ण
	वापस EFI_SUCCESS;
पूर्ण
