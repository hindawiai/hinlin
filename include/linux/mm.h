<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_MM_H
#घोषणा _LINUX_MM_H

#समावेश <linux/त्रुटिसं.स>

#अगर_घोषित __KERNEL__

#समावेश <linux/mmdebug.h>
#समावेश <linux/gfp.h>
#समावेश <linux/bug.h>
#समावेश <linux/list.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/atomic.h>
#समावेश <linux/debug_locks.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/mmap_lock.h>
#समावेश <linux/range.h>
#समावेश <linux/pfn.h>
#समावेश <linux/percpu-refcount.h>
#समावेश <linux/bit_spinlock.h>
#समावेश <linux/shrinker.h>
#समावेश <linux/resource.h>
#समावेश <linux/page_ext.h>
#समावेश <linux/err.h>
#समावेश <linux/page-flags.h>
#समावेश <linux/page_ref.h>
#समावेश <linux/memremap.h>
#समावेश <linux/overflow.h>
#समावेश <linux/sizes.h>
#समावेश <linux/sched.h>
#समावेश <linux/pgtable.h>
#समावेश <linux/kasan.h>

काष्ठा mempolicy;
काष्ठा anon_vma;
काष्ठा anon_vma_chain;
काष्ठा file_ra_state;
काष्ठा user_काष्ठा;
काष्ठा ग_लिखोback_control;
काष्ठा bdi_ग_लिखोback;
काष्ठा pt_regs;

बाह्य पूर्णांक sysctl_page_lock_unfairness;

व्योम init_mm_पूर्णांकernals(व्योम);

#अगर_अघोषित CONFIG_NEED_MULTIPLE_NODES	/* Don't use mapnrs, करो it properly */
बाह्य अचिन्हित दीर्घ max_mapnr;

अटल अंतरभूत व्योम set_max_mapnr(अचिन्हित दीर्घ limit)
अणु
	max_mapnr = limit;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम set_max_mapnr(अचिन्हित दीर्घ limit) अणु पूर्ण
#पूर्ण_अगर

बाह्य atomic_दीर्घ_t _totalram_pages;
अटल अंतरभूत अचिन्हित दीर्घ totalram_pages(व्योम)
अणु
	वापस (अचिन्हित दीर्घ)atomic_दीर्घ_पढ़ो(&_totalram_pages);
पूर्ण

अटल अंतरभूत व्योम totalram_pages_inc(व्योम)
अणु
	atomic_दीर्घ_inc(&_totalram_pages);
पूर्ण

अटल अंतरभूत व्योम totalram_pages_dec(व्योम)
अणु
	atomic_दीर्घ_dec(&_totalram_pages);
पूर्ण

अटल अंतरभूत व्योम totalram_pages_add(दीर्घ count)
अणु
	atomic_दीर्घ_add(count, &_totalram_pages);
पूर्ण

बाह्य व्योम * high_memory;
बाह्य पूर्णांक page_cluster;

#अगर_घोषित CONFIG_SYSCTL
बाह्य पूर्णांक sysctl_legacy_va_layout;
#अन्यथा
#घोषणा sysctl_legacy_va_layout 0
#पूर्ण_अगर

#अगर_घोषित CONFIG_HAVE_ARCH_MMAP_RND_BITS
बाह्य स्थिर पूर्णांक mmap_rnd_bits_min;
बाह्य स्थिर पूर्णांक mmap_rnd_bits_max;
बाह्य पूर्णांक mmap_rnd_bits __पढ़ो_mostly;
#पूर्ण_अगर
#अगर_घोषित CONFIG_HAVE_ARCH_MMAP_RND_COMPAT_BITS
बाह्य स्थिर पूर्णांक mmap_rnd_compat_bits_min;
बाह्य स्थिर पूर्णांक mmap_rnd_compat_bits_max;
बाह्य पूर्णांक mmap_rnd_compat_bits __पढ़ो_mostly;
#पूर्ण_अगर

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/processor.h>

/*
 * Architectures that support memory tagging (assigning tags to memory regions,
 * embedding these tags पूर्णांकo addresses that poपूर्णांक to these memory regions, and
 * checking that the memory and the poपूर्णांकer tags match on memory accesses)
 * redefine this macro to strip tags from poपूर्णांकers.
 * It's defined as noop for architectures that don't support memory tagging.
 */
#अगर_अघोषित untagged_addr
#घोषणा untagged_addr(addr) (addr)
#पूर्ण_अगर

#अगर_अघोषित __pa_symbol
#घोषणा __pa_symbol(x)  __pa(RELOC_HIDE((अचिन्हित दीर्घ)(x), 0))
#पूर्ण_अगर

#अगर_अघोषित page_to_virt
#घोषणा page_to_virt(x)	__va(PFN_PHYS(page_to_pfn(x)))
#पूर्ण_अगर

#अगर_अघोषित lm_alias
#घोषणा lm_alias(x)	__va(__pa_symbol(x))
#पूर्ण_अगर

/*
 * With CONFIG_CFI_CLANG, the compiler replaces function addresses in
 * instrumented C code with jump table addresses. Architectures that
 * support CFI can define this macro to वापस the actual function address
 * when needed.
 */
#अगर_अघोषित function_nocfi
#घोषणा function_nocfi(x) (x)
#पूर्ण_अगर

/*
 * To prevent common memory management code establishing
 * a zero page mapping on a पढ़ो fault.
 * This macro should be defined within <यंत्र/pgtable.h>.
 * s390 करोes this to prevent multiplexing of hardware bits
 * related to the physical page in हाल of भवization.
 */
#अगर_अघोषित mm_क्रमbids_zeropage
#घोषणा mm_क्रमbids_zeropage(X)	(0)
#पूर्ण_अगर

/*
 * On some architectures it is expensive to call स_रखो() क्रम small sizes.
 * If an architecture decides to implement their own version of
 * mm_zero_काष्ठा_page they should wrap the defines below in a #अगर_अघोषित and
 * define their own version of this macro in <यंत्र/pgtable.h>
 */
#अगर BITS_PER_LONG == 64
/* This function must be updated when the size of काष्ठा page grows above 80
 * or reduces below 56. The idea that compiler optimizes out चयन()
 * statement, and only leaves move/store inकाष्ठाions. Also the compiler can
 * combine ग_लिखो staपंचांगents अगर they are both assignments and can be reordered,
 * this can result in several of the ग_लिखोs here being dropped.
 */
#घोषणा	mm_zero_काष्ठा_page(pp) __mm_zero_काष्ठा_page(pp)
अटल अंतरभूत व्योम __mm_zero_काष्ठा_page(काष्ठा page *page)
अणु
	अचिन्हित दीर्घ *_pp = (व्योम *)page;

	 /* Check that काष्ठा page is either 56, 64, 72, or 80 bytes */
	BUILD_BUG_ON(माप(काष्ठा page) & 7);
	BUILD_BUG_ON(माप(काष्ठा page) < 56);
	BUILD_BUG_ON(माप(काष्ठा page) > 80);

	चयन (माप(काष्ठा page)) अणु
	हाल 80:
		_pp[9] = 0;
		fallthrough;
	हाल 72:
		_pp[8] = 0;
		fallthrough;
	हाल 64:
		_pp[7] = 0;
		fallthrough;
	हाल 56:
		_pp[6] = 0;
		_pp[5] = 0;
		_pp[4] = 0;
		_pp[3] = 0;
		_pp[2] = 0;
		_pp[1] = 0;
		_pp[0] = 0;
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा mm_zero_काष्ठा_page(pp)  ((व्योम)स_रखो((pp), 0, माप(काष्ठा page)))
#पूर्ण_अगर

/*
 * Default maximum number of active map areas, this limits the number of vmas
 * per mm काष्ठा. Users can overग_लिखो this number by sysctl but there is a
 * problem.
 *
 * When a program's coredump is generated as ELF क्रमmat, a section is created
 * per a vma. In ELF, the number of sections is represented in अचिन्हित लघु.
 * This means the number of sections should be smaller than 65535 at coredump.
 * Because the kernel adds some inक्रमmative sections to a image of program at
 * generating coredump, we need some margin. The number of extra sections is
 * 1-3 now and depends on arch. We use "5" as safe margin, here.
 *
 * ELF extended numbering allows more than 65535 sections, so 16-bit bound is
 * not a hard limit any more. Although some userspace tools can be surprised by
 * that.
 */
#घोषणा MAPCOUNT_ELF_CORE_MARGIN	(5)
#घोषणा DEFAULT_MAX_MAP_COUNT	(अच_लघु_उच्च - MAPCOUNT_ELF_CORE_MARGIN)

बाह्य पूर्णांक sysctl_max_map_count;

बाह्य अचिन्हित दीर्घ sysctl_user_reserve_kbytes;
बाह्य अचिन्हित दीर्घ sysctl_admin_reserve_kbytes;

बाह्य पूर्णांक sysctl_overcommit_memory;
बाह्य पूर्णांक sysctl_overcommit_ratio;
बाह्य अचिन्हित दीर्घ sysctl_overcommit_kbytes;

पूर्णांक overcommit_ratio_handler(काष्ठा ctl_table *, पूर्णांक, व्योम *, माप_प्रकार *,
		loff_t *);
पूर्णांक overcommit_kbytes_handler(काष्ठा ctl_table *, पूर्णांक, व्योम *, माप_प्रकार *,
		loff_t *);
पूर्णांक overcommit_policy_handler(काष्ठा ctl_table *, पूर्णांक, व्योम *, माप_प्रकार *,
		loff_t *);
/*
 * Any attempt to mark this function as अटल leads to build failure
 * when CONFIG_DEBUG_INFO_BTF is enabled because __add_to_page_cache_locked()
 * is referred to by BPF code. This must be visible क्रम error injection.
 */
पूर्णांक __add_to_page_cache_locked(काष्ठा page *page, काष्ठा address_space *mapping,
		pgoff_t index, gfp_t gfp, व्योम **shaकरोwp);

#घोषणा nth_page(page,n) pfn_to_page(page_to_pfn((page)) + (n))

/* to align the poपूर्णांकer to the (next) page boundary */
#घोषणा PAGE_ALIGN(addr) ALIGN(addr, PAGE_SIZE)

/* test whether an address (अचिन्हित दीर्घ or poपूर्णांकer) is aligned to PAGE_SIZE */
#घोषणा PAGE_ALIGNED(addr)	IS_ALIGNED((अचिन्हित दीर्घ)(addr), PAGE_SIZE)

#घोषणा lru_to_page(head) (list_entry((head)->prev, काष्ठा page, lru))

/*
 * Linux kernel भव memory manager primitives.
 * The idea being to have a "virtual" mm in the same way
 * we have a भव fs - giving a cleaner पूर्णांकerface to the
 * mm details, and allowing dअगरferent kinds of memory mappings
 * (from shared memory to executable loading to arbitrary
 * mmap() functions).
 */

काष्ठा vm_area_काष्ठा *vm_area_alloc(काष्ठा mm_काष्ठा *);
काष्ठा vm_area_काष्ठा *vm_area_dup(काष्ठा vm_area_काष्ठा *);
व्योम vm_area_मुक्त(काष्ठा vm_area_काष्ठा *);

#अगर_अघोषित CONFIG_MMU
बाह्य काष्ठा rb_root nommu_region_tree;
बाह्य काष्ठा rw_semaphore nommu_region_sem;

बाह्य अचिन्हित पूर्णांक kobjsize(स्थिर व्योम *objp);
#पूर्ण_अगर

/*
 * vm_flags in vm_area_काष्ठा, see mm_types.h.
 * When changing, update also include/trace/events/mmflags.h
 */
#घोषणा VM_NONE		0x00000000

#घोषणा VM_READ		0x00000001	/* currently active flags */
#घोषणा VM_WRITE	0x00000002
#घोषणा VM_EXEC		0x00000004
#घोषणा VM_SHARED	0x00000008

/* mprotect() hardcodes VM_MAYREAD >> 4 == VM_READ, and so क्रम r/w/x bits. */
#घोषणा VM_MAYREAD	0x00000010	/* limits क्रम mprotect() etc */
#घोषणा VM_MAYWRITE	0x00000020
#घोषणा VM_MAYEXEC	0x00000040
#घोषणा VM_MAYSHARE	0x00000080

#घोषणा VM_GROWSDOWN	0x00000100	/* general info on the segment */
#घोषणा VM_UFFD_MISSING	0x00000200	/* missing pages tracking */
#घोषणा VM_PFNMAP	0x00000400	/* Page-ranges managed without "struct page", just pure PFN */
#घोषणा VM_DENYWRITE	0x00000800	/* ETXTBSY on ग_लिखो attempts.. */
#घोषणा VM_UFFD_WP	0x00001000	/* wrprotect pages tracking */

#घोषणा VM_LOCKED	0x00002000
#घोषणा VM_IO           0x00004000	/* Memory mapped I/O or similar */

					/* Used by sys_madvise() */
#घोषणा VM_SEQ_READ	0x00008000	/* App will access data sequentially */
#घोषणा VM_RAND_READ	0x00010000	/* App will not benefit from clustered पढ़ोs */

#घोषणा VM_DONTCOPY	0x00020000      /* Do not copy this vma on विभाजन */
#घोषणा VM_DONTEXPAND	0x00040000	/* Cannot expand with mremap() */
#घोषणा VM_LOCKONFAULT	0x00080000	/* Lock the pages covered when they are faulted in */
#घोषणा VM_ACCOUNT	0x00100000	/* Is a VM accounted object */
#घोषणा VM_NORESERVE	0x00200000	/* should the VM suppress accounting */
#घोषणा VM_HUGETLB	0x00400000	/* Huge TLB Page VM */
#घोषणा VM_SYNC		0x00800000	/* Synchronous page faults */
#घोषणा VM_ARCH_1	0x01000000	/* Architecture-specअगरic flag */
#घोषणा VM_WIPEONFORK	0x02000000	/* Wipe VMA contents in child. */
#घोषणा VM_DONTDUMP	0x04000000	/* Do not include in the core dump */

#अगर_घोषित CONFIG_MEM_SOFT_सूचीTY
# define VM_SOFTसूचीTY	0x08000000	/* Not soft dirty clean area */
#अन्यथा
# define VM_SOFTसूचीTY	0
#पूर्ण_अगर

#घोषणा VM_MIXEDMAP	0x10000000	/* Can contain "struct page" and pure PFN pages */
#घोषणा VM_HUGEPAGE	0x20000000	/* MADV_HUGEPAGE marked this vma */
#घोषणा VM_NOHUGEPAGE	0x40000000	/* MADV_NOHUGEPAGE marked this vma */
#घोषणा VM_MERGEABLE	0x80000000	/* KSM may merge identical pages */

#अगर_घोषित CONFIG_ARCH_USES_HIGH_VMA_FLAGS
#घोषणा VM_HIGH_ARCH_BIT_0	32	/* bit only usable on 64-bit architectures */
#घोषणा VM_HIGH_ARCH_BIT_1	33	/* bit only usable on 64-bit architectures */
#घोषणा VM_HIGH_ARCH_BIT_2	34	/* bit only usable on 64-bit architectures */
#घोषणा VM_HIGH_ARCH_BIT_3	35	/* bit only usable on 64-bit architectures */
#घोषणा VM_HIGH_ARCH_BIT_4	36	/* bit only usable on 64-bit architectures */
#घोषणा VM_HIGH_ARCH_0	BIT(VM_HIGH_ARCH_BIT_0)
#घोषणा VM_HIGH_ARCH_1	BIT(VM_HIGH_ARCH_BIT_1)
#घोषणा VM_HIGH_ARCH_2	BIT(VM_HIGH_ARCH_BIT_2)
#घोषणा VM_HIGH_ARCH_3	BIT(VM_HIGH_ARCH_BIT_3)
#घोषणा VM_HIGH_ARCH_4	BIT(VM_HIGH_ARCH_BIT_4)
#पूर्ण_अगर /* CONFIG_ARCH_USES_HIGH_VMA_FLAGS */

#अगर_घोषित CONFIG_ARCH_HAS_PKEYS
# define VM_PKEY_SHIFT	VM_HIGH_ARCH_BIT_0
# define VM_PKEY_BIT0	VM_HIGH_ARCH_0	/* A protection key is a 4-bit value */
# define VM_PKEY_BIT1	VM_HIGH_ARCH_1	/* on x86 and 5-bit value on ppc64   */
# define VM_PKEY_BIT2	VM_HIGH_ARCH_2
# define VM_PKEY_BIT3	VM_HIGH_ARCH_3
#अगर_घोषित CONFIG_PPC
# define VM_PKEY_BIT4  VM_HIGH_ARCH_4
#अन्यथा
# define VM_PKEY_BIT4  0
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_ARCH_HAS_PKEYS */

#अगर defined(CONFIG_X86)
# define VM_PAT		VM_ARCH_1	/* PAT reserves whole VMA at once (x86) */
#या_अगर defined(CONFIG_PPC)
# define VM_SAO		VM_ARCH_1	/* Strong Access Ordering (घातerpc) */
#या_अगर defined(CONFIG_PARISC)
# define VM_GROWSUP	VM_ARCH_1
#या_अगर defined(CONFIG_IA64)
# define VM_GROWSUP	VM_ARCH_1
#या_अगर defined(CONFIG_SPARC64)
# define VM_SPARC_ADI	VM_ARCH_1	/* Uses ADI tag क्रम access control */
# define VM_ARCH_CLEAR	VM_SPARC_ADI
#या_अगर defined(CONFIG_ARM64)
# define VM_ARM64_BTI	VM_ARCH_1	/* BTI guarded page, a.k.a. GP bit */
# define VM_ARCH_CLEAR	VM_ARM64_BTI
#या_अगर !defined(CONFIG_MMU)
# define VM_MAPPED_COPY	VM_ARCH_1	/* T अगर mapped copy of data (nommu mmap) */
#पूर्ण_अगर

#अगर defined(CONFIG_ARM64_MTE)
# define VM_MTE		VM_HIGH_ARCH_0	/* Use Tagged memory क्रम access control */
# define VM_MTE_ALLOWED	VM_HIGH_ARCH_1	/* Tagged memory permitted */
#अन्यथा
# define VM_MTE		VM_NONE
# define VM_MTE_ALLOWED	VM_NONE
#पूर्ण_अगर

#अगर_अघोषित VM_GROWSUP
# define VM_GROWSUP	VM_NONE
#पूर्ण_अगर

#अगर_घोषित CONFIG_HAVE_ARCH_USERFAULTFD_MINOR
# define VM_UFFD_MINOR_BIT	37
# define VM_UFFD_MINOR		BIT(VM_UFFD_MINOR_BIT)	/* UFFD minor faults */
#अन्यथा /* !CONFIG_HAVE_ARCH_USERFAULTFD_MINOR */
# define VM_UFFD_MINOR		VM_NONE
#पूर्ण_अगर /* CONFIG_HAVE_ARCH_USERFAULTFD_MINOR */

/* Bits set in the VMA until the stack is in its final location */
#घोषणा VM_STACK_INCOMPLETE_SETUP	(VM_RAND_READ | VM_SEQ_READ)

#घोषणा TASK_EXEC ((current->personality & READ_IMPLIES_EXEC) ? VM_EXEC : 0)

/* Common data flag combinations */
#घोषणा VM_DATA_FLAGS_TSK_EXEC	(VM_READ | VM_WRITE | TASK_EXEC | \
				 VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC)
