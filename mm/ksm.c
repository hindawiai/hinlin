<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Memory merging support.
 *
 * This code enables dynamic sharing of identical pages found in dअगरferent
 * memory areas, even अगर they are not shared by विभाजन()
 *
 * Copyright (C) 2008-2009 Red Hat, Inc.
 * Authors:
 *	Izik Eidus
 *	Andrea Arcangeli
 *	Chris Wright
 *	Hugh Dickins
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/mman.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/coredump.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/rmap.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/xxhash.h>
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/रुको.h>
#समावेश <linux/slab.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/memory.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/swap.h>
#समावेश <linux/ksm.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/oom.h>
#समावेश <linux/numa.h>

#समावेश <यंत्र/tlbflush.h>
#समावेश "internal.h"

#अगर_घोषित CONFIG_NUMA
#घोषणा NUMA(x)		(x)
#घोषणा DO_NUMA(x)	करो अणु (x); पूर्ण जबतक (0)
#अन्यथा
#घोषणा NUMA(x)		(0)
#घोषणा DO_NUMA(x)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/**
 * DOC: Overview
 *
 * A few notes about the KSM scanning process,
 * to make it easier to understand the data काष्ठाures below:
 *
 * In order to reduce excessive scanning, KSM sorts the memory pages by their
 * contents पूर्णांकo a data काष्ठाure that holds poपूर्णांकers to the pages' locations.
 *
 * Since the contents of the pages may change at any moment, KSM cannot just
 * insert the pages पूर्णांकo a normal sorted tree and expect it to find anything.
 * Thereक्रमe KSM uses two data काष्ठाures - the stable and the unstable tree.
 *
 * The stable tree holds poपूर्णांकers to all the merged pages (ksm pages), sorted
 * by their contents.  Because each such page is ग_लिखो-रक्षित, searching on
 * this tree is fully assured to be working (except when pages are unmapped),
 * and thereक्रमe this tree is called the stable tree.
 *
 * The stable tree node includes inक्रमmation required क्रम reverse
 * mapping from a KSM page to भव addresses that map this page.
 *
 * In order to aव्योम large latencies of the rmap walks on KSM pages,
 * KSM मुख्यtains two types of nodes in the stable tree:
 *
 * * the regular nodes that keep the reverse mapping काष्ठाures in a
 *   linked list
 * * the "chains" that link nodes ("dups") that represent the same
 *   ग_लिखो रक्षित memory content, but each "dup" corresponds to a
 *   dअगरferent KSM page copy of that content
 *
 * Internally, the regular nodes, "dups" and "chains" are represented
 * using the same काष्ठा stable_node काष्ठाure.
 *
 * In addition to the stable tree, KSM uses a second data काष्ठाure called the
 * unstable tree: this tree holds poपूर्णांकers to pages which have been found to
 * be "unchanged for a period of time".  The unstable tree sorts these pages
 * by their contents, but since they are not ग_लिखो-रक्षित, KSM cannot rely
 * upon the unstable tree to work correctly - the unstable tree is liable to
 * be corrupted as its contents are modअगरied, and so it is called unstable.
 *
 * KSM solves this problem by several techniques:
 *
 * 1) The unstable tree is flushed every समय KSM completes scanning all
 *    memory areas, and then the tree is rebuilt again from the beginning.
 * 2) KSM will only insert पूर्णांकo the unstable tree, pages whose hash value
 *    has not changed since the previous scan of all memory areas.
 * 3) The unstable tree is a RedBlack Tree - so its balancing is based on the
 *    colors of the nodes and not on their contents, assuring that even when
 *    the tree माला_लो "corrupted" it won't get out of balance, so scanning समय
 *    reमुख्यs the same (also, searching and inserting nodes in an rbtree uses
 *    the same algorithm, so we have no overhead when we flush and rebuild).
 * 4) KSM never flushes the stable tree, which means that even अगर it were to
 *    take 10 attempts to find a page in the unstable tree, once it is found,
 *    it is secured in the stable tree.  (When we scan a new page, we first
 *    compare it against the stable tree, and then against the unstable tree.)
 *
 * If the merge_across_nodes tunable is unset, then KSM मुख्यtains multiple
 * stable trees and multiple unstable trees: one of each क्रम each NUMA node.
 */

/**
 * काष्ठा mm_slot - ksm inक्रमmation per mm that is being scanned
 * @link: link to the mm_slots hash list
 * @mm_list: link पूर्णांकo the mm_slots list, rooted in ksm_mm_head
 * @rmap_list: head क्रम this mm_slot's singly-linked list of rmap_items
 * @mm: the mm that this inक्रमmation is valid क्रम
 */
काष्ठा mm_slot अणु
	काष्ठा hlist_node link;
	काष्ठा list_head mm_list;
	काष्ठा rmap_item *rmap_list;
	काष्ठा mm_काष्ठा *mm;
पूर्ण;

/**
 * काष्ठा ksm_scan - cursor क्रम scanning
 * @mm_slot: the current mm_slot we are scanning
 * @address: the next address inside that to be scanned
 * @rmap_list: link to the next rmap to be scanned in the rmap_list
 * @seqnr: count of completed full scans (needed when removing unstable node)
 *
 * There is only the one ksm_scan instance of this cursor काष्ठाure.
 */
काष्ठा ksm_scan अणु
	काष्ठा mm_slot *mm_slot;
	अचिन्हित दीर्घ address;
	काष्ठा rmap_item **rmap_list;
	अचिन्हित दीर्घ seqnr;
पूर्ण;

/**
 * काष्ठा stable_node - node of the stable rbtree
 * @node: rb node of this ksm page in the stable tree
 * @head: (overlaying parent) &migrate_nodes indicates temporarily on that list
 * @hlist_dup: linked पूर्णांकo the stable_node->hlist with a stable_node chain
 * @list: linked पूर्णांकo migrate_nodes, pending placement in the proper node tree
 * @hlist: hlist head of rmap_items using this ksm page
 * @kpfn: page frame number of this ksm page (perhaps temporarily on wrong nid)
 * @chain_prune_समय: समय of the last full garbage collection
 * @rmap_hlist_len: number of rmap_item entries in hlist or STABLE_NODE_CHAIN
 * @nid: NUMA node id of stable tree in which linked (may not match kpfn)
 */
काष्ठा stable_node अणु
	जोड़ अणु
		काष्ठा rb_node node;	/* when node of stable tree */
		काष्ठा अणु		/* when listed क्रम migration */
			काष्ठा list_head *head;
			काष्ठा अणु
				काष्ठा hlist_node hlist_dup;
				काष्ठा list_head list;
			पूर्ण;
		पूर्ण;
	पूर्ण;
	काष्ठा hlist_head hlist;
	जोड़ अणु
		अचिन्हित दीर्घ kpfn;
		अचिन्हित दीर्घ chain_prune_समय;
	पूर्ण;
	/*
	 * STABLE_NODE_CHAIN can be any negative number in
	 * rmap_hlist_len negative range, but better not -1 to be able
	 * to reliably detect underflows.
	 */
#घोषणा STABLE_NODE_CHAIN -1024
	पूर्णांक rmap_hlist_len;
#अगर_घोषित CONFIG_NUMA
	पूर्णांक nid;
#पूर्ण_अगर
पूर्ण;

/**
 * काष्ठा rmap_item - reverse mapping item क्रम भव addresses
 * @rmap_list: next rmap_item in mm_slot's singly-linked rmap_list
 * @anon_vma: poपूर्णांकer to anon_vma क्रम this mm,address, when in stable tree
 * @nid: NUMA node id of unstable tree in which linked (may not match page)
 * @mm: the memory काष्ठाure this rmap_item is poपूर्णांकing पूर्णांकo
 * @address: the भव address this rmap_item tracks (+ flags in low bits)
 * @oldchecksum: previous checksum of the page at that भव address
 * @node: rb node of this rmap_item in the unstable tree
 * @head: poपूर्णांकer to stable_node heading this list in the stable tree
 * @hlist: link पूर्णांकo hlist of rmap_items hanging off that stable_node
 */
काष्ठा rmap_item अणु
	काष्ठा rmap_item *rmap_list;
	जोड़ अणु
		काष्ठा anon_vma *anon_vma;	/* when stable */
#अगर_घोषित CONFIG_NUMA
		पूर्णांक nid;		/* when node of unstable tree */
#पूर्ण_अगर
	पूर्ण;
	काष्ठा mm_काष्ठा *mm;
	अचिन्हित दीर्घ address;		/* + low bits used क्रम flags below */
	अचिन्हित पूर्णांक oldchecksum;	/* when unstable */
	जोड़ अणु
		काष्ठा rb_node node;	/* when node of unstable tree */
		काष्ठा अणु		/* when listed from stable tree */
			काष्ठा stable_node *head;
			काष्ठा hlist_node hlist;
		पूर्ण;
	पूर्ण;
पूर्ण;

#घोषणा SEQNR_MASK	0x0ff	/* low bits of unstable tree seqnr */
#घोषणा UNSTABLE_FLAG	0x100	/* is a node of the unstable tree */
#घोषणा STABLE_FLAG	0x200	/* is listed from the stable tree */

/* The stable and unstable tree heads */
अटल काष्ठा rb_root one_stable_tree[1] = अणु RB_ROOT पूर्ण;
अटल काष्ठा rb_root one_unstable_tree[1] = अणु RB_ROOT पूर्ण;
अटल काष्ठा rb_root *root_stable_tree = one_stable_tree;
अटल काष्ठा rb_root *root_unstable_tree = one_unstable_tree;

/* Recently migrated nodes of stable tree, pending proper placement */
अटल LIST_HEAD(migrate_nodes);
#घोषणा STABLE_NODE_DUP_HEAD ((काष्ठा list_head *)&migrate_nodes.prev)

#घोषणा MM_SLOTS_HASH_BITS 10
अटल DEFINE_HASHTABLE(mm_slots_hash, MM_SLOTS_HASH_BITS);

अटल काष्ठा mm_slot ksm_mm_head = अणु
	.mm_list = LIST_HEAD_INIT(ksm_mm_head.mm_list),
पूर्ण;
अटल काष्ठा ksm_scan ksm_scan = अणु
	.mm_slot = &ksm_mm_head,
पूर्ण;

अटल काष्ठा kmem_cache *rmap_item_cache;
अटल काष्ठा kmem_cache *stable_node_cache;
अटल काष्ठा kmem_cache *mm_slot_cache;

/* The number of nodes in the stable tree */
अटल अचिन्हित दीर्घ ksm_pages_shared;

/* The number of page slots additionally sharing those nodes */
अटल अचिन्हित दीर्घ ksm_pages_sharing;

/* The number of nodes in the unstable tree */
अटल अचिन्हित दीर्घ ksm_pages_unshared;

/* The number of rmap_items in use: to calculate pages_अस्थिर */
अटल अचिन्हित दीर्घ ksm_rmap_items;

/* The number of stable_node chains */
अटल अचिन्हित दीर्घ ksm_stable_node_chains;

/* The number of stable_node dups linked to the stable_node chains */
अटल अचिन्हित दीर्घ ksm_stable_node_dups;

/* Delay in pruning stale stable_node_dups in the stable_node_chains */
अटल पूर्णांक ksm_stable_node_chains_prune_millisecs = 2000;

/* Maximum number of page slots sharing a stable node */
अटल पूर्णांक ksm_max_page_sharing = 256;

/* Number of pages ksmd should scan in one batch */
अटल अचिन्हित पूर्णांक ksm_thपढ़ो_pages_to_scan = 100;

/* Milliseconds ksmd should sleep between batches */
अटल अचिन्हित पूर्णांक ksm_thपढ़ो_sleep_millisecs = 20;

/* Checksum of an empty (zeroed) page */
अटल अचिन्हित पूर्णांक zero_checksum __पढ़ो_mostly;

/* Whether to merge empty (zeroed) pages with actual zero pages */
अटल bool ksm_use_zero_pages __पढ़ो_mostly;

#अगर_घोषित CONFIG_NUMA
/* Zeroed when merging across nodes is not allowed */
अटल अचिन्हित पूर्णांक ksm_merge_across_nodes = 1;
अटल पूर्णांक ksm_nr_node_ids = 1;
#अन्यथा
#घोषणा ksm_merge_across_nodes	1U
#घोषणा ksm_nr_node_ids		1
#पूर्ण_अगर

#घोषणा KSM_RUN_STOP	0
#घोषणा KSM_RUN_MERGE	1
#घोषणा KSM_RUN_UNMERGE	2
#घोषणा KSM_RUN_OFFLINE	4
अटल अचिन्हित दीर्घ ksm_run = KSM_RUN_STOP;
अटल व्योम रुको_जबतक_offlining(व्योम);

अटल DECLARE_WAIT_QUEUE_HEAD(ksm_thपढ़ो_रुको);
अटल DECLARE_WAIT_QUEUE_HEAD(ksm_iter_रुको);
अटल DEFINE_MUTEX(ksm_thपढ़ो_mutex);
अटल DEFINE_SPINLOCK(ksm_mmlist_lock);

#घोषणा KSM_KMEM_CACHE(__काष्ठा, __flags) kmem_cache_create("ksm_"#__काष्ठा,\
		माप(काष्ठा __काष्ठा), __alignof__(काष्ठा __काष्ठा),\
		(__flags), शून्य)

अटल पूर्णांक __init ksm_slab_init(व्योम)
अणु
	rmap_item_cache = KSM_KMEM_CACHE(rmap_item, 0);
	अगर (!rmap_item_cache)
		जाओ out;

	stable_node_cache = KSM_KMEM_CACHE(stable_node, 0);
	अगर (!stable_node_cache)
		जाओ out_मुक्त1;

	mm_slot_cache = KSM_KMEM_CACHE(mm_slot, 0);
	अगर (!mm_slot_cache)
		जाओ out_मुक्त2;

	वापस 0;

out_मुक्त2:
	kmem_cache_destroy(stable_node_cache);
out_मुक्त1:
	kmem_cache_destroy(rmap_item_cache);
out:
	वापस -ENOMEM;
पूर्ण

अटल व्योम __init ksm_slab_मुक्त(व्योम)
अणु
	kmem_cache_destroy(mm_slot_cache);
	kmem_cache_destroy(stable_node_cache);
	kmem_cache_destroy(rmap_item_cache);
	mm_slot_cache = शून्य;
पूर्ण

अटल __always_अंतरभूत bool is_stable_node_chain(काष्ठा stable_node *chain)
अणु
	वापस chain->rmap_hlist_len == STABLE_NODE_CHAIN;
पूर्ण

अटल __always_अंतरभूत bool is_stable_node_dup(काष्ठा stable_node *dup)
अणु
	वापस dup->head == STABLE_NODE_DUP_HEAD;
पूर्ण

अटल अंतरभूत व्योम stable_node_chain_add_dup(काष्ठा stable_node *dup,
					     काष्ठा stable_node *chain)
अणु
	VM_BUG_ON(is_stable_node_dup(dup));
	dup->head = STABLE_NODE_DUP_HEAD;
	VM_BUG_ON(!is_stable_node_chain(chain));
	hlist_add_head(&dup->hlist_dup, &chain->hlist);
	ksm_stable_node_dups++;
