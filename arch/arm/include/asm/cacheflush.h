<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/cacheflush.h
 *
 *  Copyright (C) 1999-2002 Russell King
 */
#अगर_अघोषित _ASMARM_CACHEFLUSH_H
#घोषणा _ASMARM_CACHEFLUSH_H

#समावेश <linux/mm.h>

#समावेश <यंत्र/glue-cache.h>
#समावेश <यंत्र/shmparam.h>
#समावेश <यंत्र/cachetype.h>
#समावेश <यंत्र/outercache.h>

#घोषणा CACHE_COLOUR(vaddr)	((vaddr & (SHMLBA - 1)) >> PAGE_SHIFT)

/*
 * This flag is used to indicate that the page poपूर्णांकed to by a pte is clean
 * and करोes not require cleaning beक्रमe वापसing it to the user.
 */
#घोषणा PG_dcache_clean PG_arch_1

/*
 *	MM Cache Management
 *	===================
 *
 *	The arch/arm/mm/cache-*.S and arch/arm/mm/proc-*.S files
 *	implement these methods.
 *
 *	Start addresses are inclusive and end addresses are exclusive;
 *	start addresses should be rounded करोwn, end addresses up.
 *
 *	See Documentation/core-api/cachetlb.rst क्रम more inक्रमmation.
 *	Please note that the implementation of these, and the required
 *	effects are cache-type (VIVT/VIPT/PIPT) specअगरic.
 *
 *	flush_icache_all()
 *
 *		Unconditionally clean and invalidate the entire icache.
 *		Currently only needed क्रम cache-v6.S and cache-v7.S, see
 *		__flush_icache_all क्रम the generic implementation.
 *
 *	flush_kern_all()
 *
 *		Unconditionally clean and invalidate the entire cache.
 *
 *     flush_kern_louis()
 *
 *             Flush data cache levels up to the level of unअगरication
 *             inner shareable and invalidate the I-cache.
 *             Only needed from v7 onwards, falls back to flush_cache_all()
 *             क्रम all other processor versions.
 *
 *	flush_user_all()
 *
 *		Clean and invalidate all user space cache entries
 *		beक्रमe a change of page tables.
 *
 *	flush_user_range(start, end, flags)
 *
 *		Clean and invalidate a range of cache entries in the
 *		specअगरied address space beक्रमe a change of page tables.
 *		- start - user start address (inclusive, page aligned)
 *		- end   - user end address   (exclusive, page aligned)
 *		- flags - vma->vm_flags field
 *
 *	coherent_kern_range(start, end)
 *
 *		Ensure coherency between the Icache and the Dcache in the
 *		region described by start, end.  If you have non-snooping
 *		Harvard caches, you need to implement this function.
 *		- start  - भव start address
 *		- end    - भव end address
 *
 *	coherent_user_range(start, end)
 *
 *		Ensure coherency between the Icache and the Dcache in the
 *		region described by start, end.  If you have non-snooping
 *		Harvard caches, you need to implement this function.
 *		- start  - भव start address
 *		- end    - भव end address
 *
 *	flush_kern_dcache_area(kaddr, size)
 *
 *		Ensure that the data held in page is written back.
 *		- kaddr  - page address
 *		- size   - region size
 *
 *	DMA Cache Coherency
 *	===================
 *
 *	dma_flush_range(start, end)
 *
 *		Clean and invalidate the specअगरied भव address range.
 *		- start  - भव start address
 *		- end    - भव end address
 */

