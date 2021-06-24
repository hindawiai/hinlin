<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_MM_TYPES_H
#घोषणा _LINUX_MM_TYPES_H

#समावेश <linux/mm_types_task.h>

#समावेश <linux/auxvec.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/completion.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/uprobes.h>
#समावेश <linux/page-flags-layout.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/seqlock.h>

#समावेश <यंत्र/mmu.h>

#अगर_अघोषित AT_VECTOR_SIZE_ARCH
#घोषणा AT_VECTOR_SIZE_ARCH 0
#पूर्ण_अगर
#घोषणा AT_VECTOR_SIZE (2*(AT_VECTOR_SIZE_ARCH + AT_VECTOR_SIZE_BASE + 1))

#घोषणा INIT_PASID	0

काष्ठा address_space;
काष्ठा mem_cgroup;

/*
 * Each physical page in the प्रणाली has a काष्ठा page associated with
 * it to keep track of whatever it is we are using the page क्रम at the
 * moment. Note that we have no way to track which tasks are using
 * a page, though अगर it is a pagecache page, rmap काष्ठाures can tell us
 * who is mapping it.
 *
 * If you allocate the page using alloc_pages(), you can use some of the
 * space in काष्ठा page क्रम your own purposes.  The five words in the मुख्य
 * जोड़ are available, except क्रम bit 0 of the first word which must be
 * kept clear.  Many users use this word to store a poपूर्णांकer to an object
 * which is guaranteed to be aligned.  If you use the same storage as
 * page->mapping, you must restore it to शून्य beक्रमe मुक्तing the page.
 *
 * If your page will not be mapped to userspace, you can also use the four
 * bytes in the mapcount जोड़, but you must call page_mapcount_reset()
 * beक्रमe मुक्तing it.
 *
 * If you want to use the refcount field, it must be used in such a way
 * that other CPUs temporarily incrementing and then decrementing the
 * refcount करोes not cause problems.  On receiving the page from
 * alloc_pages(), the refcount will be positive.
 *
 * If you allocate pages of order > 0, you can use some of the fields
 * in each subpage, but you may need to restore some of their values
 * afterwards.
 *
 * SLUB uses cmpxchg_द्विगुन() to atomically update its मुक्तlist and
 * counters.  That requires that मुक्तlist & counters be adjacent and
 * द्विगुन-word aligned.  We align all काष्ठा pages to द्विगुन-word
 * boundaries, and ensure that 'freelist' is aligned within the
 * काष्ठा.
 */
#अगर_घोषित CONFIG_HAVE_ALIGNED_STRUCT_PAGE
#घोषणा _काष्ठा_page_alignment	__aligned(2 * माप(अचिन्हित दीर्घ))
#अन्यथा
#घोषणा _काष्ठा_page_alignment
#पूर्ण_अगर

काष्ठा page अणु
	अचिन्हित दीर्घ flags;		/* Atomic flags, some possibly
					 * updated asynchronously */
	/*
	 * Five words (20/40 bytes) are available in this जोड़.
	 * WARNING: bit 0 of the first word is used क्रम PageTail(). That
	 * means the other users of this जोड़ MUST NOT use the bit to
	 * aव्योम collision and false-positive PageTail().
	 */
	जोड़ अणु
		काष्ठा अणु	/* Page cache and anonymous pages */
			/**
			 * @lru: Pageout list, eg. active_list रक्षित by
			 * lruvec->lru_lock.  Someबार used as a generic list
			 * by the page owner.
			 */
			काष्ठा list_head lru;
			/* See page-flags.h क्रम PAGE_MAPPING_FLAGS */
			काष्ठा address_space *mapping;
			pgoff_t index;		/* Our offset within mapping. */
			/**
			 * @निजी: Mapping-निजी opaque data.
			 * Usually used क्रम buffer_heads अगर PagePrivate.
			 * Used क्रम swp_entry_t अगर PageSwapCache.
			 * Indicates order in the buddy प्रणाली अगर PageBuddy.
			 */
			अचिन्हित दीर्घ निजी;
		पूर्ण;
		काष्ठा अणु	/* page_pool used by netstack */
			/**
			 * @dma_addr: might require a 64-bit value on
			 * 32-bit architectures.
			 */
			अचिन्हित दीर्घ dma_addr[2];
		पूर्ण;
		काष्ठा अणु	/* slab, slob and slub */
			जोड़ अणु
				काष्ठा list_head slab_list;
				काष्ठा अणु	/* Partial pages */
					काष्ठा page *next;
#अगर_घोषित CONFIG_64BIT
					पूर्णांक pages;	/* Nr of pages left */
					पूर्णांक pobjects;	/* Approximate count */