पूर्ण

अटल अंतरभूत व्योम __stable_node_dup_del(काष्ठा stable_node *dup)
अणु
	VM_BUG_ON(!is_stable_node_dup(dup));
	hlist_del(&dup->hlist_dup);
	ksm_stable_node_dups--;
पूर्ण

अटल अंतरभूत व्योम stable_node_dup_del(काष्ठा stable_node *dup)
अणु
	VM_BUG_ON(is_stable_node_chain(dup));
	अगर (is_stable_node_dup(dup))
		__stable_node_dup_del(dup);
	अन्यथा
		rb_erase(&dup->node, root_stable_tree + NUMA(dup->nid));
#अगर_घोषित CONFIG_DEBUG_VM
	dup->head = शून्य;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत काष्ठा rmap_item *alloc_rmap_item(व्योम)
अणु
	काष्ठा rmap_item *rmap_item;

	rmap_item = kmem_cache_zalloc(rmap_item_cache, GFP_KERNEL |
						__GFP_NORETRY | __GFP_NOWARN);
	अगर (rmap_item)
		ksm_rmap_items++;
	वापस rmap_item;
पूर्ण

अटल अंतरभूत व्योम मुक्त_rmap_item(काष्ठा rmap_item *rmap_item)
अणु
	ksm_rmap_items--;
	rmap_item->mm = शून्य;	/* debug safety */
	kmem_cache_मुक्त(rmap_item_cache, rmap_item);
पूर्ण

अटल अंतरभूत काष्ठा stable_node *alloc_stable_node(व्योम)
अणु
	/*
	 * The allocation can take too दीर्घ with GFP_KERNEL when memory is under
	 * pressure, which may lead to hung task warnings.  Adding __GFP_HIGH
	 * grants access to memory reserves, helping to aव्योम this problem.
	 */
	वापस kmem_cache_alloc(stable_node_cache, GFP_KERNEL | __GFP_HIGH);
पूर्ण

अटल अंतरभूत व्योम मुक्त_stable_node(काष्ठा stable_node *stable_node)
अणु
	VM_BUG_ON(stable_node->rmap_hlist_len &&
		  !is_stable_node_chain(stable_node));
	kmem_cache_मुक्त(stable_node_cache, stable_node);
पूर्ण

अटल अंतरभूत काष्ठा mm_slot *alloc_mm_slot(व्योम)
अणु
	अगर (!mm_slot_cache)	/* initialization failed */
		वापस शून्य;
	वापस kmem_cache_zalloc(mm_slot_cache, GFP_KERNEL);
पूर्ण

अटल अंतरभूत व्योम मुक्त_mm_slot(काष्ठा mm_slot *mm_slot)
अणु
	kmem_cache_मुक्त(mm_slot_cache, mm_slot);
पूर्ण