काष्ठा cpu_cache_fns अणु
	व्योम (*flush_icache_all)(व्योम);
	व्योम (*flush_kern_all)(व्योम);
	व्योम (*flush_kern_louis)(व्योम);
	व्योम (*flush_user_all)(व्योम);
	व्योम (*flush_user_range)(अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित पूर्णांक);

	व्योम (*coherent_kern_range)(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
	पूर्णांक  (*coherent_user_range)(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
	व्योम (*flush_kern_dcache_area)(व्योम *, माप_प्रकार);

	व्योम (*dma_map_area)(स्थिर व्योम *, माप_प्रकार, पूर्णांक);
	व्योम (*dma_unmap_area)(स्थिर व्योम *, माप_प्रकार, पूर्णांक);

	व्योम (*dma_flush_range)(स्थिर व्योम *, स्थिर व्योम *);
पूर्ण __no_अक्रमomize_layout;

/*
 * Select the calling method
 */
#अगर_घोषित MULTI_CACHE

बाह्य काष्ठा cpu_cache_fns cpu_cache;

#घोषणा __cpuc_flush_icache_all		cpu_cache.flush_icache_all
#घोषणा __cpuc_flush_kern_all		cpu_cache.flush_kern_all
#घोषणा __cpuc_flush_kern_louis		cpu_cache.flush_kern_louis
#घोषणा __cpuc_flush_user_all		cpu_cache.flush_user_all
#घोषणा __cpuc_flush_user_range		cpu_cache.flush_user_range
#घोषणा __cpuc_coherent_kern_range	cpu_cache.coherent_kern_range
#घोषणा __cpuc_coherent_user_range	cpu_cache.coherent_user_range
#घोषणा __cpuc_flush_dcache_area	cpu_cache.flush_kern_dcache_area

/*
 * These are निजी to the dma-mapping API.  Do not use directly.
 * Their sole purpose is to ensure that data held in the cache
 * is visible to DMA, or data written by DMA to प्रणाली memory is
 * visible to the CPU.
 */
#घोषणा dmac_flush_range		cpu_cache.dma_flush_range

#अन्यथा

बाह्य व्योम __cpuc_flush_icache_all(व्योम);
बाह्य व्योम __cpuc_flush_kern_all(व्योम);
बाह्य व्योम __cpuc_flush_kern_louis(व्योम);
बाह्य व्योम __cpuc_flush_user_all(व्योम);
बाह्य व्योम __cpuc_flush_user_range(अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित पूर्णांक);
बाह्य व्योम __cpuc_coherent_kern_range(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
बाह्य पूर्णांक  __cpuc_coherent_user_range(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
बाह्य व्योम __cpuc_flush_dcache_area(व्योम *, माप_प्रकार);

/*
 * These are निजी to the dma-mapping API.  Do not use directly.
 * Their sole purpose is to ensure that data held in the cache
 * is visible to DMA, or data written by DMA to प्रणाली memory is
 * visible to the CPU.
 */
बाह्य व्योम dmac_flush_range(स्थिर व्योम *, स्थिर व्योम *);

#पूर्ण_अगर

/*
 * Copy user data from/to a page which is mapped पूर्णांकo a dअगरferent
 * processes address space.  Really, we want to allow our "user
 * space" model to handle this.
 */
बाह्य व्योम copy_to_user_page(काष्ठा vm_area_काष्ठा *, काष्ठा page *,
	अचिन्हित दीर्घ, व्योम *, स्थिर व्योम *, अचिन्हित दीर्घ);
#घोषणा copy_from_user_page(vma, page, vaddr, dst, src, len) \
	करो अणु							\
		स_नकल(dst, src, len);				\
	पूर्ण जबतक (0)

/*
 * Convert calls to our calling convention.
 */

/* Invalidate I-cache */
#घोषणा __flush_icache_all_generic()					\
	यंत्र("mcr	p15, 0, %0, c7, c5, 0"				\
	    : : "r" (0));

/* Invalidate I-cache inner shareable */
#घोषणा __flush_icache_all_v7_smp()					\
	यंत्र("mcr	p15, 0, %0, c7, c1, 0"				\
	    : : "r" (0));

/*
 * Optimized __flush_icache_all क्रम the common हालs. Note that UP ARMv7
 * will fall through to use __flush_icache_all_generic.
 */
#अगर (defined(CONFIG_CPU_V7) && \
     (defined(CONFIG_CPU_V6) || defined(CONFIG_CPU_V6K))) || \
	defined(CONFIG_SMP_ON_UP)
#घोषणा __flush_icache_preferred	__cpuc_flush_icache_all
#या_अगर __LINUX_ARM_ARCH__ >= 7 && defined(CONFIG_SMP)
#घोषणा __flush_icache_preferred	__flush_icache_all_v7_smp
#या_अगर __LINUX_ARM_ARCH__ == 6 && defined(CONFIG_ARM_ERRATA_411920)
#घोषणा __flush_icache_preferred	__cpuc_flush_icache_all
#अन्यथा
#घोषणा __flush_icache_preferred	__flush_icache_all_generic
#पूर्ण_अगर

अटल अंतरभूत व्योम __flush_icache_all(व्योम)
अणु
	__flush_icache_preferred();
	dsb(ishst);
पूर्ण

/*
 * Flush caches up to Level of Unअगरication Inner Shareable
 */
#घोषणा flush_cache_louis()		__cpuc_flush_kern_louis()

#घोषणा flush_cache_all()		__cpuc_flush_kern_all()

अटल अंतरभूत व्योम vivt_flush_cache_mm(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (cpumask_test_cpu(smp_processor_id(), mm_cpumask(mm)))
		__cpuc_flush_user_all();
पूर्ण

अटल अंतरभूत व्योम
vivt_flush_cache_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;

	अगर (!mm || cpumask_test_cpu(smp_processor_id(), mm_cpumask(mm)))
		__cpuc_flush_user_range(start & PAGE_MASK, PAGE_ALIGN(end),
					vma->vm_flags);
पूर्ण

अटल अंतरभूत व्योम
vivt_flush_cache_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ user_addr, अचिन्हित दीर्घ pfn)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;

	अगर (!mm || cpumask_test_cpu(smp_processor_id(), mm_cpumask(mm))) अणु
		अचिन्हित दीर्घ addr = user_addr & PAGE_MASK;
		__cpuc_flush_user_range(addr, addr + PAGE_SIZE, vma->vm_flags);
	पूर्ण
पूर्ण

#अगर_अघोषित CONFIG_CPU_CACHE_VIPT
#घोषणा flush_cache_mm(mm) \
		vivt_flush_cache_mm(mm)
#घोषणा flush_cache_range(vma,start,end) \
		vivt_flush_cache_range(vma,start,end)
#घोषणा flush_cache_page(vma,addr,pfn) \
		vivt_flush_cache_page(vma,addr,pfn)
#अन्यथा
बाह्य व्योम flush_cache_mm(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम flush_cache_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम flush_cache_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ user_addr, अचिन्हित दीर्घ pfn);
#पूर्ण_अगर

#घोषणा flush_cache_dup_mm(mm) flush_cache_mm(mm)

/*
 * flush_icache_user_range is used when we want to ensure that the
 * Harvard caches are synchronised क्रम the user space address range.
 * This is used क्रम the ARM निजी sys_cacheflush प्रणाली call.
 */
#घोषणा flush_icache_user_range(s,e)	__cpuc_coherent_user_range(s,e)

/*
 * Perक्रमm necessary cache operations to ensure that data previously
 * stored within this range of addresses can be executed by the CPU.
 */
#घोषणा flush_icache_range(s,e)		__cpuc_coherent_kern_range(s,e)

/*
 * Perक्रमm necessary cache operations to ensure that the TLB will
 * see data written in the specअगरied area.
 */
#घोषणा clean_dcache_area(start,size)	cpu_dcache_clean_area(start, size)

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

अटल अंतरभूत व्योम flush_kernel_vmap_range(व्योम *addr, पूर्णांक size)
अणु
	अगर ((cache_is_vivt() || cache_is_vipt_aliasing()))
	  __cpuc_flush_dcache_area(addr, (माप_प्रकार)size);
पूर्ण
अटल अंतरभूत व्योम invalidate_kernel_vmap_range(व्योम *addr, पूर्णांक size)
अणु
	अगर ((cache_is_vivt() || cache_is_vipt_aliasing()))
	  __cpuc_flush_dcache_area(addr, (माप_प्रकार)size);
पूर्ण

#घोषणा ARCH_HAS_FLUSH_ANON_PAGE
अटल अंतरभूत व्योम flush_anon_page(काष्ठा vm_area_काष्ठा *vma,
			 काष्ठा page *page, अचिन्हित दीर्घ vmaddr)
अणु
	बाह्य व्योम __flush_anon_page(काष्ठा vm_area_काष्ठा *vma,
				काष्ठा page *, अचिन्हित दीर्घ);
	अगर (PageAnon(page))
		__flush_anon_page(vma, page, vmaddr);
पूर्ण

#घोषणा ARCH_HAS_FLUSH_KERNEL_DCACHE_PAGE
बाह्य व्योम flush_kernel_dcache_page(काष्ठा page *);

#घोषणा flush_dcache_mmap_lock(mapping)		xa_lock_irq(&mapping->i_pages)
#घोषणा flush_dcache_mmap_unlock(mapping)	xa_unlock_irq(&mapping->i_pages)

/*
 * We करोn't appear to need to do anything here.  In fact, if we did, we'd
 * duplicate cache flushing अन्यथाwhere perक्रमmed by flush_dcache_page().
 */
#घोषणा flush_icache_page(vma,page)	करो अणु पूर्ण जबतक (0)

/*
 * flush_cache_vmap() is used when creating mappings (eg, via vmap,
 * vदो_स्मृति, ioremap etc) in kernel space क्रम pages.  On non-VIPT
 * caches, since the direct-mappings of these pages may contain cached
 * data, we need to करो a full cache flush to ensure that ग_लिखोbacks
 * करोn't corrupt data placed पूर्णांकo these pages via the new mappings.
 */
अटल अंतरभूत व्योम flush_cache_vmap(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अगर (!cache_is_vipt_nonaliasing())
		flush_cache_all();
	अन्यथा
		/*
		 * set_pte_at() called from vmap_pte_range() करोes not
		 * have a DSB after cleaning the cache line.
		 */
		dsb(ishst);
पूर्ण

अटल अंतरभूत व्योम flush_cache_vunmap(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अगर (!cache_is_vipt_nonaliasing())
		flush_cache_all();
पूर्ण

/*
 * Memory synchronization helpers क्रम mixed cached vs non cached accesses.
 *
 * Some synchronization algorithms have to set states in memory with the
 * cache enabled or disabled depending on the code path.  It is crucial
 * to always ensure proper cache मुख्यtenance to update मुख्य memory right
 * away in that हाल.
 *
 * Any cached ग_लिखो must be followed by a cache clean operation.
 * Any cached पढ़ो must be preceded by a cache invalidate operation.
 * Yet, in the पढ़ो हाल, a cache flush i.e. atomic clean+invalidate
 * operation is needed to aव्योम discarding possible concurrent ग_लिखोs to the
 * accessed memory.
 *
 * Also, in order to prevent a cached ग_लिखोr from पूर्णांकerfering with an
 * adjacent non-cached ग_लिखोr, each state variable must be located to
 * a separate cache line.
 */

/*
 * This needs to be >= the max cache ग_लिखोback size of all
 * supported platक्रमms included in the current kernel configuration.
 * This is used to align state variables to their own cache lines.
 */
#घोषणा __CACHE_WRITEBACK_ORDER 6  /* guessed from existing platक्रमms */
#घोषणा __CACHE_WRITEBACK_GRANULE (1 << __CACHE_WRITEBACK_ORDER)

/*
 * There is no __cpuc_clean_dcache_area but we use it anyway क्रम
 * code पूर्णांकent clarity, and alias it to __cpuc_flush_dcache_area.
 */
#घोषणा __cpuc_clean_dcache_area __cpuc_flush_dcache_area

/*
 * Ensure preceding ग_लिखोs to *p by this CPU are visible to
 * subsequent पढ़ोs by other CPUs:
 */
अटल अंतरभूत व्योम __sync_cache_range_w(अस्थिर व्योम *p, माप_प्रकार size)
अणु
	अक्षर *_p = (अक्षर *)p;

	__cpuc_clean_dcache_area(_p, size);
	outer_clean_range(__pa(_p), __pa(_p + size));
पूर्ण

/*
 * Ensure preceding ग_लिखोs to *p by other CPUs are visible to
 * subsequent पढ़ोs by this CPU.  We must be careful not to
 * discard data simultaneously written by another CPU, hence the
 * usage of flush rather than invalidate operations.
 */
अटल अंतरभूत व्योम __sync_cache_range_r(अस्थिर व्योम *p, माप_प्रकार size)
अणु
	अक्षर *_p = (अक्षर *)p;

#अगर_घोषित CONFIG_OUTER_CACHE
	अगर (outer_cache.flush_range) अणु
		/*
		 * Ensure dirty data migrated from other CPUs पूर्णांकo our cache
		 * are cleaned out safely beक्रमe the outer cache is cleaned:
		 */
		__cpuc_clean_dcache_area(_p, size);

		/* Clean and invalidate stale data क्रम *p from outer ... */
		outer_flush_range(__pa(_p), __pa(_p + size));
	पूर्ण
#पूर्ण_अगर

	/* ... and inner cache: */
	__cpuc_flush_dcache_area(_p, size);
पूर्ण

#घोषणा sync_cache_w(ptr) __sync_cache_range_w(ptr, माप *(ptr))
#घोषणा sync_cache_r(ptr) __sync_cache_range_r(ptr, माप *(ptr))

/*
 * Disabling cache access क्रम one CPU in an ARMv7 SMP प्रणाली is tricky.
 * To करो so we must:
 *
 * - Clear the SCTLR.C bit to prevent further cache allocations
 * - Flush the desired level of cache
 * - Clear the ACTLR "SMP" bit to disable local coherency
 *
 * ... and so without any पूर्णांकervening memory access in between those steps,
 * not even to the stack.
 *
 * WARNING -- After this has been called:
 *
 * - No ldrex/strex (and similar) inकाष्ठाions must be used.
 * - The CPU is obviously no दीर्घer coherent with the other CPUs.
 * - This is unlikely to work as expected अगर Linux is running non-secure.
 *
 * Note:
 *
 * - This is known to apply to several ARMv7 processor implementations,
 *   however some exceptions may exist.  Caveat emptor.
 *
 * - The clobber list is dictated by the call to v7_flush_dcache_*.
 *   fp is preserved to the stack explicitly prior disabling the cache
 *   since adding it to the clobber list is incompatible with having
 *   CONFIG_FRAME_POINTER=y.  ip is saved as well अगर ever r12-clobbering
 *   trampoline are inserted by the linker and to keep sp 64-bit aligned.
 */
#घोषणा v7_निकास_coherency_flush(level) \
	यंत्र अस्थिर( \
	".arch	armv7-a \n\t" \
	"stmfd	sp!, {fp, ip} \n\t" \
	"mrc	p15, 0, r0, c1, c0, 0	@ get SCTLR \n\t" \
	"bic	r0, r0, #"__stringअगरy(CR_C)" \n\t" \
	"mcr	p15, 0, r0, c1, c0, 0	@ set SCTLR \n\t" \
	"isb	\n\t" \
	"bl	v7_flush_dcache_"__stringअगरy(level)" \n\t" \
	"mrc	p15, 0, r0, c1, c0, 1	@ get ACTLR \n\t" \
	"bic	r0, r0, #(1 << 6)	@ disable local coherency \n\t" \
	"mcr	p15, 0, r0, c1, c0, 1	@ set ACTLR \n\t" \
	"isb	\n\t" \
	"dsb	\n\t" \
	"ldmfd	sp!, {fp, ip}" \
	: : : "r0","r1","r2","r3","r4","r5","r6","r7", \
	      "r9","r10","lr","memory" )

व्योम flush_uprobe_xol_access(काष्ठा page *page, अचिन्हित दीर्घ uaddr,
			     व्योम *kaddr, अचिन्हित दीर्घ len);


#अगर_घोषित CONFIG_CPU_ICACHE_MISMATCH_WORKAROUND
व्योम check_cpu_icache_size(पूर्णांक cpuid);
#अन्यथा
अटल अंतरभूत व्योम check_cpu_icache_size(पूर्णांक cpuid) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
