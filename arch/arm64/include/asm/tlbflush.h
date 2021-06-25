<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Based on arch/arm/include/यंत्र/tlbflush.h
 *
 * Copyright (C) 1999-2003 Russell King
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_TLBFLUSH_H
#घोषणा __ASM_TLBFLUSH_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/bitfield.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/mmu.h>

/*
 * Raw TLBI operations.
 *
 * Where necessary, use the __tlbi() macro to aव्योम यंत्र()
 * boilerplate. Drivers and most kernel code should use the TLB
 * management routines in preference to the macro below.
 *
 * The macro can be used as __tlbi(op) or __tlbi(op, arg), depending
 * on whether a particular TLBI operation takes an argument or
 * not. The macros handles invoking the यंत्र with or without the
 * रेजिस्टर argument as appropriate.
 */
#घोषणा __TLBI_0(op, arg) यंत्र (ARM64_ASM_PREAMBLE			       \
			       "tlbi " #op "\n"				       \
		   ALTERNATIVE("nop\n			nop",		       \
			       "dsb ish\n		tlbi " #op,	       \
			       ARM64_WORKAROUND_REPEAT_TLBI,		       \
			       CONFIG_ARM64_WORKAROUND_REPEAT_TLBI)	       \
			    : : )

#घोषणा __TLBI_1(op, arg) यंत्र (ARM64_ASM_PREAMBLE			       \
			       "tlbi " #op ", %0\n"			       \
		   ALTERNATIVE("nop\n			nop",		       \
			       "dsb ish\n		tlbi " #op ", %0",     \
			       ARM64_WORKAROUND_REPEAT_TLBI,		       \
			       CONFIG_ARM64_WORKAROUND_REPEAT_TLBI)	       \
			    : : "r" (arg))

#घोषणा __TLBI_N(op, arg, n, ...) __TLBI_##n(op, arg)

#घोषणा __tlbi(op, ...)		__TLBI_N(op, ##__VA_ARGS__, 1, 0)

#घोषणा __tlbi_user(op, arg) करो अणु						\
	अगर (arm64_kernel_unmapped_at_el0())					\
		__tlbi(op, (arg) | USER_ASID_FLAG);				\
पूर्ण जबतक (0)

/* This macro creates a properly क्रमmatted VA opeअक्रम क्रम the TLBI */
#घोषणा __TLBI_VADDR(addr, asid)				\
	(अणु							\
		अचिन्हित दीर्घ __ta = (addr) >> 12;		\
		__ta &= GENMASK_ULL(43, 0);			\
		__ta |= (अचिन्हित दीर्घ)(asid) << 48;		\
		__ta;						\
	पूर्ण)

/*
 * Get translation granule of the प्रणाली, which is decided by
 * PAGE_SIZE.  Used by TTL.
 *  - 4KB	: 1
 *  - 16KB	: 2
 *  - 64KB	: 3
 */
#घोषणा TLBI_TTL_TG_4K		1
#घोषणा TLBI_TTL_TG_16K		2
#घोषणा TLBI_TTL_TG_64K		3

अटल अंतरभूत अचिन्हित दीर्घ get_trans_granule(व्योम)
अणु
	चयन (PAGE_SIZE) अणु
	हाल SZ_4K:
		वापस TLBI_TTL_TG_4K;
	हाल SZ_16K:
		वापस TLBI_TTL_TG_16K;
	हाल SZ_64K:
		वापस TLBI_TTL_TG_64K;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/*
 * Level-based TLBI operations.
 *
 * When ARMv8.4-TTL exists, TLBI operations take an additional hपूर्णांक क्रम
 * the level at which the invalidation must take place. If the level is
 * wrong, no invalidation may take place. In the हाल where the level
 * cannot be easily determined, a 0 value क्रम the level parameter will
 * perक्रमm a non-hपूर्णांकed invalidation.
 *
 * For Stage-2 invalidation, use the level values provided to that effect
 * in यंत्र/stage2_pgtable.h.
 */
#घोषणा TLBI_TTL_MASK		GENMASK_ULL(47, 44)