#अन्यथा
					लघु पूर्णांक pages;
					लघु पूर्णांक pobjects;
#पूर्ण_अगर
				पूर्ण;
			पूर्ण;
			काष्ठा kmem_cache *slab_cache; /* not slob */
			/* Double-word boundary */
			व्योम *मुक्तlist;		/* first मुक्त object */
			जोड़ अणु
				व्योम *s_mem;	/* slab: first object */
				अचिन्हित दीर्घ counters;		/* SLUB */
				काष्ठा अणु			/* SLUB */
					अचिन्हित inuse:16;
					अचिन्हित objects:15;
					अचिन्हित frozen:1;
				पूर्ण;
			पूर्ण;
		पूर्ण;
		काष्ठा अणु	/* Tail pages of compound page */
			अचिन्हित दीर्घ compound_head;	/* Bit zero is set */

			/* First tail page only */
			अचिन्हित अक्षर compound_dtor;
			अचिन्हित अक्षर compound_order;
			atomic_t compound_mapcount;
			अचिन्हित पूर्णांक compound_nr; /* 1 << compound_order */
		पूर्ण;
		काष्ठा अणु	/* Second tail page of compound page */
			अचिन्हित दीर्घ _compound_pad_1;	/* compound_head */
			atomic_t hpage_pinned_refcount;
			/* For both global and memcg */
			काष्ठा list_head deferred_list;
		पूर्ण;
		काष्ठा अणु	/* Page table pages */
			अचिन्हित दीर्घ _pt_pad_1;	/* compound_head */
			pgtable_t pmd_huge_pte; /* रक्षित by page->ptl */
			अचिन्हित दीर्घ _pt_pad_2;	/* mapping */
			जोड़ अणु
				काष्ठा mm_काष्ठा *pt_mm; /* x86 pgds only */
				atomic_t pt_frag_refcount; /* घातerpc */
			पूर्ण;
#अगर ALLOC_SPLIT_PTLOCKS
			spinlock_t *ptl;
#अन्यथा
			spinlock_t ptl;
#पूर्ण_अगर
		पूर्ण;
		काष्ठा अणु	/* ZONE_DEVICE pages */
			/** @pgmap: Poपूर्णांकs to the hosting device page map. */
			काष्ठा dev_pagemap *pgmap;
			व्योम *zone_device_data;
			/*
			 * ZONE_DEVICE निजी pages are counted as being
			 * mapped so the next 3 words hold the mapping, index,
			 * and निजी fields from the source anonymous or
			 * page cache page जबतक the page is migrated to device
			 * निजी memory.
			 * ZONE_DEVICE MEMORY_DEVICE_FS_DAX pages also
			 * use the mapping, index, and निजी fields when
			 * pmem backed DAX files are mapped.
			 */
		पूर्ण;

		/** @rcu_head: You can use this to मुक्त a page by RCU. */
		काष्ठा rcu_head rcu_head;
	पूर्ण;

	जोड़ अणु		/* This जोड़ is 4 bytes in size. */
		/*
		 * If the page can be mapped to userspace, encodes the number
		 * of बार this page is referenced by a page table.
		 */
		atomic_t _mapcount;

		/*
		 * If the page is neither PageSlab nor mappable to userspace,
		 * the value stored here may help determine what this page
		 * is used क्रम.  See page-flags.h क्रम a list of page types
		 * which are currently stored here.
		 */
		अचिन्हित पूर्णांक page_type;

		अचिन्हित पूर्णांक active;		/* SLAB */
		पूर्णांक units;			/* SLOB */
	पूर्ण;

	/* Usage count. *DO NOT USE सूचीECTLY*. See page_ref.h */
	atomic_t _refcount;

#अगर_घोषित CONFIG_MEMCG
	अचिन्हित दीर्घ memcg_data;
#पूर्ण_अगर

	/*
	 * On machines where all RAM is mapped पूर्णांकo kernel address space,
	 * we can simply calculate the भव address. On machines with
	 * highmem some memory is mapped पूर्णांकo kernel भव memory
	 * dynamically, so we need a place to store that address.
	 * Note that this field could be 16 bits on x86 ... ;)
	 *
	 * Architectures with slow multiplication can define
	 * WANT_PAGE_VIRTUAL in यंत्र/page.h
	 */
#अगर defined(WANT_PAGE_VIRTUAL)
	व्योम *भव;			/* Kernel भव address (शून्य अगर
					   not kmapped, ie. highmem) */
#पूर्ण_अगर /* WANT_PAGE_VIRTUAL */

#अगर_घोषित LAST_CPUPID_NOT_IN_PAGE_FLAGS
	पूर्णांक _last_cpupid;
