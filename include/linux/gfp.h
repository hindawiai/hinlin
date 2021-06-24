<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_GFP_H
#घोषणा __LINUX_GFP_H

#समावेश <linux/mmdebug.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/linkage.h>
#समावेश <linux/topology.h>

/* The प्रकार is in types.h but we want the करोcumentation here */
#अगर 0
/**
 * प्रकार gfp_t - Memory allocation flags.
 *
 * GFP flags are commonly used throughout Linux to indicate how memory
 * should be allocated.  The GFP acronym stands क्रम get_मुक्त_pages(),
 * the underlying memory allocation function.  Not every GFP flag is
 * supported by every function which may allocate memory.  Most users
 * will want to use a plain ``GFP_KERNEL``.
 */
प्रकार अचिन्हित पूर्णांक __bitwise gfp_t;
#पूर्ण_अगर

काष्ठा vm_area_काष्ठा;

/*
 * In हाल of changes, please करोn't क्रमget to update
 * include/trace/events/mmflags.h and tools/perf/builtin-kmem.c
 */

/* Plain पूर्णांकeger GFP biपंचांगasks. Do not use this directly. */
#घोषणा ___GFP_DMA		0x01u
#घोषणा ___GFP_HIGHMEM		0x02u
#घोषणा ___GFP_DMA32		0x04u
#घोषणा ___GFP_MOVABLE		0x08u
#घोषणा ___GFP_RECLAIMABLE	0x10u
#घोषणा ___GFP_HIGH		0x20u
#घोषणा ___GFP_IO		0x40u
#घोषणा ___GFP_FS		0x80u
#घोषणा ___GFP_ZERO		0x100u
#घोषणा ___GFP_ATOMIC		0x200u
#घोषणा ___GFP_सूचीECT_RECLAIM	0x400u
#घोषणा ___GFP_KSWAPD_RECLAIM	0x800u
#घोषणा ___GFP_WRITE		0x1000u
#घोषणा ___GFP_NOWARN		0x2000u
#घोषणा ___GFP_RETRY_MAYFAIL	0x4000u
#घोषणा ___GFP_NOFAIL		0x8000u
#घोषणा ___GFP_NORETRY		0x10000u
#घोषणा ___GFP_MEMALLOC		0x20000u
#घोषणा ___GFP_COMP		0x40000u
#घोषणा ___GFP_NOMEMALLOC	0x80000u
#घोषणा ___GFP_HARDWALL		0x100000u
#घोषणा ___GFP_THISNODE		0x200000u
#घोषणा ___GFP_ACCOUNT		0x400000u
#अगर_घोषित CONFIG_LOCKDEP
#घोषणा ___GFP_NOLOCKDEP	0x800000u
#अन्यथा
#घोषणा ___GFP_NOLOCKDEP	0
#पूर्ण_अगर
/* If the above are modअगरied, __GFP_BITS_SHIFT may need updating */

/*
 * Physical address zone modअगरiers (see linux/mmzone.h - low four bits)
 *
 * Do not put any conditional on these. If necessary modअगरy the definitions
 * without the underscores and use them consistently. The definitions here may
 * be used in bit comparisons.
 */
#घोषणा __GFP_DMA	((__क्रमce gfp_t)___GFP_DMA)
#घोषणा __GFP_HIGHMEM	((__क्रमce gfp_t)___GFP_HIGHMEM)
#घोषणा __GFP_DMA32	((__क्रमce gfp_t)___GFP_DMA32)
#घोषणा __GFP_MOVABLE	((__क्रमce gfp_t)___GFP_MOVABLE)  /* ZONE_MOVABLE allowed */
#घोषणा GFP_ZONEMASK	(__GFP_DMA|__GFP_HIGHMEM|__GFP_DMA32|__GFP_MOVABLE)

/**
 * DOC: Page mobility and placement hपूर्णांकs
 *
 * Page mobility and placement hपूर्णांकs
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * These flags provide hपूर्णांकs about how mobile the page is. Pages with similar
 * mobility are placed within the same pageblocks to minimise problems due
 * to बाह्यal fragmentation.
 *
 * %__GFP_MOVABLE (also a zone modअगरier) indicates that the page can be
 * moved by page migration during memory compaction or can be reclaimed.
 *
 * %__GFP_RECLAIMABLE is used क्रम slab allocations that specअगरy
 * SLAB_RECLAIM_ACCOUNT and whose pages can be मुक्तd via shrinkers.
 *
 * %__GFP_WRITE indicates the caller पूर्णांकends to dirty the page. Where possible,
 * these pages will be spपढ़ो between local zones to aव्योम all the dirty
 * pages being in one zone (fair zone allocation policy).
 *
 * %__GFP_HARDWALL enक्रमces the cpuset memory allocation policy.
 *
 * %__GFP_THISNODE क्रमces the allocation to be satisfied from the requested
 * node with no fallbacks or placement policy enक्रमcements.
 *
 * %__GFP_ACCOUNT causes the allocation to be accounted to kmemcg.
 */