#घोषणा VM_DATA_FLAGS_NON_EXEC	(VM_READ | VM_WRITE | VM_MAYREAD | \
				 VM_MAYWRITE | VM_MAYEXEC)
#घोषणा VM_DATA_FLAGS_EXEC	(VM_READ | VM_WRITE | VM_EXEC | \
				 VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC)

#अगर_अघोषित VM_DATA_DEFAULT_FLAGS		/* arch can override this */
#घोषणा VM_DATA_DEFAULT_FLAGS  VM_DATA_FLAGS_EXEC
#पूर्ण_अगर

#अगर_अघोषित VM_STACK_DEFAULT_FLAGS		/* arch can override this */
#घोषणा VM_STACK_DEFAULT_FLAGS VM_DATA_DEFAULT_FLAGS
#पूर्ण_अगर

#अगर_घोषित CONFIG_STACK_GROWSUP
#घोषणा VM_STACK	VM_GROWSUP
#अन्यथा
#घोषणा VM_STACK	VM_GROWSDOWN
#पूर्ण_अगर

#घोषणा VM_STACK_FLAGS	(VM_STACK | VM_STACK_DEFAULT_FLAGS | VM_ACCOUNT)

/* VMA basic access permission flags */
#घोषणा VM_ACCESS_FLAGS (VM_READ | VM_WRITE | VM_EXEC)


/*
 * Special vmas that are non-mergable, non-mlock()able.
 */
#घोषणा VM_SPECIAL (VM_IO | VM_DONTEXPAND | VM_PFNMAP | VM_MIXEDMAP)

/* This mask prevents VMA from being scanned with khugepaged */
#घोषणा VM_NO_KHUGEPAGED (VM_SPECIAL | VM_HUGETLB)

/* This mask defines which mm->def_flags a process can inherit its parent */
#घोषणा VM_INIT_DEF_MASK	VM_NOHUGEPAGE

/* This mask is used to clear all the VMA flags used by mlock */
#घोषणा VM_LOCKED_CLEAR_MASK	(~(VM_LOCKED | VM_LOCKONFAULT))

/* Arch-specअगरic flags to clear when updating VM flags on protection change */
#अगर_अघोषित VM_ARCH_CLEAR
# define VM_ARCH_CLEAR	VM_NONE
#पूर्ण_अगर
#घोषणा VM_FLAGS_CLEAR	(ARCH_VM_PKEY_FLAGS | VM_ARCH_CLEAR)

/*
 * mapping from the currently active vm_flags protection bits (the
 * low four bits) to a page protection mask..
 */
बाह्य pgprot_t protection_map[16];

/**
 * क्रमागत fault_flag - Fault flag definitions.
 * @FAULT_FLAG_WRITE: Fault was a ग_लिखो fault.
 * @FAULT_FLAG_MKWRITE: Fault was mkग_लिखो of existing PTE.
 * @FAULT_FLAG_ALLOW_RETRY: Allow to retry the fault अगर blocked.
 * @FAULT_FLAG_RETRY_NOWAIT: Don't drop mmap_lock and रुको when retrying.
 * @FAULT_FLAG_KILLABLE: The fault task is in SIGKILL समाप्तable region.
 * @FAULT_FLAG_TRIED: The fault has been tried once.
 * @FAULT_FLAG_USER: The fault originated in userspace.
 * @FAULT_FLAG_REMOTE: The fault is not क्रम current task/mm.
 * @FAULT_FLAG_INSTRUCTION: The fault was during an inकाष्ठाion fetch.
 * @FAULT_FLAG_INTERRUPTIBLE: The fault can be पूर्णांकerrupted by non-fatal संकेतs.
 *
 * About @FAULT_FLAG_ALLOW_RETRY and @FAULT_FLAG_TRIED: we can specअगरy
 * whether we would allow page faults to retry by specअगरying these two
 * fault flags correctly.  Currently there can be three legal combinations:
 *
 * (a) ALLOW_RETRY and !TRIED:  this means the page fault allows retry, and
 *                              this is the first try
 *
 * (b) ALLOW_RETRY and TRIED:   this means the page fault allows retry, and
 *                              we've alपढ़ोy tried at least once
 *
 * (c) !ALLOW_RETRY and !TRIED: this means the page fault करोes not allow retry
 *
 * The unlisted combination (!ALLOW_RETRY && TRIED) is illegal and should never
 * be used.  Note that page faults can be allowed to retry क्रम multiple बार,
 * in which हाल we'll have an initial fault with flags (a) then later on
 * continuous faults with flags (b).  We should always try to detect pending
 * संकेतs beक्रमe a retry to make sure the continuous page faults can still be
 * पूर्णांकerrupted अगर necessary.
 */
क्रमागत fault_flag अणु
	FAULT_FLAG_WRITE =		1 << 0,
	FAULT_FLAG_MKWRITE =		1 << 1,
	FAULT_FLAG_ALLOW_RETRY =	1 << 2,
	FAULT_FLAG_RETRY_NOWAIT = 	1 << 3,
	FAULT_FLAG_KILLABLE =		1 << 4,
	FAULT_FLAG_TRIED = 		1 << 5,
	FAULT_FLAG_USER =		1 << 6,
	FAULT_FLAG_REMOTE =		1 << 7,
	FAULT_FLAG_INSTRUCTION =	1 << 8,
	FAULT_FLAG_INTERRUPTIBLE =	1 << 9,
पूर्ण;

/*
 * The शेष fault flags that should be used by most of the
 * arch-specअगरic page fault handlers.
 */
#घोषणा FAULT_FLAG_DEFAULT  (FAULT_FLAG_ALLOW_RETRY | \
			     FAULT_FLAG_KILLABLE | \
			     FAULT_FLAG_INTERRUPTIBLE)

/**
 * fault_flag_allow_retry_first - check ALLOW_RETRY the first समय
 * @flags: Fault flags.
 *
 * This is mostly used क्रम places where we want to try to aव्योम taking
 * the mmap_lock क्रम too दीर्घ a समय when रुकोing क्रम another condition
 * to change, in which हाल we can try to be polite to release the
 * mmap_lock in the first round to aव्योम potential starvation of other
 * processes that would also want the mmap_lock.
 *
 * Return: true अगर the page fault allows retry and this is the first
 * attempt of the fault handling; false otherwise.
 */
अटल अंतरभूत bool fault_flag_allow_retry_first(क्रमागत fault_flag flags)
अणु
	वापस (flags & FAULT_FLAG_ALLOW_RETRY) &&
	    (!(flags & FAULT_FLAG_TRIED));
पूर्ण

#घोषणा FAULT_FLAG_TRACE \
	अणु FAULT_FLAG_WRITE,		"WRITE" पूर्ण, \
	अणु FAULT_FLAG_MKWRITE,		"MKWRITE" पूर्ण, \
	अणु FAULT_FLAG_ALLOW_RETRY,	"ALLOW_RETRY" पूर्ण, \
	अणु FAULT_FLAG_RETRY_NOWAIT,	"RETRY_NOWAIT" पूर्ण, \
	अणु FAULT_FLAG_KILLABLE,		"KILLABLE" पूर्ण, \
	अणु FAULT_FLAG_TRIED,		"TRIED" पूर्ण, \
	अणु FAULT_FLAG_USER,		"USER" पूर्ण, \
	अणु FAULT_FLAG_REMOTE,		"REMOTE" पूर्ण, \
	अणु FAULT_FLAG_INSTRUCTION,	"INSTRUCTION" पूर्ण, \
	अणु FAULT_FLAG_INTERRUPTIBLE,	"INTERRUPTIBLE" पूर्ण

/*
 * vm_fault is filled by the pagefault handler and passed to the vma's
 * ->fault function. The vma's ->fault is responsible क्रम वापसing a biपंचांगask
 * of VM_FAULT_xxx flags that give details about how the fault was handled.
 *
 * MM layer fills up gfp_mask क्रम page allocations but fault handler might
 * alter it अगर its implementation requires a dअगरferent allocation context.
 *
 * pgoff should be used in favour of भव_address, अगर possible.
 */
काष्ठा vm_fault अणु
	स्थिर काष्ठा अणु
		काष्ठा vm_area_काष्ठा *vma;	/* Target VMA */
		gfp_t gfp_mask;			/* gfp mask to be used क्रम allocations */
		pgoff_t pgoff;			/* Logical page offset based on vma */
		अचिन्हित दीर्घ address;		/* Faulting भव address */
	पूर्ण;
	क्रमागत fault_flag flags;		/* FAULT_FLAG_xxx flags
					 * XXX: should really be 'const' */
	pmd_t *pmd;			/* Poपूर्णांकer to pmd entry matching
					 * the 'address' */
	pud_t *pud;			/* Poपूर्णांकer to pud entry matching
					 * the 'address'
					 */
	pte_t orig_pte;			/* Value of PTE at the समय of fault */

	काष्ठा page *cow_page;		/* Page handler may use क्रम COW fault */
	काष्ठा page *page;		/* ->fault handlers should वापस a
					 * page here, unless VM_FAULT_NOPAGE
					 * is set (which is also implied by
					 * VM_FAULT_ERROR).
					 */
	/* These three entries are valid only जबतक holding ptl lock */
	pte_t *pte;			/* Poपूर्णांकer to pte entry matching
					 * the 'address'. शून्य अगर the page
					 * table hasn't been allocated.
					 */
	spinlock_t *ptl;		/* Page table lock.
					 * Protects pte page table अगर 'pte'
					 * is not शून्य, otherwise pmd.
					 */
	pgtable_t pपुनः_स्मृति_pte;		/* Pre-allocated pte page table.
					 * vm_ops->map_pages() sets up a page
					 * table from atomic context.
					 * करो_fault_around() pre-allocates
					 * page table to aव्योम allocation from
					 * atomic context.
					 */
पूर्ण;

/* page entry size क्रम vm->huge_fault() */
क्रमागत page_entry_size अणु
	PE_SIZE_PTE = 0,
	PE_SIZE_PMD,
	PE_SIZE_PUD,
पूर्ण;

/*
 * These are the भव MM functions - खोलोing of an area, closing and
 * unmapping it (needed to keep files on disk up-to-date etc), poपूर्णांकer
 * to the functions called when a no-page or a wp-page exception occurs.
 */
काष्ठा vm_operations_काष्ठा अणु
	व्योम (*खोलो)(काष्ठा vm_area_काष्ठा * area);
	व्योम (*बंद)(काष्ठा vm_area_काष्ठा * area);
	/* Called any समय beक्रमe splitting to check अगर it's allowed */
	पूर्णांक (*may_split)(काष्ठा vm_area_काष्ठा *area, अचिन्हित दीर्घ addr);
	पूर्णांक (*mremap)(काष्ठा vm_area_काष्ठा *area);
	/*
	 * Called by mprotect() to make driver-specअगरic permission
	 * checks beक्रमe mprotect() is finalised.   The VMA must not
	 * be modअगरied.  Returns 0 अगर eprotect() can proceed.
	 */
	पूर्णांक (*mprotect)(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
			अचिन्हित दीर्घ end, अचिन्हित दीर्घ newflags);
	vm_fault_t (*fault)(काष्ठा vm_fault *vmf);
	vm_fault_t (*huge_fault)(काष्ठा vm_fault *vmf,
			क्रमागत page_entry_size pe_size);
	vm_fault_t (*map_pages)(काष्ठा vm_fault *vmf,
			pgoff_t start_pgoff, pgoff_t end_pgoff);
	अचिन्हित दीर्घ (*pagesize)(काष्ठा vm_area_काष्ठा * area);

	/* notअगरication that a previously पढ़ो-only page is about to become
	 * writable, अगर an error is वापसed it will cause a SIGBUS */
	vm_fault_t (*page_mkग_लिखो)(काष्ठा vm_fault *vmf);

	/* same as page_mkग_लिखो when using VM_PFNMAP|VM_MIXEDMAP */
	vm_fault_t (*pfn_mkग_लिखो)(काष्ठा vm_fault *vmf);

	/* called by access_process_vm when get_user_pages() fails, typically
	 * क्रम use by special VMAs. See also generic_access_phys() क्रम a generic
	 * implementation useful क्रम any iomem mapping.
	 */
	पूर्णांक (*access)(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
		      व्योम *buf, पूर्णांक len, पूर्णांक ग_लिखो);

	/* Called by the /proc/PID/maps code to ask the vma whether it
	 * has a special name.  Returning non-शून्य will also cause this
	 * vma to be dumped unconditionally. */
	स्थिर अक्षर *(*name)(काष्ठा vm_area_काष्ठा *vma);

#अगर_घोषित CONFIG_NUMA
	/*
	 * set_policy() op must add a reference to any non-शून्य @new mempolicy
	 * to hold the policy upon वापस.  Caller should pass शून्य @new to
	 * हटाओ a policy and fall back to surrounding context--i.e. करो not
	 * install a MPOL_DEFAULT policy, nor the task or प्रणाली शेष
	 * mempolicy.
	 */
	पूर्णांक (*set_policy)(काष्ठा vm_area_काष्ठा *vma, काष्ठा mempolicy *new);

	/*
	 * get_policy() op must add reference [mpol_get()] to any policy at
	 * (vma,addr) marked as MPOL_SHARED.  The shared policy infraकाष्ठाure
	 * in mm/mempolicy.c will करो this स्वतःmatically.
	 * get_policy() must NOT add a ref अगर the policy at (vma,addr) is not
	 * marked as MPOL_SHARED. vma policies are रक्षित by the mmap_lock.
	 * If no [shared/vma] mempolicy exists at the addr, get_policy() op
	 * must वापस शून्य--i.e., करो not "fallback" to task or प्रणाली शेष
	 * policy.
	 */
	काष्ठा mempolicy *(*get_policy)(काष्ठा vm_area_काष्ठा *vma,
					अचिन्हित दीर्घ addr);
#पूर्ण_अगर
	/*
	 * Called by vm_normal_page() क्रम special PTEs to find the
	 * page क्रम @addr.  This is useful अगर the शेष behavior
	 * (using pte_page()) would not find the correct page.
	 */
	काष्ठा page *(*find_special_page)(काष्ठा vm_area_काष्ठा *vma,
					  अचिन्हित दीर्घ addr);
पूर्ण;

अटल अंतरभूत व्योम vma_init(काष्ठा vm_area_काष्ठा *vma, काष्ठा mm_काष्ठा *mm)
अणु
	अटल स्थिर काष्ठा vm_operations_काष्ठा dummy_vm_ops = अणुपूर्ण;

	स_रखो(vma, 0, माप(*vma));
	vma->vm_mm = mm;
	vma->vm_ops = &dummy_vm_ops;
	INIT_LIST_HEAD(&vma->anon_vma_chain);
पूर्ण

अटल अंतरभूत व्योम vma_set_anonymous(काष्ठा vm_area_काष्ठा *vma)
अणु
	vma->vm_ops = शून्य;
पूर्ण

