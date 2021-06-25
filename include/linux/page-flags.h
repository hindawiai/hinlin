<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Macros क्रम manipulating and testing page->flags
 */

#अगर_अघोषित PAGE_FLAGS_H
#घोषणा PAGE_FLAGS_H

#समावेश <linux/types.h>
#समावेश <linux/bug.h>
#समावेश <linux/mmdebug.h>
#अगर_अघोषित __GENERATING_BOUNDS_H
#समावेश <linux/mm_types.h>
#समावेश <generated/bounds.h>
#पूर्ण_अगर /* !__GENERATING_BOUNDS_H */

/*
 * Various page->flags bits:
 *
 * PG_reserved is set क्रम special pages. The "struct page" of such a page
 * should in general not be touched (e.g. set dirty) except by its owner.
 * Pages marked as PG_reserved include:
 * - Pages part of the kernel image (including vDSO) and similar (e.g. BIOS,
 *   initrd, HW tables)
 * - Pages reserved or allocated early during boot (beक्रमe the page allocator
 *   was initialized). This includes (depending on the architecture) the
 *   initial vmemmap, initial page tables, crashkernel, elfcorehdr, and much
 *   much more. Once (अगर ever) मुक्तd, PG_reserved is cleared and they will
 *   be given to the page allocator.
 * - Pages falling पूर्णांकo physical memory gaps - not IORESOURCE_SYSRAM. Trying
 *   to पढ़ो/ग_लिखो these pages might end badly. Don't touch!
 * - The zero page(s)
 * - Pages not added to the page allocator when onlining a section because
 *   they were excluded via the online_page_callback() or because they are
 *   PG_hwpoison.
 * - Pages allocated in the context of kexec/kdump (loaded kernel image,
 *   control pages, vmcoreinfo)
 * - MMIO/DMA pages. Some architectures करोn't allow to ioremap pages that are
 *   not marked PG_reserved (as they might be in use by somebody अन्यथा who करोes
 *   not respect the caching strategy).
 * - Pages part of an offline section (काष्ठा pages of offline sections should
 *   not be trusted as they will be initialized when first onlined).
 * - MCA pages on ia64
 * - Pages holding CPU notes क्रम POWER Firmware Assisted Dump
 * - Device memory (e.g. PMEM, DAX, HMM)
 * Some PG_reserved pages will be excluded from the hibernation image.
 * PG_reserved करोes in general not hinder anybody from dumping or swapping
 * and is no दीर्घer required क्रम remap_pfn_range(). ioremap might require it.
 * Consequently, PG_reserved क्रम a page mapped पूर्णांकo user space can indicate
 * the zero page, the vDSO, MMIO pages or device memory.
 *
 * The PG_निजी bitflag is set on pagecache pages अगर they contain fileप्रणाली
 * specअगरic data (which is normally at page->निजी). It can be used by
 * निजी allocations क्रम its own usage.
 *
 * During initiation of disk I/O, PG_locked is set. This bit is set beक्रमe I/O
 * and cleared when ग_लिखोback _starts_ or when पढ़ो _completes_. PG_ग_लिखोback
 * is set beक्रमe ग_लिखोback starts and cleared when it finishes.
 *
 * PG_locked also pins a page in pagecache, and blocks truncation of the file
 * जबतक it is held.
 *
 * page_रुकोqueue(page) is a रुको queue of all tasks रुकोing क्रम the page
 * to become unlocked.
 *
 * PG_swapbacked is set when a page uses swap as a backing storage.  This are
 * usually PageAnon or shmem pages but please note that even anonymous pages
 * might lose their PG_swapbacked flag when they simply can be dropped (e.g. as
 * a result of MADV_FREE).
 *
 * PG_uptodate tells whether the page's contents is valid.  When a पढ़ो
 * completes, the page becomes uptodate, unless a disk I/O error happened.
 *
 * PG_referenced, PG_reclaim are used क्रम page reclaim क्रम anonymous and
 * file-backed pagecache (see mm/vmscan.c).
 *
 * PG_error is set to indicate that an I/O error occurred on this page.
 *
 * PG_arch_1 is an architecture specअगरic page state bit.  The generic code
 * guarantees that this bit is cleared क्रम a page when it first is entered पूर्णांकo
 * the page cache.
 *
 * PG_hwpoison indicates that a page got corrupted in hardware and contains
 * data with incorrect ECC bits that triggered a machine check. Accessing is
 * not safe since it may cause another machine check. Don't touch!
 */

/*
 * Don't use the pageflags directly.  Use the PageFoo macros.
 *
 * The page flags field is split पूर्णांकo two parts, the मुख्य flags area
 * which extends from the low bits upwards, and the fields area which
 * extends from the high bits करोwnwards.
 *
 *  | FIELD | ... | FLAGS |
 *  N-1           ^       0
 *               (NR_PAGEFLAGS)
 *
 * The fields area is reserved क्रम fields mapping zone, node (क्रम NUMA) and
 * SPARSEMEM section (क्रम variants of SPARSEMEM that require section ids like
 * SPARSEMEM_EXTREME with !SPARSEMEM_VMEMMAP).
 */