#घोषणा __tlbi_level(op, addr, level) करो अणु				\
	u64 arg = addr;							\
									\
	अगर (cpus_have_स्थिर_cap(ARM64_HAS_ARMv8_4_TTL) &&		\
	    level) अणु							\
		u64 ttl = level & 3;					\
		ttl |= get_trans_granule() << 2;			\
		arg &= ~TLBI_TTL_MASK;					\
		arg |= FIELD_PREP(TLBI_TTL_MASK, ttl);			\
	पूर्ण								\
									\
	__tlbi(op, arg);						\
पूर्ण जबतक(0)

#घोषणा __tlbi_user_level(op, arg, level) करो अणु				\
	अगर (arm64_kernel_unmapped_at_el0())				\
		__tlbi_level(op, (arg | USER_ASID_FLAG), level);	\
पूर्ण जबतक (0)

/*
 * This macro creates a properly क्रमmatted VA opeअक्रम क्रम the TLB RANGE.
 * The value bit assignments are:
 *
 * +----------+------+-------+-------+-------+----------------------+
 * |   ASID   |  TG  | SCALE |  NUM  |  TTL  |        BADDR         |
 * +-----------------+-------+-------+-------+----------------------+
 * |63      48|47  46|45   44|43   39|38   37|36                   0|
 *
 * The address range is determined by below क्रमmula:
 * [BADDR, BADDR + (NUM + 1) * 2^(5*SCALE + 1) * PAGESIZE)
 *
 */
#घोषणा __TLBI_VADDR_RANGE(addr, asid, scale, num, ttl)		\
	(अणु							\
		अचिन्हित दीर्घ __ta = (addr) >> PAGE_SHIFT;	\
		__ta &= GENMASK_ULL(36, 0);			\
		__ta |= (अचिन्हित दीर्घ)(ttl) << 37;		\
		__ta |= (अचिन्हित दीर्घ)(num) << 39;		\
		__ta |= (अचिन्हित दीर्घ)(scale) << 44;		\
		__ta |= get_trans_granule() << 46;		\
		__ta |= (अचिन्हित दीर्घ)(asid) << 48;		\
		__ta;						\
	पूर्ण)

/* These macros are used by the TLBI RANGE feature. */
#घोषणा __TLBI_RANGE_PAGES(num, scale)	\
	((अचिन्हित दीर्घ)((num) + 1) << (5 * (scale) + 1))
#घोषणा MAX_TLBI_RANGE_PAGES		__TLBI_RANGE_PAGES(31, 3)

/*
 * Generate 'num' values from -1 to 30 with -1 rejected by the
 * __flush_tlb_range() loop below.
 */
#घोषणा TLBI_RANGE_MASK			GENMASK_ULL(4, 0)
#घोषणा __TLBI_RANGE_NUM(pages, scale)	\
	((((pages) >> (5 * (scale) + 1)) & TLBI_RANGE_MASK) - 1)