#पूर्ण_अगर
पूर्ण _काष्ठा_page_alignment;

अटल अंतरभूत atomic_t *compound_mapcount_ptr(काष्ठा page *page)
अणु
	वापस &page[1].compound_mapcount;
पूर्ण

अटल अंतरभूत atomic_t *compound_pincount_ptr(काष्ठा page *page)
अणु
	वापस &page[2].hpage_pinned_refcount;
पूर्ण

/*
 * Used क्रम sizing the vmemmap region on some architectures
 */
#घोषणा STRUCT_PAGE_MAX_SHIFT	(order_base_2(माप(काष्ठा page)))

#घोषणा PAGE_FRAG_CACHE_MAX_SIZE	__ALIGN_MASK(32768, ~PAGE_MASK)
#घोषणा PAGE_FRAG_CACHE_MAX_ORDER	get_order(PAGE_FRAG_CACHE_MAX_SIZE)

#घोषणा page_निजी(page)		((page)->निजी)

अटल अंतरभूत व्योम set_page_निजी(काष्ठा page *page, अचिन्हित दीर्घ निजी)
अणु
	page->निजी = निजी;
पूर्ण

काष्ठा page_frag_cache अणु
	व्योम * va;
#अगर (PAGE_SIZE < PAGE_FRAG_CACHE_MAX_SIZE)
	__u16 offset;
	__u16 size;
#अन्यथा
	__u32 offset;
#पूर्ण_अगर
	/* we मुख्यtain a pagecount bias, so that we करोnt dirty cache line
	 * containing page->_refcount every समय we allocate a fragment.
	 */
	अचिन्हित पूर्णांक		pagecnt_bias;
	bool pfmeदो_स्मृति;
पूर्ण;

प्रकार अचिन्हित दीर्घ vm_flags_t;

/*
 * A region containing a mapping of a non-memory backed file under NOMMU
 * conditions.  These are held in a global tree and are pinned by the VMAs that
 * map parts of them.
 */
काष्ठा vm_region अणु
	काष्ठा rb_node	vm_rb;		/* link in global region tree */
	vm_flags_t	vm_flags;	/* VMA vm_flags */
	अचिन्हित दीर्घ	vm_start;	/* start address of region */
	अचिन्हित दीर्घ	vm_end;		/* region initialised to here */
	अचिन्हित दीर्घ	vm_top;		/* region allocated to here */
	अचिन्हित दीर्घ	vm_pgoff;	/* the offset in vm_file corresponding to vm_start */
	काष्ठा file	*vm_file;	/* the backing file or शून्य */

	पूर्णांक		vm_usage;	/* region usage count (access under nommu_region_sem) */
	bool		vm_icache_flushed : 1; /* true अगर the icache has been flushed क्रम
						* this region */
पूर्ण;

#अगर_घोषित CONFIG_USERFAULTFD
#घोषणा शून्य_VM_UFFD_CTX ((काष्ठा vm_userfaultfd_ctx) अणु शून्य, पूर्ण)
काष्ठा vm_userfaultfd_ctx अणु
	काष्ठा userfaultfd_ctx *ctx;
पूर्ण;
#अन्यथा /* CONFIG_USERFAULTFD */
#घोषणा शून्य_VM_UFFD_CTX ((काष्ठा vm_userfaultfd_ctx) अणुपूर्ण)
काष्ठा vm_userfaultfd_ctx अणुपूर्ण;
#पूर्ण_अगर /* CONFIG_USERFAULTFD */

/*
 * This काष्ठा describes a भव memory area. There is one of these
 * per VM-area/task. A VM area is any part of the process भव memory
 * space that has a special rule क्रम the page-fault handlers (ie a shared
 * library, the executable area etc).
 */