#घोषणा __GFP_RECLAIMABLE ((__क्रमce gfp_t)___GFP_RECLAIMABLE)
#घोषणा __GFP_WRITE	((__क्रमce gfp_t)___GFP_WRITE)
#घोषणा __GFP_HARDWALL   ((__क्रमce gfp_t)___GFP_HARDWALL)
#घोषणा __GFP_THISNODE	((__क्रमce gfp_t)___GFP_THISNODE)
#घोषणा __GFP_ACCOUNT	((__क्रमce gfp_t)___GFP_ACCOUNT)

/**
 * DOC: Watermark modअगरiers
 *
 * Watermark modअगरiers -- controls access to emergency reserves
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * %__GFP_HIGH indicates that the caller is high-priority and that granting
 * the request is necessary beक्रमe the प्रणाली can make क्रमward progress.
 * For example, creating an IO context to clean pages.
 *
 * %__GFP_ATOMIC indicates that the caller cannot reclaim or sleep and is
 * high priority. Users are typically पूर्णांकerrupt handlers. This may be
 * used in conjunction with %__GFP_HIGH
 *
 * %__GFP_MEMALLOC allows access to all memory. This should only be used when
 * the caller guarantees the allocation will allow more memory to be मुक्तd
 * very लघुly e.g. process निकासing or swapping. Users either should
 * be the MM or co-ordinating बंदly with the VM (e.g. swap over NFS).
 * Users of this flag have to be extremely careful to not deplete the reserve
 * completely and implement a throttling mechanism which controls the
 * consumption of the reserve based on the amount of मुक्तd memory.
 * Usage of a pre-allocated pool (e.g. mempool) should be always considered
 * beक्रमe using this flag.
 *
 * %__GFP_NOMEMALLOC is used to explicitly क्रमbid access to emergency reserves.
 * This takes precedence over the %__GFP_MEMALLOC flag अगर both are set.
 */
#घोषणा __GFP_ATOMIC	((__क्रमce gfp_t)___GFP_ATOMIC)
#घोषणा __GFP_HIGH	((__क्रमce gfp_t)___GFP_HIGH)
#घोषणा __GFP_MEMALLOC	((__क्रमce gfp_t)___GFP_MEMALLOC)
#घोषणा __GFP_NOMEMALLOC ((__क्रमce gfp_t)___GFP_NOMEMALLOC)

/**
 * DOC: Reclaim modअगरiers
 *
 * Reclaim modअगरiers
 * ~~~~~~~~~~~~~~~~~
 * Please note that all the following flags are only applicable to sleepable
 * allocations (e.g. %GFP_NOWAIT and %GFP_ATOMIC will ignore them).
 *
 * %__GFP_IO can start physical IO.
 *
 * %__GFP_FS can call करोwn to the low-level FS. Clearing the flag aव्योमs the
 * allocator recursing पूर्णांकo the fileप्रणाली which might alपढ़ोy be holding
 * locks.
 *
 * %__GFP_सूचीECT_RECLAIM indicates that the caller may enter direct reclaim.
 * This flag can be cleared to aव्योम unnecessary delays when a fallback
 * option is available.
 *
 * %__GFP_KSWAPD_RECLAIM indicates that the caller wants to wake kswapd when
 * the low watermark is reached and have it reclaim pages until the high
 * watermark is reached. A caller may wish to clear this flag when fallback
 * options are available and the reclaim is likely to disrupt the प्रणाली. The
 * canonical example is THP allocation where a fallback is cheap but
 * reclaim/compaction may cause indirect stalls.
 *
 * %__GFP_RECLAIM is लघुhand to allow/क्रमbid both direct and kswapd reclaim.
 *
 * The शेष allocator behavior depends on the request size. We have a concept
 * of so called costly allocations (with order > %PAGE_ALLOC_COSTLY_ORDER).
 * !costly allocations are too essential to fail so they are implicitly
 * non-failing by शेष (with some exceptions like OOM victims might fail so
 * the caller still has to check क्रम failures) जबतक costly requests try to be
 * not disruptive and back off even without invoking the OOM समाप्तer.
 * The following three modअगरiers might be used to override some of these
 * implicit rules
 *
 * %__GFP_NORETRY: The VM implementation will try only very lightweight
 * memory direct reclaim to get some memory under memory pressure (thus
 * it can sleep). It will aव्योम disruptive actions like OOM समाप्तer. The
 * caller must handle the failure which is quite likely to happen under
 * heavy memory pressure. The flag is suitable when failure can easily be
 * handled at small cost, such as reduced throughput
 *
 * %__GFP_RETRY_MAYFAIL: The VM implementation will retry memory reclaim
 * procedures that have previously failed अगर there is some indication
 * that progress has been made अन्यथा where.  It can रुको क्रम other
 * tasks to attempt high level approaches to मुक्तing memory such as
 * compaction (which हटाओs fragmentation) and page-out.
 * There is still a definite limit to the number of retries, but it is
 * a larger limit than with %__GFP_NORETRY.
 * Allocations with this flag may fail, but only when there is
 * genuinely little unused memory. While these allocations करो not
 * directly trigger the OOM समाप्तer, their failure indicates that
 * the प्रणाली is likely to need to use the OOM समाप्तer soon.  The
 * caller must handle failure, but can reasonably करो so by failing
 * a higher-level request, or completing it only in a much less
 * efficient manner.
 * If the allocation करोes fail, and the caller is in a position to
 * मुक्त some non-essential memory, करोing so could benefit the प्रणाली
 * as a whole.
 *
 * %__GFP_NOFAIL: The VM implementation _must_ retry infinitely: the caller
 * cannot handle allocation failures. The allocation could block
 * indefinitely but will never वापस with failure. Testing क्रम
 * failure is poपूर्णांकless.
 * New users should be evaluated carefully (and the flag should be
 * used only when there is no reasonable failure policy) but it is
 * definitely preferable to use the flag rather than खोलोcode endless
 * loop around allocator.
 * Using this flag क्रम costly allocations is _highly_ discouraged.
 */