अटल अंतरभूत bool vma_is_anonymous(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस !vma->vm_ops;
पूर्ण

अटल अंतरभूत bool vma_is_temporary_stack(काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक maybe_stack = vma->vm_flags & (VM_GROWSDOWN | VM_GROWSUP);

	अगर (!maybe_stack)
		वापस false;

	अगर ((vma->vm_flags & VM_STACK_INCOMPLETE_SETUP) ==
						VM_STACK_INCOMPLETE_SETUP)
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत bool vma_is_क्रमeign(काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (!current->mm)
		वापस true;

	अगर (current->mm != vma->vm_mm)
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत bool vma_is_accessible(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस vma->vm_flags & VM_ACCESS_FLAGS;
पूर्ण

#अगर_घोषित CONFIG_SHMEM
/*
 * The vma_is_shmem is not अंतरभूत because it is used only by slow
 * paths in userfault.
 */
bool vma_is_shmem(काष्ठा vm_area_काष्ठा *vma);
#अन्यथा
अटल अंतरभूत bool vma_is_shmem(काष्ठा vm_area_काष्ठा *vma) अणु वापस false; पूर्ण
#पूर्ण_अगर

पूर्णांक vma_is_stack_क्रम_current(काष्ठा vm_area_काष्ठा *vma);

/* flush_tlb_range() takes a vma, not a mm, and can care about flags */
#घोषणा TLB_FLUSH_VMA(mm,flags) अणु .vm_mm = (mm), .vm_flags = (flags) पूर्ण

काष्ठा mmu_gather;
काष्ठा inode;

#समावेश <linux/huge_mm.h>

/*
 * Methods to modअगरy the page usage count.
 *
 * What counts क्रम a page usage:
 * - cache mapping   (page->mapping)
 * - निजी data    (page->निजी)
 * - page mapped in a task's page tables, each mapping
 *   is counted separately
 *
 * Also, many kernel routines increase the page count beक्रमe a critical
 * routine so they can be sure the page करोesn't go away from under them.
 */

/*
 * Drop a ref, वापस true अगर the refcount fell to zero (the page has no users)
 */
अटल अंतरभूत पूर्णांक put_page_testzero(काष्ठा page *page)
अणु
	VM_BUG_ON_PAGE(page_ref_count(page) == 0, page);
	वापस page_ref_dec_and_test(page);
पूर्ण

/*
 * Try to grab a ref unless the page has a refcount of zero, वापस false अगर
 * that is the हाल.
 * This can be called when MMU is off so it must not access
 * any of the भव mappings.
 */
अटल अंतरभूत पूर्णांक get_page_unless_zero(काष्ठा page *page)
अणु
	वापस page_ref_add_unless(page, 1, 0);
पूर्ण

बाह्य पूर्णांक page_is_ram(अचिन्हित दीर्घ pfn);

क्रमागत अणु
	REGION_INTERSECTS,
	REGION_DISJOINT,
	REGION_MIXED,
पूर्ण;

पूर्णांक region_पूर्णांकersects(resource_माप_प्रकार offset, माप_प्रकार size, अचिन्हित दीर्घ flags,
		      अचिन्हित दीर्घ desc);

/* Support क्रम भवly mapped pages */
काष्ठा page *vदो_स्मृति_to_page(स्थिर व्योम *addr);
अचिन्हित दीर्घ vदो_स्मृति_to_pfn(स्थिर व्योम *addr);

/*
 * Determine अगर an address is within the vदो_स्मृति range
 *
 * On nommu, vदो_स्मृति/vमुक्त wrap through kदो_स्मृति/kमुक्त directly, so there
 * is no special casing required.
 */

#अगर_अघोषित is_ioremap_addr
#घोषणा is_ioremap_addr(x) is_vदो_स्मृति_addr(x)
#पूर्ण_अगर

#अगर_घोषित CONFIG_MMU
बाह्य bool is_vदो_स्मृति_addr(स्थिर व्योम *x);
बाह्य पूर्णांक is_vदो_स्मृति_or_module_addr(स्थिर व्योम *x);
#अन्यथा
अटल अंतरभूत bool is_vदो_स्मृति_addr(स्थिर व्योम *x)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत पूर्णांक is_vदो_स्मृति_or_module_addr(स्थिर व्योम *x)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

बाह्य व्योम *kvदो_स्मृति_node(माप_प्रकार size, gfp_t flags, पूर्णांक node);
अटल अंतरभूत व्योम *kvदो_स्मृति(माप_प्रकार size, gfp_t flags)
अणु
	वापस kvदो_स्मृति_node(size, flags, NUMA_NO_NODE);
पूर्ण
अटल अंतरभूत व्योम *kvzalloc_node(माप_प्रकार size, gfp_t flags, पूर्णांक node)
अणु
	वापस kvदो_स्मृति_node(size, flags | __GFP_ZERO, node);
पूर्ण
अटल अंतरभूत व्योम *kvzalloc(माप_प्रकार size, gfp_t flags)
अणु
	वापस kvदो_स्मृति(size, flags | __GFP_ZERO);
पूर्ण

अटल अंतरभूत व्योम *kvदो_स्मृति_array(माप_प्रकार n, माप_प्रकार size, gfp_t flags)
अणु
	माप_प्रकार bytes;

	अगर (unlikely(check_mul_overflow(n, size, &bytes)))
		वापस शून्य;

	वापस kvदो_स्मृति(bytes, flags);
पूर्ण

अटल अंतरभूत व्योम *kvसुस्मृति(माप_प्रकार n, माप_प्रकार size, gfp_t flags)
अणु
	वापस kvदो_स्मृति_array(n, size, flags | __GFP_ZERO);
पूर्ण

बाह्य व्योम kvमुक्त(स्थिर व्योम *addr);
बाह्य व्योम kvमुक्त_sensitive(स्थिर व्योम *addr, माप_प्रकार len);

अटल अंतरभूत पूर्णांक head_compound_mapcount(काष्ठा page *head)
अणु
	वापस atomic_पढ़ो(compound_mapcount_ptr(head)) + 1;
पूर्ण

/*
 * Mapcount of compound page as a whole, करोes not include mapped sub-pages.
 *
 * Must be called only क्रम compound pages or any their tail sub-pages.
 */
अटल अंतरभूत पूर्णांक compound_mapcount(काष्ठा page *page)
अणु
	VM_BUG_ON_PAGE(!PageCompound(page), page);
	page = compound_head(page);
	वापस head_compound_mapcount(page);
पूर्ण

/*
 * The atomic page->_mapcount, starts from -1: so that transitions
 * both from it and to it can be tracked, using atomic_inc_and_test
 * and atomic_add_negative(-1).
 */
अटल अंतरभूत व्योम page_mapcount_reset(काष्ठा page *page)
अणु
	atomic_set(&(page)->_mapcount, -1);
पूर्ण

पूर्णांक __page_mapcount(काष्ठा page *page);

/*
 * Mapcount of 0-order page; when compound sub-page, includes
 * compound_mapcount().
 *
 * Result is undefined क्रम pages which cannot be mapped पूर्णांकo userspace.
 * For example SLAB or special types of pages. See function page_has_type().
 * They use this place in काष्ठा page dअगरferently.
 */
अटल अंतरभूत पूर्णांक page_mapcount(काष्ठा page *page)
अणु
	अगर (unlikely(PageCompound(page)))
		वापस __page_mapcount(page);
	वापस atomic_पढ़ो(&page->_mapcount) + 1;
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
पूर्णांक total_mapcount(काष्ठा page *page);
पूर्णांक page_trans_huge_mapcount(काष्ठा page *page, पूर्णांक *total_mapcount);
#अन्यथा
अटल अंतरभूत पूर्णांक total_mapcount(काष्ठा page *page)
अणु
	वापस page_mapcount(page);
पूर्ण
अटल अंतरभूत पूर्णांक page_trans_huge_mapcount(काष्ठा page *page,
					   पूर्णांक *total_mapcount)
अणु
	पूर्णांक mapcount = page_mapcount(page);
	अगर (total_mapcount)
		*total_mapcount = mapcount;
	वापस mapcount;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत काष्ठा page *virt_to_head_page(स्थिर व्योम *x)
अणु
	काष्ठा page *page = virt_to_page(x);

	वापस compound_head(page);
पूर्ण

व्योम __put_page(काष्ठा page *page);

व्योम put_pages_list(काष्ठा list_head *pages);

व्योम split_page(काष्ठा page *page, अचिन्हित पूर्णांक order);

/*
 * Compound pages have a deकाष्ठाor function.  Provide a
 * prototype क्रम that function and accessor functions.
 * These are _only_ valid on the head of a compound page.
 */
प्रकार व्योम compound_page_dtor(काष्ठा page *);

/* Keep the क्रमागत in sync with compound_page_dtors array in mm/page_alloc.c */
क्रमागत compound_dtor_id अणु
	शून्य_COMPOUND_DTOR,
	COMPOUND_PAGE_DTOR,
#अगर_घोषित CONFIG_HUGETLB_PAGE
	HUGETLB_PAGE_DTOR,
#पूर्ण_अगर
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
	TRANSHUGE_PAGE_DTOR,
#पूर्ण_अगर
	NR_COMPOUND_DTORS,
पूर्ण;
बाह्य compound_page_dtor * स्थिर compound_page_dtors[NR_COMPOUND_DTORS];

अटल अंतरभूत व्योम set_compound_page_dtor(काष्ठा page *page,
		क्रमागत compound_dtor_id compound_dtor)
अणु
	VM_BUG_ON_PAGE(compound_dtor >= NR_COMPOUND_DTORS, page);
	page[1].compound_dtor = compound_dtor;
पूर्ण

अटल अंतरभूत व्योम destroy_compound_page(काष्ठा page *page)
अणु
	VM_BUG_ON_PAGE(page[1].compound_dtor >= NR_COMPOUND_DTORS, page);
	compound_page_dtors[page[1].compound_dtor](page);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक compound_order(काष्ठा page *page)
अणु
	अगर (!PageHead(page))
		वापस 0;
	वापस page[1].compound_order;
पूर्ण

अटल अंतरभूत bool hpage_pincount_available(काष्ठा page *page)
अणु
	/*
	 * Can the page->hpage_pinned_refcount field be used? That field is in
	 * the 3rd page of the compound page, so the smallest (2-page) compound
	 * pages cannot support it.
	 */
	page = compound_head(page);
	वापस PageCompound(page) && compound_order(page) > 1;
पूर्ण

अटल अंतरभूत पूर्णांक head_compound_pincount(काष्ठा page *head)
अणु
	वापस atomic_पढ़ो(compound_pincount_ptr(head));
पूर्ण

अटल अंतरभूत पूर्णांक compound_pincount(काष्ठा page *page)
अणु
	VM_BUG_ON_PAGE(!hpage_pincount_available(page), page);
	page = compound_head(page);
	वापस head_compound_pincount(page);
पूर्ण

अटल अंतरभूत व्योम set_compound_order(काष्ठा page *page, अचिन्हित पूर्णांक order)
अणु
	page[1].compound_order = order;
	page[1].compound_nr = 1U << order;
पूर्ण

/* Returns the number of pages in this potentially compound page. */
अटल अंतरभूत अचिन्हित दीर्घ compound_nr(काष्ठा page *page)
अणु
	अगर (!PageHead(page))
		वापस 1;
	वापस page[1].compound_nr;
पूर्ण

/* Returns the number of bytes in this potentially compound page. */
अटल अंतरभूत अचिन्हित दीर्घ page_size(काष्ठा page *page)
अणु
	वापस PAGE_SIZE << compound_order(page);
पूर्ण

/* Returns the number of bits needed क्रम the number of bytes in a page */
अटल अंतरभूत अचिन्हित पूर्णांक page_shअगरt(काष्ठा page *page)
अणु
	वापस PAGE_SHIFT + compound_order(page);
पूर्ण

व्योम मुक्त_compound_page(काष्ठा page *page);

#अगर_घोषित CONFIG_MMU
/*
 * Do pte_mkग_लिखो, but only अगर the vma says VM_WRITE.  We करो this when
 * servicing faults क्रम ग_लिखो access.  In the normal हाल, करो always want
 * pte_mkग_लिखो.  But get_user_pages can cause ग_लिखो faults क्रम mappings
 * that करो not have writing enabled, when used by access_process_vm.
 */
अटल अंतरभूत pte_t maybe_mkग_लिखो(pte_t pte, काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (likely(vma->vm_flags & VM_WRITE))
		pte = pte_mkग_लिखो(pte);
	वापस pte;
पूर्ण

vm_fault_t करो_set_pmd(काष्ठा vm_fault *vmf, काष्ठा page *page);
व्योम करो_set_pte(काष्ठा vm_fault *vmf, काष्ठा page *page, अचिन्हित दीर्घ addr);

vm_fault_t finish_fault(काष्ठा vm_fault *vmf);
vm_fault_t finish_mkग_लिखो_fault(काष्ठा vm_fault *vmf);
#पूर्ण_अगर

/*
 * Multiple processes may "see" the same page. E.g. क्रम untouched
 * mappings of /dev/null, all processes see the same page full of
 * zeroes, and text pages of executables and shared libraries have
 * only one copy in memory, at most, normally.
 *
 * For the non-reserved pages, page_count(page) denotes a reference count.
 *   page_count() == 0 means the page is मुक्त. page->lru is then used क्रम
 *   मुक्तlist management in the buddy allocator.
 *   page_count() > 0  means the page has been allocated.
 *
 * Pages are allocated by the slab allocator in order to provide memory
 * to kदो_स्मृति and kmem_cache_alloc. In this हाल, the management of the
 * page, and the fields in 'struct page' are the responsibility of mm/slab.c
 * unless a particular usage is carefully commented. (the responsibility of
 * मुक्तing the kदो_स्मृति memory is the caller's, of course).
 *
 * A page may be used by anyone अन्यथा who करोes a __get_मुक्त_page().
 * In this हाल, page_count still tracks the references, and should only
 * be used through the normal accessor functions. The top bits of page->flags
 * and page->भव store page management inक्रमmation, but all other fields
 * are unused and could be used निजीly, carefully. The management of this
 * page is the responsibility of the one who allocated it, and those who have
 * subsequently been given references to it.
 *
 * The other pages (we may call them "pagecache pages") are completely
 * managed by the Linux memory manager: I/O, buffers, swapping etc.
 * The following discussion applies only to them.
 *
 * A pagecache page contains an opaque `निजी' member, which beदीर्घs to the
 * page's address_space. Usually, this is the address of a circular list of
 * the page's disk buffers. PG_निजी must be set to tell the VM to call
 * पूर्णांकo the fileप्रणाली to release these pages.
 *
 * A page may beदीर्घ to an inode's memory mapping. In this हाल, page->mapping
 * is the poपूर्णांकer to the inode, and page->index is the file offset of the page,
 * in units of PAGE_SIZE.
 *
 * If pagecache pages are not associated with an inode, they are said to be
 * anonymous pages. These may become associated with the swapcache, and in that
 * हाल PG_swapcache is set, and page->निजी is an offset पूर्णांकo the swapcache.
 *
 * In either हाल (swapcache or inode backed), the pagecache itself holds one
 * reference to the page. Setting PG_निजी should also increment the
 * refcount. The each user mapping also has a reference to the page.
 *
 * The pagecache pages are stored in a per-mapping radix tree, which is
 * rooted at mapping->i_pages, and indexed by offset.
 * Where 2.4 and early 2.6 kernels kept dirty/clean pages in per-address_space
 * lists, we instead now tag pages as dirty/ग_लिखोback in the radix tree.
 *
 * All pagecache pages may be subject to I/O:
 * - inode pages may need to be पढ़ो from disk,
 * - inode pages which have been modअगरied and are MAP_SHARED may need
 *   to be written back to the inode on disk,
 * - anonymous pages (including MAP_PRIVATE file mappings) which have been
 *   modअगरied may need to be swapped out to swap space and (later) to be पढ़ो
 *   back पूर्णांकo memory.
 */

/*
 * The zone field is never updated after मुक्त_area_init_core()
 * sets it, so none of the operations on it need to be atomic.
 */

/* Page flags: | [SECTION] | [NODE] | ZONE | [LAST_CPUPID] | ... | FLAGS | */
#घोषणा SECTIONS_PGOFF		((माप(अचिन्हित दीर्घ)*8) - SECTIONS_WIDTH)
#घोषणा NODES_PGOFF		(SECTIONS_PGOFF - NODES_WIDTH)
#घोषणा ZONES_PGOFF		(NODES_PGOFF - ZONES_WIDTH)
#घोषणा LAST_CPUPID_PGOFF	(ZONES_PGOFF - LAST_CPUPID_WIDTH)
#घोषणा KASAN_TAG_PGOFF		(LAST_CPUPID_PGOFF - KASAN_TAG_WIDTH)

/*
 * Define the bit shअगरts to access each section.  For non-existent
 * sections we define the shअगरt as 0; that plus a 0 mask ensures
 * the compiler will optimise away reference to them.
 */
#घोषणा SECTIONS_PGSHIFT	(SECTIONS_PGOFF * (SECTIONS_WIDTH != 0))
#घोषणा NODES_PGSHIFT		(NODES_PGOFF * (NODES_WIDTH != 0))
#घोषणा ZONES_PGSHIFT		(ZONES_PGOFF * (ZONES_WIDTH != 0))
#घोषणा LAST_CPUPID_PGSHIFT	(LAST_CPUPID_PGOFF * (LAST_CPUPID_WIDTH != 0))
#घोषणा KASAN_TAG_PGSHIFT	(KASAN_TAG_PGOFF * (KASAN_TAG_WIDTH != 0))

/* NODE:ZONE or SECTION:ZONE is used to ID a zone क्रम the buddy allocator */
#अगर_घोषित NODE_NOT_IN_PAGE_FLAGS
#घोषणा ZONEID_SHIFT		(SECTIONS_SHIFT + ZONES_SHIFT)
#घोषणा ZONEID_PGOFF		((SECTIONS_PGOFF < ZONES_PGOFF)? \
						SECTIONS_PGOFF : ZONES_PGOFF)
#अन्यथा
#घोषणा ZONEID_SHIFT		(NODES_SHIFT + ZONES_SHIFT)
#घोषणा ZONEID_PGOFF		((NODES_PGOFF < ZONES_PGOFF)? \
						NODES_PGOFF : ZONES_PGOFF)
#पूर्ण_अगर

#घोषणा ZONEID_PGSHIFT		(ZONEID_PGOFF * (ZONEID_SHIFT != 0))

#घोषणा ZONES_MASK		((1UL << ZONES_WIDTH) - 1)
#घोषणा NODES_MASK		((1UL << NODES_WIDTH) - 1)
#घोषणा SECTIONS_MASK		((1UL << SECTIONS_WIDTH) - 1)
#घोषणा LAST_CPUPID_MASK	((1UL << LAST_CPUPID_SHIFT) - 1)
#घोषणा KASAN_TAG_MASK		((1UL << KASAN_TAG_WIDTH) - 1)
#घोषणा ZONEID_MASK		((1UL << ZONEID_SHIFT) - 1)

अटल अंतरभूत क्रमागत zone_type page_zonक्रमागत(स्थिर काष्ठा page *page)
अणु
	ASSERT_EXCLUSIVE_BITS(page->flags, ZONES_MASK << ZONES_PGSHIFT);
	वापस (page->flags >> ZONES_PGSHIFT) & ZONES_MASK;
पूर्ण

#अगर_घोषित CONFIG_ZONE_DEVICE
अटल अंतरभूत bool is_zone_device_page(स्थिर काष्ठा page *page)
अणु
	वापस page_zonक्रमागत(page) == ZONE_DEVICE;
पूर्ण
बाह्य व्योम memmap_init_zone_device(काष्ठा zone *, अचिन्हित दीर्घ,
				    अचिन्हित दीर्घ, काष्ठा dev_pagemap *);
#अन्यथा
अटल अंतरभूत bool is_zone_device_page(स्थिर काष्ठा page *page)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool is_zone_movable_page(स्थिर काष्ठा page *page)
अणु
	वापस page_zonक्रमागत(page) == ZONE_MOVABLE;
पूर्ण

#अगर_घोषित CONFIG_DEV_PAGEMAP_OPS
व्योम मुक्त_devmap_managed_page(काष्ठा page *page);
DECLARE_STATIC_KEY_FALSE(devmap_managed_key);

अटल अंतरभूत bool page_is_devmap_managed(काष्ठा page *page)
अणु
	अगर (!अटल_branch_unlikely(&devmap_managed_key))
		वापस false;
	अगर (!is_zone_device_page(page))
		वापस false;
	चयन (page->pgmap->type) अणु
	हाल MEMORY_DEVICE_PRIVATE:
	हाल MEMORY_DEVICE_FS_DAX:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण

व्योम put_devmap_managed_page(काष्ठा page *page);

#अन्यथा /* CONFIG_DEV_PAGEMAP_OPS */
अटल अंतरभूत bool page_is_devmap_managed(काष्ठा page *page)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम put_devmap_managed_page(काष्ठा page *page)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_DEV_PAGEMAP_OPS */

अटल अंतरभूत bool is_device_निजी_page(स्थिर काष्ठा page *page)
अणु
	वापस IS_ENABLED(CONFIG_DEV_PAGEMAP_OPS) &&
		IS_ENABLED(CONFIG_DEVICE_PRIVATE) &&
		is_zone_device_page(page) &&
		page->pgmap->type == MEMORY_DEVICE_PRIVATE;
पूर्ण

अटल अंतरभूत bool is_pci_p2pdma_page(स्थिर काष्ठा page *page)
अणु
	वापस IS_ENABLED(CONFIG_DEV_PAGEMAP_OPS) &&
		IS_ENABLED(CONFIG_PCI_P2PDMA) &&
		is_zone_device_page(page) &&
		page->pgmap->type == MEMORY_DEVICE_PCI_P2PDMA;
पूर्ण

/* 127: arbitrary अक्रमom number, small enough to assemble well */
#घोषणा page_ref_zero_or_बंद_to_overflow(page) \
	((अचिन्हित पूर्णांक) page_ref_count(page) + 127u <= 127u)

अटल अंतरभूत व्योम get_page(काष्ठा page *page)
अणु
	page = compound_head(page);
	/*
	 * Getting a normal page or the head of a compound page
	 * requires to alपढ़ोy have an elevated page->_refcount.
	 */
	VM_BUG_ON_PAGE(page_ref_zero_or_बंद_to_overflow(page), page);
	page_ref_inc(page);
पूर्ण

bool __must_check try_grab_page(काष्ठा page *page, अचिन्हित पूर्णांक flags);
__maybe_unused काष्ठा page *try_grab_compound_head(काष्ठा page *page, पूर्णांक refs,
						   अचिन्हित पूर्णांक flags);


अटल अंतरभूत __must_check bool try_get_page(काष्ठा page *page)
अणु
	page = compound_head(page);
	अगर (WARN_ON_ONCE(page_ref_count(page) <= 0))
		वापस false;
	page_ref_inc(page);
	वापस true;
पूर्ण

अटल अंतरभूत व्योम put_page(काष्ठा page *page)
अणु
	page = compound_head(page);

	/*
	 * For devmap managed pages we need to catch refcount transition from
	 * 2 to 1, when refcount reach one it means the page is मुक्त and we
	 * need to inक्रमm the device driver through callback. See
	 * include/linux/memremap.h and HMM क्रम details.
	 */
	अगर (page_is_devmap_managed(page)) अणु
		put_devmap_managed_page(page);
		वापस;
	पूर्ण

	अगर (put_page_testzero(page))
		__put_page(page);
पूर्ण

/*
 * GUP_PIN_COUNTING_BIAS, and the associated functions that use it, overload
 * the page's refcount so that two separate items are tracked: the original page
 * reference count, and also a new count of how many pin_user_pages() calls were
 * made against the page. ("gup-pinned" is another term क्रम the latter).
 *
 * With this scheme, pin_user_pages() becomes special: such pages are marked as
 * distinct from normal pages. As such, the unpin_user_page() call (and its
 * variants) must be used in order to release gup-pinned pages.
 *
 * Choice of value:
 *
 * By making GUP_PIN_COUNTING_BIAS a घातer of two, debugging of page reference
 * counts with respect to pin_user_pages() and unpin_user_page() becomes
 * simpler, due to the fact that adding an even घातer of two to the page
 * refcount has the effect of using only the upper N bits, क्रम the code that
 * counts up using the bias value. This means that the lower bits are left क्रम
 * the exclusive use of the original code that increments and decrements by one
 * (or at least, by much smaller values than the bias value).
 *
 * Of course, once the lower bits overflow पूर्णांकo the upper bits (and this is
 * OK, because subtraction recovers the original values), then visual inspection
 * no दीर्घer suffices to directly view the separate counts. However, क्रम normal
 * applications that करोn't have huge page reference counts, this won't be an
 * issue.
 *
 * Locking: the lockless algorithm described in page_cache_get_speculative()
 * and page_cache_gup_pin_speculative() provides safe operation क्रम
 * get_user_pages and page_mkclean and other calls that race to set up page
 * table entries.
 */
#घोषणा GUP_PIN_COUNTING_BIAS (1U << 10)

व्योम unpin_user_page(काष्ठा page *page);
व्योम unpin_user_pages_dirty_lock(काष्ठा page **pages, अचिन्हित दीर्घ npages,
				 bool make_dirty);
व्योम unpin_user_page_range_dirty_lock(काष्ठा page *page, अचिन्हित दीर्घ npages,
				      bool make_dirty);
व्योम unpin_user_pages(काष्ठा page **pages, अचिन्हित दीर्घ npages);

/**
 * page_maybe_dma_pinned - Report अगर a page is pinned क्रम DMA.
 * @page: The page.
 *
 * This function checks अगर a page has been pinned via a call to
 * a function in the pin_user_pages() family.
 *
 * For non-huge pages, the वापस value is partially fuzzy: false is not fuzzy,
 * because it means "definitely not pinned for DMA", but true means "probably
 * pinned क्रम DMA, but possibly a false positive due to having at least
 * GUP_PIN_COUNTING_BIAS worth of normal page references".
 *
 * False positives are OK, because: a) it's unlikely क्रम a page to get that many
 * refcounts, and b) all the callers of this routine are expected to be able to
 * deal gracefully with a false positive.
 *
 * For huge pages, the result will be exactly correct. That's because we have
 * more tracking data available: the 3rd काष्ठा page in the compound page is
 * used to track the pincount (instead using of the GUP_PIN_COUNTING_BIAS
 * scheme).
 *
 * For more inक्रमmation, please see Documentation/core-api/pin_user_pages.rst.
 *
 * Return: True, अगर it is likely that the page has been "dma-pinned".
 * False, अगर the page is definitely not dma-pinned.
 */
अटल अंतरभूत bool page_maybe_dma_pinned(काष्ठा page *page)
अणु
	अगर (hpage_pincount_available(page))
		वापस compound_pincount(page) > 0;

	/*
	 * page_ref_count() is चिन्हित. If that refcount overflows, then
	 * page_ref_count() वापसs a negative value, and callers will aव्योम
	 * further incrementing the refcount.
	 *
	 * Here, क्रम that overflow हाल, use the चिन्हित bit to count a little
	 * bit higher via अचिन्हित math, and thus still get an accurate result.
	 */
	वापस ((अचिन्हित पूर्णांक)page_ref_count(compound_head(page))) >=
		GUP_PIN_COUNTING_BIAS;
पूर्ण

अटल अंतरभूत bool is_cow_mapping(vm_flags_t flags)
अणु
	वापस (flags & (VM_SHARED | VM_MAYWRITE)) == VM_MAYWRITE;
पूर्ण

/*
 * This should most likely only be called during विभाजन() to see whether we
 * should अवरोध the cow immediately क्रम a page on the src mm.
 */
अटल अंतरभूत bool page_needs_cow_क्रम_dma(काष्ठा vm_area_काष्ठा *vma,
					  काष्ठा page *page)
अणु
	अगर (!is_cow_mapping(vma->vm_flags))
		वापस false;

	अगर (!atomic_पढ़ो(&vma->vm_mm->has_pinned))
		वापस false;

	वापस page_maybe_dma_pinned(page);
पूर्ण

#अगर defined(CONFIG_SPARSEMEM) && !defined(CONFIG_SPARSEMEM_VMEMMAP)
#घोषणा SECTION_IN_PAGE_FLAGS
#पूर्ण_अगर

/*
 * The identअगरication function is मुख्यly used by the buddy allocator क्रम
 * determining अगर two pages could be buddies. We are not really identअगरying
 * the zone since we could be using the section number id अगर we करो not have
 * node id available in page flags.
 * We only guarantee that it will वापस the same value क्रम two combinable
 * pages in a zone.
 */
अटल अंतरभूत पूर्णांक page_zone_id(काष्ठा page *page)
अणु
	वापस (page->flags >> ZONEID_PGSHIFT) & ZONEID_MASK;
पूर्ण

#अगर_घोषित NODE_NOT_IN_PAGE_FLAGS
बाह्य पूर्णांक page_to_nid(स्थिर काष्ठा page *page);
#अन्यथा
अटल अंतरभूत पूर्णांक page_to_nid(स्थिर काष्ठा page *page)
अणु
	काष्ठा page *p = (काष्ठा page *)page;

	वापस (PF_POISONED_CHECK(p)->flags >> NODES_PGSHIFT) & NODES_MASK;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NUMA_BALANCING
अटल अंतरभूत पूर्णांक cpu_pid_to_cpupid(पूर्णांक cpu, पूर्णांक pid)
अणु
	वापस ((cpu & LAST__CPU_MASK) << LAST__PID_SHIFT) | (pid & LAST__PID_MASK);
पूर्ण

अटल अंतरभूत पूर्णांक cpupid_to_pid(पूर्णांक cpupid)
अणु
	वापस cpupid & LAST__PID_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक cpupid_to_cpu(पूर्णांक cpupid)
अणु
	वापस (cpupid >> LAST__PID_SHIFT) & LAST__CPU_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक cpupid_to_nid(पूर्णांक cpupid)
अणु
	वापस cpu_to_node(cpupid_to_cpu(cpupid));
पूर्ण

अटल अंतरभूत bool cpupid_pid_unset(पूर्णांक cpupid)
अणु
	वापस cpupid_to_pid(cpupid) == (-1 & LAST__PID_MASK);
पूर्ण

अटल अंतरभूत bool cpupid_cpu_unset(पूर्णांक cpupid)
अणु
	वापस cpupid_to_cpu(cpupid) == (-1 & LAST__CPU_MASK);
पूर्ण

अटल अंतरभूत bool __cpupid_match_pid(pid_t task_pid, पूर्णांक cpupid)
अणु
	वापस (task_pid & LAST__PID_MASK) == cpupid_to_pid(cpupid);
पूर्ण

#घोषणा cpupid_match_pid(task, cpupid) __cpupid_match_pid(task->pid, cpupid)
#अगर_घोषित LAST_CPUPID_NOT_IN_PAGE_FLAGS
अटल अंतरभूत पूर्णांक page_cpupid_xchg_last(काष्ठा page *page, पूर्णांक cpupid)
अणु
	वापस xchg(&page->_last_cpupid, cpupid & LAST_CPUPID_MASK);
पूर्ण

अटल अंतरभूत पूर्णांक page_cpupid_last(काष्ठा page *page)
अणु
	वापस page->_last_cpupid;
पूर्ण
अटल अंतरभूत व्योम page_cpupid_reset_last(काष्ठा page *page)
अणु
	page->_last_cpupid = -1 & LAST_CPUPID_MASK;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक page_cpupid_last(काष्ठा page *page)
अणु
	वापस (page->flags >> LAST_CPUPID_PGSHIFT) & LAST_CPUPID_MASK;
पूर्ण

बाह्य पूर्णांक page_cpupid_xchg_last(काष्ठा page *page, पूर्णांक cpupid);

अटल अंतरभूत व्योम page_cpupid_reset_last(काष्ठा page *page)
अणु
	page->flags |= LAST_CPUPID_MASK << LAST_CPUPID_PGSHIFT;
पूर्ण
#पूर्ण_अगर /* LAST_CPUPID_NOT_IN_PAGE_FLAGS */
#अन्यथा /* !CONFIG_NUMA_BALANCING */
अटल अंतरभूत पूर्णांक page_cpupid_xchg_last(काष्ठा page *page, पूर्णांक cpupid)
अणु
	वापस page_to_nid(page); /* XXX */
पूर्ण

अटल अंतरभूत पूर्णांक page_cpupid_last(काष्ठा page *page)
अणु
	वापस page_to_nid(page); /* XXX */
पूर्ण

अटल अंतरभूत पूर्णांक cpupid_to_nid(पूर्णांक cpupid)
अणु
	वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक cpupid_to_pid(पूर्णांक cpupid)
अणु
	वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक cpupid_to_cpu(पूर्णांक cpupid)
अणु
	वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक cpu_pid_to_cpupid(पूर्णांक nid, पूर्णांक pid)
अणु
	वापस -1;
पूर्ण

अटल अंतरभूत bool cpupid_pid_unset(पूर्णांक cpupid)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत व्योम page_cpupid_reset_last(काष्ठा page *page)
अणु
पूर्ण

अटल अंतरभूत bool cpupid_match_pid(काष्ठा task_काष्ठा *task, पूर्णांक cpupid)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA_BALANCING */

#अगर defined(CONFIG_KASAN_SW_TAGS) || defined(CONFIG_KASAN_HW_TAGS)

/*
 * KASAN per-page tags are stored xor'ed with 0xff. This allows to aव्योम
 * setting tags क्रम all pages to native kernel tag value 0xff, as the शेष
 * value 0x00 maps to 0xff.
 */

अटल अंतरभूत u8 page_kasan_tag(स्थिर काष्ठा page *page)
अणु
	u8 tag = 0xff;

	अगर (kasan_enabled()) अणु
		tag = (page->flags >> KASAN_TAG_PGSHIFT) & KASAN_TAG_MASK;
		tag ^= 0xff;
	पूर्ण

	वापस tag;
पूर्ण

अटल अंतरभूत व्योम page_kasan_tag_set(काष्ठा page *page, u8 tag)
अणु
	अगर (kasan_enabled()) अणु
		tag ^= 0xff;
		page->flags &= ~(KASAN_TAG_MASK << KASAN_TAG_PGSHIFT);
		page->flags |= (tag & KASAN_TAG_MASK) << KASAN_TAG_PGSHIFT;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम page_kasan_tag_reset(काष्ठा page *page)
अणु
	अगर (kasan_enabled())
		page_kasan_tag_set(page, 0xff);
पूर्ण

#अन्यथा /* CONFIG_KASAN_SW_TAGS || CONFIG_KASAN_HW_TAGS */

अटल अंतरभूत u8 page_kasan_tag(स्थिर काष्ठा page *page)
अणु
	वापस 0xff;
पूर्ण

अटल अंतरभूत व्योम page_kasan_tag_set(काष्ठा page *page, u8 tag) अणु पूर्ण
अटल अंतरभूत व्योम page_kasan_tag_reset(काष्ठा page *page) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_KASAN_SW_TAGS || CONFIG_KASAN_HW_TAGS */

अटल अंतरभूत काष्ठा zone *page_zone(स्थिर काष्ठा page *page)
अणु
	वापस &NODE_DATA(page_to_nid(page))->node_zones[page_zonक्रमागत(page)];
पूर्ण

अटल अंतरभूत pg_data_t *page_pgdat(स्थिर काष्ठा page *page)
अणु
	वापस NODE_DATA(page_to_nid(page));
पूर्ण

#अगर_घोषित SECTION_IN_PAGE_FLAGS
अटल अंतरभूत व्योम set_page_section(काष्ठा page *page, अचिन्हित दीर्घ section)
अणु
	page->flags &= ~(SECTIONS_MASK << SECTIONS_PGSHIFT);
	page->flags |= (section & SECTIONS_MASK) << SECTIONS_PGSHIFT;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ page_to_section(स्थिर काष्ठा page *page)
अणु
	वापस (page->flags >> SECTIONS_PGSHIFT) & SECTIONS_MASK;
पूर्ण
#पूर्ण_अगर

/* MIGRATE_CMA and ZONE_MOVABLE करो not allow pin pages */
#अगर_घोषित CONFIG_MIGRATION
अटल अंतरभूत bool is_pinnable_page(काष्ठा page *page)
अणु
	वापस !(is_zone_movable_page(page) || is_migrate_cma_page(page)) ||
		is_zero_pfn(page_to_pfn(page));
पूर्ण
#अन्यथा
अटल अंतरभूत bool is_pinnable_page(काष्ठा page *page)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम set_page_zone(काष्ठा page *page, क्रमागत zone_type zone)
अणु
	page->flags &= ~(ZONES_MASK << ZONES_PGSHIFT);
	page->flags |= (zone & ZONES_MASK) << ZONES_PGSHIFT;
पूर्ण

अटल अंतरभूत व्योम set_page_node(काष्ठा page *page, अचिन्हित दीर्घ node)
अणु
	page->flags &= ~(NODES_MASK << NODES_PGSHIFT);
	page->flags |= (node & NODES_MASK) << NODES_PGSHIFT;
पूर्ण

अटल अंतरभूत व्योम set_page_links(काष्ठा page *page, क्रमागत zone_type zone,
	अचिन्हित दीर्घ node, अचिन्हित दीर्घ pfn)
अणु
	set_page_zone(page, zone);
	set_page_node(page, node);
#अगर_घोषित SECTION_IN_PAGE_FLAGS
	set_page_section(page, pfn_to_section_nr(pfn));
#पूर्ण_अगर
पूर्ण

/*
 * Some अंतरभूत functions in vmस्थिति.स depend on page_zone()
 */
#समावेश <linux/vmस्थिति.स>

अटल __always_अंतरभूत व्योम *lowmem_page_address(स्थिर काष्ठा page *page)
अणु
	वापस page_to_virt(page);
पूर्ण

#अगर defined(CONFIG_HIGHMEM) && !defined(WANT_PAGE_VIRTUAL)
#घोषणा HASHED_PAGE_VIRTUAL
#पूर्ण_अगर

#अगर defined(WANT_PAGE_VIRTUAL)
अटल अंतरभूत व्योम *page_address(स्थिर काष्ठा page *page)
अणु
	वापस page->भव;
पूर्ण
अटल अंतरभूत व्योम set_page_address(काष्ठा page *page, व्योम *address)
अणु
	page->भव = address;
पूर्ण
#घोषणा page_address_init()  करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

#अगर defined(HASHED_PAGE_VIRTUAL)
व्योम *page_address(स्थिर काष्ठा page *page);
व्योम set_page_address(काष्ठा page *page, व्योम *भव);
व्योम page_address_init(व्योम);
#पूर्ण_अगर

#अगर !defined(HASHED_PAGE_VIRTUAL) && !defined(WANT_PAGE_VIRTUAL)
#घोषणा page_address(page) lowmem_page_address(page)
#घोषणा set_page_address(page, address)  करो अणु पूर्ण जबतक(0)
#घोषणा page_address_init()  करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

बाह्य व्योम *page_rmapping(काष्ठा page *page);
बाह्य काष्ठा anon_vma *page_anon_vma(काष्ठा page *page);
बाह्य काष्ठा address_space *page_mapping(काष्ठा page *page);

बाह्य काष्ठा address_space *__page_file_mapping(काष्ठा page *);

अटल अंतरभूत
काष्ठा address_space *page_file_mapping(काष्ठा page *page)
अणु
	अगर (unlikely(PageSwapCache(page)))
		वापस __page_file_mapping(page);

	वापस page->mapping;
पूर्ण

बाह्य pgoff_t __page_file_index(काष्ठा page *page);

/*
 * Return the pagecache index of the passed page.  Regular pagecache pages
 * use ->index whereas swapcache pages use swp_offset(->निजी)
 */
अटल अंतरभूत pgoff_t page_index(काष्ठा page *page)
अणु
	अगर (unlikely(PageSwapCache(page)))
		वापस __page_file_index(page);
	वापस page->index;
पूर्ण

bool page_mapped(काष्ठा page *page);
काष्ठा address_space *page_mapping(काष्ठा page *page);

/*
 * Return true only अगर the page has been allocated with
 * ALLOC_NO_WATERMARKS and the low watermark was not
 * met implying that the प्रणाली is under some pressure.
 */
अटल अंतरभूत bool page_is_pfmeदो_स्मृति(स्थिर काष्ठा page *page)
अणु
	/*
	 * Page index cannot be this large so this must be
	 * a pfmeदो_स्मृति page.
	 */
	वापस page->index == -1UL;
पूर्ण

/*
 * Only to be called by the page allocator on a freshly allocated
 * page.
 */
अटल अंतरभूत व्योम set_page_pfmeदो_स्मृति(काष्ठा page *page)
अणु
	page->index = -1UL;
पूर्ण

अटल अंतरभूत व्योम clear_page_pfmeदो_स्मृति(काष्ठा page *page)
अणु
	page->index = 0;
पूर्ण

/*
 * Can be called by the pagefault handler when it माला_लो a VM_FAULT_OOM.
 */
बाह्य व्योम pagefault_out_of_memory(व्योम);

#घोषणा offset_in_page(p)	((अचिन्हित दीर्घ)(p) & ~PAGE_MASK)
#घोषणा offset_in_thp(page, p)	((अचिन्हित दीर्घ)(p) & (thp_size(page) - 1))

/*
 * Flags passed to show_mem() and show_मुक्त_areas() to suppress output in
 * various contexts.
 */
#घोषणा SHOW_MEM_FILTER_NODES		(0x0001u)	/* disallowed nodes */

बाह्य व्योम show_मुक्त_areas(अचिन्हित पूर्णांक flags, nodemask_t *nodemask);

#अगर_घोषित CONFIG_MMU
बाह्य bool can_करो_mlock(व्योम);
#अन्यथा
अटल अंतरभूत bool can_करो_mlock(व्योम) अणु वापस false; पूर्ण
#पूर्ण_अगर
बाह्य पूर्णांक user_shm_lock(माप_प्रकार, काष्ठा user_काष्ठा *);
बाह्य व्योम user_shm_unlock(माप_प्रकार, काष्ठा user_काष्ठा *);

/*
 * Parameter block passed करोwn to zap_pte_range in exceptional हालs.
 */
काष्ठा zap_details अणु
	काष्ठा address_space *check_mapping;	/* Check page->mapping अगर set */
	pgoff_t	first_index;			/* Lowest page->index to unmap */
	pgoff_t last_index;			/* Highest page->index to unmap */
	काष्ठा page *single_page;		/* Locked page to be unmapped */
पूर्ण;

काष्ठा page *vm_normal_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			     pte_t pte);
काष्ठा page *vm_normal_page_pmd(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
				pmd_t pmd);

व्योम zap_vma_ptes(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
		  अचिन्हित दीर्घ size);
व्योम zap_page_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
		    अचिन्हित दीर्घ size);
व्योम unmap_vmas(काष्ठा mmu_gather *tlb, काष्ठा vm_area_काष्ठा *start_vma,
		अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);

काष्ठा mmu_notअगरier_range;

व्योम मुक्त_pgd_range(काष्ठा mmu_gather *tlb, अचिन्हित दीर्घ addr,
		अचिन्हित दीर्घ end, अचिन्हित दीर्घ न्यूनमान, अचिन्हित दीर्घ उच्चमानing);
पूर्णांक
copy_page_range(काष्ठा vm_area_काष्ठा *dst_vma, काष्ठा vm_area_काष्ठा *src_vma);
पूर्णांक follow_invalidate_pte(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address,
			  काष्ठा mmu_notअगरier_range *range, pte_t **ptepp,
			  pmd_t **pmdpp, spinlock_t **ptlp);
पूर्णांक follow_pte(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address,
	       pte_t **ptepp, spinlock_t **ptlp);
पूर्णांक follow_pfn(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
	अचिन्हित दीर्घ *pfn);
पूर्णांक follow_phys(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
		अचिन्हित पूर्णांक flags, अचिन्हित दीर्घ *prot, resource_माप_प्रकार *phys);
पूर्णांक generic_access_phys(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			व्योम *buf, पूर्णांक len, पूर्णांक ग_लिखो);

बाह्य व्योम truncate_pagecache(काष्ठा inode *inode, loff_t new);
बाह्य व्योम truncate_setsize(काष्ठा inode *inode, loff_t newsize);
व्योम pagecache_isize_extended(काष्ठा inode *inode, loff_t from, loff_t to);
व्योम truncate_pagecache_range(काष्ठा inode *inode, loff_t offset, loff_t end);
पूर्णांक truncate_inode_page(काष्ठा address_space *mapping, काष्ठा page *page);
पूर्णांक generic_error_हटाओ_page(काष्ठा address_space *mapping, काष्ठा page *page);
पूर्णांक invalidate_inode_page(काष्ठा page *page);

#अगर_घोषित CONFIG_MMU
बाह्य vm_fault_t handle_mm_fault(काष्ठा vm_area_काष्ठा *vma,
				  अचिन्हित दीर्घ address, अचिन्हित पूर्णांक flags,
				  काष्ठा pt_regs *regs);
बाह्य पूर्णांक fixup_user_fault(काष्ठा mm_काष्ठा *mm,
			    अचिन्हित दीर्घ address, अचिन्हित पूर्णांक fault_flags,
			    bool *unlocked);
व्योम unmap_mapping_page(काष्ठा page *page);
व्योम unmap_mapping_pages(काष्ठा address_space *mapping,
		pgoff_t start, pgoff_t nr, bool even_cows);
व्योम unmap_mapping_range(काष्ठा address_space *mapping,
		loff_t स्थिर holebegin, loff_t स्थिर holelen, पूर्णांक even_cows);
#अन्यथा
अटल अंतरभूत vm_fault_t handle_mm_fault(काष्ठा vm_area_काष्ठा *vma,
					 अचिन्हित दीर्घ address, अचिन्हित पूर्णांक flags,
					 काष्ठा pt_regs *regs)
अणु
	/* should never happen अगर there's no MMU */
	BUG();
	वापस VM_FAULT_SIGBUS;
पूर्ण
अटल अंतरभूत पूर्णांक fixup_user_fault(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address,
		अचिन्हित पूर्णांक fault_flags, bool *unlocked)
अणु
	/* should never happen अगर there's no MMU */
	BUG();
	वापस -EFAULT;
पूर्ण
अटल अंतरभूत व्योम unmap_mapping_page(काष्ठा page *page) अणु पूर्ण
अटल अंतरभूत व्योम unmap_mapping_pages(काष्ठा address_space *mapping,
		pgoff_t start, pgoff_t nr, bool even_cows) अणु पूर्ण
अटल अंतरभूत व्योम unmap_mapping_range(काष्ठा address_space *mapping,
		loff_t स्थिर holebegin, loff_t स्थिर holelen, पूर्णांक even_cows) अणु पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम unmap_shared_mapping_range(काष्ठा address_space *mapping,
		loff_t स्थिर holebegin, loff_t स्थिर holelen)
अणु
	unmap_mapping_range(mapping, holebegin, holelen, 0);
पूर्ण

बाह्य पूर्णांक access_process_vm(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ addr,
		व्योम *buf, पूर्णांक len, अचिन्हित पूर्णांक gup_flags);
बाह्य पूर्णांक access_remote_vm(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		व्योम *buf, पूर्णांक len, अचिन्हित पूर्णांक gup_flags);
बाह्य पूर्णांक __access_remote_vm(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			      व्योम *buf, पूर्णांक len, अचिन्हित पूर्णांक gup_flags);

दीर्घ get_user_pages_remote(काष्ठा mm_काष्ठा *mm,
			    अचिन्हित दीर्घ start, अचिन्हित दीर्घ nr_pages,
			    अचिन्हित पूर्णांक gup_flags, काष्ठा page **pages,
			    काष्ठा vm_area_काष्ठा **vmas, पूर्णांक *locked);
दीर्घ pin_user_pages_remote(काष्ठा mm_काष्ठा *mm,
			   अचिन्हित दीर्घ start, अचिन्हित दीर्घ nr_pages,
			   अचिन्हित पूर्णांक gup_flags, काष्ठा page **pages,
			   काष्ठा vm_area_काष्ठा **vmas, पूर्णांक *locked);
दीर्घ get_user_pages(अचिन्हित दीर्घ start, अचिन्हित दीर्घ nr_pages,
			    अचिन्हित पूर्णांक gup_flags, काष्ठा page **pages,
			    काष्ठा vm_area_काष्ठा **vmas);
दीर्घ pin_user_pages(अचिन्हित दीर्घ start, अचिन्हित दीर्घ nr_pages,
		    अचिन्हित पूर्णांक gup_flags, काष्ठा page **pages,
		    काष्ठा vm_area_काष्ठा **vmas);
दीर्घ get_user_pages_locked(अचिन्हित दीर्घ start, अचिन्हित दीर्घ nr_pages,
		    अचिन्हित पूर्णांक gup_flags, काष्ठा page **pages, पूर्णांक *locked);
दीर्घ pin_user_pages_locked(अचिन्हित दीर्घ start, अचिन्हित दीर्घ nr_pages,
		    अचिन्हित पूर्णांक gup_flags, काष्ठा page **pages, पूर्णांक *locked);
दीर्घ get_user_pages_unlocked(अचिन्हित दीर्घ start, अचिन्हित दीर्घ nr_pages,
		    काष्ठा page **pages, अचिन्हित पूर्णांक gup_flags);
दीर्घ pin_user_pages_unlocked(अचिन्हित दीर्घ start, अचिन्हित दीर्घ nr_pages,
		    काष्ठा page **pages, अचिन्हित पूर्णांक gup_flags);

पूर्णांक get_user_pages_fast(अचिन्हित दीर्घ start, पूर्णांक nr_pages,
			अचिन्हित पूर्णांक gup_flags, काष्ठा page **pages);
पूर्णांक pin_user_pages_fast(अचिन्हित दीर्घ start, पूर्णांक nr_pages,
			अचिन्हित पूर्णांक gup_flags, काष्ठा page **pages);

पूर्णांक account_locked_vm(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ pages, bool inc);
पूर्णांक __account_locked_vm(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ pages, bool inc,
			काष्ठा task_काष्ठा *task, bool bypass_rlim);

काष्ठा kvec;
पूर्णांक get_kernel_pages(स्थिर काष्ठा kvec *iov, पूर्णांक nr_pages, पूर्णांक ग_लिखो,
			काष्ठा page **pages);
पूर्णांक get_kernel_page(अचिन्हित दीर्घ start, पूर्णांक ग_लिखो, काष्ठा page **pages);
काष्ठा page *get_dump_page(अचिन्हित दीर्घ addr);

बाह्य पूर्णांक try_to_release_page(काष्ठा page * page, gfp_t gfp_mask);
बाह्य व्योम करो_invalidatepage(काष्ठा page *page, अचिन्हित पूर्णांक offset,
			      अचिन्हित पूर्णांक length);

व्योम __set_page_dirty(काष्ठा page *, काष्ठा address_space *, पूर्णांक warn);
पूर्णांक __set_page_dirty_nobuffers(काष्ठा page *page);
पूर्णांक __set_page_dirty_no_ग_लिखोback(काष्ठा page *page);
पूर्णांक redirty_page_क्रम_ग_लिखोpage(काष्ठा ग_लिखोback_control *wbc,
				काष्ठा page *page);
व्योम account_page_dirtied(काष्ठा page *page, काष्ठा address_space *mapping);
व्योम account_page_cleaned(काष्ठा page *page, काष्ठा address_space *mapping,
			  काष्ठा bdi_ग_लिखोback *wb);
पूर्णांक set_page_dirty(काष्ठा page *page);
पूर्णांक set_page_dirty_lock(काष्ठा page *page);
व्योम __cancel_dirty_page(काष्ठा page *page);
अटल अंतरभूत व्योम cancel_dirty_page(काष्ठा page *page)
अणु
	/* Aव्योम atomic ops, locking, etc. when not actually needed. */
	अगर (PageDirty(page))
		__cancel_dirty_page(page);
पूर्ण
पूर्णांक clear_page_dirty_क्रम_io(काष्ठा page *page);

पूर्णांक get_cmdline(काष्ठा task_काष्ठा *task, अक्षर *buffer, पूर्णांक buflen);

बाह्य अचिन्हित दीर्घ move_page_tables(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ old_addr, काष्ठा vm_area_काष्ठा *new_vma,
		अचिन्हित दीर्घ new_addr, अचिन्हित दीर्घ len,
		bool need_rmap_locks);

/*
 * Flags used by change_protection().  For now we make it a biपंचांगap so
 * that we can pass in multiple flags just like parameters.  However
 * क्रम now all the callers are only use one of the flags at the same
 * समय.
 */
/* Whether we should allow dirty bit accounting */
#घोषणा  MM_CP_सूचीTY_ACCT                  (1UL << 0)
/* Whether this protection change is क्रम NUMA hपूर्णांकs */
#घोषणा  MM_CP_PROT_NUMA                   (1UL << 1)
/* Whether this change is क्रम ग_लिखो protecting */
#घोषणा  MM_CP_UFFD_WP                     (1UL << 2) /* करो wp */
#घोषणा  MM_CP_UFFD_WP_RESOLVE             (1UL << 3) /* Resolve wp */
#घोषणा  MM_CP_UFFD_WP_ALL                 (MM_CP_UFFD_WP | \
					    MM_CP_UFFD_WP_RESOLVE)

