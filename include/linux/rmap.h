<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_RMAP_H
#घोषणा _LINUX_RMAP_H
/*
 * Declarations क्रम Reverse Mapping functions in mm/rmap.c
 */

#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/memcontrol.h>
#समावेश <linux/highस्मृति.स>

/*
 * The anon_vma heads a list of निजी "related" vmas, to scan अगर
 * an anonymous page poपूर्णांकing to this anon_vma needs to be unmapped:
 * the vmas on the list will be related by विभाजनing, or by splitting.
 *
 * Since vmas come and go as they are split and merged (particularly
 * in mprotect), the mapping field of an anonymous page cannot poपूर्णांक
 * directly to a vma: instead it poपूर्णांकs to an anon_vma, on whose list
 * the related vmas can be easily linked or unlinked.
 *
 * After unlinking the last vma on the list, we must garbage collect
 * the anon_vma object itself: we're guaranteed no page can be
 * poपूर्णांकing to this anon_vma once its vma list is empty.
 */
काष्ठा anon_vma अणु
	काष्ठा anon_vma *root;		/* Root of this anon_vma tree */
	काष्ठा rw_semaphore rwsem;	/* W: modअगरication, R: walking the list */
	/*
	 * The refcount is taken on an anon_vma when there is no
	 * guarantee that the vma of page tables will exist क्रम
	 * the duration of the operation. A caller that takes
	 * the reference is responsible क्रम clearing up the
	 * anon_vma अगर they are the last user on release
	 */
	atomic_t refcount;

	/*
	 * Count of child anon_vmas and VMAs which poपूर्णांकs to this anon_vma.
	 *
	 * This counter is used क्रम making decision about reusing anon_vma
	 * instead of विभाजनing new one. See comments in function anon_vma_clone.
	 */
	अचिन्हित degree;

	काष्ठा anon_vma *parent;	/* Parent of this anon_vma */

	/*
	 * NOTE: the LSB of the rb_root.rb_node is set by
	 * mm_take_all_locks() _after_ taking the above lock. So the
	 * rb_root must only be पढ़ो/written after taking the above lock
	 * to be sure to see a valid next poपूर्णांकer. The LSB bit itself
	 * is serialized by a प्रणाली wide lock only visible to
	 * mm_take_all_locks() (mm_all_locks_mutex).
	 */

	/* Interval tree of निजी "related" vmas */
	काष्ठा rb_root_cached rb_root;
पूर्ण;

/*
 * The copy-on-ग_लिखो semantics of विभाजन mean that an anon_vma
 * can become associated with multiple processes. Furthermore,
 * each child process will have its own anon_vma, where new
 * pages क्रम that process are instantiated.
 *
 * This काष्ठाure allows us to find the anon_vmas associated
 * with a VMA, or the VMAs associated with an anon_vma.
 * The "same_vma" list contains the anon_vma_chains linking
 * all the anon_vmas associated with this VMA.
 * The "rb" field indexes on an पूर्णांकerval tree the anon_vma_chains
 * which link all the VMAs associated with this anon_vma.
 */
काष्ठा anon_vma_chain अणु
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा anon_vma *anon_vma;
	काष्ठा list_head same_vma;   /* locked by mmap_lock & page_table_lock */
	काष्ठा rb_node rb;			/* locked by anon_vma->rwsem */
	अचिन्हित दीर्घ rb_subtree_last;
#अगर_घोषित CONFIG_DEBUG_VM_RB
	अचिन्हित दीर्घ cached_vma_start, cached_vma_last;
#पूर्ण_अगर
पूर्ण;

क्रमागत ttu_flags अणु
	TTU_MIGRATION		= 0x1,	/* migration mode */
	TTU_MUNLOCK		= 0x2,	/* munlock mode */

	TTU_SPLIT_HUGE_PMD	= 0x4,	/* split huge PMD अगर any */
	TTU_IGNORE_MLOCK	= 0x8,	/* ignore mlock */
	TTU_SYNC		= 0x10,	/* aव्योम racy checks with PVMW_SYNC */
	TTU_IGNORE_HWPOISON	= 0x20,	/* corrupted page is recoverable */
	TTU_BATCH_FLUSH		= 0x40,	/* Batch TLB flushes where possible
					 * and caller guarantees they will
					 * करो a final flush अगर necessary */
	TTU_RMAP_LOCKED		= 0x80,	/* करो not grab rmap lock:
					 * caller holds it */
	TTU_SPLIT_FREEZE	= 0x100,		/* मुक्तze pte under splitting thp */