#घोषणा __GFP_IO	((__क्रमce gfp_t)___GFP_IO)
#घोषणा __GFP_FS	((__क्रमce gfp_t)___GFP_FS)
#घोषणा __GFP_सूचीECT_RECLAIM	((__क्रमce gfp_t)___GFP_सूचीECT_RECLAIM) /* Caller can reclaim */
#घोषणा __GFP_KSWAPD_RECLAIM	((__क्रमce gfp_t)___GFP_KSWAPD_RECLAIM) /* kswapd can wake */
#घोषणा __GFP_RECLAIM ((__क्रमce gfp_t)(___GFP_सूचीECT_RECLAIM|___GFP_KSWAPD_RECLAIM))
#घोषणा __GFP_RETRY_MAYFAIL	((__क्रमce gfp_t)___GFP_RETRY_MAYFAIL)
#घोषणा __GFP_NOFAIL	((__क्रमce gfp_t)___GFP_NOFAIL)
#घोषणा __GFP_NORETRY	((__क्रमce gfp_t)___GFP_NORETRY)

/**
 * DOC: Action modअगरiers
 *
 * Action modअगरiers
 * ~~~~~~~~~~~~~~~~
 *
 * %__GFP_NOWARN suppresses allocation failure reports.
 *
 * %__GFP_COMP address compound page metadata.
 *
 * %__GFP_ZERO वापसs a zeroed page on success.
 */
#घोषणा __GFP_NOWARN	((__क्रमce gfp_t)___GFP_NOWARN)
#घोषणा __GFP_COMP	((__क्रमce gfp_t)___GFP_COMP)
#घोषणा __GFP_ZERO	((__क्रमce gfp_t)___GFP_ZERO)

/* Disable lockdep क्रम GFP context tracking */
#घोषणा __GFP_NOLOCKDEP ((__क्रमce gfp_t)___GFP_NOLOCKDEP)

/* Room क्रम N __GFP_FOO bits */
#घोषणा __GFP_BITS_SHIFT (23 + IS_ENABLED(CONFIG_LOCKDEP))
#घोषणा __GFP_BITS_MASK ((__क्रमce gfp_t)((1 << __GFP_BITS_SHIFT) - 1))