बाह्य अचिन्हित दीर्घ change_protection(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
			      अचिन्हित दीर्घ end, pgprot_t newprot,
			      अचिन्हित दीर्घ cp_flags);
बाह्य पूर्णांक mprotect_fixup(काष्ठा vm_area_काष्ठा *vma,
			  काष्ठा vm_area_काष्ठा **pprev, अचिन्हित दीर्घ start,
			  अचिन्हित दीर्घ end, अचिन्हित दीर्घ newflags);

/*
 * करोesn't attempt to fault and will वापस लघु.
 */
पूर्णांक get_user_pages_fast_only(अचिन्हित दीर्घ start, पूर्णांक nr_pages,
			     अचिन्हित पूर्णांक gup_flags, काष्ठा page **pages);
पूर्णांक pin_user_pages_fast_only(अचिन्हित दीर्घ start, पूर्णांक nr_pages,
			     अचिन्हित पूर्णांक gup_flags, काष्ठा page **pages);

अटल अंतरभूत bool get_user_page_fast_only(अचिन्हित दीर्घ addr,
			अचिन्हित पूर्णांक gup_flags, काष्ठा page **pagep)
अणु
	वापस get_user_pages_fast_only(addr, 1, gup_flags, pagep) == 1;
पूर्ण
/*
 * per-process(per-mm_काष्ठा) statistics.
 */