अटल काष्ठा mm_slot *get_mm_slot(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा mm_slot *slot;

	hash_क्रम_each_possible(mm_slots_hash, slot, link, (अचिन्हित दीर्घ)mm)
		अगर (slot->mm == mm)
			वापस slot;

	वापस शून्य;
पूर्ण

अटल व्योम insert_to_mm_slots_hash(काष्ठा mm_काष्ठा *mm,
				    काष्ठा mm_slot *mm_slot)
अणु
	mm_slot->mm = mm;
	hash_add(mm_slots_hash, &mm_slot->link, (अचिन्हित दीर्घ)mm);
पूर्ण

/*
 * ksmd, and unmerge_and_हटाओ_all_rmap_items(), must not touch an mm's
 * page tables after it has passed through ksm_निकास() - which, अगर necessary,
 * takes mmap_lock briefly to serialize against them.  ksm_निकास() करोes not set
 * a special flag: they can just back out as soon as mm_users goes to zero.
 * ksm_test_निकास() is used throughout to make this test क्रम निकास: in some
 * places क्रम correctness, in some places just to aव्योम unnecessary work.
 */
अटल अंतरभूत bool ksm_test_निकास(काष्ठा mm_काष्ठा *mm)
अणु
	वापस atomic_पढ़ो(&mm->mm_users) == 0;
पूर्ण

/*
 * We use अवरोध_ksm to अवरोध COW on a ksm page: it's a stripped करोwn
 *
 *	अगर (get_user_pages(addr, 1, FOLL_WRITE, &page, शून्य) == 1)
 *		put_page(page);
 *
 * but taking great care only to touch a ksm page, in a VM_MERGEABLE vma,
 * in हाल the application has unmapped and remapped mm,addr meanजबतक.
 * Could a ksm page appear anywhere अन्यथा?  Actually yes, in a VM_PFNMAP
 * mmap of /dev/mem, where we would not want to touch it.
 *
 * FAULT_FLAG/FOLL_REMOTE are because we करो this outside the context
 * of the process that owns 'vma'.  We also करो not want to enक्रमce
 * protection keys here anyway.
 */
अटल पूर्णांक अवरोध_ksm(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr)
अणु
	काष्ठा page *page;
	vm_fault_t ret = 0;

	करो अणु
		cond_resched();
		page = follow_page(vma, addr,
				FOLL_GET | FOLL_MIGRATION | FOLL_REMOTE);
		अगर (IS_ERR_OR_शून्य(page))
			अवरोध;
		अगर (PageKsm(page))
			ret = handle_mm_fault(vma, addr,
					      FAULT_FLAG_WRITE | FAULT_FLAG_REMOTE,
					      शून्य);
		अन्यथा
			ret = VM_FAULT_WRITE;
		put_page(page);
	पूर्ण जबतक (!(ret & (VM_FAULT_WRITE | VM_FAULT_SIGBUS | VM_FAULT_संक_अंश | VM_FAULT_OOM)));
	/*
	 * We must loop because handle_mm_fault() may back out अगर there's
	 * any dअगरficulty e.g. अगर pte accessed bit माला_लो updated concurrently.
	 *
	 * VM_FAULT_WRITE is what we have been hoping क्रम: it indicates that
	 * COW has been broken, even अगर the vma करोes not permit VM_WRITE;
	 * but note that a concurrent fault might अवरोध PageKsm क्रम us.
	 *
	 * VM_FAULT_SIGBUS could occur अगर we race with truncation of the
	 * backing file, which also invalidates anonymous pages: that's
	 * okay, that truncation will have unmapped the PageKsm क्रम us.
	 *
	 * VM_FAULT_OOM: at the समय of writing (late July 2009), setting
	 * aside mem_cgroup limits, VM_FAULT_OOM would only be set अगर the
	 * current task has TIF_MEMDIE set, and will be OOM समाप्तed on वापस
	 * to user; and ksmd, having no mm, would never be chosen क्रम that.
	 *
	 * But अगर the mm is in a limited mem_cgroup, then the fault may fail
	 * with VM_FAULT_OOM even अगर the current task is not TIF_MEMDIE; and
	 * even ksmd can fail in this way - though it's usually अवरोधing ksm
	 * just to unकरो a merge it made a moment beक्रमe, so unlikely to oom.
	 *
	 * That's a pity: we might thereक्रमe have more kernel pages allocated
	 * than we're counting as nodes in the stable tree; but ksm_करो_scan
	 * will retry to अवरोध_cow on each pass, so should recover the page
	 * in due course.  The important thing is to not let VM_MERGEABLE
	 * be cleared जबतक any such pages might reमुख्य in the area.
	 */
	वापस (ret & VM_FAULT_OOM) ? -ENOMEM : 0;
पूर्ण

अटल काष्ठा vm_area_काष्ठा *find_mergeable_vma(काष्ठा mm_काष्ठा *mm,
		अचिन्हित दीर्घ addr)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	अगर (ksm_test_निकास(mm))
		वापस शून्य;
	vma = find_vma(mm, addr);
	अगर (!vma || vma->vm_start > addr)
		वापस शून्य;
	अगर (!(vma->vm_flags & VM_MERGEABLE) || !vma->anon_vma)
		वापस शून्य;
	वापस vma;
पूर्ण

अटल व्योम अवरोध_cow(काष्ठा rmap_item *rmap_item)
अणु
	काष्ठा mm_काष्ठा *mm = rmap_item->mm;
	अचिन्हित दीर्घ addr = rmap_item->address;
	काष्ठा vm_area_काष्ठा *vma;

	/*
	 * It is not an accident that whenever we want to अवरोध COW
	 * to unकरो, we also need to drop a reference to the anon_vma.
	 */
	put_anon_vma(rmap_item->anon_vma);

	mmap_पढ़ो_lock(mm);
	vma = find_mergeable_vma(mm, addr);
	अगर (vma)
		अवरोध_ksm(vma, addr);
	mmap_पढ़ो_unlock(mm);
पूर्ण

अटल काष्ठा page *get_mergeable_page(काष्ठा rmap_item *rmap_item)
अणु
	काष्ठा mm_काष्ठा *mm = rmap_item->mm;
	अचिन्हित दीर्घ addr = rmap_item->address;
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा page *page;

	mmap_पढ़ो_lock(mm);
	vma = find_mergeable_vma(mm, addr);
	अगर (!vma)
		जाओ out;

	page = follow_page(vma, addr, FOLL_GET);
	अगर (IS_ERR_OR_शून्य(page))
		जाओ out;
	अगर (PageAnon(page)) अणु
		flush_anon_page(vma, page, addr);
		flush_dcache_page(page);
	पूर्ण अन्यथा अणु
		put_page(page);
out:
		page = शून्य;
	पूर्ण
	mmap_पढ़ो_unlock(mm);
	वापस page;
पूर्ण

/*
 * This helper is used क्रम getting right index पूर्णांकo array of tree roots.
 * When merge_across_nodes knob is set to 1, there are only two rb-trees क्रम
 * stable and unstable pages from all nodes with roots in index 0. Otherwise,
 * every node has its own stable and unstable tree.
 */
अटल अंतरभूत पूर्णांक get_kpfn_nid(अचिन्हित दीर्घ kpfn)
अणु
	वापस ksm_merge_across_nodes ? 0 : NUMA(pfn_to_nid(kpfn));
पूर्ण

अटल काष्ठा stable_node *alloc_stable_node_chain(काष्ठा stable_node *dup,
						   काष्ठा rb_root *root)
अणु
	काष्ठा stable_node *chain = alloc_stable_node();
	VM_BUG_ON(is_stable_node_chain(dup));
	अगर (likely(chain)) अणु
		INIT_HLIST_HEAD(&chain->hlist);
		chain->chain_prune_समय = jअगरfies;
		chain->rmap_hlist_len = STABLE_NODE_CHAIN;
#अगर defined (CONFIG_DEBUG_VM) && defined(CONFIG_NUMA)
		chain->nid = NUMA_NO_NODE; /* debug */
#पूर्ण_अगर
		ksm_stable_node_chains++;

		/*
		 * Put the stable node chain in the first dimension of
		 * the stable tree and at the same समय हटाओ the old
		 * stable node.
		 */
		rb_replace_node(&dup->node, &chain->node, root);

		/*
		 * Move the old stable node to the second dimension
		 * queued in the hlist_dup. The invariant is that all
		 * dup stable_nodes in the chain->hlist poपूर्णांक to pages
		 * that are ग_लिखो रक्षित and have the exact same
		 * content.
		 */
		stable_node_chain_add_dup(dup, chain);
	पूर्ण
	वापस chain;
पूर्ण

अटल अंतरभूत व्योम मुक्त_stable_node_chain(काष्ठा stable_node *chain,
					  काष्ठा rb_root *root)
अणु
	rb_erase(&chain->node, root);
	मुक्त_stable_node(chain);
	ksm_stable_node_chains--;
पूर्ण

अटल व्योम हटाओ_node_from_stable_tree(काष्ठा stable_node *stable_node)
अणु
	काष्ठा rmap_item *rmap_item;

	/* check it's not STABLE_NODE_CHAIN or negative */
	BUG_ON(stable_node->rmap_hlist_len < 0);

	hlist_क्रम_each_entry(rmap_item, &stable_node->hlist, hlist) अणु
		अगर (rmap_item->hlist.next)
			ksm_pages_sharing--;
		अन्यथा
			ksm_pages_shared--;
		VM_BUG_ON(stable_node->rmap_hlist_len <= 0);
		stable_node->rmap_hlist_len--;
		put_anon_vma(rmap_item->anon_vma);
		rmap_item->address &= PAGE_MASK;
		cond_resched();
	पूर्ण

	/*
	 * We need the second aligned poपूर्णांकer of the migrate_nodes
	 * list_head to stay clear from the rb_parent_color जोड़
	 * (aligned and dअगरferent than any node) and also dअगरferent
	 * from &migrate_nodes. This will verअगरy that future list.h changes
	 * करोn't अवरोध STABLE_NODE_DUP_HEAD. Only recent gcc can handle it.
	 */
#अगर defined(GCC_VERSION) && GCC_VERSION >= 40903
	BUILD_BUG_ON(STABLE_NODE_DUP_HEAD <= &migrate_nodes);
	BUILD_BUG_ON(STABLE_NODE_DUP_HEAD >= &migrate_nodes + 1);
#पूर्ण_अगर

	अगर (stable_node->head == &migrate_nodes)
		list_del(&stable_node->list);
	अन्यथा
		stable_node_dup_del(stable_node);
	मुक्त_stable_node(stable_node);
पूर्ण

क्रमागत get_ksm_page_flags अणु
	GET_KSM_PAGE_NOLOCK,
	GET_KSM_PAGE_LOCK,
	GET_KSM_PAGE_TRYLOCK
पूर्ण;

/*
 * get_ksm_page: checks अगर the page indicated by the stable node
 * is still its ksm page, despite having held no reference to it.
 * In which हाल we can trust the content of the page, and it
 * वापसs the gotten page; but अगर the page has now been zapped,
 * हटाओ the stale node from the stable tree and वापस शून्य.
 * But beware, the stable node's page might be being migrated.
 *
 * You would expect the stable_node to hold a reference to the ksm page.
 * But अगर it increments the page's count, swapping out has to रुको क्रम
 * ksmd to come around again beक्रमe it can मुक्त the page, which may take
 * seconds or even minutes: much too unresponsive.  So instead we use a
 * "keyhole reference": access to the ksm page from the stable node peeps
 * out through its keyhole to see अगर that page still holds the right key,
 * poपूर्णांकing back to this stable node.  This relies on मुक्तing a PageAnon
 * page to reset its page->mapping to शून्य, and relies on no other use of
 * a page to put something that might look like our key in page->mapping.
 * is on its way to being मुक्तd; but it is an anomaly to bear in mind.
 */
अटल काष्ठा page *get_ksm_page(काष्ठा stable_node *stable_node,
				 क्रमागत get_ksm_page_flags flags)
अणु
	काष्ठा page *page;
	व्योम *expected_mapping;
	अचिन्हित दीर्घ kpfn;

	expected_mapping = (व्योम *)((अचिन्हित दीर्घ)stable_node |
					PAGE_MAPPING_KSM);
again:
	kpfn = READ_ONCE(stable_node->kpfn); /* Address dependency. */
	page = pfn_to_page(kpfn);
	अगर (READ_ONCE(page->mapping) != expected_mapping)
		जाओ stale;

	/*
	 * We cannot करो anything with the page जबतक its refcount is 0.
	 * Usually 0 means मुक्त, or tail of a higher-order page: in which
	 * हाल this node is no दीर्घer referenced, and should be मुक्तd;
	 * however, it might mean that the page is under page_ref_मुक्तze().
	 * The __हटाओ_mapping() हाल is easy, again the node is now stale;
	 * the same is in reuse_ksm_page() हाल; but अगर page is swapcache
	 * in migrate_page_move_mapping(), it might still be our page,
	 * in which हाल it's essential to keep the node.
	 */
	जबतक (!get_page_unless_zero(page)) अणु
		/*
		 * Another check क्रम page->mapping != expected_mapping would
		 * work here too.  We have chosen the !PageSwapCache test to
		 * optimize the common हाल, when the page is or is about to
		 * be मुक्तd: PageSwapCache is cleared (under spin_lock_irq)
		 * in the ref_मुक्तze section of __हटाओ_mapping(); but Anon
		 * page->mapping reset to शून्य later, in मुक्त_pages_prepare().
		 */
		अगर (!PageSwapCache(page))
			जाओ stale;
		cpu_relax();
	पूर्ण

	अगर (READ_ONCE(page->mapping) != expected_mapping) अणु
		put_page(page);
		जाओ stale;
	पूर्ण

	अगर (flags == GET_KSM_PAGE_TRYLOCK) अणु
		अगर (!trylock_page(page)) अणु
			put_page(page);
			वापस ERR_PTR(-EBUSY);
		पूर्ण
	पूर्ण अन्यथा अगर (flags == GET_KSM_PAGE_LOCK)
		lock_page(page);

	अगर (flags != GET_KSM_PAGE_NOLOCK) अणु
		अगर (READ_ONCE(page->mapping) != expected_mapping) अणु
			unlock_page(page);
			put_page(page);
			जाओ stale;
		पूर्ण
	पूर्ण
	वापस page;

stale:
	/*
	 * We come here from above when page->mapping or !PageSwapCache
	 * suggests that the node is stale; but it might be under migration.
	 * We need smp_rmb(), matching the smp_wmb() in ksm_migrate_page(),
	 * beक्रमe checking whether node->kpfn has been changed.
	 */
	smp_rmb();
	अगर (READ_ONCE(stable_node->kpfn) != kpfn)
		जाओ again;
	हटाओ_node_from_stable_tree(stable_node);
	वापस शून्य;
पूर्ण

/*
 * Removing rmap_item from stable or unstable tree.
 * This function will clean the inक्रमmation from the stable/unstable tree.
 */
अटल व्योम हटाओ_rmap_item_from_tree(काष्ठा rmap_item *rmap_item)
अणु
	अगर (rmap_item->address & STABLE_FLAG) अणु
		काष्ठा stable_node *stable_node;
		काष्ठा page *page;

		stable_node = rmap_item->head;
		page = get_ksm_page(stable_node, GET_KSM_PAGE_LOCK);
		अगर (!page)
			जाओ out;

		hlist_del(&rmap_item->hlist);
		unlock_page(page);
		put_page(page);

		अगर (!hlist_empty(&stable_node->hlist))
			ksm_pages_sharing--;
		अन्यथा
			ksm_pages_shared--;
		VM_BUG_ON(stable_node->rmap_hlist_len <= 0);
		stable_node->rmap_hlist_len--;

		put_anon_vma(rmap_item->anon_vma);
		rmap_item->head = शून्य;
		rmap_item->address &= PAGE_MASK;

	पूर्ण अन्यथा अगर (rmap_item->address & UNSTABLE_FLAG) अणु
		अचिन्हित अक्षर age;
		/*
		 * Usually ksmd can and must skip the rb_erase, because
		 * root_unstable_tree was alपढ़ोy reset to RB_ROOT.
		 * But be careful when an mm is निकासing: करो the rb_erase
		 * अगर this rmap_item was inserted by this scan, rather
		 * than left over from beक्रमe.
		 */
		age = (अचिन्हित अक्षर)(ksm_scan.seqnr - rmap_item->address);
		BUG_ON(age > 1);
		अगर (!age)
			rb_erase(&rmap_item->node,
				 root_unstable_tree + NUMA(rmap_item->nid));
		ksm_pages_unshared--;
		rmap_item->address &= PAGE_MASK;
	पूर्ण
out:
	cond_resched();		/* we're called from many दीर्घ loops */
पूर्ण

अटल व्योम हटाओ_trailing_rmap_items(काष्ठा rmap_item **rmap_list)
अणु
	जबतक (*rmap_list) अणु
		काष्ठा rmap_item *rmap_item = *rmap_list;
		*rmap_list = rmap_item->rmap_list;
		हटाओ_rmap_item_from_tree(rmap_item);
		मुक्त_rmap_item(rmap_item);
	पूर्ण
पूर्ण

/*
 * Though it's very tempting to unmerge rmap_items from stable tree rather
 * than check every pte of a given vma, the locking करोesn't quite work क्रम
 * that - an rmap_item is asचिन्हित to the stable tree after inserting ksm
 * page and upping mmap_lock.  Nor करोes it fit with the way we skip dup'ing
 * rmap_items from parent to child at विभाजन समय (so as not to waste समय
 * अगर निकास comes beक्रमe the next scan reaches it).
 *
 * Similarly, although we'd like to हटाओ rmap_items (so updating counts
 * and मुक्तing memory) when unmerging an area, it's easier to leave that
 * to the next pass of ksmd - consider, क्रम example, how ksmd might be
 * in cmp_and_merge_page on one of the rmap_items we would be removing.
 */
अटल पूर्णांक unmerge_ksm_pages(काष्ठा vm_area_काष्ठा *vma,
			     अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ addr;
	पूर्णांक err = 0;

	क्रम (addr = start; addr < end && !err; addr += PAGE_SIZE) अणु
		अगर (ksm_test_निकास(vma->vm_mm))
			अवरोध;
		अगर (संकेत_pending(current))
			err = -ERESTARTSYS;
		अन्यथा
			err = अवरोध_ksm(vma, addr);
	पूर्ण
	वापस err;
पूर्ण

अटल अंतरभूत काष्ठा stable_node *page_stable_node(काष्ठा page *page)
अणु
	वापस PageKsm(page) ? page_rmapping(page) : शून्य;
पूर्ण

अटल अंतरभूत व्योम set_page_stable_node(काष्ठा page *page,
					काष्ठा stable_node *stable_node)
अणु
	page->mapping = (व्योम *)((अचिन्हित दीर्घ)stable_node | PAGE_MAPPING_KSM);
पूर्ण

#अगर_घोषित CONFIG_SYSFS
/*
 * Only called through the sysfs control पूर्णांकerface:
 */
अटल पूर्णांक हटाओ_stable_node(काष्ठा stable_node *stable_node)
अणु
	काष्ठा page *page;
	पूर्णांक err;

	page = get_ksm_page(stable_node, GET_KSM_PAGE_LOCK);
	अगर (!page) अणु
		/*
		 * get_ksm_page did हटाओ_node_from_stable_tree itself.
		 */
		वापस 0;
	पूर्ण

	/*
	 * Page could be still mapped अगर this races with __mmput() running in
	 * between ksm_निकास() and निकास_mmap(). Just refuse to let
	 * merge_across_nodes/max_page_sharing be चयनed.
	 */
	err = -EBUSY;
	अगर (!page_mapped(page)) अणु
		/*
		 * The stable node did not yet appear stale to get_ksm_page(),
		 * since that allows क्रम an unmapped ksm page to be recognized
		 * right up until it is मुक्तd; but the node is safe to हटाओ.
		 * This page might be in a pagevec रुकोing to be मुक्तd,
		 * or it might be PageSwapCache (perhaps under ग_लिखोback),
		 * or it might have been हटाओd from swapcache a moment ago.
		 */
		set_page_stable_node(page, शून्य);
		हटाओ_node_from_stable_tree(stable_node);
		err = 0;
	पूर्ण

	unlock_page(page);
	put_page(page);
	वापस err;
पूर्ण

अटल पूर्णांक हटाओ_stable_node_chain(काष्ठा stable_node *stable_node,
				    काष्ठा rb_root *root)
अणु
	काष्ठा stable_node *dup;
	काष्ठा hlist_node *hlist_safe;

	अगर (!is_stable_node_chain(stable_node)) अणु
		VM_BUG_ON(is_stable_node_dup(stable_node));
		अगर (हटाओ_stable_node(stable_node))
			वापस true;
		अन्यथा
			वापस false;
	पूर्ण

	hlist_क्रम_each_entry_safe(dup, hlist_safe,
				  &stable_node->hlist, hlist_dup) अणु
		VM_BUG_ON(!is_stable_node_dup(dup));
		अगर (हटाओ_stable_node(dup))
			वापस true;
	पूर्ण
	BUG_ON(!hlist_empty(&stable_node->hlist));
	मुक्त_stable_node_chain(stable_node, root);
	वापस false;
पूर्ण

अटल पूर्णांक हटाओ_all_stable_nodes(व्योम)
अणु
	काष्ठा stable_node *stable_node, *next;
	पूर्णांक nid;
	पूर्णांक err = 0;

	क्रम (nid = 0; nid < ksm_nr_node_ids; nid++) अणु
		जबतक (root_stable_tree[nid].rb_node) अणु
			stable_node = rb_entry(root_stable_tree[nid].rb_node,
						काष्ठा stable_node, node);
			अगर (हटाओ_stable_node_chain(stable_node,
						     root_stable_tree + nid)) अणु
				err = -EBUSY;
				अवरोध;	/* proceed to next nid */
			पूर्ण
			cond_resched();
		पूर्ण
	पूर्ण
	list_क्रम_each_entry_safe(stable_node, next, &migrate_nodes, list) अणु
		अगर (हटाओ_stable_node(stable_node))
			err = -EBUSY;
		cond_resched();
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक unmerge_and_हटाओ_all_rmap_items(व्योम)
अणु
	काष्ठा mm_slot *mm_slot;
	काष्ठा mm_काष्ठा *mm;
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक err = 0;

	spin_lock(&ksm_mmlist_lock);
	ksm_scan.mm_slot = list_entry(ksm_mm_head.mm_list.next,
						काष्ठा mm_slot, mm_list);
	spin_unlock(&ksm_mmlist_lock);

	क्रम (mm_slot = ksm_scan.mm_slot;
			mm_slot != &ksm_mm_head; mm_slot = ksm_scan.mm_slot) अणु
		mm = mm_slot->mm;
		mmap_पढ़ो_lock(mm);
		क्रम (vma = mm->mmap; vma; vma = vma->vm_next) अणु
			अगर (ksm_test_निकास(mm))
				अवरोध;
			अगर (!(vma->vm_flags & VM_MERGEABLE) || !vma->anon_vma)
				जारी;
			err = unmerge_ksm_pages(vma,
						vma->vm_start, vma->vm_end);
			अगर (err)
				जाओ error;
		पूर्ण

		हटाओ_trailing_rmap_items(&mm_slot->rmap_list);
		mmap_पढ़ो_unlock(mm);

		spin_lock(&ksm_mmlist_lock);
		ksm_scan.mm_slot = list_entry(mm_slot->mm_list.next,
						काष्ठा mm_slot, mm_list);
		अगर (ksm_test_निकास(mm)) अणु
			hash_del(&mm_slot->link);
			list_del(&mm_slot->mm_list);
			spin_unlock(&ksm_mmlist_lock);

			मुक्त_mm_slot(mm_slot);
			clear_bit(MMF_VM_MERGEABLE, &mm->flags);
			mmdrop(mm);
		पूर्ण अन्यथा
			spin_unlock(&ksm_mmlist_lock);
	पूर्ण

	/* Clean up stable nodes, but करोn't worry अगर some are still busy */
	हटाओ_all_stable_nodes();
	ksm_scan.seqnr = 0;
	वापस 0;

error:
	mmap_पढ़ो_unlock(mm);
	spin_lock(&ksm_mmlist_lock);
	ksm_scan.mm_slot = &ksm_mm_head;
	spin_unlock(&ksm_mmlist_lock);
	वापस err;
पूर्ण
#पूर्ण_अगर /* CONFIG_SYSFS */

अटल u32 calc_checksum(काष्ठा page *page)
अणु
	u32 checksum;
	व्योम *addr = kmap_atomic(page);
	checksum = xxhash(addr, PAGE_SIZE, 0);
	kunmap_atomic(addr);
	वापस checksum;
पूर्ण

अटल पूर्णांक ग_लिखो_protect_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
			      pte_t *orig_pte)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	काष्ठा page_vma_mapped_walk pvmw = अणु
		.page = page,
		.vma = vma,
	पूर्ण;
	पूर्णांक swapped;
	पूर्णांक err = -EFAULT;
	काष्ठा mmu_notअगरier_range range;

	pvmw.address = page_address_in_vma(page, vma);
	अगर (pvmw.address == -EFAULT)
		जाओ out;

	BUG_ON(PageTransCompound(page));

	mmu_notअगरier_range_init(&range, MMU_NOTIFY_CLEAR, 0, vma, mm,
				pvmw.address,
				pvmw.address + PAGE_SIZE);
	mmu_notअगरier_invalidate_range_start(&range);

	अगर (!page_vma_mapped_walk(&pvmw))
		जाओ out_mn;
	अगर (WARN_ONCE(!pvmw.pte, "Unexpected PMD mapping?"))
		जाओ out_unlock;

	अगर (pte_ग_लिखो(*pvmw.pte) || pte_dirty(*pvmw.pte) ||
	    (pte_protnone(*pvmw.pte) && pte_savedग_लिखो(*pvmw.pte)) ||
						mm_tlb_flush_pending(mm)) अणु
		pte_t entry;

		swapped = PageSwapCache(page);
		flush_cache_page(vma, pvmw.address, page_to_pfn(page));
		/*
		 * Ok this is tricky, when get_user_pages_fast() run it करोesn't
		 * take any lock, thereक्रमe the check that we are going to make
		 * with the pagecount against the mapcount is racy and
		 * O_सूचीECT can happen right after the check.
		 * So we clear the pte and flush the tlb beक्रमe the check
		 * this assure us that no O_सूचीECT can happen after the check
		 * or in the middle of the check.
		 *
		 * No need to notअगरy as we are करोwngrading page table to पढ़ो
		 * only not changing it to poपूर्णांक to a new page.
		 *
		 * See Documentation/vm/mmu_notअगरier.rst
		 */
		entry = ptep_clear_flush(vma, pvmw.address, pvmw.pte);
		/*
		 * Check that no O_सूचीECT or similar I/O is in progress on the
		 * page
		 */
		अगर (page_mapcount(page) + 1 + swapped != page_count(page)) अणु
			set_pte_at(mm, pvmw.address, pvmw.pte, entry);
			जाओ out_unlock;
		पूर्ण
		अगर (pte_dirty(entry))
			set_page_dirty(page);

		अगर (pte_protnone(entry))
			entry = pte_mkclean(pte_clear_savedग_लिखो(entry));
		अन्यथा
			entry = pte_mkclean(pte_wrprotect(entry));
		set_pte_at_notअगरy(mm, pvmw.address, pvmw.pte, entry);
	पूर्ण
	*orig_pte = *pvmw.pte;
	err = 0;

out_unlock:
	page_vma_mapped_walk_करोne(&pvmw);
out_mn:
	mmu_notअगरier_invalidate_range_end(&range);
out:
	वापस err;
पूर्ण

/**
 * replace_page - replace page in vma by new ksm page
 * @vma:      vma that holds the pte poपूर्णांकing to page
 * @page:     the page we are replacing by kpage
 * @kpage:    the ksm page we replace page by
 * @orig_pte: the original value of the pte
 *
 * Returns 0 on success, -EFAULT on failure.
 */
अटल पूर्णांक replace_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
			काष्ठा page *kpage, pte_t orig_pte)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	pmd_t *pmd;
	pte_t *ptep;
	pte_t newpte;
	spinlock_t *ptl;
	अचिन्हित दीर्घ addr;
	पूर्णांक err = -EFAULT;
	काष्ठा mmu_notअगरier_range range;

	addr = page_address_in_vma(page, vma);
	अगर (addr == -EFAULT)
		जाओ out;

	pmd = mm_find_pmd(mm, addr);
	अगर (!pmd)
		जाओ out;

	mmu_notअगरier_range_init(&range, MMU_NOTIFY_CLEAR, 0, vma, mm, addr,
				addr + PAGE_SIZE);
	mmu_notअगरier_invalidate_range_start(&range);

	ptep = pte_offset_map_lock(mm, pmd, addr, &ptl);
	अगर (!pte_same(*ptep, orig_pte)) अणु
		pte_unmap_unlock(ptep, ptl);
		जाओ out_mn;
	पूर्ण

	/*
	 * No need to check ksm_use_zero_pages here: we can only have a
	 * zero_page here अगर ksm_use_zero_pages was enabled alपढ़ोy.
	 */
	अगर (!is_zero_pfn(page_to_pfn(kpage))) अणु
		get_page(kpage);
		page_add_anon_rmap(kpage, vma, addr, false);
		newpte = mk_pte(kpage, vma->vm_page_prot);
	पूर्ण अन्यथा अणु
		newpte = pte_mkspecial(pfn_pte(page_to_pfn(kpage),
					       vma->vm_page_prot));
		/*
		 * We're replacing an anonymous page with a zero page, which is
		 * not anonymous. We need to करो proper accounting otherwise we
		 * will get wrong values in /proc, and a BUG message in dmesg
		 * when tearing करोwn the mm.
		 */
		dec_mm_counter(mm, MM_ANONPAGES);
	पूर्ण

	flush_cache_page(vma, addr, pte_pfn(*ptep));
	/*
	 * No need to notअगरy as we are replacing a पढ़ो only page with another
	 * पढ़ो only page with the same content.
	 *
	 * See Documentation/vm/mmu_notअगरier.rst
	 */
	ptep_clear_flush(vma, addr, ptep);
	set_pte_at_notअगरy(mm, addr, ptep, newpte);

	page_हटाओ_rmap(page, false);
	अगर (!page_mapped(page))
		try_to_मुक्त_swap(page);
	put_page(page);

	pte_unmap_unlock(ptep, ptl);
	err = 0;