/**
 * DOC: Useful GFP flag combinations
 *
 * Useful GFP flag combinations
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Useful GFP flag combinations that are commonly used. It is recommended
 * that subप्रणालीs start with one of these combinations and then set/clear
 * %__GFP_FOO flags as necessary.
 *
 * %GFP_ATOMIC users can not sleep and need the allocation to succeed. A lower
 * watermark is applied to allow access to "atomic reserves".
 * The current implementation करोesn't support NMI and few other strict
 * non-preemptive contexts (e.g. raw_spin_lock). The same applies to %GFP_NOWAIT.
 *
 * %GFP_KERNEL is typical क्रम kernel-पूर्णांकernal allocations. The caller requires
 * %ZONE_NORMAL or a lower zone क्रम direct access but can direct reclaim.
 *
 * %GFP_KERNEL_ACCOUNT is the same as GFP_KERNEL, except the allocation is
 * accounted to kmemcg.
 *
 * %GFP_NOWAIT is क्रम kernel allocations that should not stall क्रम direct
 * reclaim, start physical IO or use any fileप्रणाली callback.
 *
 * %GFP_NOIO will use direct reclaim to discard clean pages or slab pages
 * that करो not require the starting of any physical IO.
 * Please try to aव्योम using this flag directly and instead use
 * meदो_स्मृति_noio_अणुsave,restoreपूर्ण to mark the whole scope which cannot
 * perक्रमm any IO with a लघु explanation why. All allocation requests
 * will inherit GFP_NOIO implicitly.
 *
 * %GFP_NOFS will use direct reclaim but will not use any fileप्रणाली पूर्णांकerfaces.
 * Please try to aव्योम using this flag directly and instead use
 * meदो_स्मृति_nofs_अणुsave,restoreपूर्ण to mark the whole scope which cannot/shouldn't
 * recurse पूर्णांकo the FS layer with a लघु explanation why. All allocation
 * requests will inherit GFP_NOFS implicitly.
 *
 * %GFP_USER is क्रम userspace allocations that also need to be directly
 * accessibly by the kernel or hardware. It is typically used by hardware
 * क्रम buffers that are mapped to userspace (e.g. graphics) that hardware
 * still must DMA to. cpuset limits are enक्रमced क्रम these allocations.
 *
 * %GFP_DMA exists क्रम historical reasons and should be aव्योमed where possible.
 * The flags indicates that the caller requires that the lowest zone be
 * used (%ZONE_DMA or 16M on x86-64). Ideally, this would be हटाओd but
 * it would require careful auditing as some users really require it and
 * others use the flag to aव्योम lowmem reserves in %ZONE_DMA and treat the
 * lowest zone as a type of emergency reserve.
 *
 * %GFP_DMA32 is similar to %GFP_DMA except that the caller requires a 32-bit
 * address.
 *
 * %GFP_HIGHUSER is क्रम userspace allocations that may be mapped to userspace,
 * करो not need to be directly accessible by the kernel but that cannot
 * move once in use. An example may be a hardware allocation that maps
 * data directly पूर्णांकo userspace but has no addressing limitations.
 *
 * %GFP_HIGHUSER_MOVABLE is क्रम userspace allocations that the kernel करोes not
 * need direct access to but can use kmap() when access is required. They
 * are expected to be movable via page reclaim or page migration. Typically,
 * pages on the LRU would also be allocated with %GFP_HIGHUSER_MOVABLE.
 *
 * %GFP_TRANSHUGE and %GFP_TRANSHUGE_LIGHT are used क्रम THP allocations. They
 * are compound allocations that will generally fail quickly अगर memory is not
 * available and will not wake kswapd/kcompactd on failure. The _LIGHT
 * version करोes not attempt reclaim/compaction at all and is by शेष used
 * in page fault path, जबतक the non-light is used by khugepaged.
 */
#घोषणा GFP_ATOMIC	(__GFP_HIGH|__GFP_ATOMIC|__GFP_KSWAPD_RECLAIM)
#घोषणा GFP_KERNEL	(__GFP_RECLAIM | __GFP_IO | __GFP_FS)
#घोषणा GFP_KERNEL_ACCOUNT (GFP_KERNEL | __GFP_ACCOUNT)
#घोषणा GFP_NOWAIT	(__GFP_KSWAPD_RECLAIM)
#घोषणा GFP_NOIO	(__GFP_RECLAIM)
#घोषणा GFP_NOFS	(__GFP_RECLAIM | __GFP_IO)
#घोषणा GFP_USER	(__GFP_RECLAIM | __GFP_IO | __GFP_FS | __GFP_HARDWALL)
#घोषणा GFP_DMA		__GFP_DMA
#घोषणा GFP_DMA32	__GFP_DMA32
#घोषणा GFP_HIGHUSER	(GFP_USER | __GFP_HIGHMEM)
#घोषणा GFP_HIGHUSER_MOVABLE	(GFP_HIGHUSER | __GFP_MOVABLE)
#घोषणा GFP_TRANSHUGE_LIGHT	((GFP_HIGHUSER_MOVABLE | __GFP_COMP | \
			 __GFP_NOMEMALLOC | __GFP_NOWARN) & ~__GFP_RECLAIM)