/*
 *	TLB Invalidation
 *	================
 *
 * 	This header file implements the low-level TLB invalidation routines
 *	(someबार referred to as "flushing" in the kernel) क्रम arm64.
 *
 *	Every invalidation operation uses the following ढाँचा:
 *
 *	DSB ISHST	// Ensure prior page-table updates have completed
 *	TLBI ...	// Invalidate the TLB
 *	DSB ISH		// Ensure the TLB invalidation has completed
 *      अगर (invalidated kernel mappings)
 *		ISB	// Discard any inकाष्ठाions fetched from the old mapping
 *
 *
 *	The following functions क्रमm part of the "core" TLB invalidation API,
 *	as करोcumented in Documentation/core-api/cachetlb.rst:
 *
 *	flush_tlb_all()
 *		Invalidate the entire TLB (kernel + user) on all CPUs
 *
 *	flush_tlb_mm(mm)
 *		Invalidate an entire user address space on all CPUs.
 *		The 'mm' argument identअगरies the ASID to invalidate.
 *
 *	flush_tlb_range(vma, start, end)
 *		Invalidate the भव-address range '[start, end)' on all
 *		CPUs क्रम the user address space corresponding to 'vma->mm'.
 *		Note that this operation also invalidates any walk-cache
 *		entries associated with translations क्रम the specअगरied address
 *		range.
 *
 *	flush_tlb_kernel_range(start, end)
 *		Same as flush_tlb_range(..., start, end), but applies to
 * 		kernel mappings rather than a particular user address space.
 *		Whilst not explicitly करोcumented, this function is used when
 *		unmapping pages from vदो_स्मृति/io space.
 *
 *	flush_tlb_page(vma, addr)
 *		Invalidate a single user mapping क्रम address 'addr' in the
 *		address space corresponding to 'vma->mm'.  Note that this
 *		operation only invalidates a single, last-level page-table
 *		entry and thereक्रमe करोes not affect any walk-caches.
 *
 *
 *	Next, we have some unकरोcumented invalidation routines that you probably
 *	करोn't want to call unless you know what you're करोing:
 *
 *	local_flush_tlb_all()
 *		Same as flush_tlb_all(), but only applies to the calling CPU.
 *
 *	__flush_tlb_kernel_pgtable(addr)
 *		Invalidate a single kernel mapping क्रम address 'addr' on all
 *		CPUs, ensuring that any walk-cache entries associated with the
 *		translation are also invalidated.
 *
 *	__flush_tlb_range(vma, start, end, stride, last_level)
 *		Invalidate the भव-address range '[start, end)' on all
 *		CPUs क्रम the user address space corresponding to 'vma->mm'.
 *		The invalidation operations are issued at a granularity
 *		determined by 'stride' and only affect any walk-cache entries
 *		अगर 'last_level' is equal to false.
 *
 *
 *	Finally, take a look at यंत्र/tlb.h to see how tlb_flush() is implemented
 *	on top of these routines, since that is our पूर्णांकerface to the mmu_gather
 *	API as used by munmap() and मित्रs.
 */
अटल अंतरभूत व्योम local_flush_tlb_all(व्योम)
अणु
	dsb(nshst);
	__tlbi(vmalle1);
	dsb(nsh);
	isb();
पूर्ण

अटल अंतरभूत व्योम flush_tlb_all(व्योम)
अणु
	dsb(ishst);
	__tlbi(vmalle1is);
	dsb(ish);
	isb();
पूर्ण

अटल अंतरभूत व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ asid = __TLBI_VADDR(0, ASID(mm));

	dsb(ishst);
	__tlbi(aside1is, asid);
	__tlbi_user(aside1is, asid);
	dsb(ish);
पूर्ण

अटल अंतरभूत व्योम flush_tlb_page_nosync(काष्ठा vm_area_काष्ठा *vma,
					 अचिन्हित दीर्घ uaddr)
अणु
	अचिन्हित दीर्घ addr = __TLBI_VADDR(uaddr, ASID(vma->vm_mm));

	dsb(ishst);
	__tlbi(vale1is, addr);
	__tlbi_user(vale1is, addr);
पूर्ण

अटल अंतरभूत व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *vma,
				  अचिन्हित दीर्घ uaddr)
अणु
	flush_tlb_page_nosync(vma, uaddr);
	dsb(ish);
पूर्ण

/*
 * This is meant to aव्योम soft lock-ups on large TLB flushing ranges and not
 * necessarily a perक्रमmance improvement.
 */
#घोषणा MAX_TLBI_OPS	PTRS_PER_PTE

अटल अंतरभूत व्योम __flush_tlb_range(काष्ठा vm_area_काष्ठा *vma,
				     अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				     अचिन्हित दीर्घ stride, bool last_level,
				     पूर्णांक tlb_level)