out_mn:
	mmu_notअगरier_invalidate_range_end(&range);
out:
	वापस err;
पूर्ण

/*
 * try_to_merge_one_page - take two pages and merge them पूर्णांकo one
 * @vma: the vma that holds the pte poपूर्णांकing to page
 * @page: the PageAnon page that we want to replace with kpage
 * @kpage: the PageKsm page that we want to map instead of page,
 *         or शून्य the first समय when we want to use page as kpage.
 *
 * This function वापसs 0 अगर the pages were merged, -EFAULT otherwise.
 */
अटल पूर्णांक try_to_merge_one_page(काष्ठा vm_area_काष्ठा *vma,
				 काष्ठा page *page, काष्ठा page *kpage)
अणु
	pte_t orig_pte = __pte(0);
	पूर्णांक err = -EFAULT;

	अगर (page == kpage)			/* ksm page विभाजनed */
		वापस 0;

	अगर (!PageAnon(page))
		जाओ out;

	/*
	 * We need the page lock to पढ़ो a stable PageSwapCache in
	 * ग_लिखो_protect_page().  We use trylock_page() instead of
	 * lock_page() because we करोn't want to रुको here - we
	 * prefer to जारी scanning and merging dअगरferent pages,
	 * then come back to this page when it is unlocked.
	 */
	अगर (!trylock_page(page))
		जाओ out;

	अगर (PageTransCompound(page)) अणु
		अगर (split_huge_page(page))
			जाओ out_unlock;
	पूर्ण

	/*
	 * If this anonymous page is mapped only here, its pte may need
	 * to be ग_लिखो-रक्षित.  If it's mapped अन्यथाwhere, all of its
	 * ptes are necessarily alपढ़ोy ग_लिखो-रक्षित.  But in either
	 * हाल, we need to lock and check page_count is not उठाओd.
	 */
	अगर (ग_लिखो_protect_page(vma, page, &orig_pte) == 0) अणु
		अगर (!kpage) अणु
			/*
			 * While we hold page lock, upgrade page from
			 * PageAnon+anon_vma to PageKsm+शून्य stable_node:
			 * stable_tree_insert() will update stable_node.
			 */
			set_page_stable_node(page, शून्य);
			mark_page_accessed(page);
			/*
			 * Page reclaim just मुक्तs a clean page with no dirty
			 * ptes: make sure that the ksm page would be swapped.
			 */
			अगर (!PageDirty(page))
				SetPageDirty(page);
			err = 0;
		पूर्ण अन्यथा अगर (pages_identical(page, kpage))
			err = replace_page(vma, page, kpage, orig_pte);
	पूर्ण

	अगर ((vma->vm_flags & VM_LOCKED) && kpage && !err) अणु
		munlock_vma_page(page);
		अगर (!PageMlocked(kpage)) अणु
			unlock_page(page);
			lock_page(kpage);
			mlock_vma_page(kpage);
			page = kpage;		/* क्रम final unlock */
		पूर्ण
	पूर्ण

out_unlock:
	unlock_page(page);
out:
	वापस err;
पूर्ण

/*
 * try_to_merge_with_ksm_page - like try_to_merge_two_pages,
 * but no new kernel page is allocated: kpage must alपढ़ोy be a ksm page.
 *
 * This function वापसs 0 अगर the pages were merged, -EFAULT otherwise.
 */
अटल पूर्णांक try_to_merge_with_ksm_page(काष्ठा rmap_item *rmap_item,
				      काष्ठा page *page, काष्ठा page *kpage)
अणु
	काष्ठा mm_काष्ठा *mm = rmap_item->mm;
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक err = -EFAULT;

	mmap_पढ़ो_lock(mm);
	vma = find_mergeable_vma(mm, rmap_item->address);
	अगर (!vma)
		जाओ out;

	err = try_to_merge_one_page(vma, page, kpage);
	अगर (err)
		जाओ out;

	/* Unstable nid is in जोड़ with stable anon_vma: हटाओ first */
	हटाओ_rmap_item_from_tree(rmap_item);

	/* Must get reference to anon_vma जबतक still holding mmap_lock */
	rmap_item->anon_vma = vma->anon_vma;
	get_anon_vma(vma->anon_vma);
out:
	mmap_पढ़ो_unlock(mm);
	वापस err;
पूर्ण

/*
 * try_to_merge_two_pages - take two identical pages and prepare them
 * to be merged पूर्णांकo one page.
 *
 * This function वापसs the kpage अगर we successfully merged two identical
 * pages पूर्णांकo one ksm page, शून्य otherwise.
 *
 * Note that this function upgrades page to ksm page: अगर one of the pages
 * is alपढ़ोy a ksm page, try_to_merge_with_ksm_page should be used.
 */
अटल काष्ठा page *try_to_merge_two_pages(काष्ठा rmap_item *rmap_item,
					   काष्ठा page *page,
					   काष्ठा rmap_item *tree_rmap_item,
					   काष्ठा page *tree_page)
अणु
	पूर्णांक err;

	err = try_to_merge_with_ksm_page(rmap_item, page, शून्य);
	अगर (!err) अणु
		err = try_to_merge_with_ksm_page(tree_rmap_item,
							tree_page, page);
		/*
		 * If that fails, we have a ksm page with only one pte
		 * poपूर्णांकing to it: so अवरोध it.
		 */
		अगर (err)
			अवरोध_cow(rmap_item);
	पूर्ण
	वापस err ? शून्य : page;
पूर्ण

अटल __always_अंतरभूत
bool __is_page_sharing_candidate(काष्ठा stable_node *stable_node, पूर्णांक offset)
अणु
	VM_BUG_ON(stable_node->rmap_hlist_len < 0);
	/*
	 * Check that at least one mapping still exists, otherwise
	 * there's no much poपूर्णांक to merge and share with this
	 * stable_node, as the underlying tree_page of the other
	 * sharer is going to be मुक्तd soon.
	 */
	वापस stable_node->rmap_hlist_len &&
		stable_node->rmap_hlist_len + offset < ksm_max_page_sharing;
पूर्ण

अटल __always_अंतरभूत
bool is_page_sharing_candidate(काष्ठा stable_node *stable_node)
अणु
	वापस __is_page_sharing_candidate(stable_node, 0);
पूर्ण

अटल काष्ठा page *stable_node_dup(काष्ठा stable_node **_stable_node_dup,
				    काष्ठा stable_node **_stable_node,
				    काष्ठा rb_root *root,
				    bool prune_stale_stable_nodes)
अणु
	काष्ठा stable_node *dup, *found = शून्य, *stable_node = *_stable_node;
	काष्ठा hlist_node *hlist_safe;
	काष्ठा page *_tree_page, *tree_page = शून्य;
	पूर्णांक nr = 0;
	पूर्णांक found_rmap_hlist_len;

	अगर (!prune_stale_stable_nodes ||
	    समय_beक्रमe(jअगरfies, stable_node->chain_prune_समय +
			msecs_to_jअगरfies(
				ksm_stable_node_chains_prune_millisecs)))
		prune_stale_stable_nodes = false;
	अन्यथा
		stable_node->chain_prune_समय = jअगरfies;

	hlist_क्रम_each_entry_safe(dup, hlist_safe,
				  &stable_node->hlist, hlist_dup) अणु
		cond_resched();
		/*
		 * We must walk all stable_node_dup to prune the stale
		 * stable nodes during lookup.
		 *
		 * get_ksm_page can drop the nodes from the
		 * stable_node->hlist अगर they poपूर्णांक to मुक्तd pages
		 * (that's why we करो a _safe walk). The "dup"
		 * stable_node parameter itself will be मुक्तd from
		 * under us अगर it वापसs शून्य.
		 */
		_tree_page = get_ksm_page(dup, GET_KSM_PAGE_NOLOCK);
		अगर (!_tree_page)
			जारी;
		nr += 1;
		अगर (is_page_sharing_candidate(dup)) अणु
			अगर (!found ||
			    dup->rmap_hlist_len > found_rmap_hlist_len) अणु
				अगर (found)
					put_page(tree_page);
				found = dup;
				found_rmap_hlist_len = found->rmap_hlist_len;
				tree_page = _tree_page;

				/* skip put_page क्रम found dup */
				अगर (!prune_stale_stable_nodes)
					अवरोध;
				जारी;
			पूर्ण
		पूर्ण
		put_page(_tree_page);
	पूर्ण

	अगर (found) अणु
		/*
		 * nr is counting all dups in the chain only अगर
		 * prune_stale_stable_nodes is true, otherwise we may
		 * अवरोध the loop at nr == 1 even अगर there are
		 * multiple entries.
		 */
		अगर (prune_stale_stable_nodes && nr == 1) अणु
			/*
			 * If there's not just one entry it would
			 * corrupt memory, better BUG_ON. In KSM
			 * context with no lock held it's not even
			 * fatal.
			 */
			BUG_ON(stable_node->hlist.first->next);

			/*
			 * There's just one entry and it is below the
			 * deduplication limit so drop the chain.
			 */
			rb_replace_node(&stable_node->node, &found->node,
					root);
			मुक्त_stable_node(stable_node);
			ksm_stable_node_chains--;
			ksm_stable_node_dups--;
			/*
			 * NOTE: the caller depends on the stable_node
			 * to be equal to stable_node_dup अगर the chain
			 * was collapsed.
			 */
			*_stable_node = found;
			/*
			 * Just क्रम robustness, as stable_node is
			 * otherwise left as a stable poपूर्णांकer, the
			 * compiler shall optimize it away at build
			 * समय.
			 */
			stable_node = शून्य;
		पूर्ण अन्यथा अगर (stable_node->hlist.first != &found->hlist_dup &&
			   __is_page_sharing_candidate(found, 1)) अणु
			/*
			 * If the found stable_node dup can accept one
			 * more future merge (in addition to the one
			 * that is underway) and is not at the head of
			 * the chain, put it there so next search will
			 * be quicker in the !prune_stale_stable_nodes
			 * हाल.
			 *
			 * NOTE: it would be inaccurate to use nr > 1
			 * instead of checking the hlist.first poपूर्णांकer
			 * directly, because in the
			 * prune_stale_stable_nodes हाल "nr" isn't
			 * the position of the found dup in the chain,
			 * but the total number of dups in the chain.
			 */
			hlist_del(&found->hlist_dup);
			hlist_add_head(&found->hlist_dup,
				       &stable_node->hlist);
		पूर्ण
	पूर्ण

	*_stable_node_dup = found;
	वापस tree_page;
पूर्ण

अटल काष्ठा stable_node *stable_node_dup_any(काष्ठा stable_node *stable_node,
					       काष्ठा rb_root *root)
अणु
	अगर (!is_stable_node_chain(stable_node))
		वापस stable_node;
	अगर (hlist_empty(&stable_node->hlist)) अणु
		मुक्त_stable_node_chain(stable_node, root);
		वापस शून्य;
	पूर्ण
	वापस hlist_entry(stable_node->hlist.first,
			   typeof(*stable_node), hlist_dup);
पूर्ण

/*
 * Like क्रम get_ksm_page, this function can मुक्त the *_stable_node and
 * *_stable_node_dup अगर the वापसed tree_page is शून्य.
 *
 * It can also मुक्त and overग_लिखो *_stable_node with the found
 * stable_node_dup अगर the chain is collapsed (in which हाल
 * *_stable_node will be equal to *_stable_node_dup like अगर the chain
 * never existed). It's up to the caller to verअगरy tree_page is not
 * शून्य beक्रमe dereferencing *_stable_node or *_stable_node_dup.
 *
 * *_stable_node_dup is really a second output parameter of this
 * function and will be overwritten in all हालs, the caller करोesn't
 * need to initialize it.
 */
अटल काष्ठा page *__stable_node_chain(काष्ठा stable_node **_stable_node_dup,
					काष्ठा stable_node **_stable_node,
					काष्ठा rb_root *root,
					bool prune_stale_stable_nodes)