क्रमागत pageflags अणु
	PG_locked,		/* Page is locked. Don't touch. */
	PG_referenced,
	PG_uptodate,
	PG_dirty,
	PG_lru,
	PG_active,
	PG_workingset,
	PG_रुकोers,		/* Page has रुकोers, check its रुकोqueue. Must be bit #7 and in the same byte as "PG_locked" */
	PG_error,
	PG_slab,
	PG_owner_priv_1,	/* Owner use. If pagecache, fs may use*/
	PG_arch_1,
	PG_reserved,
	PG_निजी,		/* If pagecache, has fs-निजी data */
	PG_निजी_2,		/* If pagecache, has fs aux data */
	PG_ग_लिखोback,		/* Page is under ग_लिखोback */
	PG_head,		/* A head page */
	PG_mappedtodisk,	/* Has blocks allocated on-disk */
	PG_reclaim,		/* To be reclaimed asap */
	PG_swapbacked,		/* Page is backed by RAM/swap */
	PG_unevictable,		/* Page is "unevictable"  */
#अगर_घोषित CONFIG_MMU
	PG_mlocked,		/* Page is vma mlocked */
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_USES_PG_UNCACHED
	PG_uncached,		/* Page has been mapped as uncached */
#पूर्ण_अगर
#अगर_घोषित CONFIG_MEMORY_FAILURE
	PG_hwpoison,		/* hardware poisoned page. Don't touch */
#पूर्ण_अगर
#अगर defined(CONFIG_IDLE_PAGE_TRACKING) && defined(CONFIG_64BIT)
	PG_young,
	PG_idle,
#पूर्ण_अगर
#अगर_घोषित CONFIG_64BIT
	PG_arch_2,
#पूर्ण_अगर
	__NR_PAGEFLAGS,

	/* Fileप्रणालीs */
	PG_checked = PG_owner_priv_1,

	/* SwapBacked */
	PG_swapcache = PG_owner_priv_1,	/* Swap page: swp_entry_t in निजी */

	/* Two page bits are conscripted by FS-Cache to मुख्यtain local caching
	 * state.  These bits are set on pages beदीर्घing to the netfs's inodes
	 * when those inodes are being locally cached.
	 */
	PG_fscache = PG_निजी_2,	/* page backed by cache */

	/* XEN */
	/* Pinned in Xen as a पढ़ो-only pagetable page. */
	PG_pinned = PG_owner_priv_1,
	/* Pinned as part of करोमुख्य save (see xen_mm_pin_all()). */
	PG_savepinned = PG_dirty,
	/* Has a grant mapping of another (क्रमeign) करोमुख्य's page. */
	PG_क्रमeign = PG_owner_priv_1,
	/* Remapped by swiotlb-xen. */
	PG_xen_remapped = PG_owner_priv_1,

	/* SLOB */
	PG_slob_मुक्त = PG_निजी,

	/* Compound pages. Stored in first tail page's flags */
	PG_द्विगुन_map = PG_workingset,

	/* non-lru isolated movable page */
	PG_isolated = PG_reclaim,

	/* Only valid क्रम buddy pages. Used to track pages that are reported */
	PG_reported = PG_uptodate,
पूर्ण;

#अगर_अघोषित __GENERATING_BOUNDS_H

काष्ठा page;	/* क्रमward declaration */

अटल अंतरभूत काष्ठा page *compound_head(काष्ठा page *page)
अणु
	अचिन्हित दीर्घ head = READ_ONCE(page->compound_head);

	अगर (unlikely(head & 1))
		वापस (काष्ठा page *) (head - 1);
	वापस page;
पूर्ण

अटल __always_अंतरभूत पूर्णांक PageTail(काष्ठा page *page)
अणु
	वापस READ_ONCE(page->compound_head) & 1;
पूर्ण

अटल __always_अंतरभूत पूर्णांक PageCompound(काष्ठा page *page)
अणु
	वापस test_bit(PG_head, &page->flags) || PageTail(page);
पूर्ण

#घोषणा	PAGE_POISON_PATTERN	-1l
अटल अंतरभूत पूर्णांक PagePoisoned(स्थिर काष्ठा page *page)
अणु
	वापस page->flags == PAGE_POISON_PATTERN;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_VM
व्योम page_init_poison(काष्ठा page *page, माप_प्रकार size);
#अन्यथा
अटल अंतरभूत व्योम page_init_poison(काष्ठा page *page, माप_प्रकार size)
अणु
पूर्ण
#पूर्ण_अगर

/*
 * Page flags policies wrt compound pages
 *
 * PF_POISONED_CHECK
 *     check अगर this काष्ठा page poisoned/uninitialized
 *
 * PF_ANY:
 *     the page flag is relevant क्रम small, head and tail pages.
 *
 * PF_HEAD:
 *     क्रम compound page all operations related to the page flag applied to
 *     head page.
 *
 * PF_ONLY_HEAD:
 *     क्रम compound page, callers only ever operate on the head page.
 *
 * PF_NO_TAIL:
 *     modअगरications of the page flag must be करोne on small or head pages,
 *     checks can be करोne on tail pages too.
 *
 * PF_NO_COMPOUND:
 *     the page flag is not relevant क्रम compound pages.
 *
 * PF_SECOND:
 *     the page flag is stored in the first tail page.
 */