काष्ठा vm_area_काष्ठा अणु
	/* The first cache line has the info क्रम VMA tree walking. */

	अचिन्हित दीर्घ vm_start;		/* Our start address within vm_mm. */
	अचिन्हित दीर्घ vm_end;		/* The first byte after our end address
					   within vm_mm. */

	/* linked list of VM areas per task, sorted by address */
	काष्ठा vm_area_काष्ठा *vm_next, *vm_prev;

	काष्ठा rb_node vm_rb;

	/*
	 * Largest मुक्त memory gap in bytes to the left of this VMA.
	 * Either between this VMA and vma->vm_prev, or between one of the
	 * VMAs below us in the VMA rbtree and its ->vm_prev. This helps
	 * get_unmapped_area find a मुक्त area of the right size.
	 */
	अचिन्हित दीर्घ rb_subtree_gap;

	/* Second cache line starts here. */

	काष्ठा mm_काष्ठा *vm_mm;	/* The address space we beदीर्घ to. */

	/*
	 * Access permissions of this VMA.
	 * See vmf_insert_mixed_prot() क्रम discussion.
	 */
	pgprot_t vm_page_prot;
	अचिन्हित दीर्घ vm_flags;		/* Flags, see mm.h. */

	/*
	 * For areas with an address space and backing store,
	 * linkage पूर्णांकo the address_space->i_mmap पूर्णांकerval tree.
	 */
	काष्ठा अणु
		काष्ठा rb_node rb;
		अचिन्हित दीर्घ rb_subtree_last;
	पूर्ण shared;

	/*
	 * A file's MAP_PRIVATE vma can be in both i_mmap tree and anon_vma
	 * list, after a COW of one of the file pages.	A MAP_SHARED vma
	 * can only be in the i_mmap tree.  An anonymous MAP_PRIVATE, stack
	 * or brk vma (with शून्य file) can only be in an anon_vma list.
	 */
	काष्ठा list_head anon_vma_chain; /* Serialized by mmap_lock &
					  * page_table_lock */
	काष्ठा anon_vma *anon_vma;	/* Serialized by page_table_lock */

	/* Function poपूर्णांकers to deal with this काष्ठा. */
	स्थिर काष्ठा vm_operations_काष्ठा *vm_ops;

	/* Inक्रमmation about our backing store: */
	अचिन्हित दीर्घ vm_pgoff;		/* Offset (within vm_file) in PAGE_SIZE
					   units */
	काष्ठा file * vm_file;		/* File we map to (can be शून्य). */
	व्योम * vm_निजी_data;		/* was vm_pte (shared mem) */

#अगर_घोषित CONFIG_SWAP
	atomic_दीर्घ_t swap_पढ़ोahead_info;
#पूर्ण_अगर
#अगर_अघोषित CONFIG_MMU
	काष्ठा vm_region *vm_region;	/* NOMMU mapping region */
#पूर्ण_अगर
#अगर_घोषित CONFIG_NUMA
	काष्ठा mempolicy *vm_policy;	/* NUMA policy क्रम the VMA */
#पूर्ण_अगर
	काष्ठा vm_userfaultfd_ctx vm_userfaultfd_ctx;
पूर्ण __अक्रमomize_layout;

काष्ठा core_thपढ़ो अणु
	काष्ठा task_काष्ठा *task;
	काष्ठा core_thपढ़ो *next;
पूर्ण;

काष्ठा core_state अणु
	atomic_t nr_thपढ़ोs;
	काष्ठा core_thपढ़ो dumper;
	काष्ठा completion startup;
पूर्ण;

काष्ठा kioctx_table;
काष्ठा mm_काष्ठा अणु
	काष्ठा अणु
		काष्ठा vm_area_काष्ठा *mmap;		/* list of VMAs */
		काष्ठा rb_root mm_rb;
		u64 vmacache_seqnum;                   /* per-thपढ़ो vmacache */
#अगर_घोषित CONFIG_MMU
		अचिन्हित दीर्घ (*get_unmapped_area) (काष्ठा file *filp,
				अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
				अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags);
#पूर्ण_अगर
		अचिन्हित दीर्घ mmap_base;	/* base of mmap area */
		अचिन्हित दीर्घ mmap_legacy_base;	/* base of mmap area in bottom-up allocations */
#अगर_घोषित CONFIG_HAVE_ARCH_COMPAT_MMAP_BASES
		/* Base adresses क्रम compatible mmap() */
		अचिन्हित दीर्घ mmap_compat_base;
		अचिन्हित दीर्घ mmap_compat_legacy_base;
#पूर्ण_अगर
		अचिन्हित दीर्घ task_size;	/* size of task vm space */
		अचिन्हित दीर्घ highest_vm_end;	/* highest vma end address */
		pgd_t * pgd;

#अगर_घोषित CONFIG_MEMBARRIER
		/**
		 * @membarrier_state: Flags controlling membarrier behavior.
		 *
		 * This field is बंद to @pgd to hopefully fit in the same
		 * cache-line, which needs to be touched by चयन_mm().
		 */
		atomic_t membarrier_state;