अणु
	काष्ठा stable_node *stable_node = *_stable_node;
	अगर (!is_stable_node_chain(stable_node)) अणु
		अगर (is_page_sharing_candidate(stable_node)) अणु
			*_stable_node_dup = stable_node;
			वापस get_ksm_page(stable_node, GET_KSM_PAGE_NOLOCK);
		पूर्ण
		/*
		 * _stable_node_dup set to शून्य means the stable_node
		 * reached the ksm_max_page_sharing limit.
		 */
		*_stable_node_dup = शून्य;
		वापस शून्य;
	पूर्ण
	वापस stable_node_dup(_stable_node_dup, _stable_node, root,
			       prune_stale_stable_nodes);
पूर्ण

अटल __always_अंतरभूत काष्ठा page *chain_prune(काष्ठा stable_node **s_n_d,
						काष्ठा stable_node **s_n,
						काष्ठा rb_root *root)
अणु
	वापस __stable_node_chain(s_n_d, s_n, root, true);
पूर्ण

अटल __always_अंतरभूत काष्ठा page *chain(काष्ठा stable_node **s_n_d,
					  काष्ठा stable_node *s_n,
					  काष्ठा rb_root *root)
अणु
	काष्ठा stable_node *old_stable_node = s_n;
	काष्ठा page *tree_page;

	tree_page = __stable_node_chain(s_n_d, &s_n, root, false);
	/* not pruning dups so s_n cannot have changed */
	VM_BUG_ON(s_n != old_stable_node);
	वापस tree_page;
पूर्ण

/*
 * stable_tree_search - search क्रम page inside the stable tree
 *
 * This function checks अगर there is a page inside the stable tree
 * with identical content to the page that we are scanning right now.
 *
 * This function वापसs the stable tree node of identical content अगर found,
 * शून्य otherwise.
 */
अटल काष्ठा page *stable_tree_search(काष्ठा page *page)
अणु
	पूर्णांक nid;
	काष्ठा rb_root *root;
	काष्ठा rb_node **new;
	काष्ठा rb_node *parent;
	काष्ठा stable_node *stable_node, *stable_node_dup, *stable_node_any;
	काष्ठा stable_node *page_node;

	page_node = page_stable_node(page);
	अगर (page_node && page_node->head != &migrate_nodes) अणु
		/* ksm page विभाजनed */
		get_page(page);
		वापस page;
	पूर्ण

	nid = get_kpfn_nid(page_to_pfn(page));
	root = root_stable_tree + nid;
again:
	new = &root->rb_node;
	parent = शून्य;

	जबतक (*new) अणु
		काष्ठा page *tree_page;
		पूर्णांक ret;

		cond_resched();
		stable_node = rb_entry(*new, काष्ठा stable_node, node);
		stable_node_any = शून्य;
		tree_page = chain_prune(&stable_node_dup, &stable_node,	root);
		/*
		 * NOTE: stable_node may have been मुक्तd by
		 * chain_prune() अगर the वापसed stable_node_dup is
		 * not शून्य. stable_node_dup may have been inserted in
		 * the rbtree instead as a regular stable_node (in
		 * order to collapse the stable_node chain अगर a single
		 * stable_node dup was found in it). In such हाल the
		 * stable_node is overwritten by the calleee to poपूर्णांक
		 * to the stable_node_dup that was collapsed in the
		 * stable rbtree and stable_node will be equal to
		 * stable_node_dup like अगर the chain never existed.
		 */
		अगर (!stable_node_dup) अणु
			/*
			 * Either all stable_node dups were full in
			 * this stable_node chain, or this chain was
			 * empty and should be rb_erased.
			 */
			stable_node_any = stable_node_dup_any(stable_node,
							      root);
			अगर (!stable_node_any) अणु
				/* rb_erase just run */
				जाओ again;
			पूर्ण
			/*
			 * Take any of the stable_node dups page of
			 * this stable_node chain to let the tree walk
			 * जारी. All KSM pages beदीर्घing to the
			 * stable_node dups in a stable_node chain
			 * have the same content and they're
			 * ग_लिखो रक्षित at all बार. Any will work
			 * fine to जारी the walk.
			 */
			tree_page = get_ksm_page(stable_node_any,
						 GET_KSM_PAGE_NOLOCK);
		पूर्ण
		VM_BUG_ON(!stable_node_dup ^ !!stable_node_any);
		अगर (!tree_page) अणु
			/*
			 * If we walked over a stale stable_node,
			 * get_ksm_page() will call rb_erase() and it
			 * may rebalance the tree from under us. So
			 * restart the search from scratch. Returning
			 * शून्य would be safe too, but we'd generate
			 * false negative insertions just because some
			 * stable_node was stale.
			 */
			जाओ again;
		पूर्ण

		ret = स_भेद_pages(page, tree_page);
		put_page(tree_page);

		parent = *new;
		अगर (ret < 0)
			new = &parent->rb_left;
		अन्यथा अगर (ret > 0)
			new = &parent->rb_right;
		अन्यथा अणु
			अगर (page_node) अणु
				VM_BUG_ON(page_node->head != &migrate_nodes);
				/*
				 * Test अगर the migrated page should be merged
				 * पूर्णांकo a stable node dup. If the mapcount is
				 * 1 we can migrate it with another KSM page
				 * without adding it to the chain.
				 */
				अगर (page_mapcount(page) > 1)
					जाओ chain_append;
			पूर्ण

			अगर (!stable_node_dup) अणु
				/*
				 * If the stable_node is a chain and
				 * we got a payload match in स_भेद
				 * but we cannot merge the scanned
				 * page in any of the existing
				 * stable_node dups because they're
				 * all full, we need to रुको the
				 * scanned page to find itself a match
				 * in the unstable tree to create a
				 * bअक्रम new KSM page to add later to
				 * the dups of this stable_node.
				 */
				वापस शून्य;
			पूर्ण

			/*
			 * Lock and unlock the stable_node's page (which
			 * might alपढ़ोy have been migrated) so that page
			 * migration is sure to notice its उठाओd count.
			 * It would be more elegant to वापस stable_node
			 * than kpage, but that involves more changes.
			 */
			tree_page = get_ksm_page(stable_node_dup,
						 GET_KSM_PAGE_TRYLOCK);

			अगर (PTR_ERR(tree_page) == -EBUSY)
				वापस ERR_PTR(-EBUSY);

			अगर (unlikely(!tree_page))
				/*
				 * The tree may have been rebalanced,
				 * so re-evaluate parent and new.
				 */
				जाओ again;
			unlock_page(tree_page);

			अगर (get_kpfn_nid(stable_node_dup->kpfn) !=
			    NUMA(stable_node_dup->nid)) अणु
				put_page(tree_page);
				जाओ replace;
			पूर्ण
			वापस tree_page;
		पूर्ण
	पूर्ण

	अगर (!page_node)
		वापस शून्य;

	list_del(&page_node->list);
	DO_NUMA(page_node->nid = nid);
	rb_link_node(&page_node->node, parent, new);
	rb_insert_color(&page_node->node, root);
out:
	अगर (is_page_sharing_candidate(page_node)) अणु
		get_page(page);
		वापस page;
	पूर्ण अन्यथा
		वापस शून्य;

replace:
	/*
	 * If stable_node was a chain and chain_prune collapsed it,
	 * stable_node has been updated to be the new regular
	 * stable_node. A collapse of the chain is indistinguishable
	 * from the हाल there was no chain in the stable
	 * rbtree. Otherwise stable_node is the chain and
	 * stable_node_dup is the dup to replace.
	 */
	अगर (stable_node_dup == stable_node) अणु
		VM_BUG_ON(is_stable_node_chain(stable_node_dup));
		VM_BUG_ON(is_stable_node_dup(stable_node_dup));
		/* there is no chain */
		अगर (page_node) अणु
			VM_BUG_ON(page_node->head != &migrate_nodes);
			list_del(&page_node->list);
			DO_NUMA(page_node->nid = nid);
			rb_replace_node(&stable_node_dup->node,
					&page_node->node,
					root);
			अगर (is_page_sharing_candidate(page_node))
				get_page(page);
			अन्यथा
				page = शून्य;
		पूर्ण अन्यथा अणु
			rb_erase(&stable_node_dup->node, root);
			page = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		VM_BUG_ON(!is_stable_node_chain(stable_node));
		__stable_node_dup_del(stable_node_dup);
		अगर (page_node) अणु
			VM_BUG_ON(page_node->head != &migrate_nodes);
			list_del(&page_node->list);
			DO_NUMA(page_node->nid = nid);
			stable_node_chain_add_dup(page_node, stable_node);
			अगर (is_page_sharing_candidate(page_node))
				get_page(page);
			अन्यथा
				page = शून्य;
		पूर्ण अन्यथा अणु
			page = शून्य;
		पूर्ण
	पूर्ण
	stable_node_dup->head = &migrate_nodes;
	list_add(&stable_node_dup->list, stable_node_dup->head);
	वापस page;

chain_append:
	/* stable_node_dup could be null अगर it reached the limit */
	अगर (!stable_node_dup)
		stable_node_dup = stable_node_any;
	/*
	 * If stable_node was a chain and chain_prune collapsed it,
	 * stable_node has been updated to be the new regular
	 * stable_node. A collapse of the chain is indistinguishable
	 * from the हाल there was no chain in the stable
	 * rbtree. Otherwise stable_node is the chain and
	 * stable_node_dup is the dup to replace.
	 */
	अगर (stable_node_dup == stable_node) अणु
		VM_BUG_ON(is_stable_node_dup(stable_node_dup));
		/* chain is missing so create it */
		stable_node = alloc_stable_node_chain(stable_node_dup,
						      root);
		अगर (!stable_node)
			वापस शून्य;
	पूर्ण
	/*
	 * Add this stable_node dup that was
	 * migrated to the stable_node chain
	 * of the current nid क्रम this page
	 * content.
	 */
	VM_BUG_ON(!is_stable_node_dup(stable_node_dup));
	VM_BUG_ON(page_node->head != &migrate_nodes);
	list_del(&page_node->list);
	DO_NUMA(page_node->nid = nid);
	stable_node_chain_add_dup(page_node, stable_node);
	जाओ out;
पूर्ण

/*
 * stable_tree_insert - insert stable tree node poपूर्णांकing to new ksm page
 * पूर्णांकo the stable tree.
 *
 * This function वापसs the stable tree node just allocated on success,
 * शून्य otherwise.
 */
अटल काष्ठा stable_node *stable_tree_insert(काष्ठा page *kpage)
अणु
	पूर्णांक nid;
	अचिन्हित दीर्घ kpfn;
	काष्ठा rb_root *root;
	काष्ठा rb_node **new;
	काष्ठा rb_node *parent;
	काष्ठा stable_node *stable_node, *stable_node_dup, *stable_node_any;
	bool need_chain = false;

	kpfn = page_to_pfn(kpage);
	nid = get_kpfn_nid(kpfn);
	root = root_stable_tree + nid;
again:
	parent = शून्य;
	new = &root->rb_node;

	जबतक (*new) अणु
		काष्ठा page *tree_page;
		पूर्णांक ret;

		cond_resched();
		stable_node = rb_entry(*new, काष्ठा stable_node, node);
		stable_node_any = शून्य;
		tree_page = chain(&stable_node_dup, stable_node, root);
		अगर (!stable_node_dup) अणु
			/*
			 * Either all stable_node dups were full in
			 * this stable_node chain, or this chain was
			 * empty and should be rb_erased.
			 */
			stable_node_any = stable_node_dup_any(stable_node,
							      root);
			अगर (!stable_node_any) अणु
				/* rb_erase just run */
				जाओ again;
			पूर्ण
			/*
			 * Take any of the stable_node dups page of
			 * this stable_node chain to let the tree walk
			 * जारी. All KSM pages beदीर्घing to the
			 * stable_node dups in a stable_node chain
			 * have the same content and they're
			 * ग_लिखो रक्षित at all बार. Any will work
			 * fine to जारी the walk.
			 */
			tree_page = get_ksm_page(stable_node_any,
						 GET_KSM_PAGE_NOLOCK);
		पूर्ण
		VM_BUG_ON(!stable_node_dup ^ !!stable_node_any);
		अगर (!tree_page) अणु
			/*
			 * If we walked over a stale stable_node,
			 * get_ksm_page() will call rb_erase() and it
			 * may rebalance the tree from under us. So
			 * restart the search from scratch. Returning
			 * शून्य would be safe too, but we'd generate
			 * false negative insertions just because some
			 * stable_node was stale.
			 */
			जाओ again;
		पूर्ण

		ret = स_भेद_pages(kpage, tree_page);
		put_page(tree_page);

		parent = *new;
		अगर (ret < 0)
			new = &parent->rb_left;
		अन्यथा अगर (ret > 0)
			new = &parent->rb_right;
		अन्यथा अणु
			need_chain = true;
			अवरोध;
		पूर्ण
	पूर्ण

	stable_node_dup = alloc_stable_node();
	अगर (!stable_node_dup)
		वापस शून्य;

	INIT_HLIST_HEAD(&stable_node_dup->hlist);
	stable_node_dup->kpfn = kpfn;
	set_page_stable_node(kpage, stable_node_dup);
	stable_node_dup->rmap_hlist_len = 0;
	DO_NUMA(stable_node_dup->nid = nid);
	अगर (!need_chain) अणु
		rb_link_node(&stable_node_dup->node, parent, new);
		rb_insert_color(&stable_node_dup->node, root);
	पूर्ण अन्यथा अणु
		अगर (!is_stable_node_chain(stable_node)) अणु
			काष्ठा stable_node *orig = stable_node;
			/* chain is missing so create it */
			stable_node = alloc_stable_node_chain(orig, root);
			अगर (!stable_node) अणु
				मुक्त_stable_node(stable_node_dup);
				वापस शून्य;
			पूर्ण
		पूर्ण
		stable_node_chain_add_dup(stable_node_dup, stable_node);
	पूर्ण

	वापस stable_node_dup;
पूर्ण

/*
 * unstable_tree_search_insert - search क्रम identical page,
 * अन्यथा insert rmap_item पूर्णांकo the unstable tree.
 *
 * This function searches क्रम a page in the unstable tree identical to the
 * page currently being scanned; and अगर no identical page is found in the
 * tree, we insert rmap_item as a new object पूर्णांकo the unstable tree.
 *
 * This function वापसs poपूर्णांकer to rmap_item found to be identical
 * to the currently scanned page, शून्य otherwise.
 *
 * This function करोes both searching and inserting, because they share
 * the same walking algorithm in an rbtree.
 */
अटल
काष्ठा rmap_item *unstable_tree_search_insert(काष्ठा rmap_item *rmap_item,
					      काष्ठा page *page,
					      काष्ठा page **tree_pagep)