अटल अंतरभूत अचिन्हित दीर्घ get_mm_counter(काष्ठा mm_काष्ठा *mm, पूर्णांक member)
अणु
	दीर्घ val = atomic_दीर्घ_पढ़ो(&mm->rss_stat.count[member]);

#अगर_घोषित SPLIT_RSS_COUNTING
	/*
	 * counter is updated in asynchronous manner and may go to minus.
	 * But it's never be expected number क्रम users.
	 */
	अगर (val < 0)
		val = 0;
#पूर्ण_अगर
	वापस (अचिन्हित दीर्घ)val;
पूर्ण

व्योम mm_trace_rss_stat(काष्ठा mm_काष्ठा *mm, पूर्णांक member, दीर्घ count);

अटल अंतरभूत व्योम add_mm_counter(काष्ठा mm_काष्ठा *mm, पूर्णांक member, दीर्घ value)
अणु
	दीर्घ count = atomic_दीर्घ_add_वापस(value, &mm->rss_stat.count[member]);

	mm_trace_rss_stat(mm, member, count);
पूर्ण

अटल अंतरभूत व्योम inc_mm_counter(काष्ठा mm_काष्ठा *mm, पूर्णांक member)
अणु
	दीर्घ count = atomic_दीर्घ_inc_वापस(&mm->rss_stat.count[member]);

	mm_trace_rss_stat(mm, member, count);
पूर्ण

अटल अंतरभूत व्योम dec_mm_counter(काष्ठा mm_काष्ठा *mm, पूर्णांक member)
अणु
	दीर्घ count = atomic_दीर्घ_dec_वापस(&mm->rss_stat.count[member]);

	mm_trace_rss_stat(mm, member, count);
पूर्ण

/* Optimized variant when page is alपढ़ोy known not to be PageAnon */
अटल अंतरभूत पूर्णांक mm_counter_file(काष्ठा page *page)
अणु
	अगर (PageSwapBacked(page))
		वापस MM_SHMEMPAGES;
	वापस MM_खाताPAGES;
पूर्ण

अटल अंतरभूत पूर्णांक mm_counter(काष्ठा page *page)
अणु
	अगर (PageAnon(page))
		वापस MM_ANONPAGES;
	वापस mm_counter_file(page);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_mm_rss(काष्ठा mm_काष्ठा *mm)
अणु
	वापस get_mm_counter(mm, MM_खाताPAGES) +
		get_mm_counter(mm, MM_ANONPAGES) +
		get_mm_counter(mm, MM_SHMEMPAGES);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_mm_hiwater_rss(काष्ठा mm_काष्ठा *mm)
अणु
	वापस max(mm->hiwater_rss, get_mm_rss(mm));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_mm_hiwater_vm(काष्ठा mm_काष्ठा *mm)
अणु
	वापस max(mm->hiwater_vm, mm->total_vm);
पूर्ण