#घोषणा GFP_TRANSHUGE	(GFP_TRANSHUGE_LIGHT | __GFP_सूचीECT_RECLAIM)

/* Convert GFP flags to their corresponding migrate type */
#घोषणा GFP_MOVABLE_MASK (__GFP_RECLAIMABLE|__GFP_MOVABLE)
#घोषणा GFP_MOVABLE_SHIFT 3

अटल अंतरभूत पूर्णांक gfp_migratetype(स्थिर gfp_t gfp_flags)
अणु
	VM_WARN_ON((gfp_flags & GFP_MOVABLE_MASK) == GFP_MOVABLE_MASK);
	BUILD_BUG_ON((1UL << GFP_MOVABLE_SHIFT) != ___GFP_MOVABLE);
	BUILD_BUG_ON((___GFP_MOVABLE >> GFP_MOVABLE_SHIFT) != MIGRATE_MOVABLE);

	अगर (unlikely(page_group_by_mobility_disabled))
		वापस MIGRATE_UNMOVABLE;

	/* Group based on mobility */
	वापस (gfp_flags & GFP_MOVABLE_MASK) >> GFP_MOVABLE_SHIFT;
पूर्ण
#अघोषित GFP_MOVABLE_MASK
#अघोषित GFP_MOVABLE_SHIFT

अटल अंतरभूत bool gfpflags_allow_blocking(स्थिर gfp_t gfp_flags)
अणु
	वापस !!(gfp_flags & __GFP_सूचीECT_RECLAIM);
पूर्ण

/**
 * gfpflags_normal_context - is gfp_flags a normal sleepable context?
 * @gfp_flags: gfp_flags to test
 *
 * Test whether @gfp_flags indicates that the allocation is from the
 * %current context and allowed to sleep.
 *
 * An allocation being allowed to block करोesn't mean it owns the %current
 * context.  When direct reclaim path tries to allocate memory, the
 * allocation context is nested inside whatever %current was करोing at the
 * समय of the original allocation.  The nested allocation may be allowed
 * to block but modअगरying anything %current owns can corrupt the outer
 * context's expectations.
 *
 * %true result from this function indicates that the allocation context
 * can sleep and use anything that's associated with %current.
 */
अटल अंतरभूत bool gfpflags_normal_context(स्थिर gfp_t gfp_flags)
अणु
	वापस (gfp_flags & (__GFP_सूचीECT_RECLAIM | __GFP_MEMALLOC)) ==
		__GFP_सूचीECT_RECLAIM;
पूर्ण

#अगर_घोषित CONFIG_HIGHMEM
#घोषणा OPT_ZONE_HIGHMEM ZONE_HIGHMEM
#अन्यथा
#घोषणा OPT_ZONE_HIGHMEM ZONE_NORMAL
#पूर्ण_अगर

#अगर_घोषित CONFIG_ZONE_DMA
#घोषणा OPT_ZONE_DMA ZONE_DMA
#अन्यथा
#घोषणा OPT_ZONE_DMA ZONE_NORMAL
#पूर्ण_अगर

#अगर_घोषित CONFIG_ZONE_DMA32
#घोषणा OPT_ZONE_DMA32 ZONE_DMA32
#अन्यथा
#घोषणा OPT_ZONE_DMA32 ZONE_NORMAL
#पूर्ण_अगर

/*
 * GFP_ZONE_TABLE is a word size bitstring that is used क्रम looking up the
 * zone to use given the lowest 4 bits of gfp_t. Entries are GFP_ZONES_SHIFT
 * bits दीर्घ and there are 16 of them to cover all possible combinations of
 * __GFP_DMA, __GFP_DMA32, __GFP_MOVABLE and __GFP_HIGHMEM.
 *
 * The zone fallback order is MOVABLE=>HIGHMEM=>NORMAL=>DMA32=>DMA.
 * But GFP_MOVABLE is not only a zone specअगरier but also an allocation
 * policy. Thereक्रमe __GFP_MOVABLE plus another zone selector is valid.
 * Only 1 bit of the lowest 3 bits (DMA,DMA32,HIGHMEM) can be set to "1".
 *
 *       bit       result
 *       =================
 *       0x0    => NORMAL
 *       0x1    => DMA or NORMAL
 *       0x2    => HIGHMEM or NORMAL
 *       0x3    => BAD (DMA+HIGHMEM)
 *       0x4    => DMA32 or NORMAL
 *       0x5    => BAD (DMA+DMA32)
 *       0x6    => BAD (HIGHMEM+DMA32)
 *       0x7    => BAD (HIGHMEM+DMA32+DMA)
 *       0x8    => NORMAL (MOVABLE+0)
 *       0x9    => DMA or NORMAL (MOVABLE+DMA)
 *       0xa    => MOVABLE (Movable is valid only अगर HIGHMEM is set too)
 *       0xb    => BAD (MOVABLE+HIGHMEM+DMA)
 *       0xc    => DMA32 or NORMAL (MOVABLE+DMA32)
 *       0xd    => BAD (MOVABLE+DMA32+DMA)
 *       0xe    => BAD (MOVABLE+DMA32+HIGHMEM)
 *       0xf    => BAD (MOVABLE+DMA32+HIGHMEM+DMA)
 *
 * GFP_ZONES_SHIFT must be <= 2 on 32 bit platक्रमms.
 */