#घोषणा PF_POISONED_CHECK(page) (अणु					\
		VM_BUG_ON_PGFLAGS(PagePoisoned(page), page);		\
		page; पूर्ण)
#घोषणा PF_ANY(page, enक्रमce)	PF_POISONED_CHECK(page)
#घोषणा PF_HEAD(page, enक्रमce)	PF_POISONED_CHECK(compound_head(page))
#घोषणा PF_ONLY_HEAD(page, enक्रमce) (अणु					\
		VM_BUG_ON_PGFLAGS(PageTail(page), page);		\
		PF_POISONED_CHECK(page); पूर्ण)
#घोषणा PF_NO_TAIL(page, enक्रमce) (अणु					\
		VM_BUG_ON_PGFLAGS(enक्रमce && PageTail(page), page);	\
		PF_POISONED_CHECK(compound_head(page)); पूर्ण)
#घोषणा PF_NO_COMPOUND(page, enक्रमce) (अणु				\
		VM_BUG_ON_PGFLAGS(enक्रमce && PageCompound(page), page);	\
		PF_POISONED_CHECK(page); पूर्ण)
#घोषणा PF_SECOND(page, enक्रमce) (अणु					\
		VM_BUG_ON_PGFLAGS(!PageHead(page), page);		\
		PF_POISONED_CHECK(&page[1]); पूर्ण)

/*
 * Macros to create function definitions क्रम page flags
 */