#पूर्ण_अगर

		/**
		 * @mm_users: The number of users including userspace.
		 *
		 * Use mmget()/mmget_not_zero()/mmput() to modअगरy. When this
		 * drops to 0 (i.e. when the task निकासs and there are no other
		 * temporary reference holders), we also release a reference on
		 * @mm_count (which may then मुक्त the &काष्ठा mm_काष्ठा अगर
		 * @mm_count also drops to 0).
		 */
		atomic_t mm_users;

		/**
		 * @mm_count: The number of references to &काष्ठा mm_काष्ठा
		 * (@mm_users count as 1).
		 *
		 * Use mmgrab()/mmdrop() to modअगरy. When this drops to 0, the
		 * &काष्ठा mm_काष्ठा is मुक्तd.
		 */
		atomic_t mm_count;

		/**
		 * @has_pinned: Whether this mm has pinned any pages.  This can
		 * be either replaced in the future by @pinned_vm when it
		 * becomes stable, or grow पूर्णांकo a counter on its own. We're
		 * aggresive on this bit now - even अगर the pinned pages were
		 * unpinned later on, we'll still keep this bit set क्रम the
		 * lअगरecycle of this mm just क्रम simplicity.
		 */
		atomic_t has_pinned;

#अगर_घोषित CONFIG_MMU
		atomic_दीर्घ_t pgtables_bytes;	/* PTE page table pages */
#पूर्ण_अगर
		पूर्णांक map_count;			/* number of VMAs */

		spinlock_t page_table_lock; /* Protects page tables and some
					     * counters
					     */
		/*
		 * With some kernel config, the current mmap_lock's offset
		 * inside 'mm_struct' is at 0x120, which is very optimal, as
		 * its two hot fields 'count' and 'owner' sit in 2 dअगरferent
		 * cachelines,  and when mmap_lock is highly contended, both
		 * of the 2 fields will be accessed frequently, current layout
		 * will help to reduce cache bouncing.
		 *
		 * So please be careful with adding new fields beक्रमe
		 * mmap_lock, which can easily push the 2 fields पूर्णांकo one
		 * cacheline.
		 */
		काष्ठा rw_semaphore mmap_lock;

		काष्ठा list_head mmlist; /* List of maybe swapped mm's.	These
					  * are globally strung together off
					  * init_mm.mmlist, and are रक्षित
					  * by mmlist_lock
					  */


		अचिन्हित दीर्घ hiwater_rss; /* High-watermark of RSS usage */
		अचिन्हित दीर्घ hiwater_vm;  /* High-water भव memory usage */

		अचिन्हित दीर्घ total_vm;	   /* Total pages mapped */
		अचिन्हित दीर्घ locked_vm;   /* Pages that have PG_mlocked set */
		atomic64_t    pinned_vm;   /* Refcount permanently increased */
		अचिन्हित दीर्घ data_vm;	   /* VM_WRITE & ~VM_SHARED & ~VM_STACK */
		अचिन्हित दीर्घ exec_vm;	   /* VM_EXEC & ~VM_WRITE & ~VM_STACK */
		अचिन्हित दीर्घ stack_vm;	   /* VM_STACK */
		अचिन्हित दीर्घ def_flags;

		/**
		 * @ग_लिखो_protect_seq: Locked when any thपढ़ो is ग_लिखो
		 * protecting pages mapped by this mm to enक्रमce a later COW,
		 * क्रम instance during page table copying क्रम विभाजन().
		 */
		seqcount_t ग_लिखो_protect_seq;

		spinlock_t arg_lock; /* protect the below fields */

		अचिन्हित दीर्घ start_code, end_code, start_data, end_data;
		अचिन्हित दीर्घ start_brk, brk, start_stack;
		अचिन्हित दीर्घ arg_start, arg_end, env_start, env_end;

		अचिन्हित दीर्घ saved_auxv[AT_VECTOR_SIZE]; /* क्रम /proc/PID/auxv */

		/*
		 * Special counters, in some configurations रक्षित by the
		 * page_table_lock, in other configurations by being atomic.
		 */
		काष्ठा mm_rss_stat rss_stat;

		काष्ठा linux_binfmt *binfmt;

		/* Architecture-specअगरic MM context */
		mm_context_t context;

		अचिन्हित दीर्घ flags; /* Must use atomic bitops to access */

		काष्ठा core_state *core_state; /* coredumping support */

#अगर_घोषित CONFIG_AIO
		spinlock_t			ioctx_lock;
		काष्ठा kioctx_table __rcu	*ioctx_table;
#पूर्ण_अगर
#अगर_घोषित CONFIG_MEMCG
		/*
		 * "owner" poपूर्णांकs to a task that is regarded as the canonical
		 * user/owner of this mm. All of the following must be true in
		 * order क्रम it to be changed:
		 *
		 * current == mm->owner
		 * current->mm != mm
		 * new_owner->mm == mm
		 * new_owner->alloc_lock is held
		 */
		काष्ठा task_काष्ठा __rcu *owner;