अणु
	पूर्णांक num = 0;
	पूर्णांक scale = 0;
	अचिन्हित दीर्घ asid = ASID(vma->vm_mm);
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ pages;

	start = round_करोwn(start, stride);
	end = round_up(end, stride);
	pages = (end - start) >> PAGE_SHIFT;

	/*
	 * When not uses TLB range ops, we can handle up to
	 * (MAX_TLBI_OPS - 1) pages;
	 * When uses TLB range ops, we can handle up to
	 * (MAX_TLBI_RANGE_PAGES - 1) pages.
	 */
	अगर ((!प्रणाली_supports_tlb_range() &&
	     (end - start) >= (MAX_TLBI_OPS * stride)) ||
	    pages >= MAX_TLBI_RANGE_PAGES) अणु
		flush_tlb_mm(vma->vm_mm);
		वापस;
	पूर्ण

	dsb(ishst);

	/*
	 * When the CPU करोes not support TLB range operations, flush the TLB
	 * entries one by one at the granularity of 'stride'. If the the TLB
	 * range ops are supported, then:
	 *
	 * 1. If 'pages' is odd, flush the first page through non-range
	 *    operations;
	 *
	 * 2. For reमुख्यing pages: the minimum range granularity is decided
	 *    by 'scale', so multiple range TLBI operations may be required.
	 *    Start from scale = 0, flush the corresponding number of pages
	 *    ((num+1)*2^(5*scale+1) starting from 'addr'), then increase it
	 *    until no pages left.
	 *
	 * Note that certain ranges can be represented by either num = 31 and
	 * scale or num = 0 and scale + 1. The loop below favours the latter
	 * since num is limited to 30 by the __TLBI_RANGE_NUM() macro.
	 */
	जबतक (pages > 0) अणु
		अगर (!प्रणाली_supports_tlb_range() ||
		    pages % 2 == 1) अणु
			addr = __TLBI_VADDR(start, asid);
			अगर (last_level) अणु
				__tlbi_level(vale1is, addr, tlb_level);
				__tlbi_user_level(vale1is, addr, tlb_level);
			पूर्ण अन्यथा अणु
				__tlbi_level(vae1is, addr, tlb_level);
				__tlbi_user_level(vae1is, addr, tlb_level);
			पूर्ण
			start += stride;
			pages -= stride >> PAGE_SHIFT;
			जारी;
		पूर्ण

		num = __TLBI_RANGE_NUM(pages, scale);
		अगर (num >= 0) अणु
			addr = __TLBI_VADDR_RANGE(start, asid, scale,
						  num, tlb_level);
			अगर (last_level) अणु
				__tlbi(rvale1is, addr);
				__tlbi_user(rvale1is, addr);
			पूर्ण अन्यथा अणु
				__tlbi(rvae1is, addr);
				__tlbi_user(rvae1is, addr);
			पूर्ण
			start += __TLBI_RANGE_PAGES(num, scale) << PAGE_SHIFT;
			pages -= __TLBI_RANGE_PAGES(num, scale);
		पूर्ण
		scale++;
	पूर्ण
	dsb(ish);
पूर्ण

अटल अंतरभूत व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *vma,
				   अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	/*
	 * We cannot use leaf-only invalidation here, since we may be invalidating
	 * table entries as part of collapsing hugepages or moving page tables.
	 * Set the tlb_level to 0 because we can not get enough inक्रमmation here.
	 */
	__flush_tlb_range(vma, start, end, PAGE_SIZE, false, 0);
पूर्ण

अटल अंतरभूत व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ addr;

	अगर ((end - start) > (MAX_TLBI_OPS * PAGE_SIZE)) अणु
		flush_tlb_all();
		वापस;
	पूर्ण

	start = __TLBI_VADDR(start, 0);
	end = __TLBI_VADDR(end, 0);

	dsb(ishst);
	क्रम (addr = start; addr < end; addr += 1 << (PAGE_SHIFT - 12))
		__tlbi(vaale1is, addr);
	dsb(ish);
	isb();
पूर्ण

/*
 * Used to invalidate the TLB (walk caches) corresponding to पूर्णांकermediate page
 * table levels (pgd/pud/pmd).
 */
अटल अंतरभूत व्योम __flush_tlb_kernel_pgtable(अचिन्हित दीर्घ kaddr)
अणु
	अचिन्हित दीर्घ addr = __TLBI_VADDR(kaddr, 0);

	dsb(ishst);
	__tlbi(vaae1is, addr);
	dsb(ish);
	isb();
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