अणु
	काष्ठा rb_node **new;
	काष्ठा rb_root *root;
	काष्ठा rb_node *parent = शून्य;
	पूर्णांक nid;

	nid = get_kpfn_nid(page_to_pfn(page));
	root = root_unstable_tree + nid;
	new = &root->rb_node;

	जबतक (*new) अणु
		काष्ठा rmap_item *tree_rmap_item;
		काष्ठा page *tree_page;
		पूर्णांक ret;

		cond_resched();
		tree_rmap_item = rb_entry(*new, काष्ठा rmap_item, node);
		tree_page = get_mergeable_page(tree_rmap_item);
		अगर (!tree_page)
			वापस शून्य;

		/*
		 * Don't substitute a ksm page क्रम a विभाजनed page.
		 */
		अगर (page == tree_page) अणु
			put_page(tree_page);
			वापस शून्य;
		पूर्ण

		ret = स_भेद_pages(page, tree_page);

		parent = *new;
		अगर (ret < 0) अणु
			put_page(tree_page);
			new = &parent->rb_left;
		पूर्ण अन्यथा अगर (ret > 0) अणु
			put_page(tree_page);
			new = &parent->rb_right;
		पूर्ण अन्यथा अगर (!ksm_merge_across_nodes &&
			   page_to_nid(tree_page) != nid) अणु
			/*
			 * If tree_page has been migrated to another NUMA node,
			 * it will be flushed out and put in the right unstable
			 * tree next समय: only merge with it when across_nodes.
			 */
			put_page(tree_page);
			वापस शून्य;
		पूर्ण अन्यथा अणु
			*tree_pagep = tree_page;
			वापस tree_rmap_item;
		पूर्ण
	पूर्ण

	rmap_item->address |= UNSTABLE_FLAG;
	rmap_item->address |= (ksm_scan.seqnr & SEQNR_MASK);
	DO_NUMA(rmap_item->nid = nid);
	rb_link_node(&rmap_item->node, parent, new);
	rb_insert_color(&rmap_item->node, root);

	ksm_pages_unshared++;
	वापस शून्य;
पूर्ण

/*
 * stable_tree_append - add another rmap_item to the linked list of
 * rmap_items hanging off a given node of the stable tree, all sharing
 * the same ksm page.
 */
अटल व्योम stable_tree_append(काष्ठा rmap_item *rmap_item,
			       काष्ठा stable_node *stable_node,
			       bool max_page_sharing_bypass)
अणु
	/*
	 * rmap won't find this mapping if we don't insert the
	 * rmap_item in the right stable_node
	 * duplicate. page_migration could अवरोध later अगर rmap अवरोधs,
	 * so we can as well crash here. We really need to check क्रम
	 * rmap_hlist_len == STABLE_NODE_CHAIN, but we can as well check
	 * क्रम other negative values as an underflow अगर detected here
	 * क्रम the first समय (and not when decreasing rmap_hlist_len)
	 * would be sign of memory corruption in the stable_node.
	 */
	BUG_ON(stable_node->rmap_hlist_len < 0);

	stable_node->rmap_hlist_len++;
	अगर (!max_page_sharing_bypass)
		/* possibly non fatal but unexpected overflow, only warn */
		WARN_ON_ONCE(stable_node->rmap_hlist_len >
			     ksm_max_page_sharing);

	rmap_item->head = stable_node;
	rmap_item->address |= STABLE_FLAG;
	hlist_add_head(&rmap_item->hlist, &stable_node->hlist);

	अगर (rmap_item->hlist.next)
		ksm_pages_sharing++;
	अन्यथा
		ksm_pages_shared++;
पूर्ण

/*
 * cmp_and_merge_page - first see अगर page can be merged पूर्णांकo the stable tree;
 * अगर not, compare checksum to previous and अगर it's the same, see अगर page can
 * be inserted पूर्णांकo the unstable tree, or merged with a page alपढ़ोy there and
 * both transferred to the stable tree.
 *
 * @page: the page that we are searching identical page to.
 * @rmap_item: the reverse mapping पूर्णांकo the भव address of this page
 */
अटल व्योम cmp_and_merge_page(काष्ठा page *page, काष्ठा rmap_item *rmap_item)
अणु
	काष्ठा mm_काष्ठा *mm = rmap_item->mm;
	काष्ठा rmap_item *tree_rmap_item;
	काष्ठा page *tree_page = शून्य;
	काष्ठा stable_node *stable_node;
	काष्ठा page *kpage;
	अचिन्हित पूर्णांक checksum;
	पूर्णांक err;
	bool max_page_sharing_bypass = false;

	stable_node = page_stable_node(page);
	अगर (stable_node) अणु
		अगर (stable_node->head != &migrate_nodes &&
		    get_kpfn_nid(READ_ONCE(stable_node->kpfn)) !=
		    NUMA(stable_node->nid)) अणु
			stable_node_dup_del(stable_node);
			stable_node->head = &migrate_nodes;
			list_add(&stable_node->list, stable_node->head);
		पूर्ण
		अगर (stable_node->head != &migrate_nodes &&
		    rmap_item->head == stable_node)
			वापस;
		/*
		 * If it's a KSM विभाजन, allow it to go over the sharing limit
		 * without warnings.
		 */
		अगर (!is_page_sharing_candidate(stable_node))
			max_page_sharing_bypass = true;
	पूर्ण

	/* We first start with searching the page inside the stable tree */
	kpage = stable_tree_search(page);
	अगर (kpage == page && rmap_item->head == stable_node) अणु
		put_page(kpage);
		वापस;
	पूर्ण

	हटाओ_rmap_item_from_tree(rmap_item);

	अगर (kpage) अणु
		अगर (PTR_ERR(kpage) == -EBUSY)
			वापस;

		err = try_to_merge_with_ksm_page(rmap_item, page, kpage);
		अगर (!err) अणु
			/*
			 * The page was successfully merged:
			 * add its rmap_item to the stable tree.
			 */
			lock_page(kpage);
			stable_tree_append(rmap_item, page_stable_node(kpage),
					   max_page_sharing_bypass);
			unlock_page(kpage);
		पूर्ण
		put_page(kpage);
		वापस;
	पूर्ण

	/*
	 * If the hash value of the page has changed from the last समय
	 * we calculated it, this page is changing frequently: thereक्रमe we
	 * करोn't want to insert it in the unstable tree, and we don't want
	 * to waste our समय searching क्रम something identical to it there.
	 */
	checksum = calc_checksum(page);
	अगर (rmap_item->oldchecksum != checksum) अणु
		rmap_item->oldchecksum = checksum;
		वापस;
	पूर्ण

	/*
	 * Same checksum as an empty page. We attempt to merge it with the
	 * appropriate zero page अगर the user enabled this via sysfs.
	 */
	अगर (ksm_use_zero_pages && (checksum == zero_checksum)) अणु
		काष्ठा vm_area_काष्ठा *vma;

		mmap_पढ़ो_lock(mm);
		vma = find_mergeable_vma(mm, rmap_item->address);
		अगर (vma) अणु
			err = try_to_merge_one_page(vma, page,
					ZERO_PAGE(rmap_item->address));
		पूर्ण अन्यथा अणु
			/*
			 * If the vma is out of date, we करो not need to
			 * जारी.
			 */
			err = 0;
		पूर्ण
		mmap_पढ़ो_unlock(mm);
		/*
		 * In हाल of failure, the page was not really empty, so we
		 * need to जारी. Otherwise we're करोne.
		 */
		अगर (!err)
			वापस;
	पूर्ण
	tree_rmap_item =
		unstable_tree_search_insert(rmap_item, page, &tree_page);
	अगर (tree_rmap_item) अणु
		bool split;

		kpage = try_to_merge_two_pages(rmap_item, page,
						tree_rmap_item, tree_page);
		/*
		 * If both pages we tried to merge beदीर्घ to the same compound
		 * page, then we actually ended up increasing the reference
		 * count of the same compound page twice, and split_huge_page
		 * failed.
		 * Here we set a flag अगर that happened, and we use it later to
		 * try split_huge_page again. Since we call put_page right
		 * afterwards, the reference count will be correct and
		 * split_huge_page should succeed.
		 */
		split = PageTransCompound(page)
			&& compound_head(page) == compound_head(tree_page);
		put_page(tree_page);
		अगर (kpage) अणु
			/*
			 * The pages were successfully merged: insert new
			 * node in the stable tree and add both rmap_items.
			 */
			lock_page(kpage);
			stable_node = stable_tree_insert(kpage);
			अगर (stable_node) अणु
				stable_tree_append(tree_rmap_item, stable_node,
						   false);
				stable_tree_append(rmap_item, stable_node,
						   false);
			पूर्ण
			unlock_page(kpage);

			/*
			 * If we fail to insert the page पूर्णांकo the stable tree,
			 * we will have 2 भव addresses that are poपूर्णांकing
			 * to a ksm page left outside the stable tree,
			 * in which हाल we need to अवरोध_cow on both.
			 */
			अगर (!stable_node) अणु
				अवरोध_cow(tree_rmap_item);
				अवरोध_cow(rmap_item);
			पूर्ण
		पूर्ण अन्यथा अगर (split) अणु
			/*
			 * We are here अगर we tried to merge two pages and
			 * failed because they both beदीर्घed to the same
			 * compound page. We will split the page now, but no
			 * merging will take place.
			 * We करो not want to add the cost of a full lock; अगर
			 * the page is locked, it is better to skip it and
			 * perhaps try again later.
			 */
			अगर (!trylock_page(page))
				वापस;
			split_huge_page(page);
			unlock_page(page);
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा rmap_item *get_next_rmap_item(काष्ठा mm_slot *mm_slot,
					    काष्ठा rmap_item **rmap_list,
					    अचिन्हित दीर्घ addr)
अणु
	काष्ठा rmap_item *rmap_item;

	जबतक (*rmap_list) अणु
		rmap_item = *rmap_list;
		अगर ((rmap_item->address & PAGE_MASK) == addr)
			वापस rmap_item;
		अगर (rmap_item->address > addr)
			अवरोध;
		*rmap_list = rmap_item->rmap_list;
		हटाओ_rmap_item_from_tree(rmap_item);
		मुक्त_rmap_item(rmap_item);
	पूर्ण

	rmap_item = alloc_rmap_item();
	अगर (rmap_item) अणु
		/* It has alपढ़ोy been zeroed */
		rmap_item->mm = mm_slot->mm;
		rmap_item->address = addr;
		rmap_item->rmap_list = *rmap_list;
		*rmap_list = rmap_item;
	पूर्ण
	वापस rmap_item;
पूर्ण

अटल काष्ठा rmap_item *scan_get_next_rmap_item(काष्ठा page **page)
अणु
	काष्ठा mm_काष्ठा *mm;
	काष्ठा mm_slot *slot;
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा rmap_item *rmap_item;
	पूर्णांक nid;

	अगर (list_empty(&ksm_mm_head.mm_list))
		वापस शून्य;

	slot = ksm_scan.mm_slot;
	अगर (slot == &ksm_mm_head) अणु
		/*
		 * A number of pages can hang around indefinitely on per-cpu
		 * pagevecs, उठाओd page count preventing ग_लिखो_protect_page
		 * from merging them.  Though it करोesn't really matter much,
		 * it is puzzling to see some stuck in pages_अस्थिर until
		 * other activity jostles them out, and they also prevented
		 * LTP's KSM test from succeeding deterministically; so drain
		 * them here (here rather than on entry to ksm_करो_scan(),
		 * so we करोn't IPI too often when pages_to_scan is set low).
		 */
		lru_add_drain_all();

		/*
		 * Whereas stale stable_nodes on the stable_tree itself
		 * get pruned in the regular course of stable_tree_search(),
		 * those moved out to the migrate_nodes list can accumulate:
		 * so prune them once beक्रमe each full scan.
		 */
		अगर (!ksm_merge_across_nodes) अणु
			काष्ठा stable_node *stable_node, *next;
			काष्ठा page *page;

			list_क्रम_each_entry_safe(stable_node, next,
						 &migrate_nodes, list) अणु
				page = get_ksm_page(stable_node,
						    GET_KSM_PAGE_NOLOCK);
				अगर (page)
					put_page(page);
				cond_resched();
			पूर्ण
		पूर्ण

		क्रम (nid = 0; nid < ksm_nr_node_ids; nid++)
			root_unstable_tree[nid] = RB_ROOT;

		spin_lock(&ksm_mmlist_lock);
		slot = list_entry(slot->mm_list.next, काष्ठा mm_slot, mm_list);
		ksm_scan.mm_slot = slot;
		spin_unlock(&ksm_mmlist_lock);
		/*
		 * Although we tested list_empty() above, a racing __ksm_निकास
		 * of the last mm on the list may have हटाओd it since then.
		 */
		अगर (slot == &ksm_mm_head)
			वापस शून्य;
next_mm:
		ksm_scan.address = 0;
		ksm_scan.rmap_list = &slot->rmap_list;
	पूर्ण

	mm = slot->mm;
	mmap_पढ़ो_lock(mm);
	अगर (ksm_test_निकास(mm))
		vma = शून्य;
	अन्यथा
		vma = find_vma(mm, ksm_scan.address);

	क्रम (; vma; vma = vma->vm_next) अणु
		अगर (!(vma->vm_flags & VM_MERGEABLE))
			जारी;
		अगर (ksm_scan.address < vma->vm_start)
			ksm_scan.address = vma->vm_start;
		अगर (!vma->anon_vma)
			ksm_scan.address = vma->vm_end;

		जबतक (ksm_scan.address < vma->vm_end) अणु
			अगर (ksm_test_निकास(mm))
				अवरोध;
			*page = follow_page(vma, ksm_scan.address, FOLL_GET);
			अगर (IS_ERR_OR_शून्य(*page)) अणु
				ksm_scan.address += PAGE_SIZE;
				cond_resched();
				जारी;
			पूर्ण
			अगर (PageAnon(*page)) अणु
				flush_anon_page(vma, *page, ksm_scan.address);
				flush_dcache_page(*page);
				rmap_item = get_next_rmap_item(slot,
					ksm_scan.rmap_list, ksm_scan.address);
				अगर (rmap_item) अणु
					ksm_scan.rmap_list =
							&rmap_item->rmap_list;
					ksm_scan.address += PAGE_SIZE;
				पूर्ण अन्यथा
					put_page(*page);
				mmap_पढ़ो_unlock(mm);
				वापस rmap_item;
			पूर्ण
			put_page(*page);
			ksm_scan.address += PAGE_SIZE;
			cond_resched();
		पूर्ण
	पूर्ण

	अगर (ksm_test_निकास(mm)) अणु
		ksm_scan.address = 0;
		ksm_scan.rmap_list = &slot->rmap_list;
	पूर्ण
	/*
	 * Nuke all the rmap_items that are above this current rmap:
	 * because there were no VM_MERGEABLE vmas with such addresses.
	 */
	हटाओ_trailing_rmap_items(ksm_scan.rmap_list);

	spin_lock(&ksm_mmlist_lock);
	ksm_scan.mm_slot = list_entry(slot->mm_list.next,
						काष्ठा mm_slot, mm_list);
	अगर (ksm_scan.address == 0) अणु
		/*
		 * We've completed a full scan of all vmas, holding mmap_lock
		 * throughout, and found no VM_MERGEABLE: so करो the same as
		 * __ksm_निकास करोes to हटाओ this mm from all our lists now.
		 * This applies either when cleaning up after __ksm_निकास
		 * (but beware: we can reach here even beक्रमe __ksm_निकास),
		 * or when all VM_MERGEABLE areas have been unmapped (and
		 * mmap_lock then protects against race with MADV_MERGEABLE).
		 */
		hash_del(&slot->link);
		list_del(&slot->mm_list);
		spin_unlock(&ksm_mmlist_lock);

		मुक्त_mm_slot(slot);
		clear_bit(MMF_VM_MERGEABLE, &mm->flags);
		mmap_पढ़ो_unlock(mm);
		mmdrop(mm);
	पूर्ण अन्यथा अणु
		mmap_पढ़ो_unlock(mm);
		/*
		 * mmap_पढ़ो_unlock(mm) first because after
		 * spin_unlock(&ksm_mmlist_lock) run, the "mm" may
		 * alपढ़ोy have been मुक्तd under us by __ksm_निकास()
		 * because the "mm_slot" is still hashed and
		 * ksm_scan.mm_slot करोesn't poपूर्णांक to it anymore.
		 */
		spin_unlock(&ksm_mmlist_lock);
	पूर्ण

	/* Repeat until we've completed scanning the whole list */
	slot = ksm_scan.mm_slot;
	अगर (slot != &ksm_mm_head)
		जाओ next_mm;

	ksm_scan.seqnr++;
	वापस शून्य;