पूर्ण;

#अगर_घोषित CONFIG_MMU
अटल अंतरभूत व्योम get_anon_vma(काष्ठा anon_vma *anon_vma)
अणु
	atomic_inc(&anon_vma->refcount);
पूर्ण

व्योम __put_anon_vma(काष्ठा anon_vma *anon_vma);

अटल अंतरभूत व्योम put_anon_vma(काष्ठा anon_vma *anon_vma)
अणु
	अगर (atomic_dec_and_test(&anon_vma->refcount))
		__put_anon_vma(anon_vma);
पूर्ण

अटल अंतरभूत व्योम anon_vma_lock_ग_लिखो(काष्ठा anon_vma *anon_vma)
अणु
	करोwn_ग_लिखो(&anon_vma->root->rwsem);
पूर्ण

अटल अंतरभूत व्योम anon_vma_unlock_ग_लिखो(काष्ठा anon_vma *anon_vma)
अणु
	up_ग_लिखो(&anon_vma->root->rwsem);
पूर्ण

अटल अंतरभूत व्योम anon_vma_lock_पढ़ो(काष्ठा anon_vma *anon_vma)
अणु
	करोwn_पढ़ो(&anon_vma->root->rwsem);
पूर्ण

अटल अंतरभूत व्योम anon_vma_unlock_पढ़ो(काष्ठा anon_vma *anon_vma)
अणु
	up_पढ़ो(&anon_vma->root->rwsem);
पूर्ण


/*
 * anon_vma helper functions.
 */
व्योम anon_vma_init(व्योम);	/* create anon_vma_cachep */
पूर्णांक  __anon_vma_prepare(काष्ठा vm_area_काष्ठा *);
व्योम unlink_anon_vmas(काष्ठा vm_area_काष्ठा *);
पूर्णांक anon_vma_clone(काष्ठा vm_area_काष्ठा *, काष्ठा vm_area_काष्ठा *);
पूर्णांक anon_vma_विभाजन(काष्ठा vm_area_काष्ठा *, काष्ठा vm_area_काष्ठा *);