#पूर्ण_अगर
		काष्ठा user_namespace *user_ns;

		/* store ref to file /proc/<pid>/exe symlink poपूर्णांकs to */
		काष्ठा file __rcu *exe_file;
#अगर_घोषित CONFIG_MMU_NOTIFIER
		काष्ठा mmu_notअगरier_subscriptions *notअगरier_subscriptions;
#पूर्ण_अगर
#अगर defined(CONFIG_TRANSPARENT_HUGEPAGE) && !USE_SPLIT_PMD_PTLOCKS
		pgtable_t pmd_huge_pte; /* रक्षित by page_table_lock */
#पूर्ण_अगर
#अगर_घोषित CONFIG_NUMA_BALANCING
		/*
		 * numa_next_scan is the next समय that the PTEs will be marked
		 * pte_numa. NUMA hपूर्णांकing faults will gather statistics and
		 * migrate pages to new nodes अगर necessary.
		 */
		अचिन्हित दीर्घ numa_next_scan;

		/* Restart poपूर्णांक क्रम scanning and setting pte_numa */
		अचिन्हित दीर्घ numa_scan_offset;

		/* numa_scan_seq prevents two thपढ़ोs setting pte_numa */
		पूर्णांक numa_scan_seq;
#पूर्ण_अगर
		/*
		 * An operation with batched TLB flushing is going on. Anything
		 * that can move process memory needs to flush the TLB when
		 * moving a PROT_NONE or PROT_NUMA mapped page.
		 */
		atomic_t tlb_flush_pending;
#अगर_घोषित CONFIG_ARCH_WANT_BATCHED_UNMAP_TLB_FLUSH
		/* See flush_tlb_batched_pending() */
		bool tlb_flush_batched;
#पूर्ण_अगर
		काष्ठा uprobes_state uprobes_state;
#अगर_घोषित CONFIG_HUGETLB_PAGE
		atomic_दीर्घ_t hugetlb_usage;
#पूर्ण_अगर
		काष्ठा work_काष्ठा async_put_work;

#अगर_घोषित CONFIG_IOMMU_SUPPORT
		u32 pasid;
#पूर्ण_अगर
	पूर्ण __अक्रमomize_layout;

	/*
	 * The mm_cpumask needs to be at the end of mm_काष्ठा, because it
	 * is dynamically sized based on nr_cpu_ids.
	 */
	अचिन्हित दीर्घ cpu_biपंचांगap[];
पूर्ण;

बाह्य काष्ठा mm_काष्ठा init_mm;

