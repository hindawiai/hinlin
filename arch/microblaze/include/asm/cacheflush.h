<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2007-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2007-2009 PetaLogix
 * Copyright (C) 2007 John Williams <john.williams@petalogix.com>
 * based on v850 version which was
 * Copyright (C) 2001,02,03 NEC Electronics Corporation
 * Copyright (C) 2001,02,03 Miles Bader <miles@gnu.org>
 */

#अगर_अघोषित _ASM_MICROBLAZE_CACHEFLUSH_H
#घोषणा _ASM_MICROBLAZE_CACHEFLUSH_H

/* Somebody depends on this; sigh... */
#समावेश <linux/mm.h>
#समावेश <linux/पन.स>

/* Look at Documentation/core-api/cachetlb.rst */

/*
 * Cache handling functions.
 * Microblaze has a ग_लिखो-through data cache, meaning that the data cache
 * never needs to be flushed.  The only flushing operations that are
 * implemented are to invalidate the inकाष्ठाion cache.  These are called
 * after loading a user application पूर्णांकo memory, we must invalidate the
 * inकाष्ठाion cache to make sure we करोn't fetch old, bad code.
 */

/* काष्ठा cache, d=dcache, i=icache, fl = flush, iv = invalidate,
 * suffix r = range */
काष्ठा scache अणु
	/* icache */
	व्योम (*ie)(व्योम); /* enable */
	व्योम (*id)(व्योम); /* disable */
	व्योम (*अगरl)(व्योम); /* flush */
	व्योम (*अगरlr)(अचिन्हित दीर्घ a, अचिन्हित दीर्घ b);
	व्योम (*iin)(व्योम); /* invalidate */
	व्योम (*iinr)(अचिन्हित दीर्घ a, अचिन्हित दीर्घ b);
	/* dcache */
	व्योम (*de)(व्योम); /* enable */
	व्योम (*dd)(व्योम); /* disable */
	व्योम (*dfl)(व्योम); /* flush */
	व्योम (*dflr)(अचिन्हित दीर्घ a, अचिन्हित दीर्घ b);
	व्योम (*din)(व्योम); /* invalidate */
	व्योम (*dinr)(अचिन्हित दीर्घ a, अचिन्हित दीर्घ b);
पूर्ण;

/* microblaze cache */
बाह्य काष्ठा scache *mbc;

व्योम microblaze_cache_init(व्योम);

#घोषणा enable_icache()					mbc->ie();
#घोषणा disable_icache()				mbc->id();
#घोषणा flush_icache()					mbc->अगरl();
#घोषणा flush_icache_range(start, end)			mbc->अगरlr(start, end);
#घोषणा invalidate_icache()				mbc->iin();
#घोषणा invalidate_icache_range(start, end)		mbc->iinr(start, end);

#घोषणा enable_dcache()					mbc->de();
#घोषणा disable_dcache()				mbc->dd();
/* FIXME क्रम LL-temac driver */
#घोषणा invalidate_dcache()				mbc->din();
#घोषणा invalidate_dcache_range(start, end)		mbc->dinr(start, end);
#घोषणा flush_dcache()					mbc->dfl();
#घोषणा flush_dcache_range(start, end)			mbc->dflr(start, end);

#घोषणा ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE 1
/* MS: We have to implement it because of rootfs-jffs2 issue on WB */
#घोषणा flush_dcache_page(page) \
करो अणु \
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) page_address(page); /* भव */ \
	addr = (u32)virt_to_phys((व्योम *)addr); \
	flush_dcache_range((अचिन्हित) (addr), (अचिन्हित) (addr) + PAGE_SIZE); \
पूर्ण जबतक (0);

#घोषणा flush_cache_page(vma, vmaddr, pfn) \
	flush_dcache_range(pfn << PAGE_SHIFT, (pfn << PAGE_SHIFT) + PAGE_SIZE);

अटल अंतरभूत व्योम copy_to_user_page(काष्ठा vm_area_काष्ठा *vma,
				     काष्ठा page *page, अचिन्हित दीर्घ vaddr,
				     व्योम *dst, व्योम *src, पूर्णांक len)
अणु
	u32 addr = virt_to_phys(dst);
	स_नकल(dst, src, len);
	अगर (vma->vm_flags & VM_EXEC) अणु
		invalidate_icache_range(addr, addr + PAGE_SIZE);
		flush_dcache_range(addr, addr + PAGE_SIZE);
	पूर्ण
पूर्ण
#घोषणा copy_to_user_page copy_to_user_page

#समावेश <यंत्र-generic/cacheflush.h>

#पूर्ण_अगर /* _ASM_MICROBLAZE_CACHEFLUSH_H */