#घोषणा TESTPAGEFLAG(uname, lname, policy)				\
अटल __always_अंतरभूत पूर्णांक Page##uname(काष्ठा page *page)		\
	अणु वापस test_bit(PG_##lname, &policy(page, 0)->flags); पूर्ण

#घोषणा SETPAGEFLAG(uname, lname, policy)				\
अटल __always_अंतरभूत व्योम SetPage##uname(काष्ठा page *page)		\
	अणु set_bit(PG_##lname, &policy(page, 1)->flags); पूर्ण

#घोषणा CLEARPAGEFLAG(uname, lname, policy)				\
अटल __always_अंतरभूत व्योम ClearPage##uname(काष्ठा page *page)		\
	अणु clear_bit(PG_##lname, &policy(page, 1)->flags); पूर्ण

#घोषणा __SETPAGEFLAG(uname, lname, policy)				\
अटल __always_अंतरभूत व्योम __SetPage##uname(काष्ठा page *page)		\
	अणु __set_bit(PG_##lname, &policy(page, 1)->flags); पूर्ण

#घोषणा __CLEARPAGEFLAG(uname, lname, policy)				\
अटल __always_अंतरभूत व्योम __ClearPage##uname(काष्ठा page *page)	\
	अणु __clear_bit(PG_##lname, &policy(page, 1)->flags); पूर्ण

#घोषणा TESTSETFLAG(uname, lname, policy)				\
अटल __always_अंतरभूत पूर्णांक TestSetPage##uname(काष्ठा page *page)	\
	अणु वापस test_and_set_bit(PG_##lname, &policy(page, 1)->flags); पूर्ण

#घोषणा TESTCLEARFLAG(uname, lname, policy)				\
अटल __always_अंतरभूत पूर्णांक TestClearPage##uname(काष्ठा page *page)	\
	अणु वापस test_and_clear_bit(PG_##lname, &policy(page, 1)->flags); पूर्ण

#घोषणा PAGEFLAG(uname, lname, policy)					\
	TESTPAGEFLAG(uname, lname, policy)				\
	SETPAGEFLAG(uname, lname, policy)				\
	CLEARPAGEFLAG(uname, lname, policy)

#घोषणा __PAGEFLAG(uname, lname, policy)				\
	TESTPAGEFLAG(uname, lname, policy)				\
	__SETPAGEFLAG(uname, lname, policy)				\
	__CLEARPAGEFLAG(uname, lname, policy)

#घोषणा TESTSCFLAG(uname, lname, policy)				\
	TESTSETFLAG(uname, lname, policy)				\
	TESTCLEARFLAG(uname, lname, policy)

#घोषणा TESTPAGEFLAG_FALSE(uname)					\
अटल अंतरभूत पूर्णांक Page##uname(स्थिर काष्ठा page *page) अणु वापस 0; पूर्ण

#घोषणा SETPAGEFLAG_NOOP(uname)						\
अटल अंतरभूत व्योम SetPage##uname(काष्ठा page *page) अणु  पूर्ण

#घोषणा CLEARPAGEFLAG_NOOP(uname)					\
अटल अंतरभूत व्योम ClearPage##uname(काष्ठा page *page) अणु  पूर्ण

#घोषणा __CLEARPAGEFLAG_NOOP(uname)					\
अटल अंतरभूत व्योम __ClearPage##uname(काष्ठा page *page) अणु  पूर्ण

#घोषणा TESTSETFLAG_FALSE(uname)					\
अटल अंतरभूत पूर्णांक TestSetPage##uname(काष्ठा page *page) अणु वापस 0; पूर्ण

#घोषणा TESTCLEARFLAG_FALSE(uname)					\
अटल अंतरभूत पूर्णांक TestClearPage##uname(काष्ठा page *page) अणु वापस 0; पूर्ण

#घोषणा PAGEFLAG_FALSE(uname) TESTPAGEFLAG_FALSE(uname)			\
	SETPAGEFLAG_NOOP(uname) CLEARPAGEFLAG_NOOP(uname)

#घोषणा TESTSCFLAG_FALSE(uname)						\
	TESTSETFLAG_FALSE(uname) TESTCLEARFLAG_FALSE(uname)

__PAGEFLAG(Locked, locked, PF_NO_TAIL)
PAGEFLAG(Waiters, रुकोers, PF_ONLY_HEAD) __CLEARPAGEFLAG(Waiters, रुकोers, PF_ONLY_HEAD)
PAGEFLAG(Error, error, PF_NO_TAIL) TESTCLEARFLAG(Error, error, PF_NO_TAIL)
PAGEFLAG(Referenced, referenced, PF_HEAD)
	TESTCLEARFLAG(Referenced, referenced, PF_HEAD)
	__SETPAGEFLAG(Referenced, referenced, PF_HEAD)
PAGEFLAG(Dirty, dirty, PF_HEAD) TESTSCFLAG(Dirty, dirty, PF_HEAD)
	__CLEARPAGEFLAG(Dirty, dirty, PF_HEAD)
PAGEFLAG(LRU, lru, PF_HEAD) __CLEARPAGEFLAG(LRU, lru, PF_HEAD)
	TESTCLEARFLAG(LRU, lru, PF_HEAD)
PAGEFLAG(Active, active, PF_HEAD) __CLEARPAGEFLAG(Active, active, PF_HEAD)
	TESTCLEARFLAG(Active, active, PF_HEAD)
PAGEFLAG(Workingset, workingset, PF_HEAD)
	TESTCLEARFLAG(Workingset, workingset, PF_HEAD)
__PAGEFLAG(Slab, slab, PF_NO_TAIL)
__PAGEFLAG(SlobFree, slob_मुक्त, PF_NO_TAIL)
PAGEFLAG(Checked, checked, PF_NO_COMPOUND)	   /* Used by some fileप्रणालीs */

/* Xen */
PAGEFLAG(Pinned, pinned, PF_NO_COMPOUND)
	TESTSCFLAG(Pinned, pinned, PF_NO_COMPOUND)
PAGEFLAG(SavePinned, savepinned, PF_NO_COMPOUND);
PAGEFLAG(Foreign, क्रमeign, PF_NO_COMPOUND);
PAGEFLAG(XenRemapped, xen_remapped, PF_NO_COMPOUND)
	TESTCLEARFLAG(XenRemapped, xen_remapped, PF_NO_COMPOUND)

PAGEFLAG(Reserved, reserved, PF_NO_COMPOUND)
	__CLEARPAGEFLAG(Reserved, reserved, PF_NO_COMPOUND)
	__SETPAGEFLAG(Reserved, reserved, PF_NO_COMPOUND)
PAGEFLAG(SwapBacked, swapbacked, PF_NO_TAIL)
	__CLEARPAGEFLAG(SwapBacked, swapbacked, PF_NO_TAIL)
	__SETPAGEFLAG(SwapBacked, swapbacked, PF_NO_TAIL)

/*
 * Private page markings that may be used by the fileप्रणाली that owns the page
 * क्रम its own purposes.
 * - PG_निजी and PG_निजी_2 cause releasepage() and co to be invoked
 */
PAGEFLAG(Private, निजी, PF_ANY)
PAGEFLAG(Private2, निजी_2, PF_ANY) TESTSCFLAG(Private2, निजी_2, PF_ANY)
PAGEFLAG(OwnerPriv1, owner_priv_1, PF_ANY)
	TESTCLEARFLAG(OwnerPriv1, owner_priv_1, PF_ANY)

/*
 * Only test-and-set exist क्रम PG_ग_लिखोback.  The unconditional चालकs are
 * risky: they bypass page accounting.
 */
TESTPAGEFLAG(Writeback, ग_लिखोback, PF_NO_TAIL)
	TESTSCFLAG(Writeback, ग_लिखोback, PF_NO_TAIL)
PAGEFLAG(MappedToDisk, mappedtodisk, PF_NO_TAIL)

/* PG_पढ़ोahead is only used क्रम पढ़ोs; PG_reclaim is only क्रम ग_लिखोs */
PAGEFLAG(Reclaim, reclaim, PF_NO_TAIL)
	TESTCLEARFLAG(Reclaim, reclaim, PF_NO_TAIL)
PAGEFLAG(Readahead, reclaim, PF_NO_COMPOUND)
	TESTCLEARFLAG(Readahead, reclaim, PF_NO_COMPOUND)

#अगर_घोषित CONFIG_HIGHMEM
/*
 * Must use a macro here due to header dependency issues. page_zone() is not
 * available at this poपूर्णांक.
 */
#घोषणा PageHighMem(__p) is_highmem_idx(page_zonक्रमागत(__p))
#अन्यथा
PAGEFLAG_FALSE(HighMem)
#पूर्ण_अगर

#अगर_घोषित CONFIG_SWAP
अटल __always_अंतरभूत पूर्णांक PageSwapCache(काष्ठा page *page)
अणु
#अगर_घोषित CONFIG_THP_SWAP
	page = compound_head(page);
#पूर्ण_अगर
	वापस PageSwapBacked(page) && test_bit(PG_swapcache, &page->flags);

पूर्ण
SETPAGEFLAG(SwapCache, swapcache, PF_NO_TAIL)
CLEARPAGEFLAG(SwapCache, swapcache, PF_NO_TAIL)
#अन्यथा
PAGEFLAG_FALSE(SwapCache)
#पूर्ण_अगर

PAGEFLAG(Unevictable, unevictable, PF_HEAD)
	__CLEARPAGEFLAG(Unevictable, unevictable, PF_HEAD)
	TESTCLEARFLAG(Unevictable, unevictable, PF_HEAD)

#अगर_घोषित CONFIG_MMU
PAGEFLAG(Mlocked, mlocked, PF_NO_TAIL)
	__CLEARPAGEFLAG(Mlocked, mlocked, PF_NO_TAIL)
	TESTSCFLAG(Mlocked, mlocked, PF_NO_TAIL)
#अन्यथा
PAGEFLAG_FALSE(Mlocked) __CLEARPAGEFLAG_NOOP(Mlocked)
	TESTSCFLAG_FALSE(Mlocked)
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_USES_PG_UNCACHED
PAGEFLAG(Uncached, uncached, PF_NO_COMPOUND)
#अन्यथा
PAGEFLAG_FALSE(Uncached)
#पूर्ण_अगर

#अगर_घोषित CONFIG_MEMORY_FAILURE
PAGEFLAG(HWPoison, hwpoison, PF_ANY)
TESTSCFLAG(HWPoison, hwpoison, PF_ANY)
#घोषणा __PG_HWPOISON (1UL << PG_hwpoison)
बाह्य bool take_page_off_buddy(काष्ठा page *page);
#अन्यथा
PAGEFLAG_FALSE(HWPoison)
#घोषणा __PG_HWPOISON 0
#पूर्ण_अगर

#अगर defined(CONFIG_IDLE_PAGE_TRACKING) && defined(CONFIG_64BIT)
TESTPAGEFLAG(Young, young, PF_ANY)
SETPAGEFLAG(Young, young, PF_ANY)
TESTCLEARFLAG(Young, young, PF_ANY)
PAGEFLAG(Idle, idle, PF_ANY)
#पूर्ण_अगर

/*
 * PageReported() is used to track reported मुक्त pages within the Buddy
 * allocator. We can use the non-atomic version of the test and set
 * operations as both should be shielded with the zone lock to prevent
 * any possible races on the setting or clearing of the bit.
 */
__PAGEFLAG(Reported, reported, PF_NO_COMPOUND)

/*
 * On an anonymous page mapped पूर्णांकo a user भव memory area,
 * page->mapping poपूर्णांकs to its anon_vma, not to a काष्ठा address_space;
 * with the PAGE_MAPPING_ANON bit set to distinguish it.  See rmap.h.
 *
 * On an anonymous page in a VM_MERGEABLE area, अगर CONFIG_KSM is enabled,
 * the PAGE_MAPPING_MOVABLE bit may be set aदीर्घ with the PAGE_MAPPING_ANON
 * bit; and then page->mapping poपूर्णांकs, not to an anon_vma, but to a निजी
 * काष्ठाure which KSM associates with that merged page.  See ksm.h.
 *
 * PAGE_MAPPING_KSM without PAGE_MAPPING_ANON is used क्रम non-lru movable
 * page and then page->mapping poपूर्णांकs a काष्ठा address_space.
 *
 * Please note that, confusingly, "page_mapping" refers to the inode
 * address_space which maps the page from disk; whereas "page_mapped"
 * refers to user भव address space पूर्णांकo which the page is mapped.
 */
#घोषणा PAGE_MAPPING_ANON	0x1
#घोषणा PAGE_MAPPING_MOVABLE	0x2
#घोषणा PAGE_MAPPING_KSM	(PAGE_MAPPING_ANON | PAGE_MAPPING_MOVABLE)
#घोषणा PAGE_MAPPING_FLAGS	(PAGE_MAPPING_ANON | PAGE_MAPPING_MOVABLE)

अटल __always_अंतरभूत पूर्णांक PageMappingFlags(काष्ठा page *page)
अणु
	वापस ((अचिन्हित दीर्घ)page->mapping & PAGE_MAPPING_FLAGS) != 0;
पूर्ण

अटल __always_अंतरभूत पूर्णांक PageAnon(काष्ठा page *page)
अणु
	page = compound_head(page);
	वापस ((अचिन्हित दीर्घ)page->mapping & PAGE_MAPPING_ANON) != 0;
पूर्ण

अटल __always_अंतरभूत पूर्णांक __PageMovable(काष्ठा page *page)
अणु
	वापस ((अचिन्हित दीर्घ)page->mapping & PAGE_MAPPING_FLAGS) ==
				PAGE_MAPPING_MOVABLE;
पूर्ण

#अगर_घोषित CONFIG_KSM
/*
 * A KSM page is one of those ग_लिखो-रक्षित "shared pages" or "merged pages"
 * which KSM maps पूर्णांकo multiple mms, wherever identical anonymous page content
 * is found in VM_MERGEABLE vmas.  It's a PageAnon page, poपूर्णांकing not to any
 * anon_vma, but to that page's node of the stable tree.
 */
अटल __always_अंतरभूत पूर्णांक PageKsm(काष्ठा page *page)
अणु
	page = compound_head(page);
	वापस ((अचिन्हित दीर्घ)page->mapping & PAGE_MAPPING_FLAGS) ==
				PAGE_MAPPING_KSM;
पूर्ण
#अन्यथा
TESTPAGEFLAG_FALSE(Ksm)
#पूर्ण_अगर

u64 stable_page_flags(काष्ठा page *page);

अटल अंतरभूत पूर्णांक PageUptodate(काष्ठा page *page)
अणु
	पूर्णांक ret;
	page = compound_head(page);
	ret = test_bit(PG_uptodate, &(page)->flags);
	/*
	 * Must ensure that the data we पढ़ो out of the page is loaded
	 * _after_ we've loaded page->flags to check क्रम PageUptodate.
	 * We can skip the barrier अगर the page is not uptodate, because
	 * we wouldn't be पढ़ोing anything from it.
	 *
	 * See SetPageUptodate() क्रम the other side of the story.
	 */
	अगर (ret)
		smp_rmb();

	वापस ret;
पूर्ण

अटल __always_अंतरभूत व्योम __SetPageUptodate(काष्ठा page *page)
अणु
	VM_BUG_ON_PAGE(PageTail(page), page);
	smp_wmb();
	__set_bit(PG_uptodate, &page->flags);
पूर्ण

अटल __always_अंतरभूत व्योम SetPageUptodate(काष्ठा page *page)
अणु
	VM_BUG_ON_PAGE(PageTail(page), page);
	/*
	 * Memory barrier must be issued beक्रमe setting the PG_uptodate bit,
	 * so that all previous stores issued in order to bring the page
	 * uptodate are actually visible beक्रमe PageUptodate becomes true.
	 */
	smp_wmb();
	set_bit(PG_uptodate, &page->flags);
पूर्ण

CLEARPAGEFLAG(Uptodate, uptodate, PF_NO_TAIL)

पूर्णांक test_clear_page_ग_लिखोback(काष्ठा page *page);
पूर्णांक __test_set_page_ग_लिखोback(काष्ठा page *page, bool keep_ग_लिखो);

#घोषणा test_set_page_ग_लिखोback(page)			\
	__test_set_page_ग_लिखोback(page, false)
#घोषणा test_set_page_ग_लिखोback_keepग_लिखो(page)	\
	__test_set_page_ग_लिखोback(page, true)

अटल अंतरभूत व्योम set_page_ग_लिखोback(काष्ठा page *page)
अणु
	test_set_page_ग_लिखोback(page);
पूर्ण

अटल अंतरभूत व्योम set_page_ग_लिखोback_keepग_लिखो(काष्ठा page *page)
अणु
	test_set_page_ग_लिखोback_keepग_लिखो(page);
पूर्ण

__PAGEFLAG(Head, head, PF_ANY) CLEARPAGEFLAG(Head, head, PF_ANY)

अटल __always_अंतरभूत व्योम set_compound_head(काष्ठा page *page, काष्ठा page *head)
अणु
	WRITE_ONCE(page->compound_head, (अचिन्हित दीर्घ)head + 1);
पूर्ण

अटल __always_अंतरभूत व्योम clear_compound_head(काष्ठा page *page)
अणु
	WRITE_ONCE(page->compound_head, 0);
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
अटल अंतरभूत व्योम ClearPageCompound(काष्ठा page *page)
अणु
	BUG_ON(!PageHead(page));
	ClearPageHead(page);
पूर्ण
#पूर्ण_अगर

#घोषणा PG_head_mask ((1UL << PG_head))

#अगर_घोषित CONFIG_HUGETLB_PAGE
पूर्णांक PageHuge(काष्ठा page *page);
पूर्णांक PageHeadHuge(काष्ठा page *page);
#अन्यथा
TESTPAGEFLAG_FALSE(Huge)
TESTPAGEFLAG_FALSE(HeadHuge)
#पूर्ण_अगर


#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
/*
 * PageHuge() only वापसs true क्रम hugetlbfs pages, but not क्रम
 * normal or transparent huge pages.
 *
 * PageTransHuge() वापसs true क्रम both transparent huge and
 * hugetlbfs pages, but not normal pages. PageTransHuge() can only be
 * called only in the core VM paths where hugetlbfs pages can't exist.
 */
अटल अंतरभूत पूर्णांक PageTransHuge(काष्ठा page *page)
अणु
	VM_BUG_ON_PAGE(PageTail(page), page);
	वापस PageHead(page);
पूर्ण

/*
 * PageTransCompound वापसs true क्रम both transparent huge pages
 * and hugetlbfs pages, so it should only be called when it's known
 * that hugetlbfs pages aren't involved.
 */
अटल अंतरभूत पूर्णांक PageTransCompound(काष्ठा page *page)
अणु
	वापस PageCompound(page);
पूर्ण

/*
 * PageTransCompoundMap is the same as PageTransCompound, but it also
 * guarantees the primary MMU has the entire compound page mapped
 * through pmd_trans_huge, which in turn guarantees the secondary MMUs
 * can also map the entire compound page. This allows the secondary
 * MMUs to call get_user_pages() only once क्रम each compound page and
 * to immediately map the entire compound page with a single secondary
 * MMU fault. If there will be a pmd split later, the secondary MMUs
 * will get an update through the MMU notअगरier invalidation through
 * split_huge_pmd().
 *
 * Unlike PageTransCompound, this is safe to be called only जबतक
 * split_huge_pmd() cannot run from under us, like अगर रक्षित by the
 * MMU notअगरier, otherwise it may result in page->_mapcount check false
 * positives.
 *
 * We have to treat page cache THP dअगरferently since every subpage of it
 * would get _mapcount inc'ed once it is PMD mapped.  But, it may be PTE
 * mapped in the current process so comparing subpage's _mapcount to
 * compound_mapcount to filter out PTE mapped हाल.
 */
अटल अंतरभूत पूर्णांक PageTransCompoundMap(काष्ठा page *page)
अणु
	काष्ठा page *head;

	अगर (!PageTransCompound(page))
		वापस 0;

	अगर (PageAnon(page))
		वापस atomic_पढ़ो(&page->_mapcount) < 0;

	head = compound_head(page);
	/* File THP is PMD mapped and not PTE mapped */
	वापस atomic_पढ़ो(&page->_mapcount) ==
	       atomic_पढ़ो(compound_mapcount_ptr(head));
पूर्ण

/*
 * PageTransTail वापसs true क्रम both transparent huge pages
 * and hugetlbfs pages, so it should only be called when it's known
 * that hugetlbfs pages aren't involved.
 */
अटल अंतरभूत पूर्णांक PageTransTail(काष्ठा page *page)
अणु
	वापस PageTail(page);
पूर्ण

/*
 * PageDoubleMap indicates that the compound page is mapped with PTEs as well
 * as PMDs.
 *
 * This is required क्रम optimization of rmap operations क्रम THP: we can postpone
 * per small page mapcount accounting (and its overhead from atomic operations)
 * until the first PMD split.
 *
 * For the page PageDoubleMap means ->_mapcount in all sub-pages is offset up
 * by one. This reference will go away with last compound_mapcount.
 *
 * See also __split_huge_pmd_locked() and page_हटाओ_anon_compound_rmap().
 */
PAGEFLAG(DoubleMap, द्विगुन_map, PF_SECOND)
	TESTSCFLAG(DoubleMap, द्विगुन_map, PF_SECOND)
#अन्यथा
TESTPAGEFLAG_FALSE(TransHuge)
TESTPAGEFLAG_FALSE(TransCompound)
TESTPAGEFLAG_FALSE(TransCompoundMap)
TESTPAGEFLAG_FALSE(TransTail)
PAGEFLAG_FALSE(DoubleMap)
	TESTSCFLAG_FALSE(DoubleMap)
#पूर्ण_अगर

/*
 * For pages that are never mapped to userspace (and aren't PageSlab),
 * page_type may be used.  Because it is initialised to -1, we invert the
 * sense of the bit, so __SetPageFoo *clears* the bit used क्रम PageFoo, and
 * __ClearPageFoo *sets* the bit used क्रम PageFoo.  We reserve a few high and
 * low bits so that an underflow or overflow of page_mapcount() won't be
 * mistaken क्रम a page type value.
 */

#घोषणा PAGE_TYPE_BASE	0xf0000000
/* Reserve		0x0000007f to catch underflows of page_mapcount */
#घोषणा PAGE_MAPCOUNT_RESERVE	-128
#घोषणा PG_buddy	0x00000080
#घोषणा PG_offline	0x00000100
#घोषणा PG_table	0x00000200
#घोषणा PG_guard	0x00000400

#घोषणा PageType(page, flag)						\
	((page->page_type & (PAGE_TYPE_BASE | flag)) == PAGE_TYPE_BASE)

अटल अंतरभूत पूर्णांक page_has_type(काष्ठा page *page)
अणु
	वापस (पूर्णांक)page->page_type < PAGE_MAPCOUNT_RESERVE;
पूर्ण

#घोषणा PAGE_TYPE_OPS(uname, lname)					\
अटल __always_अंतरभूत पूर्णांक Page##uname(काष्ठा page *page)		\
अणु									\
	वापस PageType(page, PG_##lname);				\
पूर्ण									\
अटल __always_अंतरभूत व्योम __SetPage##uname(काष्ठा page *page)		\
अणु									\
	VM_BUG_ON_PAGE(!PageType(page, 0), page);			\
	page->page_type &= ~PG_##lname;					\
पूर्ण									\
अटल __always_अंतरभूत व्योम __ClearPage##uname(काष्ठा page *page)	\
अणु									\
	VM_BUG_ON_PAGE(!Page##uname(page), page);			\
	page->page_type |= PG_##lname;					\
पूर्ण

/*
 * PageBuddy() indicates that the page is मुक्त and in the buddy प्रणाली
 * (see mm/page_alloc.c).
 */
PAGE_TYPE_OPS(Buddy, buddy)

/*
 * PageOffline() indicates that the page is logically offline although the
 * containing section is online. (e.g. inflated in a balloon driver or
 * not onlined when onlining the section).
 * The content of these pages is effectively stale. Such pages should not
 * be touched (पढ़ो/ग_लिखो/dump/save) except by their owner.
 *
 * If a driver wants to allow to offline unmovable PageOffline() pages without
 * putting them back to the buddy, it can करो so via the memory notअगरier by
 * decrementing the reference count in MEM_GOING_OFFLINE and incrementing the
 * reference count in MEM_CANCEL_OFFLINE. When offlining, the PageOffline()
 * pages (now with a reference count of zero) are treated like मुक्त pages,
 * allowing the containing memory block to get offlined. A driver that
 * relies on this feature is aware that re-onlining the memory block will
 * require to re-set the pages PageOffline() and not giving them to the
 * buddy via online_page_callback_t.
 */
PAGE_TYPE_OPS(Offline, offline)

/*
 * Marks pages in use as page tables.
 */
PAGE_TYPE_OPS(Table, table)

/*
 * Marks guardpages used with debug_pagealloc.
 */
PAGE_TYPE_OPS(Guard, guard)

बाह्य bool is_मुक्त_buddy_page(काष्ठा page *page);

__PAGEFLAG(Isolated, isolated, PF_ANY);

/*
 * If network-based swap is enabled, sl*b must keep track of whether pages
 * were allocated from pfmeदो_स्मृति reserves.
 */
अटल अंतरभूत पूर्णांक PageSlabPfmeदो_स्मृति(काष्ठा page *page)
अणु
	VM_BUG_ON_PAGE(!PageSlab(page), page);
	वापस PageActive(page);
पूर्ण

अटल अंतरभूत व्योम SetPageSlabPfmeदो_स्मृति(काष्ठा page *page)
अणु
	VM_BUG_ON_PAGE(!PageSlab(page), page);
	SetPageActive(page);
पूर्ण

अटल अंतरभूत व्योम __ClearPageSlabPfmeदो_स्मृति(काष्ठा page *page)
अणु
	VM_BUG_ON_PAGE(!PageSlab(page), page);
	__ClearPageActive(page);
पूर्ण

अटल अंतरभूत व्योम ClearPageSlabPfmeदो_स्मृति(काष्ठा page *page)
अणु
	VM_BUG_ON_PAGE(!PageSlab(page), page);
	ClearPageActive(page);
पूर्ण

#अगर_घोषित CONFIG_MMU
#घोषणा __PG_MLOCKED		(1UL << PG_mlocked)
#अन्यथा
#घोषणा __PG_MLOCKED		0
#पूर्ण_अगर

/*
 * Flags checked when a page is मुक्तd.  Pages being मुक्तd should not have
 * these flags set.  If they are, there is a problem.
 */
#घोषणा PAGE_FLAGS_CHECK_AT_FREE				\
	(1UL << PG_lru		| 1UL << PG_locked	|	\
	 1UL << PG_निजी	| 1UL << PG_निजी_2	|	\
	 1UL << PG_ग_लिखोback	| 1UL << PG_reserved	|	\
	 1UL << PG_slab		| 1UL << PG_active 	|	\
	 1UL << PG_unevictable	| __PG_MLOCKED)

/*
 * Flags checked when a page is prepped क्रम वापस by the page allocator.
 * Pages being prepped should not have these flags set.  If they are set,
 * there has been a kernel bug or काष्ठा page corruption.
 *
 * __PG_HWPOISON is exceptional because it needs to be kept beyond page's
 * alloc-मुक्त cycle to prevent from reusing the page.
 */
#घोषणा PAGE_FLAGS_CHECK_AT_PREP	\
	(((1UL << NR_PAGEFLAGS) - 1) & ~__PG_HWPOISON)

#घोषणा PAGE_FLAGS_PRIVATE				\
	(1UL << PG_निजी | 1UL << PG_निजी_2)
/**
 * page_has_निजी - Determine अगर page has निजी stuff
 * @page: The page to be checked
 *
 * Determine अगर a page has निजी stuff, indicating that release routines
 * should be invoked upon it.
 */
अटल अंतरभूत पूर्णांक page_has_निजी(काष्ठा page *page)
अणु
	वापस !!(page->flags & PAGE_FLAGS_PRIVATE);
पूर्ण

#अघोषित PF_ANY
#अघोषित PF_HEAD
#अघोषित PF_ONLY_HEAD
#अघोषित PF_NO_TAIL
#अघोषित PF_NO_COMPOUND
#अघोषित PF_SECOND
#पूर्ण_अगर /* !__GENERATING_BOUNDS_H */

#पूर्ण_अगर	/* PAGE_FLAGS_H */