पूर्ण

/**
 * ksm_करो_scan  - the ksm scanner मुख्य worker function.
 * @scan_npages:  number of pages we want to scan beक्रमe we वापस.
 */
अटल व्योम ksm_करो_scan(अचिन्हित पूर्णांक scan_npages)
अणु
	काष्ठा rmap_item *rmap_item;
	काष्ठा page *page;

	जबतक (scan_npages-- && likely(!मुक्तzing(current))) अणु
		cond_resched();
		rmap_item = scan_get_next_rmap_item(&page);
		अगर (!rmap_item)
			वापस;
		cmp_and_merge_page(page, rmap_item);
		put_page(page);
	पूर्ण
पूर्ण

अटल पूर्णांक ksmd_should_run(व्योम)
अणु
	वापस (ksm_run & KSM_RUN_MERGE) && !list_empty(&ksm_mm_head.mm_list);
पूर्ण

अटल पूर्णांक ksm_scan_thपढ़ो(व्योम *nothing)
अणु
	अचिन्हित पूर्णांक sleep_ms;

	set_मुक्तzable();
	set_user_nice(current, 5);

	जबतक (!kthपढ़ो_should_stop()) अणु
		mutex_lock(&ksm_thपढ़ो_mutex);
		रुको_जबतक_offlining();
		अगर (ksmd_should_run())
			ksm_करो_scan(ksm_thपढ़ो_pages_to_scan);
		mutex_unlock(&ksm_thपढ़ो_mutex);

		try_to_मुक्तze();

		अगर (ksmd_should_run()) अणु
			sleep_ms = READ_ONCE(ksm_thपढ़ो_sleep_millisecs);
			रुको_event_पूर्णांकerruptible_समयout(ksm_iter_रुको,
				sleep_ms != READ_ONCE(ksm_thपढ़ो_sleep_millisecs),
				msecs_to_jअगरfies(sleep_ms));
		पूर्ण अन्यथा अणु
			रुको_event_मुक्तzable(ksm_thपढ़ो_रुको,
				ksmd_should_run() || kthपढ़ो_should_stop());
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक ksm_madvise(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
		अचिन्हित दीर्घ end, पूर्णांक advice, अचिन्हित दीर्घ *vm_flags)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	पूर्णांक err;

	चयन (advice) अणु
	हाल MADV_MERGEABLE:
		/*
		 * Be somewhat over-protective क्रम now!
		 */
		अगर (*vm_flags & (VM_MERGEABLE | VM_SHARED  | VM_MAYSHARE   |
				 VM_PFNMAP    | VM_IO      | VM_DONTEXPAND |
				 VM_HUGETLB | VM_MIXEDMAP))
			वापस 0;		/* just ignore the advice */

		अगर (vma_is_dax(vma))
			वापस 0;

#अगर_घोषित VM_SAO
		अगर (*vm_flags & VM_SAO)
			वापस 0;
#पूर्ण_अगर
#अगर_घोषित VM_SPARC_ADI
		अगर (*vm_flags & VM_SPARC_ADI)
			वापस 0;
#पूर्ण_अगर

		अगर (!test_bit(MMF_VM_MERGEABLE, &mm->flags)) अणु
			err = __ksm_enter(mm);
			अगर (err)
				वापस err;
		पूर्ण

		*vm_flags |= VM_MERGEABLE;
		अवरोध;

	हाल MADV_UNMERGEABLE:
		अगर (!(*vm_flags & VM_MERGEABLE))
			वापस 0;		/* just ignore the advice */

		अगर (vma->anon_vma) अणु
			err = unmerge_ksm_pages(vma, start, end);
			अगर (err)
				वापस err;
		पूर्ण

		*vm_flags &= ~VM_MERGEABLE;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ksm_madvise);