#अगर defined(CONFIG_ZONE_DEVICE) && (MAX_NR_ZONES-1) <= 4
/* ZONE_DEVICE is not a valid GFP zone specअगरier */
#घोषणा GFP_ZONES_SHIFT 2
#अन्यथा
#घोषणा GFP_ZONES_SHIFT ZONES_SHIFT
#पूर्ण_अगर

#अगर 16 * GFP_ZONES_SHIFT > BITS_PER_LONG
#त्रुटि GFP_ZONES_SHIFT too large to create GFP_ZONE_TABLE पूर्णांकeger
#पूर्ण_अगर

#घोषणा GFP_ZONE_TABLE ( \
	(ZONE_NORMAL << 0 * GFP_ZONES_SHIFT)				       \
	| (OPT_ZONE_DMA << ___GFP_DMA * GFP_ZONES_SHIFT)		       \
	| (OPT_ZONE_HIGHMEM << ___GFP_HIGHMEM * GFP_ZONES_SHIFT)	       \
	| (OPT_ZONE_DMA32 << ___GFP_DMA32 * GFP_ZONES_SHIFT)		       \
	| (ZONE_NORMAL << ___GFP_MOVABLE * GFP_ZONES_SHIFT)		       \
	| (OPT_ZONE_DMA << (___GFP_MOVABLE | ___GFP_DMA) * GFP_ZONES_SHIFT)    \
	| (ZONE_MOVABLE << (___GFP_MOVABLE | ___GFP_HIGHMEM) * GFP_ZONES_SHIFT)\
	| (OPT_ZONE_DMA32 << (___GFP_MOVABLE | ___GFP_DMA32) * GFP_ZONES_SHIFT)\
)

/*
 * GFP_ZONE_BAD is a biपंचांगap क्रम all combinations of __GFP_DMA, __GFP_DMA32
 * __GFP_HIGHMEM and __GFP_MOVABLE that are not permitted. One flag per
 * entry starting with bit 0. Bit is set अगर the combination is not
 * allowed.
 */
#घोषणा GFP_ZONE_BAD ( \
	1 << (___GFP_DMA | ___GFP_HIGHMEM)				      \
	| 1 << (___GFP_DMA | ___GFP_DMA32)				      \
	| 1 << (___GFP_DMA32 | ___GFP_HIGHMEM)				      \
	| 1 << (___GFP_DMA | ___GFP_DMA32 | ___GFP_HIGHMEM)		      \
	| 1 << (___GFP_MOVABLE | ___GFP_HIGHMEM | ___GFP_DMA)		      \
	| 1 << (___GFP_MOVABLE | ___GFP_DMA32 | ___GFP_DMA)		      \
	| 1 << (___GFP_MOVABLE | ___GFP_DMA32 | ___GFP_HIGHMEM)		      \
	| 1 << (___GFP_MOVABLE | ___GFP_DMA32 | ___GFP_DMA | ___GFP_HIGHMEM)  \
)

अटल अंतरभूत क्रमागत zone_type gfp_zone(gfp_t flags)
अणु
	क्रमागत zone_type z;
	पूर्णांक bit = (__क्रमce पूर्णांक) (flags & GFP_ZONEMASK);

	z = (GFP_ZONE_TABLE >> (bit * GFP_ZONES_SHIFT)) &
					 ((1 << GFP_ZONES_SHIFT) - 1);
	VM_BUG_ON((GFP_ZONE_BAD >> bit) & 1);
	वापस z;
पूर्ण

/*
 * There is only one page-allocator function, and two मुख्य namespaces to
 * it. The alloc_page*() variants वापस 'struct page *' and as such
 * can allocate highmem pages, the *get*page*() variants वापस
 * भव kernel addresses to the allocated page(s).
 */

अटल अंतरभूत पूर्णांक gfp_zonelist(gfp_t flags)
अणु
#अगर_घोषित CONFIG_NUMA
	अगर (unlikely(flags & __GFP_THISNODE))
		वापस ZONELIST_NOFALLBACK;
