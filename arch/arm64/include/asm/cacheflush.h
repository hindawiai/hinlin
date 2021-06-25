<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Based on arch/arm/include/यंत्र/cacheflush.h
 *
 * Copyright (C) 1999-2002 Russell King.
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_CACHEFLUSH_H
#घोषणा __ASM_CACHEFLUSH_H

#समावेश <linux/kgdb.h>
#समावेश <linux/mm.h>

/*
 * This flag is used to indicate that the page poपूर्णांकed to by a pte is clean
 * and करोes not require cleaning beक्रमe वापसing it to the user.
 */
#घोषणा PG_dcache_clean PG_arch_1

/*
 *	MM Cache Management
 *	===================
 *
 *	The arch/arm64/mm/cache.S implements these methods.
 *
 *	Start addresses are inclusive and end addresses are exclusive; start
 *	addresses should be rounded करोwn, end addresses up.
 *
 *	See Documentation/core-api/cachetlb.rst क्रम more inक्रमmation. Please note that
 *	the implementation assumes non-aliasing VIPT D-cache and (aliasing)
 *	VIPT I-cache.
 *
 *	flush_icache_range(start, end)
 *
 *		Ensure coherency between the I-cache and the D-cache in the
 *		region described by start, end.
 *		- start  - भव start address
 *		- end    - भव end address
 *
 *	invalidate_icache_range(start, end)
 *
 *		Invalidate the I-cache in the region described by start, end.
 *		- start  - भव start address
 *		- end    - भव end address
 *
 *	__flush_cache_user_range(start, end)
 *
 *		Ensure coherency between the I-cache and the D-cache in the
 *		region described by start, end.
 *		- start  - भव start address
 *		- end    - भव end address
 *
 *	__flush_dcache_area(kaddr, size)
 *
 *		Ensure that the data held in page is written back.
 *		- kaddr  - page address
 *		- size   - region size
 */
बाह्य व्योम __flush_icache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य पूर्णांक  invalidate_icache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम __flush_dcache_area(व्योम *addr, माप_प्रकार len);
बाह्य व्योम __inval_dcache_area(व्योम *addr, माप_प्रकार len);
बाह्य व्योम __clean_dcache_area_poc(व्योम *addr, माप_प्रकार len);
बाह्य व्योम __clean_dcache_area_pop(व्योम *addr, माप_प्रकार len);
बाह्य व्योम __clean_dcache_area_pou(व्योम *addr, माप_प्रकार len);
बाह्य दीर्घ __flush_cache_user_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम sync_icache_aliases(व्योम *kaddr, अचिन्हित दीर्घ len);

अटल अंतरभूत व्योम flush_icache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	__flush_icache_range(start, end);

	/*
	 * IPI all online CPUs so that they undergo a context synchronization
	 * event and are क्रमced to refetch the new inकाष्ठाions.
	 */

	/*
	 * KGDB perक्रमms cache मुख्यtenance with पूर्णांकerrupts disabled, so we
	 * will deadlock trying to IPI the secondary CPUs. In theory, we can
	 * set CACHE_FLUSH_IS_SAFE to 0 to aव्योम this known issue, but that
	 * just means that KGDB will elide the मुख्यtenance altogether! As it
	 * turns out, KGDB uses IPIs to round-up the secondary CPUs during
	 * the patching operation, so we करोn't need extra IPIs here anyway.
	 * In which हाल, add a KGDB-specअगरic bodge and वापस early.
	 */
	अगर (in_dbg_master())
		वापस;

	kick_all_cpus_sync();
पूर्ण
#घोषणा flush_icache_range flush_icache_range

/*
 * Cache मुख्यtenance functions used by the DMA API. No to be used directly.
 */
बाह्य व्योम __dma_map_area(स्थिर व्योम *, माप_प्रकार, पूर्णांक);
बाह्य व्योम __dma_unmap_area(स्थिर व्योम *, माप_प्रकार, पूर्णांक);
बाह्य व्योम __dma_flush_area(स्थिर व्योम *, माप_प्रकार);

/*
 * Copy user data from/to a page which is mapped पूर्णांकo a dअगरferent
 * processes address space.  Really, we want to allow our "user
 * space" model to handle this.
 */
बाह्य व्योम copy_to_user_page(काष्ठा vm_area_काष्ठा *, काष्ठा page *,
	अचिन्हित दीर्घ, व्योम *, स्थिर व्योम *, अचिन्हित दीर्घ);
#घोषणा copy_to_user_page copy_to_user_page

/*
 * flush_dcache_page is used when the kernel has written to the page
 * cache page at भव address page->भव.
 *
 * If this page isn't mapped (ie, page_mapping == शून्य), or it might
 * have userspace mappings, then we _must_ always clean + invalidate
 * the dcache entries associated with the kernel mapping.
 *
 * Otherwise we can defer the operation, and clean the cache when we are
 * about to change to user space.  This is the same method as used on SPARC64.
 * See update_mmu_cache क्रम the user space part.
 */
#घोषणा ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE 1
बाह्य व्योम flush_dcache_page(काष्ठा page *);

अटल __always_अंतरभूत व्योम __flush_icache_all(व्योम)
अणु
	अगर (cpus_have_स्थिर_cap(ARM64_HAS_CACHE_DIC))
		वापस;

	यंत्र("ic	ialluis");
	dsb(ish);
पूर्ण

पूर्णांक set_memory_valid(अचिन्हित दीर्घ addr, पूर्णांक numpages, पूर्णांक enable);

पूर्णांक set_direct_map_invalid_noflush(काष्ठा page *page);
पूर्णांक set_direct_map_शेष_noflush(काष्ठा page *page);
bool kernel_page_present(काष्ठा page *page);

#समावेश <यंत्र-generic/cacheflush.h>

#पूर्ण_अगर /* __ASM_CACHEFLUSH_H */
