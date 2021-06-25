<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/mm.h>
#समावेश <linux/io-mapping.h>

/**
 * io_mapping_map_user - remap an I/O mapping to userspace
 * @iomap: the source io_mapping
 * @vma: user vma to map to
 * @addr: target user address to start at
 * @pfn: physical address of kernel memory
 * @size: size of map area
 *
 *  Note: this is only safe अगर the mm semaphore is held when called.
 */
पूर्णांक io_mapping_map_user(काष्ठा io_mapping *iomap, काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ addr, अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ size)
अणु
	vm_flags_t expected_flags = VM_PFNMAP | VM_DONTEXPAND | VM_DONTDUMP;

	अगर (WARN_ON_ONCE((vma->vm_flags & expected_flags) != expected_flags))
		वापस -EINVAL;

	/* We rely on prevalidation of the io-mapping to skip track_pfn(). */
	वापस remap_pfn_range_notrack(vma, addr, pfn, size,
		__pgprot((pgprot_val(iomap->prot) & _PAGE_CACHE_MASK) |
			 (pgprot_val(vma->vm_page_prot) & ~_PAGE_CACHE_MASK)));
पूर्ण
EXPORT_SYMBOL_GPL(io_mapping_map_user);