अटल अंतरभूत व्योम update_hiwater_rss(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ _rss = get_mm_rss(mm);

	अगर ((mm)->hiwater_rss < _rss)
		(mm)->hiwater_rss = _rss;
पूर्ण

अटल अंतरभूत व्योम update_hiwater_vm(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (mm->hiwater_vm < mm->total_vm)
		mm->hiwater_vm = mm->total_vm;
पूर्ण

अटल अंतरभूत व्योम reset_mm_hiwater_rss(काष्ठा mm_काष्ठा *mm)
अणु
	mm->hiwater_rss = get_mm_rss(mm);
पूर्ण

अटल अंतरभूत व्योम seपंचांगax_mm_hiwater_rss(अचिन्हित दीर्घ *maxrss,
					 काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ hiwater_rss = get_mm_hiwater_rss(mm);

	अगर (*maxrss < hiwater_rss)
		*maxrss = hiwater_rss;
पूर्ण

#अगर defined(SPLIT_RSS_COUNTING)
व्योम sync_mm_rss(काष्ठा mm_काष्ठा *mm);
#अन्यथा
अटल अंतरभूत व्योम sync_mm_rss(काष्ठा mm_काष्ठा *mm)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित CONFIG_ARCH_HAS_PTE_SPECIAL
अटल अंतरभूत पूर्णांक pte_special(pte_t pte)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत pte_t pte_mkspecial(pte_t pte)
अणु
	वापस pte;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित CONFIG_ARCH_HAS_PTE_DEVMAP
अटल अंतरभूत पूर्णांक pte_devmap(pte_t pte)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक vma_wants_ग_लिखोnotअगरy(काष्ठा vm_area_काष्ठा *vma, pgprot_t vm_page_prot);

बाह्य pte_t *__get_locked_pte(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			       spinlock_t **ptl);
अटल अंतरभूत pte_t *get_locked_pte(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				    spinlock_t **ptl)
अणु
	pte_t *ptep;
	__cond_lock(*ptl, ptep = __get_locked_pte(mm, addr, ptl));
	वापस ptep;
पूर्ण

#अगर_घोषित __PAGETABLE_P4D_FOLDED
अटल अंतरभूत पूर्णांक __p4d_alloc(काष्ठा mm_काष्ठा *mm, pgd_t *pgd,
						अचिन्हित दीर्घ address)
अणु
	वापस 0;
पूर्ण
#अन्यथा
पूर्णांक __p4d_alloc(काष्ठा mm_काष्ठा *mm, pgd_t *pgd, अचिन्हित दीर्घ address);
#पूर्ण_अगर

#अगर defined(__PAGETABLE_PUD_FOLDED) || !defined(CONFIG_MMU)
अटल अंतरभूत पूर्णांक __pud_alloc(काष्ठा mm_काष्ठा *mm, p4d_t *p4d,
						अचिन्हित दीर्घ address)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम mm_inc_nr_puds(काष्ठा mm_काष्ठा *mm) अणुपूर्ण
अटल अंतरभूत व्योम mm_dec_nr_puds(काष्ठा mm_काष्ठा *mm) अणुपूर्ण

#अन्यथा
पूर्णांक __pud_alloc(काष्ठा mm_काष्ठा *mm, p4d_t *p4d, अचिन्हित दीर्घ address);

अटल अंतरभूत व्योम mm_inc_nr_puds(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (mm_pud_folded(mm))
		वापस;
	atomic_दीर्घ_add(PTRS_PER_PUD * माप(pud_t), &mm->pgtables_bytes);
पूर्ण

अटल अंतरभूत व्योम mm_dec_nr_puds(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (mm_pud_folded(mm))
		वापस;
	atomic_दीर्घ_sub(PTRS_PER_PUD * माप(pud_t), &mm->pgtables_bytes);
पूर्ण
#पूर्ण_अगर

#अगर defined(__PAGETABLE_PMD_FOLDED) || !defined(CONFIG_MMU)
अटल अंतरभूत पूर्णांक __pmd_alloc(काष्ठा mm_काष्ठा *mm, pud_t *pud,
						अचिन्हित दीर्घ address)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mm_inc_nr_pmds(काष्ठा mm_काष्ठा *mm) अणुपूर्ण
अटल अंतरभूत व्योम mm_dec_nr_pmds(काष्ठा mm_काष्ठा *mm) अणुपूर्ण

#अन्यथा
पूर्णांक __pmd_alloc(काष्ठा mm_काष्ठा *mm, pud_t *pud, अचिन्हित दीर्घ address);

अटल अंतरभूत व्योम mm_inc_nr_pmds(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (mm_pmd_folded(mm))
		वापस;
	atomic_दीर्घ_add(PTRS_PER_PMD * माप(pmd_t), &mm->pgtables_bytes);
पूर्ण

अटल अंतरभूत व्योम mm_dec_nr_pmds(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (mm_pmd_folded(mm))
		वापस;
	atomic_दीर्घ_sub(PTRS_PER_PMD * माप(pmd_t), &mm->pgtables_bytes);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_MMU
अटल अंतरभूत व्योम mm_pgtables_bytes_init(काष्ठा mm_काष्ठा *mm)
अणु
	atomic_दीर्घ_set(&mm->pgtables_bytes, 0);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ mm_pgtables_bytes(स्थिर काष्ठा mm_काष्ठा *mm)
अणु
	वापस atomic_दीर्घ_पढ़ो(&mm->pgtables_bytes);
पूर्ण

अटल अंतरभूत व्योम mm_inc_nr_ptes(काष्ठा mm_काष्ठा *mm)
अणु
	atomic_दीर्घ_add(PTRS_PER_PTE * माप(pte_t), &mm->pgtables_bytes);
पूर्ण

अटल अंतरभूत व्योम mm_dec_nr_ptes(काष्ठा mm_काष्ठा *mm)
अणु
	atomic_दीर्घ_sub(PTRS_PER_PTE * माप(pte_t), &mm->pgtables_bytes);
पूर्ण
#अन्यथा

अटल अंतरभूत व्योम mm_pgtables_bytes_init(काष्ठा mm_काष्ठा *mm) अणुपूर्ण
अटल अंतरभूत अचिन्हित दीर्घ mm_pgtables_bytes(स्थिर काष्ठा mm_काष्ठा *mm)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mm_inc_nr_ptes(काष्ठा mm_काष्ठा *mm) अणुपूर्ण
अटल अंतरभूत व्योम mm_dec_nr_ptes(काष्ठा mm_काष्ठा *mm) अणुपूर्ण
#पूर्ण_अगर

पूर्णांक __pte_alloc(काष्ठा mm_काष्ठा *mm, pmd_t *pmd);
पूर्णांक __pte_alloc_kernel(pmd_t *pmd);

#अगर defined(CONFIG_MMU)

अटल अंतरभूत p4d_t *p4d_alloc(काष्ठा mm_काष्ठा *mm, pgd_t *pgd,
		अचिन्हित दीर्घ address)
अणु
	वापस (unlikely(pgd_none(*pgd)) && __p4d_alloc(mm, pgd, address)) ?
		शून्य : p4d_offset(pgd, address);
पूर्ण

अटल अंतरभूत pud_t *pud_alloc(काष्ठा mm_काष्ठा *mm, p4d_t *p4d,
		अचिन्हित दीर्घ address)
अणु
	वापस (unlikely(p4d_none(*p4d)) && __pud_alloc(mm, p4d, address)) ?
		शून्य : pud_offset(p4d, address);
पूर्ण

अटल अंतरभूत pmd_t *pmd_alloc(काष्ठा mm_काष्ठा *mm, pud_t *pud, अचिन्हित दीर्घ address)
अणु
	वापस (unlikely(pud_none(*pud)) && __pmd_alloc(mm, pud, address))?
		शून्य: pmd_offset(pud, address);
पूर्ण
#पूर्ण_अगर /* CONFIG_MMU */

#अगर USE_SPLIT_PTE_PTLOCKS
#अगर ALLOC_SPLIT_PTLOCKS
व्योम __init ptlock_cache_init(व्योम);
बाह्य bool ptlock_alloc(काष्ठा page *page);
बाह्य व्योम ptlock_मुक्त(काष्ठा page *page);

अटल अंतरभूत spinlock_t *ptlock_ptr(काष्ठा page *page)
अणु
	वापस page->ptl;
पूर्ण
#अन्यथा /* ALLOC_SPLIT_PTLOCKS */
अटल अंतरभूत व्योम ptlock_cache_init(व्योम)
अणु
पूर्ण

अटल अंतरभूत bool ptlock_alloc(काष्ठा page *page)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत व्योम ptlock_मुक्त(काष्ठा page *page)
अणु
पूर्ण

अटल अंतरभूत spinlock_t *ptlock_ptr(काष्ठा page *page)
अणु
	वापस &page->ptl;
पूर्ण
#पूर्ण_अगर /* ALLOC_SPLIT_PTLOCKS */

अटल अंतरभूत spinlock_t *pte_lockptr(काष्ठा mm_काष्ठा *mm, pmd_t *pmd)
अणु
	वापस ptlock_ptr(pmd_page(*pmd));
पूर्ण

अटल अंतरभूत bool ptlock_init(काष्ठा page *page)
अणु
	/*
	 * prep_new_page() initialize page->निजी (and thereक्रमe page->ptl)
	 * with 0. Make sure nobody took it in use in between.
	 *
	 * It can happen अगर arch try to use slab क्रम page table allocation:
	 * slab code uses page->slab_cache, which share storage with page->ptl.
	 */
	VM_BUG_ON_PAGE(*(अचिन्हित दीर्घ *)&page->ptl, page);
	अगर (!ptlock_alloc(page))
		वापस false;
	spin_lock_init(ptlock_ptr(page));
	वापस true;
पूर्ण

#अन्यथा	/* !USE_SPLIT_PTE_PTLOCKS */
/*
 * We use mm->page_table_lock to guard all pagetable pages of the mm.
 */
अटल अंतरभूत spinlock_t *pte_lockptr(काष्ठा mm_काष्ठा *mm, pmd_t *pmd)
अणु
	वापस &mm->page_table_lock;
पूर्ण
अटल अंतरभूत व्योम ptlock_cache_init(व्योम) अणुपूर्ण
अटल अंतरभूत bool ptlock_init(काष्ठा page *page) अणु वापस true; पूर्ण
अटल अंतरभूत व्योम ptlock_मुक्त(काष्ठा page *page) अणुपूर्ण
#पूर्ण_अगर /* USE_SPLIT_PTE_PTLOCKS */

अटल अंतरभूत व्योम pgtable_init(व्योम)
अणु
	ptlock_cache_init();
	pgtable_cache_init();
पूर्ण

अटल अंतरभूत bool pgtable_pte_page_ctor(काष्ठा page *page)
अणु
	अगर (!ptlock_init(page))
		वापस false;
	__SetPageTable(page);
	inc_lruvec_page_state(page, NR_PAGETABLE);
	वापस true;
पूर्ण

अटल अंतरभूत व्योम pgtable_pte_page_dtor(काष्ठा page *page)
अणु
	ptlock_मुक्त(page);
	__ClearPageTable(page);
	dec_lruvec_page_state(page, NR_PAGETABLE);
पूर्ण

#घोषणा pte_offset_map_lock(mm, pmd, address, ptlp)	\
(अणु							\
	spinlock_t *__ptl = pte_lockptr(mm, pmd);	\
	pte_t *__pte = pte_offset_map(pmd, address);	\
	*(ptlp) = __ptl;				\
	spin_lock(__ptl);				\
	__pte;						\
पूर्ण)

#घोषणा pte_unmap_unlock(pte, ptl)	करो अणु		\
	spin_unlock(ptl);				\
	pte_unmap(pte);					\
पूर्ण जबतक (0)

#घोषणा pte_alloc(mm, pmd) (unlikely(pmd_none(*(pmd))) && __pte_alloc(mm, pmd))

#घोषणा pte_alloc_map(mm, pmd, address)			\
	(pte_alloc(mm, pmd) ? शून्य : pte_offset_map(pmd, address))

#घोषणा pte_alloc_map_lock(mm, pmd, address, ptlp)	\
	(pte_alloc(mm, pmd) ?			\
		 शून्य : pte_offset_map_lock(mm, pmd, address, ptlp))

#घोषणा pte_alloc_kernel(pmd, address)			\
	((unlikely(pmd_none(*(pmd))) && __pte_alloc_kernel(pmd))? \
		शून्य: pte_offset_kernel(pmd, address))

#अगर USE_SPLIT_PMD_PTLOCKS

अटल काष्ठा page *pmd_to_page(pmd_t *pmd)
अणु
	अचिन्हित दीर्घ mask = ~(PTRS_PER_PMD * माप(pmd_t) - 1);
	वापस virt_to_page((व्योम *)((अचिन्हित दीर्घ) pmd & mask));
पूर्ण

अटल अंतरभूत spinlock_t *pmd_lockptr(काष्ठा mm_काष्ठा *mm, pmd_t *pmd)
अणु
	वापस ptlock_ptr(pmd_to_page(pmd));
पूर्ण

अटल अंतरभूत bool pmd_ptlock_init(काष्ठा page *page)
अणु
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
	page->pmd_huge_pte = शून्य;
#पूर्ण_अगर
	वापस ptlock_init(page);
पूर्ण

अटल अंतरभूत व्योम pmd_ptlock_मुक्त(काष्ठा page *page)
अणु
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
	VM_BUG_ON_PAGE(page->pmd_huge_pte, page);
#पूर्ण_अगर
	ptlock_मुक्त(page);
पूर्ण

#घोषणा pmd_huge_pte(mm, pmd) (pmd_to_page(pmd)->pmd_huge_pte)

#अन्यथा

अटल अंतरभूत spinlock_t *pmd_lockptr(काष्ठा mm_काष्ठा *mm, pmd_t *pmd)
अणु
	वापस &mm->page_table_lock;
पूर्ण

अटल अंतरभूत bool pmd_ptlock_init(काष्ठा page *page) अणु वापस true; पूर्ण
अटल अंतरभूत व्योम pmd_ptlock_मुक्त(काष्ठा page *page) अणुपूर्ण

#घोषणा pmd_huge_pte(mm, pmd) ((mm)->pmd_huge_pte)

#पूर्ण_अगर

अटल अंतरभूत spinlock_t *pmd_lock(काष्ठा mm_काष्ठा *mm, pmd_t *pmd)
अणु
	spinlock_t *ptl = pmd_lockptr(mm, pmd);
	spin_lock(ptl);
	वापस ptl;
पूर्ण

अटल अंतरभूत bool pgtable_pmd_page_ctor(काष्ठा page *page)
अणु
	अगर (!pmd_ptlock_init(page))
		वापस false;
	__SetPageTable(page);
	inc_lruvec_page_state(page, NR_PAGETABLE);
	वापस true;
पूर्ण

अटल अंतरभूत व्योम pgtable_pmd_page_dtor(काष्ठा page *page)
अणु
	pmd_ptlock_मुक्त(page);
	__ClearPageTable(page);
	dec_lruvec_page_state(page, NR_PAGETABLE);
पूर्ण

/*
 * No scalability reason to split PUD locks yet, but follow the same pattern
 * as the PMD locks to make it easier अगर we decide to.  The VM should not be
 * considered पढ़ोy to चयन to split PUD locks yet; there may be places
 * which need to be converted from page_table_lock.
 */
अटल अंतरभूत spinlock_t *pud_lockptr(काष्ठा mm_काष्ठा *mm, pud_t *pud)
अणु
	वापस &mm->page_table_lock;
पूर्ण

अटल अंतरभूत spinlock_t *pud_lock(काष्ठा mm_काष्ठा *mm, pud_t *pud)
अणु
	spinlock_t *ptl = pud_lockptr(mm, pud);

	spin_lock(ptl);
	वापस ptl;
पूर्ण

बाह्य व्योम __init pagecache_init(व्योम);
बाह्य व्योम __init मुक्त_area_init_memoryless_node(पूर्णांक nid);
बाह्य व्योम मुक्त_iniपंचांगem(व्योम);

/*
 * Free reserved pages within range [PAGE_ALIGN(start), end & PAGE_MASK)
 * पूर्णांकo the buddy प्रणाली. The मुक्तd pages will be poisoned with pattern
 * "poison" अगर it's within range [0, अच_अक्षर_उच्च].
 * Return pages मुक्तd पूर्णांकo the buddy प्रणाली.
 */
बाह्य अचिन्हित दीर्घ मुक्त_reserved_area(व्योम *start, व्योम *end,
					पूर्णांक poison, स्थिर अक्षर *s);

बाह्य व्योम adjust_managed_page_count(काष्ठा page *page, दीर्घ count);
बाह्य व्योम mem_init_prपूर्णांक_info(व्योम);

बाह्य व्योम reserve_booपंचांगem_region(phys_addr_t start, phys_addr_t end);

/* Free the reserved page पूर्णांकo the buddy प्रणाली, so it माला_लो managed. */
अटल अंतरभूत व्योम मुक्त_reserved_page(काष्ठा page *page)
अणु
	ClearPageReserved(page);
	init_page_count(page);
	__मुक्त_page(page);
	adjust_managed_page_count(page, 1);
पूर्ण
#घोषणा मुक्त_highmem_page(page) मुक्त_reserved_page(page)

अटल अंतरभूत व्योम mark_page_reserved(काष्ठा page *page)
अणु
	SetPageReserved(page);
	adjust_managed_page_count(page, -1);
पूर्ण

/*
 * Default method to मुक्त all the __init memory पूर्णांकo the buddy प्रणाली.
 * The मुक्तd pages will be poisoned with pattern "poison" अगर it's within
 * range [0, अच_अक्षर_उच्च].
 * Return pages मुक्तd पूर्णांकo the buddy प्रणाली.
 */
अटल अंतरभूत अचिन्हित दीर्घ मुक्त_iniपंचांगem_शेष(पूर्णांक poison)
अणु
	बाह्य अक्षर __init_begin[], __init_end[];

	वापस मुक्त_reserved_area(&__init_begin, &__init_end,
				  poison, "unused kernel");
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_num_physpages(व्योम)
अणु
	पूर्णांक nid;
	अचिन्हित दीर्घ phys_pages = 0;

	क्रम_each_online_node(nid)
		phys_pages += node_present_pages(nid);

	वापस phys_pages;
पूर्ण

/*
 * Using memblock node mappings, an architecture may initialise its
 * zones, allocate the backing mem_map and account क्रम memory holes in an
 * architecture independent manner.
 *
 * An architecture is expected to रेजिस्टर range of page frames backed by
 * physical memory with memblock_add[_node]() beक्रमe calling
 * मुक्त_area_init() passing in the PFN each zone ends at. At a basic
 * usage, an architecture is expected to करो something like
 *
 * अचिन्हित दीर्घ max_zone_pfns[MAX_NR_ZONES] = अणुmax_dma, max_normal_pfn,
 * 							 max_highmem_pfnपूर्ण;
 * क्रम_each_valid_physical_page_range()
 * 	memblock_add_node(base, size, nid)
 * मुक्त_area_init(max_zone_pfns);
 */
व्योम मुक्त_area_init(अचिन्हित दीर्घ *max_zone_pfn);
अचिन्हित दीर्घ node_map_pfn_alignment(व्योम);
अचिन्हित दीर्घ __असलent_pages_in_range(पूर्णांक nid, अचिन्हित दीर्घ start_pfn,
						अचिन्हित दीर्घ end_pfn);
बाह्य अचिन्हित दीर्घ असलent_pages_in_range(अचिन्हित दीर्घ start_pfn,
						अचिन्हित दीर्घ end_pfn);
बाह्य व्योम get_pfn_range_क्रम_nid(अचिन्हित पूर्णांक nid,
			अचिन्हित दीर्घ *start_pfn, अचिन्हित दीर्घ *end_pfn);
बाह्य अचिन्हित दीर्घ find_min_pfn_with_active_regions(व्योम);

#अगर_अघोषित CONFIG_NEED_MULTIPLE_NODES
अटल अंतरभूत पूर्णांक early_pfn_to_nid(अचिन्हित दीर्घ pfn)
अणु
	वापस 0;
पूर्ण
#अन्यथा
/* please see mm/page_alloc.c */
बाह्य पूर्णांक __meminit early_pfn_to_nid(अचिन्हित दीर्घ pfn);
#पूर्ण_अगर

बाह्य व्योम set_dma_reserve(अचिन्हित दीर्घ new_dma_reserve);
बाह्य व्योम memmap_init_range(अचिन्हित दीर्घ, पूर्णांक, अचिन्हित दीर्घ,
		अचिन्हित दीर्घ, अचिन्हित दीर्घ, क्रमागत meminit_context,
		काष्ठा vmem_alपंचांगap *, पूर्णांक migratetype);
बाह्य व्योम memmap_init_zone(काष्ठा zone *zone);
बाह्य व्योम setup_per_zone_wmarks(व्योम);
बाह्य पूर्णांक __meminit init_per_zone_wmark_min(व्योम);
बाह्य व्योम mem_init(व्योम);
बाह्य व्योम __init mmap_init(व्योम);
बाह्य व्योम show_mem(अचिन्हित पूर्णांक flags, nodemask_t *nodemask);
बाह्य दीर्घ si_mem_available(व्योम);
बाह्य व्योम si_meminfo(काष्ठा sysinfo * val);
बाह्य व्योम si_meminfo_node(काष्ठा sysinfo *val, पूर्णांक nid);
#अगर_घोषित __HAVE_ARCH_RESERVED_KERNEL_PAGES
बाह्य अचिन्हित दीर्घ arch_reserved_kernel_pages(व्योम);
#पूर्ण_अगर

बाह्य __म_लिखो(3, 4)
व्योम warn_alloc(gfp_t gfp_mask, nodemask_t *nodemask, स्थिर अक्षर *fmt, ...);

बाह्य व्योम setup_per_cpu_pageset(व्योम);

/* page_alloc.c */
बाह्य पूर्णांक min_मुक्त_kbytes;
बाह्य पूर्णांक watermark_boost_factor;
बाह्य पूर्णांक watermark_scale_factor;
बाह्य bool arch_has_descending_max_zone_pfns(व्योम);

/* nommu.c */
बाह्य atomic_दीर्घ_t mmap_pages_allocated;
बाह्य पूर्णांक nommu_shrink_inode_mappings(काष्ठा inode *, माप_प्रकार, माप_प्रकार);

/* पूर्णांकerval_tree.c */
व्योम vma_पूर्णांकerval_tree_insert(काष्ठा vm_area_काष्ठा *node,
			      काष्ठा rb_root_cached *root);
व्योम vma_पूर्णांकerval_tree_insert_after(काष्ठा vm_area_काष्ठा *node,
				    काष्ठा vm_area_काष्ठा *prev,
				    काष्ठा rb_root_cached *root);
व्योम vma_पूर्णांकerval_tree_हटाओ(काष्ठा vm_area_काष्ठा *node,
			      काष्ठा rb_root_cached *root);
काष्ठा vm_area_काष्ठा *vma_पूर्णांकerval_tree_iter_first(काष्ठा rb_root_cached *root,
				अचिन्हित दीर्घ start, अचिन्हित दीर्घ last);
काष्ठा vm_area_काष्ठा *vma_पूर्णांकerval_tree_iter_next(काष्ठा vm_area_काष्ठा *node,
				अचिन्हित दीर्घ start, अचिन्हित दीर्घ last);

#घोषणा vma_पूर्णांकerval_tree_क्रमeach(vma, root, start, last)		\
	क्रम (vma = vma_पूर्णांकerval_tree_iter_first(root, start, last);	\
	     vma; vma = vma_पूर्णांकerval_tree_iter_next(vma, start, last))

व्योम anon_vma_पूर्णांकerval_tree_insert(काष्ठा anon_vma_chain *node,
				   काष्ठा rb_root_cached *root);
व्योम anon_vma_पूर्णांकerval_tree_हटाओ(काष्ठा anon_vma_chain *node,
				   काष्ठा rb_root_cached *root);
काष्ठा anon_vma_chain *
anon_vma_पूर्णांकerval_tree_iter_first(काष्ठा rb_root_cached *root,
				  अचिन्हित दीर्घ start, अचिन्हित दीर्घ last);
काष्ठा anon_vma_chain *anon_vma_पूर्णांकerval_tree_iter_next(
	काष्ठा anon_vma_chain *node, अचिन्हित दीर्घ start, अचिन्हित दीर्घ last);
#अगर_घोषित CONFIG_DEBUG_VM_RB
व्योम anon_vma_पूर्णांकerval_tree_verअगरy(काष्ठा anon_vma_chain *node);
#पूर्ण_अगर

#घोषणा anon_vma_पूर्णांकerval_tree_क्रमeach(avc, root, start, last)		 \
	क्रम (avc = anon_vma_पूर्णांकerval_tree_iter_first(root, start, last); \
	     avc; avc = anon_vma_पूर्णांकerval_tree_iter_next(avc, start, last))

/* mmap.c */
बाह्य पूर्णांक __vm_enough_memory(काष्ठा mm_काष्ठा *mm, दीर्घ pages, पूर्णांक cap_sys_admin);
बाह्य पूर्णांक __vma_adjust(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
	अचिन्हित दीर्घ end, pgoff_t pgoff, काष्ठा vm_area_काष्ठा *insert,
	काष्ठा vm_area_काष्ठा *expand);
अटल अंतरभूत पूर्णांक vma_adjust(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
	अचिन्हित दीर्घ end, pgoff_t pgoff, काष्ठा vm_area_काष्ठा *insert)
अणु
	वापस __vma_adjust(vma, start, end, pgoff, insert, शून्य);
पूर्ण
बाह्य काष्ठा vm_area_काष्ठा *vma_merge(काष्ठा mm_काष्ठा *,
	काष्ठा vm_area_काष्ठा *prev, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
	अचिन्हित दीर्घ vm_flags, काष्ठा anon_vma *, काष्ठा file *, pgoff_t,
	काष्ठा mempolicy *, काष्ठा vm_userfaultfd_ctx);
बाह्य काष्ठा anon_vma *find_mergeable_anon_vma(काष्ठा vm_area_काष्ठा *);
बाह्य पूर्णांक __split_vma(काष्ठा mm_काष्ठा *, काष्ठा vm_area_काष्ठा *,
	अचिन्हित दीर्घ addr, पूर्णांक new_below);
बाह्य पूर्णांक split_vma(काष्ठा mm_काष्ठा *, काष्ठा vm_area_काष्ठा *,
	अचिन्हित दीर्घ addr, पूर्णांक new_below);
बाह्य पूर्णांक insert_vm_काष्ठा(काष्ठा mm_काष्ठा *, काष्ठा vm_area_काष्ठा *);
बाह्य व्योम __vma_link_rb(काष्ठा mm_काष्ठा *, काष्ठा vm_area_काष्ठा *,
	काष्ठा rb_node **, काष्ठा rb_node *);
बाह्य व्योम unlink_file_vma(काष्ठा vm_area_काष्ठा *);
बाह्य काष्ठा vm_area_काष्ठा *copy_vma(काष्ठा vm_area_काष्ठा **,
	अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len, pgoff_t pgoff,
	bool *need_rmap_locks);
बाह्य व्योम निकास_mmap(काष्ठा mm_काष्ठा *);

अटल अंतरभूत पूर्णांक check_data_rlimit(अचिन्हित दीर्घ rlim,
				    अचिन्हित दीर्घ new,
				    अचिन्हित दीर्घ start,
				    अचिन्हित दीर्घ end_data,
				    अचिन्हित दीर्घ start_data)
अणु
	अगर (rlim < RLIM_अनन्त) अणु
		अगर (((new - start) + (end_data - start_data)) > rlim)
			वापस -ENOSPC;
	पूर्ण

	वापस 0;
पूर्ण

बाह्य पूर्णांक mm_take_all_locks(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम mm_drop_all_locks(काष्ठा mm_काष्ठा *mm);

बाह्य व्योम set_mm_exe_file(काष्ठा mm_काष्ठा *mm, काष्ठा file *new_exe_file);
बाह्य काष्ठा file *get_mm_exe_file(काष्ठा mm_काष्ठा *mm);
बाह्य काष्ठा file *get_task_exe_file(काष्ठा task_काष्ठा *task);

बाह्य bool may_expand_vm(काष्ठा mm_काष्ठा *, vm_flags_t, अचिन्हित दीर्घ npages);
बाह्य व्योम vm_stat_account(काष्ठा mm_काष्ठा *, vm_flags_t, दीर्घ npages);

बाह्य bool vma_is_special_mapping(स्थिर काष्ठा vm_area_काष्ठा *vma,
				   स्थिर काष्ठा vm_special_mapping *sm);
बाह्य काष्ठा vm_area_काष्ठा *_install_special_mapping(काष्ठा mm_काष्ठा *mm,
				   अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
				   अचिन्हित दीर्घ flags,
				   स्थिर काष्ठा vm_special_mapping *spec);
/* This is an obsolete alternative to _install_special_mapping. */
बाह्य पूर्णांक install_special_mapping(काष्ठा mm_काष्ठा *mm,
				   अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
				   अचिन्हित दीर्घ flags, काष्ठा page **pages);

अचिन्हित दीर्घ अक्रमomize_stack_top(अचिन्हित दीर्घ stack_top);

बाह्य अचिन्हित दीर्घ get_unmapped_area(काष्ठा file *, अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ);

बाह्य अचिन्हित दीर्घ mmap_region(काष्ठा file *file, अचिन्हित दीर्घ addr,
	अचिन्हित दीर्घ len, vm_flags_t vm_flags, अचिन्हित दीर्घ pgoff,
	काष्ठा list_head *uf);
बाह्य अचिन्हित दीर्घ करो_mmap(काष्ठा file *file, अचिन्हित दीर्घ addr,
	अचिन्हित दीर्घ len, अचिन्हित दीर्घ prot, अचिन्हित दीर्घ flags,
	अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ *populate, काष्ठा list_head *uf);
बाह्य पूर्णांक __करो_munmap(काष्ठा mm_काष्ठा *, अचिन्हित दीर्घ, माप_प्रकार,
		       काष्ठा list_head *uf, bool करोwngrade);
बाह्य पूर्णांक करो_munmap(काष्ठा mm_काष्ठा *, अचिन्हित दीर्घ, माप_प्रकार,
		     काष्ठा list_head *uf);
बाह्य पूर्णांक करो_madvise(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start, माप_प्रकार len_in, पूर्णांक behavior);

#अगर_घोषित CONFIG_MMU
बाह्य पूर्णांक __mm_populate(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
			 पूर्णांक ignore_errors);
अटल अंतरभूत व्योम mm_populate(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len)
अणु
	/* Ignore errors */
	(व्योम) __mm_populate(addr, len, 1);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम mm_populate(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len) अणुपूर्ण
#पूर्ण_अगर

/* These take the mm semaphore themselves */
बाह्य पूर्णांक __must_check vm_brk(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
बाह्य पूर्णांक __must_check vm_brk_flags(अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ);
बाह्य पूर्णांक vm_munmap(अचिन्हित दीर्घ, माप_प्रकार);
बाह्य अचिन्हित दीर्घ __must_check vm_mmap(काष्ठा file *, अचिन्हित दीर्घ,
        अचिन्हित दीर्घ, अचिन्हित दीर्घ,
        अचिन्हित दीर्घ, अचिन्हित दीर्घ);

काष्ठा vm_unmapped_area_info अणु
#घोषणा VM_UNMAPPED_AREA_TOPDOWN 1
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ length;
	अचिन्हित दीर्घ low_limit;
	अचिन्हित दीर्घ high_limit;
	अचिन्हित दीर्घ align_mask;
	अचिन्हित दीर्घ align_offset;
पूर्ण;

बाह्य अचिन्हित दीर्घ vm_unmapped_area(काष्ठा vm_unmapped_area_info *info);

/* truncate.c */
बाह्य व्योम truncate_inode_pages(काष्ठा address_space *, loff_t);
बाह्य व्योम truncate_inode_pages_range(काष्ठा address_space *,
				       loff_t lstart, loff_t lend);
बाह्य व्योम truncate_inode_pages_final(काष्ठा address_space *);

/* generic vm_area_ops exported क्रम stackable file प्रणालीs */
बाह्य vm_fault_t filemap_fault(काष्ठा vm_fault *vmf);
बाह्य vm_fault_t filemap_map_pages(काष्ठा vm_fault *vmf,
		pgoff_t start_pgoff, pgoff_t end_pgoff);
बाह्य vm_fault_t filemap_page_mkग_लिखो(काष्ठा vm_fault *vmf);

/* mm/page-ग_लिखोback.c */
पूर्णांक __must_check ग_लिखो_one_page(काष्ठा page *page);
व्योम task_dirty_inc(काष्ठा task_काष्ठा *tsk);

बाह्य अचिन्हित दीर्घ stack_guard_gap;
/* Generic expand stack which grows the stack according to GROWSअणुUP,DOWNपूर्ण */
बाह्य पूर्णांक expand_stack(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address);

/* CONFIG_STACK_GROWSUP still needs to grow करोwnwards at some places */
बाह्य पूर्णांक expand_करोwnwards(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ address);
#अगर VM_GROWSUP
बाह्य पूर्णांक expand_upwards(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address);
#अन्यथा
  #घोषणा expand_upwards(vma, address) (0)
#पूर्ण_अगर

/* Look up the first VMA which satisfies  addr < vm_end,  शून्य अगर none. */
बाह्य काष्ठा vm_area_काष्ठा * find_vma(काष्ठा mm_काष्ठा * mm, अचिन्हित दीर्घ addr);
बाह्य काष्ठा vm_area_काष्ठा * find_vma_prev(काष्ठा mm_काष्ठा * mm, अचिन्हित दीर्घ addr,
					     काष्ठा vm_area_काष्ठा **pprev);

/* Look up the first VMA which पूर्णांकersects the पूर्णांकerval start_addr..end_addr-1,
   शून्य अगर none.  Assume start_addr < end_addr. */
अटल अंतरभूत काष्ठा vm_area_काष्ठा * find_vma_पूर्णांकersection(काष्ठा mm_काष्ठा * mm, अचिन्हित दीर्घ start_addr, अचिन्हित दीर्घ end_addr)
अणु
	काष्ठा vm_area_काष्ठा * vma = find_vma(mm,start_addr);

	अगर (vma && end_addr <= vma->vm_start)
		vma = शून्य;
	वापस vma;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ vm_start_gap(काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ vm_start = vma->vm_start;

	अगर (vma->vm_flags & VM_GROWSDOWN) अणु
		vm_start -= stack_guard_gap;
		अगर (vm_start > vma->vm_start)
			vm_start = 0;
	पूर्ण
	वापस vm_start;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ vm_end_gap(काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ vm_end = vma->vm_end;

	अगर (vma->vm_flags & VM_GROWSUP) अणु
		vm_end += stack_guard_gap;
		अगर (vm_end < vma->vm_end)
			vm_end = -PAGE_SIZE;
	पूर्ण
	वापस vm_end;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ vma_pages(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस (vma->vm_end - vma->vm_start) >> PAGE_SHIFT;
पूर्ण

/* Look up the first VMA which exactly match the पूर्णांकerval vm_start ... vm_end */
अटल अंतरभूत काष्ठा vm_area_काष्ठा *find_exact_vma(काष्ठा mm_काष्ठा *mm,
				अचिन्हित दीर्घ vm_start, अचिन्हित दीर्घ vm_end)
अणु
	काष्ठा vm_area_काष्ठा *vma = find_vma(mm, vm_start);

	अगर (vma && (vma->vm_start != vm_start || vma->vm_end != vm_end))
		vma = शून्य;

	वापस vma;
पूर्ण

अटल अंतरभूत bool range_in_vma(काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	वापस (vma && vma->vm_start <= start && end <= vma->vm_end);
पूर्ण

#अगर_घोषित CONFIG_MMU
pgprot_t vm_get_page_prot(अचिन्हित दीर्घ vm_flags);
व्योम vma_set_page_prot(काष्ठा vm_area_काष्ठा *vma);
#अन्यथा
अटल अंतरभूत pgprot_t vm_get_page_prot(अचिन्हित दीर्घ vm_flags)
अणु
	वापस __pgprot(0);
पूर्ण
अटल अंतरभूत व्योम vma_set_page_prot(काष्ठा vm_area_काष्ठा *vma)
अणु
	vma->vm_page_prot = vm_get_page_prot(vma->vm_flags);
पूर्ण
#पूर्ण_अगर

व्योम vma_set_file(काष्ठा vm_area_काष्ठा *vma, काष्ठा file *file);

#अगर_घोषित CONFIG_NUMA_BALANCING
अचिन्हित दीर्घ change_prot_numa(काष्ठा vm_area_काष्ठा *vma,
			अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
#पूर्ण_अगर

काष्ठा vm_area_काष्ठा *find_extend_vma(काष्ठा mm_काष्ठा *, अचिन्हित दीर्घ addr);
पूर्णांक remap_pfn_range(काष्ठा vm_area_काष्ठा *, अचिन्हित दीर्घ addr,
			अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ size, pgprot_t);
पूर्णांक remap_pfn_range_notrack(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
		अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ size, pgprot_t prot);
पूर्णांक vm_insert_page(काष्ठा vm_area_काष्ठा *, अचिन्हित दीर्घ addr, काष्ठा page *);
पूर्णांक vm_insert_pages(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			काष्ठा page **pages, अचिन्हित दीर्घ *num);
पूर्णांक vm_map_pages(काष्ठा vm_area_काष्ठा *vma, काष्ठा page **pages,
				अचिन्हित दीर्घ num);
पूर्णांक vm_map_pages_zero(काष्ठा vm_area_काष्ठा *vma, काष्ठा page **pages,
				अचिन्हित दीर्घ num);
vm_fault_t vmf_insert_pfn(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			अचिन्हित दीर्घ pfn);
vm_fault_t vmf_insert_pfn_prot(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			अचिन्हित दीर्घ pfn, pgprot_t pgprot);
vm_fault_t vmf_insert_mixed(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			pfn_t pfn);
vm_fault_t vmf_insert_mixed_prot(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			pfn_t pfn, pgprot_t pgprot);
vm_fault_t vmf_insert_mixed_mkग_लिखो(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ addr, pfn_t pfn);
पूर्णांक vm_iomap_memory(काष्ठा vm_area_काष्ठा *vma, phys_addr_t start, अचिन्हित दीर्घ len);

अटल अंतरभूत vm_fault_t vmf_insert_page(काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ addr, काष्ठा page *page)
अणु
	पूर्णांक err = vm_insert_page(vma, addr, page);

	अगर (err == -ENOMEM)
		वापस VM_FAULT_OOM;
	अगर (err < 0 && err != -EBUSY)
		वापस VM_FAULT_SIGBUS;

	वापस VM_FAULT_NOPAGE;
पूर्ण

#अगर_अघोषित io_remap_pfn_range
अटल अंतरभूत पूर्णांक io_remap_pfn_range(काष्ठा vm_area_काष्ठा *vma,
				     अचिन्हित दीर्घ addr, अचिन्हित दीर्घ pfn,
				     अचिन्हित दीर्घ size, pgprot_t prot)
अणु
	वापस remap_pfn_range(vma, addr, pfn, size, pgprot_decrypted(prot));
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत vm_fault_t vmf_error(पूर्णांक err)
अणु
	अगर (err == -ENOMEM)
		वापस VM_FAULT_OOM;
	वापस VM_FAULT_SIGBUS;
पूर्ण

काष्ठा page *follow_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
			 अचिन्हित पूर्णांक foll_flags);

#घोषणा FOLL_WRITE	0x01	/* check pte is writable */
#घोषणा FOLL_TOUCH	0x02	/* mark page accessed */
#घोषणा FOLL_GET	0x04	/* करो get_page on page */
#घोषणा FOLL_DUMP	0x08	/* give error on hole अगर it would be zero */
#घोषणा FOLL_FORCE	0x10	/* get_user_pages पढ़ो/ग_लिखो w/o permission */
#घोषणा FOLL_NOWAIT	0x20	/* अगर a disk transfer is needed, start the IO
				 * and वापस without रुकोing upon it */
#घोषणा FOLL_POPULATE	0x40	/* fault in page */
#घोषणा FOLL_HWPOISON	0x100	/* check page is hwpoisoned */
#घोषणा FOLL_NUMA	0x200	/* क्रमce NUMA hपूर्णांकing page fault */
#घोषणा FOLL_MIGRATION	0x400	/* रुको क्रम page to replace migration entry */
#घोषणा FOLL_TRIED	0x800	/* a retry, previous pass started an IO */
#घोषणा FOLL_MLOCK	0x1000	/* lock present pages */
#घोषणा FOLL_REMOTE	0x2000	/* we are working on non-current tsk/mm */
#घोषणा FOLL_COW	0x4000	/* पूर्णांकernal GUP flag */
#घोषणा FOLL_ANON	0x8000	/* करोn't करो file mappings */
#घोषणा FOLL_LONGTERM	0x10000	/* mapping lअगरeसमय is indefinite: see below */
#घोषणा FOLL_SPLIT_PMD	0x20000	/* split huge pmd beक्रमe वापसing */
#घोषणा FOLL_PIN	0x40000	/* pages must be released via unpin_user_page */
#घोषणा FOLL_FAST_ONLY	0x80000	/* gup_fast: prevent fall-back to slow gup */

/*
 * FOLL_PIN and FOLL_LONGTERM may be used in various combinations with each
 * other. Here is what they mean, and how to use them:
 *
 * FOLL_LONGTERM indicates that the page will be held क्रम an indefinite समय
 * period _often_ under userspace control.  This is in contrast to
 * iov_iter_get_pages(), whose usages are transient.
 *
 * FIXME: For pages which are part of a fileप्रणाली, mappings are subject to the
 * lअगरeसमय enक्रमced by the fileप्रणाली and we need guarantees that दीर्घterm
 * users like RDMA and V4L2 only establish mappings which coordinate usage with
 * the fileप्रणाली.  Ideas क्रम this coordination include revoking the दीर्घterm
 * pin, delaying ग_लिखोback, bounce buffer page ग_लिखोback, etc.  As FS DAX was
 * added after the problem with fileप्रणालीs was found FS DAX VMAs are
 * specअगरically failed.  Fileप्रणाली pages are still subject to bugs and use of
 * FOLL_LONGTERM should be aव्योमed on those pages.
 *
 * FIXME: Also NOTE that FOLL_LONGTERM is not supported in every GUP call.
 * Currently only get_user_pages() and get_user_pages_fast() support this flag
 * and calls to get_user_pages_[un]locked are specअगरically not allowed.  This
 * is due to an incompatibility with the FS DAX check and
 * FAULT_FLAG_ALLOW_RETRY.
 *
 * In the CMA हाल: दीर्घ term pins in a CMA region would unnecessarily fragment
 * that region.  And so, CMA attempts to migrate the page beक्रमe pinning, when
 * FOLL_LONGTERM is specअगरied.
 *
 * FOLL_PIN indicates that a special kind of tracking (not just page->_refcount,
 * but an additional pin counting प्रणाली) will be invoked. This is पूर्णांकended क्रम
 * anything that माला_लो a page reference and then touches page data (क्रम example,
 * Direct IO). This lets the fileप्रणाली know that some non-file-प्रणाली entity is
 * potentially changing the pages' data. In contrast to FOLL_GET (whose pages
 * are released via put_page()), FOLL_PIN pages must be released, ultimately, by
 * a call to unpin_user_page().
 *
 * FOLL_PIN is similar to FOLL_GET: both of these pin pages. They use dअगरferent
 * and separate refcounting mechanisms, however, and that means that each has
 * its own acquire and release mechanisms:
 *
 *     FOLL_GET: get_user_pages*() to acquire, and put_page() to release.
 *
 *     FOLL_PIN: pin_user_pages*() to acquire, and unpin_user_pages to release.
 *
 * FOLL_PIN and FOLL_GET are mutually exclusive क्रम a given function call.
 * (The underlying pages may experience both FOLL_GET-based and FOLL_PIN-based
 * calls applied to them, and that's perfectly OK. This is a स्थिरraपूर्णांक on the
 * callers, not on the pages.)
 *
 * FOLL_PIN should be set पूर्णांकernally by the pin_user_pages*() APIs, never
 * directly by the caller. That's in order to help aव्योम mismatches when
 * releasing pages: get_user_pages*() pages must be released via put_page(),
 * जबतक pin_user_pages*() pages must be released via unpin_user_page().
 *
 * Please see Documentation/core-api/pin_user_pages.rst क्रम more inक्रमmation.
 */

अटल अंतरभूत पूर्णांक vm_fault_to_त्रुटि_सं(vm_fault_t vm_fault, पूर्णांक foll_flags)
अणु
	अगर (vm_fault & VM_FAULT_OOM)
		वापस -ENOMEM;
	अगर (vm_fault & (VM_FAULT_HWPOISON | VM_FAULT_HWPOISON_LARGE))
		वापस (foll_flags & FOLL_HWPOISON) ? -EHWPOISON : -EFAULT;
	अगर (vm_fault & (VM_FAULT_SIGBUS | VM_FAULT_संक_अंश))
		वापस -EFAULT;
	वापस 0;
पूर्ण

प्रकार पूर्णांक (*pte_fn_t)(pte_t *pte, अचिन्हित दीर्घ addr, व्योम *data);
बाह्य पूर्णांक apply_to_page_range(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address,
			       अचिन्हित दीर्घ size, pte_fn_t fn, व्योम *data);
बाह्य पूर्णांक apply_to_existing_page_range(काष्ठा mm_काष्ठा *mm,
				   अचिन्हित दीर्घ address, अचिन्हित दीर्घ size,
				   pte_fn_t fn, व्योम *data);

बाह्य व्योम init_mem_debugging_and_hardening(व्योम);
#अगर_घोषित CONFIG_PAGE_POISONING
बाह्य व्योम __kernel_poison_pages(काष्ठा page *page, पूर्णांक numpages);
बाह्य व्योम __kernel_unpoison_pages(काष्ठा page *page, पूर्णांक numpages);
बाह्य bool _page_poisoning_enabled_early;
DECLARE_STATIC_KEY_FALSE(_page_poisoning_enabled);
अटल अंतरभूत bool page_poisoning_enabled(व्योम)
अणु
	वापस _page_poisoning_enabled_early;
पूर्ण
/*
 * For use in fast paths after init_mem_debugging() has run, or when a
 * false negative result is not harmful when called too early.
 */
अटल अंतरभूत bool page_poisoning_enabled_अटल(व्योम)
अणु
	वापस अटल_branch_unlikely(&_page_poisoning_enabled);
पूर्ण
अटल अंतरभूत व्योम kernel_poison_pages(काष्ठा page *page, पूर्णांक numpages)
अणु
	अगर (page_poisoning_enabled_अटल())
		__kernel_poison_pages(page, numpages);
पूर्ण
अटल अंतरभूत व्योम kernel_unpoison_pages(काष्ठा page *page, पूर्णांक numpages)
अणु
	अगर (page_poisoning_enabled_अटल())
		__kernel_unpoison_pages(page, numpages);
पूर्ण
#अन्यथा
अटल अंतरभूत bool page_poisoning_enabled(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत bool page_poisoning_enabled_अटल(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम __kernel_poison_pages(काष्ठा page *page, पूर्णांक nunmpages) अणु पूर्ण
अटल अंतरभूत व्योम kernel_poison_pages(काष्ठा page *page, पूर्णांक numpages) अणु पूर्ण
अटल अंतरभूत व्योम kernel_unpoison_pages(काष्ठा page *page, पूर्णांक numpages) अणु पूर्ण
#पूर्ण_अगर

DECLARE_STATIC_KEY_MAYBE(CONFIG_INIT_ON_ALLOC_DEFAULT_ON, init_on_alloc);
अटल अंतरभूत bool want_init_on_alloc(gfp_t flags)
अणु
	अगर (अटल_branch_maybe(CONFIG_INIT_ON_ALLOC_DEFAULT_ON,
				&init_on_alloc))
		वापस true;
	वापस flags & __GFP_ZERO;
पूर्ण

DECLARE_STATIC_KEY_MAYBE(CONFIG_INIT_ON_FREE_DEFAULT_ON, init_on_मुक्त);
अटल अंतरभूत bool want_init_on_मुक्त(व्योम)
अणु
	वापस अटल_branch_maybe(CONFIG_INIT_ON_FREE_DEFAULT_ON,
				   &init_on_मुक्त);
पूर्ण

बाह्य bool _debug_pagealloc_enabled_early;
DECLARE_STATIC_KEY_FALSE(_debug_pagealloc_enabled);

अटल अंतरभूत bool debug_pagealloc_enabled(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_DEBUG_PAGEALLOC) &&
		_debug_pagealloc_enabled_early;
पूर्ण

/*
 * For use in fast paths after init_debug_pagealloc() has run, or when a
 * false negative result is not harmful when called too early.
 */
अटल अंतरभूत bool debug_pagealloc_enabled_अटल(व्योम)
अणु
	अगर (!IS_ENABLED(CONFIG_DEBUG_PAGEALLOC))
		वापस false;

	वापस अटल_branch_unlikely(&_debug_pagealloc_enabled);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_PAGEALLOC
/*
 * To support DEBUG_PAGEALLOC architecture must ensure that
 * __kernel_map_pages() never fails
 */
बाह्य व्योम __kernel_map_pages(काष्ठा page *page, पूर्णांक numpages, पूर्णांक enable);

अटल अंतरभूत व्योम debug_pagealloc_map_pages(काष्ठा page *page, पूर्णांक numpages)
अणु
	अगर (debug_pagealloc_enabled_अटल())
		__kernel_map_pages(page, numpages, 1);
पूर्ण

अटल अंतरभूत व्योम debug_pagealloc_unmap_pages(काष्ठा page *page, पूर्णांक numpages)
अणु
	अगर (debug_pagealloc_enabled_अटल())
		__kernel_map_pages(page, numpages, 0);
पूर्ण
#अन्यथा	/* CONFIG_DEBUG_PAGEALLOC */
अटल अंतरभूत व्योम debug_pagealloc_map_pages(काष्ठा page *page, पूर्णांक numpages) अणुपूर्ण
अटल अंतरभूत व्योम debug_pagealloc_unmap_pages(काष्ठा page *page, पूर्णांक numpages) अणुपूर्ण
#पूर्ण_अगर	/* CONFIG_DEBUG_PAGEALLOC */

#अगर_घोषित __HAVE_ARCH_GATE_AREA
बाह्य काष्ठा vm_area_काष्ठा *get_gate_vma(काष्ठा mm_काष्ठा *mm);
बाह्य पूर्णांक in_gate_area_no_mm(अचिन्हित दीर्घ addr);
बाह्य पूर्णांक in_gate_area(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr);
#अन्यथा
अटल अंतरभूत काष्ठा vm_area_काष्ठा *get_gate_vma(काष्ठा mm_काष्ठा *mm)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत पूर्णांक in_gate_area_no_mm(अचिन्हित दीर्घ addr) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक in_gate_area(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर	/* __HAVE_ARCH_GATE_AREA */

बाह्य bool process_shares_mm(काष्ठा task_काष्ठा *p, काष्ठा mm_काष्ठा *mm);

#अगर_घोषित CONFIG_SYSCTL
बाह्य पूर्णांक sysctl_drop_caches;
पूर्णांक drop_caches_sysctl_handler(काष्ठा ctl_table *, पूर्णांक, व्योम *, माप_प्रकार *,
		loff_t *);
#पूर्ण_अगर

व्योम drop_slab(व्योम);
व्योम drop_slab_node(पूर्णांक nid);

#अगर_अघोषित CONFIG_MMU
#घोषणा अक्रमomize_va_space 0
#अन्यथा
बाह्य पूर्णांक अक्रमomize_va_space;
#पूर्ण_अगर

स्थिर अक्षर * arch_vma_name(काष्ठा vm_area_काष्ठा *vma);
#अगर_घोषित CONFIG_MMU
व्योम prपूर्णांक_vma_addr(अक्षर *prefix, अचिन्हित दीर्घ rip);
#अन्यथा
अटल अंतरभूत व्योम prपूर्णांक_vma_addr(अक्षर *prefix, अचिन्हित दीर्घ rip)
अणु
पूर्ण
#पूर्ण_अगर

व्योम *sparse_buffer_alloc(अचिन्हित दीर्घ size);
काष्ठा page * __populate_section_memmap(अचिन्हित दीर्घ pfn,
		अचिन्हित दीर्घ nr_pages, पूर्णांक nid, काष्ठा vmem_alपंचांगap *alपंचांगap);
pgd_t *vmemmap_pgd_populate(अचिन्हित दीर्घ addr, पूर्णांक node);
p4d_t *vmemmap_p4d_populate(pgd_t *pgd, अचिन्हित दीर्घ addr, पूर्णांक node);
pud_t *vmemmap_pud_populate(p4d_t *p4d, अचिन्हित दीर्घ addr, पूर्णांक node);
pmd_t *vmemmap_pmd_populate(pud_t *pud, अचिन्हित दीर्घ addr, पूर्णांक node);
pte_t *vmemmap_pte_populate(pmd_t *pmd, अचिन्हित दीर्घ addr, पूर्णांक node,
			    काष्ठा vmem_alपंचांगap *alपंचांगap);
व्योम *vmemmap_alloc_block(अचिन्हित दीर्घ size, पूर्णांक node);
काष्ठा vmem_alपंचांगap;
व्योम *vmemmap_alloc_block_buf(अचिन्हित दीर्घ size, पूर्णांक node,
			      काष्ठा vmem_alपंचांगap *alपंचांगap);
व्योम vmemmap_verअगरy(pte_t *, पूर्णांक, अचिन्हित दीर्घ, अचिन्हित दीर्घ);
पूर्णांक vmemmap_populate_basepages(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
			       पूर्णांक node, काष्ठा vmem_alपंचांगap *alपंचांगap);
पूर्णांक vmemmap_populate(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, पूर्णांक node,
		काष्ठा vmem_alपंचांगap *alपंचांगap);
व्योम vmemmap_populate_prपूर्णांक_last(व्योम);
#अगर_घोषित CONFIG_MEMORY_HOTPLUG
व्योम vmemmap_मुक्त(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
		काष्ठा vmem_alपंचांगap *alपंचांगap);
#पूर्ण_अगर
व्योम रेजिस्टर_page_booपंचांगem_memmap(अचिन्हित दीर्घ section_nr, काष्ठा page *map,
				  अचिन्हित दीर्घ nr_pages);

क्रमागत mf_flags अणु
	MF_COUNT_INCREASED = 1 << 0,
	MF_ACTION_REQUIRED = 1 << 1,
	MF_MUST_KILL = 1 << 2,
	MF_SOFT_OFFLINE = 1 << 3,
पूर्ण;
बाह्य पूर्णांक memory_failure(अचिन्हित दीर्घ pfn, पूर्णांक flags);
बाह्य व्योम memory_failure_queue(अचिन्हित दीर्घ pfn, पूर्णांक flags);
बाह्य व्योम memory_failure_queue_kick(पूर्णांक cpu);
बाह्य पूर्णांक unpoison_memory(अचिन्हित दीर्घ pfn);
बाह्य पूर्णांक sysctl_memory_failure_early_समाप्त;
बाह्य पूर्णांक sysctl_memory_failure_recovery;
बाह्य व्योम shake_page(काष्ठा page *p, पूर्णांक access);
बाह्य atomic_दीर्घ_t num_poisoned_pages __पढ़ो_mostly;
बाह्य पूर्णांक soft_offline_page(अचिन्हित दीर्घ pfn, पूर्णांक flags);


/*
 * Error handlers क्रम various types of pages.
 */
क्रमागत mf_result अणु
	MF_IGNORED,	/* Error: cannot be handled */
	MF_FAILED,	/* Error: handling failed */
	MF_DELAYED,	/* Will be handled later */
	MF_RECOVERED,	/* Successfully recovered */
पूर्ण;

क्रमागत mf_action_page_type अणु
	MF_MSG_KERNEL,
	MF_MSG_KERNEL_HIGH_ORDER,
	MF_MSG_SLAB,
	MF_MSG_DIFFERENT_COMPOUND,
	MF_MSG_POISONED_HUGE,
	MF_MSG_HUGE,
	MF_MSG_FREE_HUGE,
	MF_MSG_NON_PMD_HUGE,
	MF_MSG_UNMAP_FAILED,
	MF_MSG_सूचीTY_SWAPCACHE,
	MF_MSG_CLEAN_SWAPCACHE,
	MF_MSG_सूचीTY_MLOCKED_LRU,
	MF_MSG_CLEAN_MLOCKED_LRU,
	MF_MSG_सूचीTY_UNEVICTABLE_LRU,
	MF_MSG_CLEAN_UNEVICTABLE_LRU,
	MF_MSG_सूचीTY_LRU,
	MF_MSG_CLEAN_LRU,
	MF_MSG_TRUNCATED_LRU,
	MF_MSG_BUDDY,
	MF_MSG_BUDDY_2ND,
	MF_MSG_DAX,
	MF_MSG_UNSPLIT_THP,
	MF_MSG_UNKNOWN,
पूर्ण;

#अगर defined(CONFIG_TRANSPARENT_HUGEPAGE) || defined(CONFIG_HUGETLBFS)
बाह्य व्योम clear_huge_page(काष्ठा page *page,
			    अचिन्हित दीर्घ addr_hपूर्णांक,
			    अचिन्हित पूर्णांक pages_per_huge_page);
बाह्य व्योम copy_user_huge_page(काष्ठा page *dst, काष्ठा page *src,
				अचिन्हित दीर्घ addr_hपूर्णांक,
				काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित पूर्णांक pages_per_huge_page);
बाह्य दीर्घ copy_huge_page_from_user(काष्ठा page *dst_page,
				स्थिर व्योम __user *usr_src,
				अचिन्हित पूर्णांक pages_per_huge_page,
				bool allow_pagefault);

/**
 * vma_is_special_huge - Are transhuge page-table entries considered special?
 * @vma: Poपूर्णांकer to the काष्ठा vm_area_काष्ठा to consider
 *
 * Whether transhuge page-table entries are considered "special" following
 * the definition in vm_normal_page().
 *
 * Return: true अगर transhuge page-table entries should be considered special,
 * false otherwise.
 */
अटल अंतरभूत bool vma_is_special_huge(स्थिर काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस vma_is_dax(vma) || (vma->vm_file &&
				   (vma->vm_flags & (VM_PFNMAP | VM_MIXEDMAP)));
पूर्ण

#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE || CONFIG_HUGETLBFS */

#अगर_घोषित CONFIG_DEBUG_PAGEALLOC
बाह्य अचिन्हित पूर्णांक _debug_guardpage_minorder;
DECLARE_STATIC_KEY_FALSE(_debug_guardpage_enabled);

अटल अंतरभूत अचिन्हित पूर्णांक debug_guardpage_minorder(व्योम)
अणु
	वापस _debug_guardpage_minorder;
पूर्ण

अटल अंतरभूत bool debug_guardpage_enabled(व्योम)
अणु
	वापस अटल_branch_unlikely(&_debug_guardpage_enabled);
पूर्ण

अटल अंतरभूत bool page_is_guard(काष्ठा page *page)
अणु
	अगर (!debug_guardpage_enabled())
		वापस false;

	वापस PageGuard(page);
पूर्ण
#अन्यथा
अटल अंतरभूत अचिन्हित पूर्णांक debug_guardpage_minorder(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत bool debug_guardpage_enabled(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत bool page_is_guard(काष्ठा page *page) अणु वापस false; पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_PAGEALLOC */

#अगर MAX_NUMNODES > 1
व्योम __init setup_nr_node_ids(व्योम);
#अन्यथा
अटल अंतरभूत व्योम setup_nr_node_ids(व्योम) अणुपूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक स_भेद_pages(काष्ठा page *page1, काष्ठा page *page2);

अटल अंतरभूत पूर्णांक pages_identical(काष्ठा page *page1, काष्ठा page *page2)
अणु
	वापस !स_भेद_pages(page1, page2);
पूर्ण

#अगर_घोषित CONFIG_MAPPING_सूचीTY_HELPERS
अचिन्हित दीर्घ clean_record_shared_mapping_range(काष्ठा address_space *mapping,
						pgoff_t first_index, pgoff_t nr,
						pgoff_t biपंचांगap_pgoff,
						अचिन्हित दीर्घ *biपंचांगap,
						pgoff_t *start,
						pgoff_t *end);

अचिन्हित दीर्घ wp_shared_mapping_range(काष्ठा address_space *mapping,
				      pgoff_t first_index, pgoff_t nr);
#पूर्ण_अगर

बाह्य पूर्णांक sysctl_nr_trim_pages;

#अगर_घोषित CONFIG_PRINTK
व्योम mem_dump_obj(व्योम *object);
#अन्यथा
अटल अंतरभूत व्योम mem_dump_obj(व्योम *object) अणुपूर्ण
#पूर्ण_अगर

/**
 * seal_check_future_ग_लिखो - Check क्रम F_SEAL_FUTURE_WRITE flag and handle it
 * @seals: the seals to check
 * @vma: the vma to operate on
 *
 * Check whether F_SEAL_FUTURE_WRITE is set; अगर so, करो proper check/handling on
 * the vma flags.  Return 0 अगर check pass, or <0 क्रम errors.
 */
अटल अंतरभूत पूर्णांक seal_check_future_ग_लिखो(पूर्णांक seals, काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (seals & F_SEAL_FUTURE_WRITE) अणु
		/*
		 * New PROT_WRITE and MAP_SHARED mmaps are not allowed when
		 * "future write" seal active.
		 */
		अगर ((vma->vm_flags & VM_SHARED) && (vma->vm_flags & VM_WRITE))
			वापस -EPERM;

		/*
		 * Since an F_SEAL_FUTURE_WRITE sealed memfd can be mapped as
		 * MAP_SHARED and पढ़ो-only, take care to not allow mprotect to
		 * revert protections on such mappings. Do this only क्रम shared
		 * mappings. For निजी mappings, करोn't need to mask
		 * VM_MAYWRITE as we still want them to be COW-writable.
		 */
		अगर (vma->vm_flags & VM_SHARED)
			vma->vm_flags &= ~(VM_MAYWRITE);
	पूर्ण

	वापस 0;
पूर्ण

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _LINUX_MM_H */