#पूर्ण_अगर
	वापस ZONELIST_FALLBACK;
पूर्ण

/*
 * We get the zone list from the current node and the gfp_mask.
 * This zone list contains a maximum of MAX_NUMNODES*MAX_NR_ZONES zones.
 * There are two zonelists per node, one क्रम all zones with memory and
 * one containing just zones from the node the zonelist beदीर्घs to.
 *
 * For the normal हाल of non-DISCONTIGMEM प्रणालीs the NODE_DATA() माला_लो
 * optimized to &contig_page_data at compile-समय.
 */
अटल अंतरभूत काष्ठा zonelist *node_zonelist(पूर्णांक nid, gfp_t flags)
अणु
	वापस NODE_DATA(nid)->node_zonelists + gfp_zonelist(flags);
पूर्ण

#अगर_अघोषित HAVE_ARCH_FREE_PAGE
अटल अंतरभूत व्योम arch_मुक्त_page(काष्ठा page *page, पूर्णांक order) अणु पूर्ण
#पूर्ण_अगर
#अगर_अघोषित HAVE_ARCH_ALLOC_PAGE
अटल अंतरभूत व्योम arch_alloc_page(काष्ठा page *page, पूर्णांक order) अणु पूर्ण
#पूर्ण_अगर
#अगर_अघोषित HAVE_ARCH_MAKE_PAGE_ACCESSIBLE
अटल अंतरभूत पूर्णांक arch_make_page_accessible(काष्ठा page *page)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

काष्ठा page *__alloc_pages(gfp_t gfp, अचिन्हित पूर्णांक order, पूर्णांक preferred_nid,
		nodemask_t *nodemask);

अचिन्हित दीर्घ __alloc_pages_bulk(gfp_t gfp, पूर्णांक preferred_nid,
				nodemask_t *nodemask, पूर्णांक nr_pages,
				काष्ठा list_head *page_list,
				काष्ठा page **page_array);

/* Bulk allocate order-0 pages */
अटल अंतरभूत अचिन्हित दीर्घ
alloc_pages_bulk_list(gfp_t gfp, अचिन्हित दीर्घ nr_pages, काष्ठा list_head *list)
अणु
	वापस __alloc_pages_bulk(gfp, numa_mem_id(), शून्य, nr_pages, list, शून्य);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
alloc_pages_bulk_array(gfp_t gfp, अचिन्हित दीर्घ nr_pages, काष्ठा page **page_array)
अणु
	वापस __alloc_pages_bulk(gfp, numa_mem_id(), शून्य, nr_pages, शून्य, page_array);
पूर्ण

/*
 * Allocate pages, preferring the node given as nid. The node must be valid and
 * online. For more general पूर्णांकerface, see alloc_pages_node().
 */
अटल अंतरभूत काष्ठा page *
__alloc_pages_node(पूर्णांक nid, gfp_t gfp_mask, अचिन्हित पूर्णांक order)
अणु
	VM_BUG_ON(nid < 0 || nid >= MAX_NUMNODES);
	VM_WARN_ON((gfp_mask & __GFP_THISNODE) && !node_online(nid));

	वापस __alloc_pages(gfp_mask, order, nid, शून्य);
पूर्ण

/*
 * Allocate pages, preferring the node given as nid. When nid == NUMA_NO_NODE,
 * prefer the current CPU's बंदst node. Otherwise node must be valid and
 * online.
 */
अटल अंतरभूत काष्ठा page *alloc_pages_node(पूर्णांक nid, gfp_t gfp_mask,
						अचिन्हित पूर्णांक order)
अणु
	अगर (nid == NUMA_NO_NODE)
		nid = numa_mem_id();

	वापस __alloc_pages_node(nid, gfp_mask, order);
पूर्ण

#अगर_घोषित CONFIG_NUMA
काष्ठा page *alloc_pages(gfp_t gfp, अचिन्हित पूर्णांक order);
बाह्य काष्ठा page *alloc_pages_vma(gfp_t gfp_mask, पूर्णांक order,
			काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			पूर्णांक node, bool hugepage);
#घोषणा alloc_hugepage_vma(gfp_mask, vma, addr, order) \
	alloc_pages_vma(gfp_mask, order, vma, addr, numa_node_id(), true)
#अन्यथा
अटल अंतरभूत काष्ठा page *alloc_pages(gfp_t gfp_mask, अचिन्हित पूर्णांक order)
अणु
	वापस alloc_pages_node(numa_node_id(), gfp_mask, order);
पूर्ण
#घोषणा alloc_pages_vma(gfp_mask, order, vma, addr, node, false)\
	alloc_pages(gfp_mask, order)