अटल अंतरभूत पूर्णांक anon_vma_prepare(काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (likely(vma->anon_vma))
		वापस 0;

	वापस __anon_vma_prepare(vma);
पूर्ण

अटल अंतरभूत व्योम anon_vma_merge(काष्ठा vm_area_काष्ठा *vma,
				  काष्ठा vm_area_काष्ठा *next)
अणु
	VM_BUG_ON_VMA(vma->anon_vma != next->anon_vma, vma);
	unlink_anon_vmas(next);
पूर्ण

काष्ठा anon_vma *page_get_anon_vma(काष्ठा page *page);

/* bitflags क्रम करो_page_add_anon_rmap() */
#घोषणा RMAP_EXCLUSIVE 0x01
#घोषणा RMAP_COMPOUND 0x02

/*
 * rmap पूर्णांकerfaces called when adding or removing pte of page
 */
व्योम page_move_anon_rmap(काष्ठा page *, काष्ठा vm_area_काष्ठा *);
व्योम page_add_anon_rmap(काष्ठा page *, काष्ठा vm_area_काष्ठा *,
		अचिन्हित दीर्घ, bool);
व्योम करो_page_add_anon_rmap(काष्ठा page *, काष्ठा vm_area_काष्ठा *,
			   अचिन्हित दीर्घ, पूर्णांक);
व्योम page_add_new_anon_rmap(काष्ठा page *, काष्ठा vm_area_काष्ठा *,
		अचिन्हित दीर्घ, bool);
व्योम page_add_file_rmap(काष्ठा page *, bool);
व्योम page_हटाओ_rmap(काष्ठा page *, bool);

व्योम hugepage_add_anon_rmap(काष्ठा page *, काष्ठा vm_area_काष्ठा *,
			    अचिन्हित दीर्घ);
व्योम hugepage_add_new_anon_rmap(काष्ठा page *, काष्ठा vm_area_काष्ठा *,
				अचिन्हित दीर्घ);

अटल अंतरभूत व्योम page_dup_rmap(काष्ठा page *page, bool compound)
अणु
	atomic_inc(compound ? compound_mapcount_ptr(page) : &page->_mapcount);
पूर्ण

/*
 * Called from mm/vmscan.c to handle paging out
 */
पूर्णांक page_referenced(काष्ठा page *, पूर्णांक is_locked,
			काष्ठा mem_cgroup *memcg, अचिन्हित दीर्घ *vm_flags);

bool try_to_unmap(काष्ठा page *, क्रमागत ttu_flags flags);

/* Aव्योम racy checks */
#घोषणा PVMW_SYNC		(1 << 0)
/* Look क्रम migarion entries rather than present PTEs */
#घोषणा PVMW_MIGRATION		(1 << 1)

काष्ठा page_vma_mapped_walk अणु
	काष्ठा page *page;
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ address;
	pmd_t *pmd;
	pte_t *pte;
	spinlock_t *ptl;
	अचिन्हित पूर्णांक flags;
पूर्ण;

अटल अंतरभूत व्योम page_vma_mapped_walk_करोne(काष्ठा page_vma_mapped_walk *pvmw)
अणु
	/* HugeTLB pte is set to the relevant page table entry without pte_mapped. */
	अगर (pvmw->pte && !PageHuge(pvmw->page))
		pte_unmap(pvmw->pte);
	अगर (pvmw->ptl)
		spin_unlock(pvmw->ptl);
पूर्ण

bool page_vma_mapped_walk(काष्ठा page_vma_mapped_walk *pvmw);

/*
 * Used by swapoff to help locate where page is expected in vma.
 */
अचिन्हित दीर्घ page_address_in_vma(काष्ठा page *, काष्ठा vm_area_काष्ठा *);

/*
 * Cleans the PTEs of shared mappings.
 * (and since clean PTEs should also be पढ़ोonly, ग_लिखो protects them too)
 *
 * वापसs the number of cleaned PTEs.
 */
पूर्णांक page_mkclean(काष्ठा page *);

/*
 * called in munlock()/munmap() path to check क्रम other vmas holding
 * the page mlocked.
 */
व्योम try_to_munlock(काष्ठा page *);

व्योम हटाओ_migration_ptes(काष्ठा page *old, काष्ठा page *new, bool locked);

/*
 * Called by memory-failure.c to समाप्त processes.
 */
काष्ठा anon_vma *page_lock_anon_vma_पढ़ो(काष्ठा page *page);
व्योम page_unlock_anon_vma_पढ़ो(काष्ठा anon_vma *anon_vma);
पूर्णांक page_mapped_in_vma(काष्ठा page *page, काष्ठा vm_area_काष्ठा *vma);

/*
 * rmap_walk_control: To control rmap traversing क्रम specअगरic needs
 *
 * arg: passed to rmap_one() and invalid_vma()
 * rmap_one: executed on each vma where page is mapped
 * करोne: क्रम checking traversing termination condition
 * anon_lock: क्रम getting anon_lock by optimized way rather than शेष
 * invalid_vma: क्रम skipping unपूर्णांकerested vma
 */
काष्ठा rmap_walk_control अणु
	व्योम *arg;
	/*
	 * Return false अगर page table scanning in rmap_walk should be stopped.
	 * Otherwise, वापस true.
	 */
	bool (*rmap_one)(काष्ठा page *page, काष्ठा vm_area_काष्ठा *vma,
					अचिन्हित दीर्घ addr, व्योम *arg);
	पूर्णांक (*करोne)(काष्ठा page *page);
	काष्ठा anon_vma *(*anon_lock)(काष्ठा page *page);
	bool (*invalid_vma)(काष्ठा vm_area_काष्ठा *vma, व्योम *arg);
पूर्ण;

व्योम rmap_walk(काष्ठा page *page, काष्ठा rmap_walk_control *rwc);
व्योम rmap_walk_locked(काष्ठा page *page, काष्ठा rmap_walk_control *rwc);

#अन्यथा	/* !CONFIG_MMU */

#घोषणा anon_vma_init()		करो अणुपूर्ण जबतक (0)
#घोषणा anon_vma_prepare(vma)	(0)
#घोषणा anon_vma_link(vma)	करो अणुपूर्ण जबतक (0)

अटल अंतरभूत पूर्णांक page_referenced(काष्ठा page *page, पूर्णांक is_locked,
				  काष्ठा mem_cgroup *memcg,
				  अचिन्हित दीर्घ *vm_flags)
अणु
	*vm_flags = 0;
	वापस 0;
पूर्ण

#घोषणा try_to_unmap(page, refs) false

अटल अंतरभूत पूर्णांक page_mkclean(काष्ठा page *page)
अणु
	वापस 0;
पूर्ण


#पूर्ण_अगर	/* CONFIG_MMU */

#पूर्ण_अगर	/* _LINUX_RMAP_H */