/* Poपूर्णांकer magic because the dynamic array size confuses some compilers. */
अटल अंतरभूत व्योम mm_init_cpumask(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ cpu_biपंचांगap = (अचिन्हित दीर्घ)mm;

	cpu_biपंचांगap += दुरत्व(काष्ठा mm_काष्ठा, cpu_biपंचांगap);
	cpumask_clear((काष्ठा cpumask *)cpu_biपंचांगap);
पूर्ण

/* Future-safe accessor क्रम काष्ठा mm_काष्ठा's cpu_vm_mask. */
अटल अंतरभूत cpumask_t *mm_cpumask(काष्ठा mm_काष्ठा *mm)
अणु
	वापस (काष्ठा cpumask *)&mm->cpu_biपंचांगap;
पूर्ण

काष्ठा mmu_gather;
बाह्य व्योम tlb_gather_mmu(काष्ठा mmu_gather *tlb, काष्ठा mm_काष्ठा *mm);
बाह्य व्योम tlb_gather_mmu_fullmm(काष्ठा mmu_gather *tlb, काष्ठा mm_काष्ठा *mm);
बाह्य व्योम tlb_finish_mmu(काष्ठा mmu_gather *tlb);

अटल अंतरभूत व्योम init_tlb_flush_pending(काष्ठा mm_काष्ठा *mm)
अणु
	atomic_set(&mm->tlb_flush_pending, 0);
पूर्ण

अटल अंतरभूत व्योम inc_tlb_flush_pending(काष्ठा mm_काष्ठा *mm)
अणु
	atomic_inc(&mm->tlb_flush_pending);
	/*
	 * The only समय this value is relevant is when there are indeed pages
	 * to flush. And we'll only flush pages after changing them, which
	 * requires the PTL.
	 *
	 * So the ordering here is:
	 *
	 *	atomic_inc(&mm->tlb_flush_pending);
	 *	spin_lock(&ptl);
	 *	...
	 *	set_pte_at();
	 *	spin_unlock(&ptl);
	 *
	 *				spin_lock(&ptl)
	 *				mm_tlb_flush_pending();
	 *				....
	 *				spin_unlock(&ptl);
	 *
	 *	flush_tlb_range();
	 *	atomic_dec(&mm->tlb_flush_pending);
	 *
	 * Where the increment अगर स्थिरrained by the PTL unlock, it thus
	 * ensures that the increment is visible अगर the PTE modअगरication is
	 * visible. After all, अगर there is no PTE modअगरication, nobody cares
	 * about TLB flushes either.
	 *
	 * This very much relies on users (mm_tlb_flush_pending() and
	 * mm_tlb_flush_nested()) only caring about _specअगरic_ PTEs (and
	 * thereक्रमe specअगरic PTLs), because with SPLIT_PTE_PTLOCKS and RCpc
	 * locks (PPC) the unlock of one करोesn't order against the lock of
	 * another PTL.
	 *
	 * The decrement is ordered by the flush_tlb_range(), such that
	 * mm_tlb_flush_pending() will not वापस false unless all flushes have
	 * completed.
	 */
पूर्ण

अटल अंतरभूत व्योम dec_tlb_flush_pending(काष्ठा mm_काष्ठा *mm)
अणु
	/*
	 * See inc_tlb_flush_pending().
	 *
	 * This cannot be smp_mb__beक्रमe_atomic() because smp_mb() simply करोes
	 * not order against TLB invalidate completion, which is what we need.
	 *
	 * Thereक्रमe we must rely on tlb_flush_*() to guarantee order.
	 */
	atomic_dec(&mm->tlb_flush_pending);
पूर्ण

अटल अंतरभूत bool mm_tlb_flush_pending(काष्ठा mm_काष्ठा *mm)
अणु
	/*
	 * Must be called after having acquired the PTL; orders against that
	 * PTLs release and thereक्रमe ensures that अगर we observe the modअगरied
	 * PTE we must also observe the increment from inc_tlb_flush_pending().
	 *
	 * That is, it only guarantees to वापस true अगर there is a flush
	 * pending क्रम _this_ PTL.
	 */
	वापस atomic_पढ़ो(&mm->tlb_flush_pending);
पूर्ण

अटल अंतरभूत bool mm_tlb_flush_nested(काष्ठा mm_काष्ठा *mm)
अणु
	/*
	 * Similar to mm_tlb_flush_pending(), we must have acquired the PTL
	 * क्रम which there is a TLB flush pending in order to guarantee
	 * we've seen both that PTE modअगरication and the increment.
	 *
	 * (no requirement on actually still holding the PTL, that is irrelevant)
	 */
	वापस atomic_पढ़ो(&mm->tlb_flush_pending) > 1;
पूर्ण

काष्ठा vm_fault;

/**
 * प्रकार vm_fault_t - Return type क्रम page fault handlers.
 *
 * Page fault handlers वापस a biपंचांगask of %VM_FAULT values.
 */
प्रकार __bitwise अचिन्हित पूर्णांक vm_fault_t;

/**
 * क्रमागत vm_fault_reason - Page fault handlers वापस a biपंचांगask of
 * these values to tell the core VM what happened when handling the
 * fault. Used to decide whether a process माला_लो delivered SIGBUS or
 * just माला_लो major/minor fault counters bumped up.
 *
 * @VM_FAULT_OOM:		Out Of Memory
 * @VM_FAULT_SIGBUS:		Bad access
 * @VM_FAULT_MAJOR:		Page पढ़ो from storage
 * @VM_FAULT_WRITE:		Special हाल क्रम get_user_pages
 * @VM_FAULT_HWPOISON:		Hit poisoned small page
 * @VM_FAULT_HWPOISON_LARGE:	Hit poisoned large page. Index encoded
 *				in upper bits
 * @VM_FAULT_संक_अंश:		segmentation fault
 * @VM_FAULT_NOPAGE:		->fault installed the pte, not वापस page
 * @VM_FAULT_LOCKED:		->fault locked the वापसed page
 * @VM_FAULT_RETRY:		->fault blocked, must retry
 * @VM_FAULT_FALLBACK:		huge page fault failed, fall back to small
 * @VM_FAULT_DONE_COW:		->fault has fully handled COW
 * @VM_FAULT_NEEDDSYNC:		->fault did not modअगरy page tables and needs
 *				fsync() to complete (क्रम synchronous page faults
 *				in DAX)
 * @VM_FAULT_HINDEX_MASK:	mask HINDEX value
 *
 */
क्रमागत vm_fault_reason अणु
	VM_FAULT_OOM            = (__क्रमce vm_fault_t)0x000001,
	VM_FAULT_SIGBUS         = (__क्रमce vm_fault_t)0x000002,
	VM_FAULT_MAJOR          = (__क्रमce vm_fault_t)0x000004,
	VM_FAULT_WRITE          = (__क्रमce vm_fault_t)0x000008,
	VM_FAULT_HWPOISON       = (__क्रमce vm_fault_t)0x000010,
	VM_FAULT_HWPOISON_LARGE = (__क्रमce vm_fault_t)0x000020,
	VM_FAULT_संक_अंश        = (__क्रमce vm_fault_t)0x000040,
	VM_FAULT_NOPAGE         = (__क्रमce vm_fault_t)0x000100,
	VM_FAULT_LOCKED         = (__क्रमce vm_fault_t)0x000200,
	VM_FAULT_RETRY          = (__क्रमce vm_fault_t)0x000400,
	VM_FAULT_FALLBACK       = (__क्रमce vm_fault_t)0x000800,
	VM_FAULT_DONE_COW       = (__क्रमce vm_fault_t)0x001000,
	VM_FAULT_NEEDDSYNC      = (__क्रमce vm_fault_t)0x002000,
	VM_FAULT_HINDEX_MASK    = (__क्रमce vm_fault_t)0x0f0000,
पूर्ण;

/* Encode hstate index क्रम a hwpoisoned large page */
#घोषणा VM_FAULT_SET_HINDEX(x) ((__क्रमce vm_fault_t)((x) << 16))
#घोषणा VM_FAULT_GET_HINDEX(x) (((__क्रमce अचिन्हित पूर्णांक)(x) >> 16) & 0xf)

#घोषणा VM_FAULT_ERROR (VM_FAULT_OOM | VM_FAULT_SIGBUS |	\
			VM_FAULT_संक_अंश | VM_FAULT_HWPOISON |	\
			VM_FAULT_HWPOISON_LARGE | VM_FAULT_FALLBACK)