#घोषणा alloc_hugepage_vma(gfp_mask, vma, addr, order) \
	alloc_pages(gfp_mask, order)
#पूर्ण_अगर
#घोषणा alloc_page(gfp_mask) alloc_pages(gfp_mask, 0)
#घोषणा alloc_page_vma(gfp_mask, vma, addr)			\
	alloc_pages_vma(gfp_mask, 0, vma, addr, numa_node_id(), false)

बाह्य अचिन्हित दीर्घ __get_मुक्त_pages(gfp_t gfp_mask, अचिन्हित पूर्णांक order);
बाह्य अचिन्हित दीर्घ get_zeroed_page(gfp_t gfp_mask);

व्योम *alloc_pages_exact(माप_प्रकार size, gfp_t gfp_mask);
व्योम मुक्त_pages_exact(व्योम *virt, माप_प्रकार size);
व्योम * __meminit alloc_pages_exact_nid(पूर्णांक nid, माप_प्रकार size, gfp_t gfp_mask);

#घोषणा __get_मुक्त_page(gfp_mask) \
		__get_मुक्त_pages((gfp_mask), 0)

#घोषणा __get_dma_pages(gfp_mask, order) \
		__get_मुक्त_pages((gfp_mask) | GFP_DMA, (order))

बाह्य व्योम __मुक्त_pages(काष्ठा page *page, अचिन्हित पूर्णांक order);
बाह्य व्योम मुक्त_pages(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक order);

काष्ठा page_frag_cache;
बाह्य व्योम __page_frag_cache_drain(काष्ठा page *page, अचिन्हित पूर्णांक count);
बाह्य व्योम *page_frag_alloc_align(काष्ठा page_frag_cache *nc,
				   अचिन्हित पूर्णांक fragsz, gfp_t gfp_mask,
				   अचिन्हित पूर्णांक align_mask);

अटल अंतरभूत व्योम *page_frag_alloc(काष्ठा page_frag_cache *nc,
			     अचिन्हित पूर्णांक fragsz, gfp_t gfp_mask)
अणु
	वापस page_frag_alloc_align(nc, fragsz, gfp_mask, ~0u);
पूर्ण

बाह्य व्योम page_frag_मुक्त(व्योम *addr);

#घोषणा __मुक्त_page(page) __मुक्त_pages((page), 0)
#घोषणा मुक्त_page(addr) मुक्त_pages((addr), 0)

व्योम page_alloc_init(व्योम);
व्योम drain_zone_pages(काष्ठा zone *zone, काष्ठा per_cpu_pages *pcp);
व्योम drain_all_pages(काष्ठा zone *zone);
व्योम drain_local_pages(काष्ठा zone *zone);

व्योम page_alloc_init_late(व्योम);

/*
 * gfp_allowed_mask is set to GFP_BOOT_MASK during early boot to restrict what
 * GFP flags are used beक्रमe पूर्णांकerrupts are enabled. Once पूर्णांकerrupts are
 * enabled, it is set to __GFP_BITS_MASK जबतक the प्रणाली is running. During
 * hibernation, it is used by PM to aव्योम I/O during memory allocation जबतक
 * devices are suspended.
 */
बाह्य gfp_t gfp_allowed_mask;

/* Returns true अगर the gfp_mask allows use of ALLOC_NO_WATERMARK */
bool gfp_pfmeदो_स्मृति_allowed(gfp_t gfp_mask);

बाह्य व्योम pm_restrict_gfp_mask(व्योम);
बाह्य व्योम pm_restore_gfp_mask(व्योम);

बाह्य gfp_t vma_thp_gfp_mask(काष्ठा vm_area_काष्ठा *vma);

#अगर_घोषित CONFIG_PM_SLEEP
बाह्य bool pm_suspended_storage(व्योम);
#अन्यथा
अटल अंतरभूत bool pm_suspended_storage(व्योम)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#अगर_घोषित CONFIG_CONTIG_ALLOC
/* The below functions must be run on a range from a single zone. */
बाह्य पूर्णांक alloc_contig_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
			      अचिन्हित migratetype, gfp_t gfp_mask);
बाह्य काष्ठा page *alloc_contig_pages(अचिन्हित दीर्घ nr_pages, gfp_t gfp_mask,
				       पूर्णांक nid, nodemask_t *nodemask);
#पूर्ण_अगर
व्योम मुक्त_contig_range(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages);

#अगर_घोषित CONFIG_CMA
/* CMA stuff */
बाह्य व्योम init_cma_reserved_pageblock(काष्ठा page *page);
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_GFP_H */