पूर्णांक __ksm_enter(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा mm_slot *mm_slot;
	पूर्णांक needs_wakeup;

	mm_slot = alloc_mm_slot();
	अगर (!mm_slot)
		वापस -ENOMEM;

	/* Check ksm_run too?  Would need tighter locking */
	needs_wakeup = list_empty(&ksm_mm_head.mm_list);

	spin_lock(&ksm_mmlist_lock);
	insert_to_mm_slots_hash(mm, mm_slot);
	/*
	 * When KSM_RUN_MERGE (or KSM_RUN_STOP),
	 * insert just behind the scanning cursor, to let the area settle
	 * करोwn a little; when विभाजन is followed by immediate exec, we करोn't
	 * want ksmd to waste समय setting up and tearing करोwn an rmap_list.
	 *
	 * But when KSM_RUN_UNMERGE, it's important to insert ahead of its
	 * scanning cursor, otherwise KSM pages in newly विभाजनed mms will be
	 * missed: then we might as well insert at the end of the list.
	 */
	अगर (ksm_run & KSM_RUN_UNMERGE)
		list_add_tail(&mm_slot->mm_list, &ksm_mm_head.mm_list);
	अन्यथा
		list_add_tail(&mm_slot->mm_list, &ksm_scan.mm_slot->mm_list);
	spin_unlock(&ksm_mmlist_lock);

	set_bit(MMF_VM_MERGEABLE, &mm->flags);
	mmgrab(mm);

	अगर (needs_wakeup)
		wake_up_पूर्णांकerruptible(&ksm_thपढ़ो_रुको);

	वापस 0;
पूर्ण

व्योम __ksm_निकास(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा mm_slot *mm_slot;
	पूर्णांक easy_to_मुक्त = 0;

	/*
	 * This process is निकासing: अगर it's straightक्रमward (as is the
	 * हाल when ksmd was never running), मुक्त mm_slot immediately.
	 * But अगर it's at the cursor or has rmap_items linked to it, use
	 * mmap_lock to synchronize with any अवरोध_cows beक्रमe pagetables
	 * are मुक्तd, and leave the mm_slot on the list क्रम ksmd to मुक्त.
	 * Beware: ksm may alपढ़ोy have noticed it निकासing and मुक्तd the slot.
	 */

	spin_lock(&ksm_mmlist_lock);
	mm_slot = get_mm_slot(mm);
	अगर (mm_slot && ksm_scan.mm_slot != mm_slot) अणु
		अगर (!mm_slot->rmap_list) अणु
			hash_del(&mm_slot->link);
			list_del(&mm_slot->mm_list);
			easy_to_मुक्त = 1;
		पूर्ण अन्यथा अणु
			list_move(&mm_slot->mm_list,
				  &ksm_scan.mm_slot->mm_list);
		पूर्ण
	पूर्ण
	spin_unlock(&ksm_mmlist_lock);

	अगर (easy_to_मुक्त) अणु
		मुक्त_mm_slot(mm_slot);
		clear_bit(MMF_VM_MERGEABLE, &mm->flags);
		mmdrop(mm);
	पूर्ण अन्यथा अगर (mm_slot) अणु
		mmap_ग_लिखो_lock(mm);
		mmap_ग_लिखो_unlock(mm);
	पूर्ण
पूर्ण

काष्ठा page *ksm_might_need_to_copy(काष्ठा page *page,
			काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address)
अणु
	काष्ठा anon_vma *anon_vma = page_anon_vma(page);
	काष्ठा page *new_page;

	अगर (PageKsm(page)) अणु
		अगर (page_stable_node(page) &&
		    !(ksm_run & KSM_RUN_UNMERGE))
			वापस page;	/* no need to copy it */
	पूर्ण अन्यथा अगर (!anon_vma) अणु
		वापस page;		/* no need to copy it */
	पूर्ण अन्यथा अगर (anon_vma->root == vma->anon_vma->root &&
		 page->index == linear_page_index(vma, address)) अणु
		वापस page;		/* still no need to copy it */
	पूर्ण
	अगर (!PageUptodate(page))
		वापस page;		/* let करो_swap_page report the error */

	new_page = alloc_page_vma(GFP_HIGHUSER_MOVABLE, vma, address);
	अगर (new_page && mem_cgroup_अक्षरge(new_page, vma->vm_mm, GFP_KERNEL)) अणु
		put_page(new_page);
		new_page = शून्य;
	पूर्ण
	अगर (new_page) अणु
		copy_user_highpage(new_page, page, address, vma);

		SetPageDirty(new_page);
		__SetPageUptodate(new_page);
		__SetPageLocked(new_page);
	पूर्ण

	वापस new_page;
पूर्ण

व्योम rmap_walk_ksm(काष्ठा page *page, काष्ठा rmap_walk_control *rwc)
अणु
	काष्ठा stable_node *stable_node;
	काष्ठा rmap_item *rmap_item;
	पूर्णांक search_new_विभाजनs = 0;

	VM_BUG_ON_PAGE(!PageKsm(page), page);

	/*
	 * Rely on the page lock to protect against concurrent modअगरications
	 * to that page's node of the stable tree.
	 */
	VM_BUG_ON_PAGE(!PageLocked(page), page);

	stable_node = page_stable_node(page);
	अगर (!stable_node)
		वापस;
again:
	hlist_क्रम_each_entry(rmap_item, &stable_node->hlist, hlist) अणु
		काष्ठा anon_vma *anon_vma = rmap_item->anon_vma;
		काष्ठा anon_vma_chain *vmac;
		काष्ठा vm_area_काष्ठा *vma;

		cond_resched();
		anon_vma_lock_पढ़ो(anon_vma);
		anon_vma_पूर्णांकerval_tree_क्रमeach(vmac, &anon_vma->rb_root,
					       0, अच_दीर्घ_उच्च) अणु
			अचिन्हित दीर्घ addr;

			cond_resched();
			vma = vmac->vma;

			/* Ignore the stable/unstable/sqnr flags */
			addr = rmap_item->address & PAGE_MASK;

			अगर (addr < vma->vm_start || addr >= vma->vm_end)
				जारी;
			/*
			 * Initially we examine only the vma which covers this
			 * rmap_item; but later, अगर there is still work to करो,
			 * we examine covering vmas in other mms: in हाल they
			 * were विभाजनed from the original since ksmd passed.
			 */
			अगर ((rmap_item->mm == vma->vm_mm) == search_new_विभाजनs)
				जारी;

			अगर (rwc->invalid_vma && rwc->invalid_vma(vma, rwc->arg))
				जारी;

			अगर (!rwc->rmap_one(page, vma, addr, rwc->arg)) अणु
				anon_vma_unlock_पढ़ो(anon_vma);
				वापस;
			पूर्ण
			अगर (rwc->करोne && rwc->करोne(page)) अणु
				anon_vma_unlock_पढ़ो(anon_vma);
				वापस;
			पूर्ण
		पूर्ण
		anon_vma_unlock_पढ़ो(anon_vma);
	पूर्ण
	अगर (!search_new_विभाजनs++)
		जाओ again;
पूर्ण

#अगर_घोषित CONFIG_MIGRATION
व्योम ksm_migrate_page(काष्ठा page *newpage, काष्ठा page *oldpage)
अणु
	काष्ठा stable_node *stable_node;

	VM_BUG_ON_PAGE(!PageLocked(oldpage), oldpage);
	VM_BUG_ON_PAGE(!PageLocked(newpage), newpage);
	VM_BUG_ON_PAGE(newpage->mapping != oldpage->mapping, newpage);

	stable_node = page_stable_node(newpage);
	अगर (stable_node) अणु
		VM_BUG_ON_PAGE(stable_node->kpfn != page_to_pfn(oldpage), oldpage);
		stable_node->kpfn = page_to_pfn(newpage);
		/*
		 * newpage->mapping was set in advance; now we need smp_wmb()
		 * to make sure that the new stable_node->kpfn is visible
		 * to get_ksm_page() beक्रमe it can see that oldpage->mapping
		 * has gone stale (or that PageSwapCache has been cleared).
		 */
		smp_wmb();
		set_page_stable_node(oldpage, शून्य);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_MIGRATION */

#अगर_घोषित CONFIG_MEMORY_HOTREMOVE
अटल व्योम रुको_जबतक_offlining(व्योम)
अणु
	जबतक (ksm_run & KSM_RUN_OFFLINE) अणु
		mutex_unlock(&ksm_thपढ़ो_mutex);
		रुको_on_bit(&ksm_run, ilog2(KSM_RUN_OFFLINE),
			    TASK_UNINTERRUPTIBLE);
		mutex_lock(&ksm_thपढ़ो_mutex);
	पूर्ण
पूर्ण

अटल bool stable_node_dup_हटाओ_range(काष्ठा stable_node *stable_node,
					 अचिन्हित दीर्घ start_pfn,
					 अचिन्हित दीर्घ end_pfn)
अणु
	अगर (stable_node->kpfn >= start_pfn &&
	    stable_node->kpfn < end_pfn) अणु
		/*
		 * Don't get_ksm_page, page has alपढ़ोy gone:
		 * which is why we keep kpfn instead of page*
		 */
		हटाओ_node_from_stable_tree(stable_node);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool stable_node_chain_हटाओ_range(काष्ठा stable_node *stable_node,
					   अचिन्हित दीर्घ start_pfn,
					   अचिन्हित दीर्घ end_pfn,
					   काष्ठा rb_root *root)
अणु
	काष्ठा stable_node *dup;
	काष्ठा hlist_node *hlist_safe;

	अगर (!is_stable_node_chain(stable_node)) अणु
		VM_BUG_ON(is_stable_node_dup(stable_node));
		वापस stable_node_dup_हटाओ_range(stable_node, start_pfn,
						    end_pfn);
	पूर्ण

	hlist_क्रम_each_entry_safe(dup, hlist_safe,
				  &stable_node->hlist, hlist_dup) अणु
		VM_BUG_ON(!is_stable_node_dup(dup));
		stable_node_dup_हटाओ_range(dup, start_pfn, end_pfn);
	पूर्ण
	अगर (hlist_empty(&stable_node->hlist)) अणु
		मुक्त_stable_node_chain(stable_node, root);
		वापस true; /* notअगरy caller that tree was rebalanced */
	पूर्ण अन्यथा
		वापस false;
पूर्ण

अटल व्योम ksm_check_stable_tree(अचिन्हित दीर्घ start_pfn,
				  अचिन्हित दीर्घ end_pfn)
अणु
	काष्ठा stable_node *stable_node, *next;
	काष्ठा rb_node *node;
	पूर्णांक nid;

	क्रम (nid = 0; nid < ksm_nr_node_ids; nid++) अणु
		node = rb_first(root_stable_tree + nid);
		जबतक (node) अणु
			stable_node = rb_entry(node, काष्ठा stable_node, node);
			अगर (stable_node_chain_हटाओ_range(stable_node,
							   start_pfn, end_pfn,
							   root_stable_tree +
							   nid))
				node = rb_first(root_stable_tree + nid);
			अन्यथा
				node = rb_next(node);
			cond_resched();
		पूर्ण
	पूर्ण
	list_क्रम_each_entry_safe(stable_node, next, &migrate_nodes, list) अणु
		अगर (stable_node->kpfn >= start_pfn &&
		    stable_node->kpfn < end_pfn)
			हटाओ_node_from_stable_tree(stable_node);
		cond_resched();
	पूर्ण
पूर्ण

अटल पूर्णांक ksm_memory_callback(काष्ठा notअगरier_block *self,
			       अचिन्हित दीर्घ action, व्योम *arg)
अणु
	काष्ठा memory_notअगरy *mn = arg;

	चयन (action) अणु
	हाल MEM_GOING_OFFLINE:
		/*
		 * Prevent ksm_करो_scan(), unmerge_and_हटाओ_all_rmap_items()
		 * and हटाओ_all_stable_nodes() जबतक memory is going offline:
		 * it is unsafe क्रम them to touch the stable tree at this समय.
		 * But unmerge_ksm_pages(), rmap lookups and other entry poपूर्णांकs
		 * which करो not need the ksm_thपढ़ो_mutex are all safe.
		 */
		mutex_lock(&ksm_thपढ़ो_mutex);
		ksm_run |= KSM_RUN_OFFLINE;
		mutex_unlock(&ksm_thपढ़ो_mutex);
		अवरोध;

	हाल MEM_OFFLINE:
		/*
		 * Most of the work is करोne by page migration; but there might
		 * be a few stable_nodes left over, still poपूर्णांकing to काष्ठा
		 * pages which have been offlined: prune those from the tree,
		 * otherwise get_ksm_page() might later try to access a
		 * non-existent काष्ठा page.
		 */
		ksm_check_stable_tree(mn->start_pfn,
				      mn->start_pfn + mn->nr_pages);
		fallthrough;
	हाल MEM_CANCEL_OFFLINE:
		mutex_lock(&ksm_thपढ़ो_mutex);
		ksm_run &= ~KSM_RUN_OFFLINE;
		mutex_unlock(&ksm_thपढ़ो_mutex);

		smp_mb();	/* wake_up_bit advises this */
		wake_up_bit(&ksm_run, ilog2(KSM_RUN_OFFLINE));
		अवरोध;
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण
#अन्यथा
अटल व्योम रुको_जबतक_offlining(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_MEMORY_HOTREMOVE */

#अगर_घोषित CONFIG_SYSFS
/*
 * This all compiles without CONFIG_SYSFS, but is a waste of space.
 */

#घोषणा KSM_ATTR_RO(_name) \
	अटल काष्ठा kobj_attribute _name##_attr = __ATTR_RO(_name)
#घोषणा KSM_ATTR(_name) \
	अटल काष्ठा kobj_attribute _name##_attr = \
		__ATTR(_name, 0644, _name##_show, _name##_store)

अटल sमाप_प्रकार sleep_millisecs_show(काष्ठा kobject *kobj,
				    काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%u\n", ksm_thपढ़ो_sleep_millisecs);
पूर्ण

अटल sमाप_प्रकार sleep_millisecs_store(काष्ठा kobject *kobj,
				     काष्ठा kobj_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक msecs;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 10, &msecs);
	अगर (err)
		वापस -EINVAL;

	ksm_thपढ़ो_sleep_millisecs = msecs;
	wake_up_पूर्णांकerruptible(&ksm_iter_रुको);

	वापस count;
पूर्ण
KSM_ATTR(sleep_millisecs);

अटल sमाप_प्रकार pages_to_scan_show(काष्ठा kobject *kobj,
				  काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%u\n", ksm_thपढ़ो_pages_to_scan);
पूर्ण

अटल sमाप_प्रकार pages_to_scan_store(काष्ठा kobject *kobj,
				   काष्ठा kobj_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक nr_pages;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 10, &nr_pages);
	अगर (err)
		वापस -EINVAL;

	ksm_thपढ़ो_pages_to_scan = nr_pages;

	वापस count;
पूर्ण
KSM_ATTR(pages_to_scan);

अटल sमाप_प्रकार run_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%lu\n", ksm_run);
पूर्ण

अटल sमाप_प्रकार run_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक flags;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 10, &flags);
	अगर (err)
		वापस -EINVAL;
	अगर (flags > KSM_RUN_UNMERGE)
		वापस -EINVAL;

	/*
	 * KSM_RUN_MERGE sets ksmd running, and 0 stops it running.
	 * KSM_RUN_UNMERGE stops it running and unmerges all rmap_items,
	 * अवरोधing COW to मुक्त the pages_shared (but leaves mm_slots
	 * on the list क्रम when ksmd may be set running again).
	 */

	mutex_lock(&ksm_thपढ़ो_mutex);
	रुको_जबतक_offlining();
	अगर (ksm_run != flags) अणु
		ksm_run = flags;
		अगर (flags & KSM_RUN_UNMERGE) अणु
			set_current_oom_origin();
			err = unmerge_and_हटाओ_all_rmap_items();
			clear_current_oom_origin();
			अगर (err) अणु
				ksm_run = KSM_RUN_STOP;
				count = err;
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&ksm_thपढ़ो_mutex);

	अगर (flags & KSM_RUN_MERGE)
		wake_up_पूर्णांकerruptible(&ksm_thपढ़ो_रुको);

	वापस count;
पूर्ण
KSM_ATTR(run);

#अगर_घोषित CONFIG_NUMA
अटल sमाप_प्रकार merge_across_nodes_show(काष्ठा kobject *kobj,
				       काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%u\n", ksm_merge_across_nodes);
पूर्ण

अटल sमाप_प्रकार merge_across_nodes_store(काष्ठा kobject *kobj,
				   काष्ठा kobj_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ knob;

	err = kम_से_अदीर्घ(buf, 10, &knob);
	अगर (err)
		वापस err;
	अगर (knob > 1)
		वापस -EINVAL;

	mutex_lock(&ksm_thपढ़ो_mutex);
	रुको_जबतक_offlining();
	अगर (ksm_merge_across_nodes != knob) अणु
		अगर (ksm_pages_shared || हटाओ_all_stable_nodes())
			err = -EBUSY;
		अन्यथा अगर (root_stable_tree == one_stable_tree) अणु
			काष्ठा rb_root *buf;
			/*
			 * This is the first समय that we चयन away from the
			 * शेष of merging across nodes: must now allocate
			 * a buffer to hold as many roots as may be needed.
			 * Allocate stable and unstable together:
			 * MAXSMP NODES_SHIFT 10 will use 16kB.
			 */
			buf = kसुस्मृति(nr_node_ids + nr_node_ids, माप(*buf),
				      GFP_KERNEL);
			/* Let us assume that RB_ROOT is शून्य is zero */
			अगर (!buf)
				err = -ENOMEM;
			अन्यथा अणु
				root_stable_tree = buf;
				root_unstable_tree = buf + nr_node_ids;
				/* Stable tree is empty but not the unstable */
				root_unstable_tree[0] = one_unstable_tree[0];
			पूर्ण
		पूर्ण
		अगर (!err) अणु
			ksm_merge_across_nodes = knob;
			ksm_nr_node_ids = knob ? 1 : nr_node_ids;
		पूर्ण
	पूर्ण
	mutex_unlock(&ksm_thपढ़ो_mutex);

	वापस err ? err : count;
पूर्ण
KSM_ATTR(merge_across_nodes);
#पूर्ण_अगर

अटल sमाप_प्रकार use_zero_pages_show(काष्ठा kobject *kobj,
				   काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%u\n", ksm_use_zero_pages);
पूर्ण
अटल sमाप_प्रकार use_zero_pages_store(काष्ठा kobject *kobj,
				   काष्ठा kobj_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक err;
	bool value;

	err = kstrtobool(buf, &value);
	अगर (err)
		वापस -EINVAL;

	ksm_use_zero_pages = value;

	वापस count;
पूर्ण
KSM_ATTR(use_zero_pages);

अटल sमाप_प्रकार max_page_sharing_show(काष्ठा kobject *kobj,
				     काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%u\n", ksm_max_page_sharing);
पूर्ण

अटल sमाप_प्रकार max_page_sharing_store(काष्ठा kobject *kobj,
				      काष्ठा kobj_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक err;
	पूर्णांक knob;

	err = kstrtoपूर्णांक(buf, 10, &knob);
	अगर (err)
		वापस err;
	/*
	 * When a KSM page is created it is shared by 2 mappings. This
	 * being a चिन्हित comparison, it implicitly verअगरies it's not
	 * negative.
	 */
	अगर (knob < 2)
		वापस -EINVAL;

	अगर (READ_ONCE(ksm_max_page_sharing) == knob)
		वापस count;

	mutex_lock(&ksm_thपढ़ो_mutex);
	रुको_जबतक_offlining();
	अगर (ksm_max_page_sharing != knob) अणु
		अगर (ksm_pages_shared || हटाओ_all_stable_nodes())
			err = -EBUSY;
		अन्यथा
			ksm_max_page_sharing = knob;
	पूर्ण
	mutex_unlock(&ksm_thपढ़ो_mutex);

	वापस err ? err : count;
पूर्ण
KSM_ATTR(max_page_sharing);

अटल sमाप_प्रकार pages_shared_show(काष्ठा kobject *kobj,
				 काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%lu\n", ksm_pages_shared);
पूर्ण
KSM_ATTR_RO(pages_shared);

अटल sमाप_प्रकार pages_sharing_show(काष्ठा kobject *kobj,
				  काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%lu\n", ksm_pages_sharing);
पूर्ण
KSM_ATTR_RO(pages_sharing);

अटल sमाप_प्रकार pages_unshared_show(काष्ठा kobject *kobj,
				   काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%lu\n", ksm_pages_unshared);
पूर्ण
KSM_ATTR_RO(pages_unshared);

अटल sमाप_प्रकार pages_अस्थिर_show(काष्ठा kobject *kobj,
				   काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	दीर्घ ksm_pages_अस्थिर;

	ksm_pages_अस्थिर = ksm_rmap_items - ksm_pages_shared
				- ksm_pages_sharing - ksm_pages_unshared;
	/*
	 * It was not worth any locking to calculate that statistic,
	 * but it might thereक्रमe someबार be negative: conceal that.
	 */
	अगर (ksm_pages_अस्थिर < 0)
		ksm_pages_अस्थिर = 0;
	वापस sysfs_emit(buf, "%ld\n", ksm_pages_अस्थिर);
पूर्ण
KSM_ATTR_RO(pages_अस्थिर);

अटल sमाप_प्रकार stable_node_dups_show(काष्ठा kobject *kobj,
				     काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%lu\n", ksm_stable_node_dups);
पूर्ण
KSM_ATTR_RO(stable_node_dups);

अटल sमाप_प्रकार stable_node_chains_show(काष्ठा kobject *kobj,
				       काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%lu\n", ksm_stable_node_chains);
पूर्ण
KSM_ATTR_RO(stable_node_chains);

अटल sमाप_प्रकार
stable_node_chains_prune_millisecs_show(काष्ठा kobject *kobj,
					काष्ठा kobj_attribute *attr,
					अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%u\n", ksm_stable_node_chains_prune_millisecs);
पूर्ण

अटल sमाप_प्रकार
stable_node_chains_prune_millisecs_store(काष्ठा kobject *kobj,
					 काष्ठा kobj_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ msecs;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &msecs);
	अगर (err || msecs > अच_पूर्णांक_उच्च)
		वापस -EINVAL;

	ksm_stable_node_chains_prune_millisecs = msecs;

	वापस count;
पूर्ण
KSM_ATTR(stable_node_chains_prune_millisecs);

अटल sमाप_प्रकार full_scans_show(काष्ठा kobject *kobj,
			       काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%lu\n", ksm_scan.seqnr);
पूर्ण
KSM_ATTR_RO(full_scans);

अटल काष्ठा attribute *ksm_attrs[] = अणु
	&sleep_millisecs_attr.attr,
	&pages_to_scan_attr.attr,
	&run_attr.attr,
	&pages_shared_attr.attr,
	&pages_sharing_attr.attr,
	&pages_unshared_attr.attr,
	&pages_अस्थिर_attr.attr,
	&full_scans_attr.attr,
#अगर_घोषित CONFIG_NUMA
	&merge_across_nodes_attr.attr,
#पूर्ण_अगर
	&max_page_sharing_attr.attr,
	&stable_node_chains_attr.attr,
	&stable_node_dups_attr.attr,
	&stable_node_chains_prune_millisecs_attr.attr,
	&use_zero_pages_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ksm_attr_group = अणु
	.attrs = ksm_attrs,
	.name = "ksm",
पूर्ण;
#पूर्ण_अगर /* CONFIG_SYSFS */

अटल पूर्णांक __init ksm_init(व्योम)
अणु
	काष्ठा task_काष्ठा *ksm_thपढ़ो;
	पूर्णांक err;

	/* The correct value depends on page size and endianness */
	zero_checksum = calc_checksum(ZERO_PAGE(0));
	/* Default to false क्रम backwards compatibility */
	ksm_use_zero_pages = false;

	err = ksm_slab_init();
	अगर (err)
		जाओ out;

	ksm_thपढ़ो = kthपढ़ो_run(ksm_scan_thपढ़ो, शून्य, "ksmd");
	अगर (IS_ERR(ksm_thपढ़ो)) अणु
		pr_err("ksm: creating kthread failed\n");
		err = PTR_ERR(ksm_thपढ़ो);
		जाओ out_मुक्त;
	पूर्ण

#अगर_घोषित CONFIG_SYSFS
	err = sysfs_create_group(mm_kobj, &ksm_attr_group);
	अगर (err) अणु
		pr_err("ksm: register sysfs failed\n");
		kthपढ़ो_stop(ksm_thपढ़ो);
		जाओ out_मुक्त;
	पूर्ण
#अन्यथा
	ksm_run = KSM_RUN_MERGE;	/* no way क्रम user to start it */

#पूर्ण_अगर /* CONFIG_SYSFS */

#अगर_घोषित CONFIG_MEMORY_HOTREMOVE
	/* There is no signअगरicance to this priority 100 */
	hotplug_memory_notअगरier(ksm_memory_callback, 100);
#पूर्ण_अगर
	वापस 0;

out_मुक्त:
	ksm_slab_मुक्त();
out:
	वापस err;
पूर्ण
subsys_initcall(ksm_init);