#घोषणा VM_FAULT_RESULT_TRACE \
	अणु VM_FAULT_OOM,                 "OOM" पूर्ण,	\
	अणु VM_FAULT_SIGBUS,              "SIGBUS" पूर्ण,	\
	अणु VM_FAULT_MAJOR,               "MAJOR" पूर्ण,	\
	अणु VM_FAULT_WRITE,               "WRITE" पूर्ण,	\
	अणु VM_FAULT_HWPOISON,            "HWPOISON" पूर्ण,	\
	अणु VM_FAULT_HWPOISON_LARGE,      "HWPOISON_LARGE" पूर्ण,	\
	अणु VM_FAULT_संक_अंश,             "SIGSEGV" पूर्ण,	\
	अणु VM_FAULT_NOPAGE,              "NOPAGE" पूर्ण,	\
	अणु VM_FAULT_LOCKED,              "LOCKED" पूर्ण,	\
	अणु VM_FAULT_RETRY,               "RETRY" पूर्ण,	\
	अणु VM_FAULT_FALLBACK,            "FALLBACK" पूर्ण,	\
	अणु VM_FAULT_DONE_COW,            "DONE_COW" पूर्ण,	\
	अणु VM_FAULT_NEEDDSYNC,           "NEEDDSYNC" पूर्ण

काष्ठा vm_special_mapping अणु
	स्थिर अक्षर *name;	/* The name, e.g. "[vdso]". */

	/*
	 * If .fault is not provided, this poपूर्णांकs to a
	 * शून्य-terminated array of pages that back the special mapping.
	 *
	 * This must not be शून्य unless .fault is provided.
	 */
	काष्ठा page **pages;

	/*
	 * If non-शून्य, then this is called to resolve page faults
	 * on the special mapping.  If used, .pages is not checked.
	 */
	vm_fault_t (*fault)(स्थिर काष्ठा vm_special_mapping *sm,
				काष्ठा vm_area_काष्ठा *vma,
				काष्ठा vm_fault *vmf);

	पूर्णांक (*mremap)(स्थिर काष्ठा vm_special_mapping *sm,
		     काष्ठा vm_area_काष्ठा *new_vma);
पूर्ण;

क्रमागत tlb_flush_reason अणु
	TLB_FLUSH_ON_TASK_SWITCH,
	TLB_REMOTE_SHOOTDOWN,
	TLB_LOCAL_SHOOTDOWN,
	TLB_LOCAL_MM_SHOOTDOWN,
	TLB_REMOTE_SEND_IPI,
	NR_TLB_FLUSH_REASONS,
पूर्ण;

 /*
  * A swap entry has to fit पूर्णांकo a "unsigned long", as the entry is hidden
  * in the "index" field of the swapper address space.
  */
प्रकार काष्ठा अणु
	अचिन्हित दीर्घ val;
पूर्ण swp_entry_t;

#पूर्ण_अगर /* _LINUX_MM_TYPES_H */
