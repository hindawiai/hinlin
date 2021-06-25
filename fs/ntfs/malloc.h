<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * दो_स्मृति.h - NTFS kernel memory handling. Part of the Linux-NTFS project.
 *
 * Copyright (c) 2001-2005 Anton Altaparmakov
 */

#अगर_अघोषित _LINUX_NTFS_MALLOC_H
#घोषणा _LINUX_NTFS_MALLOC_H

#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <linux/highस्मृति.स>

/**
 * __ntfs_दो_स्मृति - allocate memory in multiples of pages
 * @size:	number of bytes to allocate
 * @gfp_mask:	extra flags क्रम the allocator
 *
 * Internal function.  You probably want ntfs_दो_स्मृति_nofs()...
 *
 * Allocates @size bytes of memory, rounded up to multiples of PAGE_SIZE and
 * वापसs a poपूर्णांकer to the allocated memory.
 *
 * If there was insufficient memory to complete the request, वापस शून्य.
 * Depending on @gfp_mask the allocation may be guaranteed to succeed.
 */
अटल अंतरभूत व्योम *__ntfs_दो_स्मृति(अचिन्हित दीर्घ size, gfp_t gfp_mask)
अणु
	अगर (likely(size <= PAGE_SIZE)) अणु
		BUG_ON(!size);
		/* kदो_स्मृति() has per-CPU caches so is faster क्रम now. */
		वापस kदो_स्मृति(PAGE_SIZE, gfp_mask & ~__GFP_HIGHMEM);
		/* वापस (व्योम *)__get_मुक्त_page(gfp_mask); */
	पूर्ण
	अगर (likely((size >> PAGE_SHIFT) < totalram_pages()))
		वापस __vदो_स्मृति(size, gfp_mask);
	वापस शून्य;
पूर्ण

/**
 * ntfs_दो_स्मृति_nofs - allocate memory in multiples of pages
 * @size:	number of bytes to allocate
 *
 * Allocates @size bytes of memory, rounded up to multiples of PAGE_SIZE and
 * वापसs a poपूर्णांकer to the allocated memory.
 *
 * If there was insufficient memory to complete the request, वापस शून्य.
 */
अटल अंतरभूत व्योम *ntfs_दो_स्मृति_nofs(अचिन्हित दीर्घ size)
अणु
	वापस __ntfs_दो_स्मृति(size, GFP_NOFS | __GFP_HIGHMEM);
पूर्ण

/**
 * ntfs_दो_स्मृति_nofs_nofail - allocate memory in multiples of pages
 * @size:	number of bytes to allocate
 *
 * Allocates @size bytes of memory, rounded up to multiples of PAGE_SIZE and
 * वापसs a poपूर्णांकer to the allocated memory.
 *
 * This function guarantees that the allocation will succeed.  It will sleep
 * क्रम as दीर्घ as it takes to complete the allocation.
 *
 * If there was insufficient memory to complete the request, वापस शून्य.
 */
अटल अंतरभूत व्योम *ntfs_दो_स्मृति_nofs_nofail(अचिन्हित दीर्घ size)
अणु
	वापस __ntfs_दो_स्मृति(size, GFP_NOFS | __GFP_HIGHMEM | __GFP_NOFAIL);
पूर्ण

अटल अंतरभूत व्योम ntfs_मुक्त(व्योम *addr)
अणु
	kvमुक्त(addr);
पूर्ण

#पूर्ण_अगर /* _LINUX_NTFS_MALLOC_H */
