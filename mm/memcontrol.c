<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* memcontrol.c - Memory Controller
 *
 * Copyright IBM Corporation, 2007
 * Author Balbir Singh <balbir@linux.vnet.ibm.com>
 *
 * Copyright 2007 OpenVZ SWsoft Inc
 * Author: Pavel Emelianov <xemul@खोलोvz.org>
 *
 * Memory thresholds
 * Copyright (C) 2009 Nokia Corporation
 * Author: Kirill A. Shutemov
 *
 * Kernel Memory Controller
 * Copyright (C) 2012 Parallels Inc. and Google Inc.
 * Authors: Glauber Costa and Suleiman Souhlal
 *
 * Native page reclaim
 * Charge lअगरeसमय sanitation
 * Lockless page tracking & accounting
 * Unअगरied hierarchy configuration model
 * Copyright (C) 2015 Red Hat, Inc., Johannes Weiner
 *
 * Per memcg lru locking
 * Copyright (C) 2020 Alibaba, Inc, Alex Shi
 */

#समावेश <linux/page_counter.h>
#समावेश <linux/memcontrol.h>
#समावेश <linux/cgroup.h>
#समावेश <linux/pagewalk.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/vm_event_item.h>
#समावेश <linux/smp.h>
#समावेश <linux/page-flags.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/bit_spinlock.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/export.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/slab.h>
#समावेश <linux/swap.h>
#समावेश <linux/swapops.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/eventfd.h>
#समावेश <linux/poll.h>
#समावेश <linux/sort.h>
#समावेश <linux/fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/vmpressure.h>
#समावेश <linux/mm_अंतरभूत.h>
#समावेश <linux/swap_cgroup.h>
#समावेश <linux/cpu.h>
#समावेश <linux/oom.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/file.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/psi.h>
#समावेश <linux/seq_buf.h>
#समावेश "internal.h"
#समावेश <net/sock.h>
#समावेश <net/ip.h>
#समावेश "slab.h"

#समावेश <linux/uaccess.h>

#समावेश <trace/events/vmscan.h>

काष्ठा cgroup_subsys memory_cgrp_subsys __पढ़ो_mostly;
EXPORT_SYMBOL(memory_cgrp_subsys);

काष्ठा mem_cgroup *root_mem_cgroup __पढ़ो_mostly;

/* Active memory cgroup to use from an पूर्णांकerrupt context */
DEFINE_PER_CPU(काष्ठा mem_cgroup *, पूर्णांक_active_memcg);

/* Socket memory accounting disabled? */
अटल bool cgroup_memory_nosocket;

/* Kernel memory accounting disabled? */
अटल bool cgroup_memory_nokmem;

/* Whether the swap controller is active */
#अगर_घोषित CONFIG_MEMCG_SWAP
bool cgroup_memory_noswap __पढ़ो_mostly;
#अन्यथा
#घोषणा cgroup_memory_noswap		1
#पूर्ण_अगर

#अगर_घोषित CONFIG_CGROUP_WRITEBACK
अटल DECLARE_WAIT_QUEUE_HEAD(memcg_cgwb_frn_रुकोq);
#पूर्ण_अगर

/* Whether legacy memory+swap accounting is active */
अटल bool करो_memsw_account(व्योम)
अणु
	वापस !cgroup_subsys_on_dfl(memory_cgrp_subsys) && !cgroup_memory_noswap;
पूर्ण

#घोषणा THRESHOLDS_EVENTS_TARGET 128
#घोषणा SOFTLIMIT_EVENTS_TARGET 1024

/*
 * Cgroups above their limits are मुख्यtained in a RB-Tree, independent of
 * their hierarchy representation
 */

काष्ठा mem_cgroup_tree_per_node अणु
	काष्ठा rb_root rb_root;
	काष्ठा rb_node *rb_righपंचांगost;
	spinlock_t lock;
पूर्ण;

काष्ठा mem_cgroup_tree अणु
	काष्ठा mem_cgroup_tree_per_node *rb_tree_per_node[MAX_NUMNODES];
पूर्ण;

अटल काष्ठा mem_cgroup_tree soft_limit_tree __पढ़ो_mostly;

/* क्रम OOM */
काष्ठा mem_cgroup_eventfd_list अणु
	काष्ठा list_head list;
	काष्ठा eventfd_ctx *eventfd;
पूर्ण;

/*
 * cgroup_event represents events which userspace want to receive.
 */
काष्ठा mem_cgroup_event अणु
	/*
	 * memcg which the event beदीर्घs to.
	 */
	काष्ठा mem_cgroup *memcg;
	/*
	 * eventfd to संकेत userspace about the event.
	 */
	काष्ठा eventfd_ctx *eventfd;
	/*
	 * Each of these stored in a list by the cgroup.
	 */
	काष्ठा list_head list;
	/*
	 * रेजिस्टर_event() callback will be used to add new userspace
	 * रुकोer क्रम changes related to this event.  Use eventfd_संकेत()
	 * on eventfd to send notअगरication to userspace.
	 */
	पूर्णांक (*रेजिस्टर_event)(काष्ठा mem_cgroup *memcg,
			      काष्ठा eventfd_ctx *eventfd, स्थिर अक्षर *args);
	/*
	 * unरेजिस्टर_event() callback will be called when userspace बंदs
	 * the eventfd or on cgroup removing.  This callback must be set,
	 * अगर you want provide notअगरication functionality.
	 */
	व्योम (*unरेजिस्टर_event)(काष्ठा mem_cgroup *memcg,
				 काष्ठा eventfd_ctx *eventfd);
	/*
	 * All fields below needed to unरेजिस्टर event when
	 * userspace बंदs eventfd.
	 */
	poll_table pt;
	रुको_queue_head_t *wqh;
	रुको_queue_entry_t रुको;
	काष्ठा work_काष्ठा हटाओ;
पूर्ण;

अटल व्योम mem_cgroup_threshold(काष्ठा mem_cgroup *memcg);
अटल व्योम mem_cgroup_oom_notअगरy(काष्ठा mem_cgroup *memcg);

/* Stuffs क्रम move अक्षरges at task migration. */
/*
 * Types of अक्षरges to be moved.
 */
#घोषणा MOVE_ANON	0x1U
#घोषणा MOVE_खाता	0x2U
#घोषणा MOVE_MASK	(MOVE_ANON | MOVE_खाता)

/* "mc" and its members are रक्षित by cgroup_mutex */
अटल काष्ठा move_अक्षरge_काष्ठा अणु
	spinlock_t	  lock; /* क्रम from, to */
	काष्ठा mm_काष्ठा  *mm;
	काष्ठा mem_cgroup *from;
	काष्ठा mem_cgroup *to;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ preअक्षरge;
	अचिन्हित दीर्घ moved_अक्षरge;
	अचिन्हित दीर्घ moved_swap;
	काष्ठा task_काष्ठा *moving_task;	/* a task moving अक्षरges */
	रुको_queue_head_t रुकोq;		/* a रुकोq क्रम other context */
पूर्ण mc = अणु
	.lock = __SPIN_LOCK_UNLOCKED(mc.lock),
	.रुकोq = __WAIT_QUEUE_HEAD_INITIALIZER(mc.रुकोq),
पूर्ण;

/*
 * Maximum loops in mem_cgroup_hierarchical_reclaim(), used क्रम soft
 * limit reclaim to prevent infinite loops, अगर they ever occur.
 */
#घोषणा	MEM_CGROUP_MAX_RECLAIM_LOOPS		100
#घोषणा	MEM_CGROUP_MAX_SOFT_LIMIT_RECLAIM_LOOPS	2

/* क्रम encoding cft->निजी value on file */
क्रमागत res_type अणु
	_MEM,
	_MEMSWAP,
	_OOM_TYPE,
	_KMEM,
	_TCP,
पूर्ण;

#घोषणा MEMखाता_PRIVATE(x, val)	((x) << 16 | (val))
#घोषणा MEMखाता_TYPE(val)	((val) >> 16 & 0xffff)
#घोषणा MEMखाता_ATTR(val)	((val) & 0xffff)
/* Used क्रम OOM notअगरier */
#घोषणा OOM_CONTROL		(0)

/*
 * Iteration स्थिरructs क्रम visiting all cgroups (under a tree).  If
 * loops are निकासed prematurely (अवरोध), mem_cgroup_iter_अवरोध() must
 * be used क्रम reference counting.
 */
#घोषणा क्रम_each_mem_cgroup_tree(iter, root)		\
	क्रम (iter = mem_cgroup_iter(root, शून्य, शून्य);	\
	     iter != शून्य;				\
	     iter = mem_cgroup_iter(root, iter, शून्य))

#घोषणा क्रम_each_mem_cgroup(iter)			\
	क्रम (iter = mem_cgroup_iter(शून्य, शून्य, शून्य);	\
	     iter != शून्य;				\
	     iter = mem_cgroup_iter(शून्य, iter, शून्य))

अटल अंतरभूत bool should_क्रमce_अक्षरge(व्योम)
अणु
	वापस tsk_is_oom_victim(current) || fatal_संकेत_pending(current) ||
		(current->flags & PF_EXITING);
पूर्ण

/* Some nice accessors क्रम the vmpressure. */
काष्ठा vmpressure *memcg_to_vmpressure(काष्ठा mem_cgroup *memcg)
अणु
	अगर (!memcg)
		memcg = root_mem_cgroup;
	वापस &memcg->vmpressure;
पूर्ण

काष्ठा cgroup_subsys_state *vmpressure_to_css(काष्ठा vmpressure *vmpr)
अणु
	वापस &container_of(vmpr, काष्ठा mem_cgroup, vmpressure)->css;
पूर्ण

#अगर_घोषित CONFIG_MEMCG_KMEM
बाह्य spinlock_t css_set_lock;

अटल व्योम obj_cgroup_unअक्षरge_pages(काष्ठा obj_cgroup *objcg,
				      अचिन्हित पूर्णांक nr_pages);

अटल व्योम obj_cgroup_release(काष्ठा percpu_ref *ref)
अणु
	काष्ठा obj_cgroup *objcg = container_of(ref, काष्ठा obj_cgroup, refcnt);
	काष्ठा mem_cgroup *memcg;
	अचिन्हित पूर्णांक nr_bytes;
	अचिन्हित पूर्णांक nr_pages;
	अचिन्हित दीर्घ flags;

	/*
	 * At this poपूर्णांक all allocated objects are मुक्तd, and
	 * objcg->nr_अक्षरged_bytes can't have an arbitrary byte value.
	 * However, it can be PAGE_SIZE or (x * PAGE_SIZE).
	 *
	 * The following sequence can lead to it:
	 * 1) CPU0: objcg == stock->cached_objcg
	 * 2) CPU1: we करो a small allocation (e.g. 92 bytes),
	 *          PAGE_SIZE bytes are अक्षरged
	 * 3) CPU1: a process from another memcg is allocating something,
	 *          the stock अगर flushed,
	 *          objcg->nr_अक्षरged_bytes = PAGE_SIZE - 92
	 * 5) CPU0: we करो release this object,
	 *          92 bytes are added to stock->nr_bytes
	 * 6) CPU0: stock is flushed,
	 *          92 bytes are added to objcg->nr_अक्षरged_bytes
	 *
	 * In the result, nr_अक्षरged_bytes == PAGE_SIZE.
	 * This page will be unअक्षरged in obj_cgroup_release().
	 */
	nr_bytes = atomic_पढ़ो(&objcg->nr_अक्षरged_bytes);
	WARN_ON_ONCE(nr_bytes & (PAGE_SIZE - 1));
	nr_pages = nr_bytes >> PAGE_SHIFT;

	spin_lock_irqsave(&css_set_lock, flags);
	memcg = obj_cgroup_memcg(objcg);
	अगर (nr_pages)
		obj_cgroup_unअक्षरge_pages(objcg, nr_pages);
	list_del(&objcg->list);
	mem_cgroup_put(memcg);
	spin_unlock_irqrestore(&css_set_lock, flags);

	percpu_ref_निकास(ref);
	kमुक्त_rcu(objcg, rcu);
पूर्ण

अटल काष्ठा obj_cgroup *obj_cgroup_alloc(व्योम)
अणु
	काष्ठा obj_cgroup *objcg;
	पूर्णांक ret;

	objcg = kzalloc(माप(काष्ठा obj_cgroup), GFP_KERNEL);
	अगर (!objcg)
		वापस शून्य;

	ret = percpu_ref_init(&objcg->refcnt, obj_cgroup_release, 0,
			      GFP_KERNEL);
	अगर (ret) अणु
		kमुक्त(objcg);
		वापस शून्य;
	पूर्ण
	INIT_LIST_HEAD(&objcg->list);
	वापस objcg;
पूर्ण

अटल व्योम memcg_reparent_objcgs(काष्ठा mem_cgroup *memcg,
				  काष्ठा mem_cgroup *parent)
अणु
	काष्ठा obj_cgroup *objcg, *iter;

	objcg = rcu_replace_poपूर्णांकer(memcg->objcg, शून्य, true);

	spin_lock_irq(&css_set_lock);

	/* Move active objcg to the parent's list */
	xchg(&objcg->memcg, parent);
	css_get(&parent->css);
	list_add(&objcg->list, &parent->objcg_list);

	/* Move alपढ़ोy reparented objcgs to the parent's list */
	list_क्रम_each_entry(iter, &memcg->objcg_list, list) अणु
		css_get(&parent->css);
		xchg(&iter->memcg, parent);
		css_put(&memcg->css);
	पूर्ण
	list_splice(&memcg->objcg_list, &parent->objcg_list);

	spin_unlock_irq(&css_set_lock);

	percpu_ref_समाप्त(&objcg->refcnt);
पूर्ण

/*
 * This will be used as a shrinker list's index.
 * The मुख्य reason क्रम not using cgroup id क्रम this:
 *  this works better in sparse environments, where we have a lot of memcgs,
 *  but only a few kmem-limited. Or also, अगर we have, क्रम instance, 200
 *  memcgs, and none but the 200th is kmem-limited, we'd have to have a
 *  200 entry array क्रम that.
 *
 * The current size of the caches array is stored in memcg_nr_cache_ids. It
 * will द्विगुन each समय we have to increase it.
 */
अटल DEFINE_IDA(memcg_cache_ida);
पूर्णांक memcg_nr_cache_ids;

/* Protects memcg_nr_cache_ids */
अटल DECLARE_RWSEM(memcg_cache_ids_sem);

व्योम memcg_get_cache_ids(व्योम)
अणु
	करोwn_पढ़ो(&memcg_cache_ids_sem);
पूर्ण

व्योम memcg_put_cache_ids(व्योम)
अणु
	up_पढ़ो(&memcg_cache_ids_sem);
पूर्ण

/*
 * MIN_SIZE is dअगरferent than 1, because we would like to aव्योम going through
 * the alloc/मुक्त process all the समय. In a small machine, 4 kmem-limited
 * cgroups is a reasonable guess. In the future, it could be a parameter or
 * tunable, but that is strictly not necessary.
 *
 * MAX_SIZE should be as large as the number of cgrp_ids. Ideally, we could get
 * this स्थिरant directly from cgroup, but it is understandable that this is
 * better kept as an पूर्णांकernal representation in cgroup.c. In any हाल, the
 * cgrp_id space is not getting any smaller, and we करोn't have to necessarily
 * increase ours as well अगर it increases.
 */
#घोषणा MEMCG_CACHES_MIN_SIZE 4
#घोषणा MEMCG_CACHES_MAX_SIZE MEM_CGROUP_ID_MAX

/*
 * A lot of the calls to the cache allocation functions are expected to be
 * अंतरभूतd by the compiler. Since the calls to memcg_slab_pre_alloc_hook() are
 * conditional to this अटल branch, we'll have to allow modules that करोes
 * kmem_cache_alloc and the such to see this symbol as well
 */
DEFINE_STATIC_KEY_FALSE(memcg_kmem_enabled_key);
EXPORT_SYMBOL(memcg_kmem_enabled_key);
#पूर्ण_अगर

/**
 * mem_cgroup_css_from_page - css of the memcg associated with a page
 * @page: page of पूर्णांकerest
 *
 * If memcg is bound to the शेष hierarchy, css of the memcg associated
 * with @page is वापसed.  The वापसed css reमुख्यs associated with @page
 * until it is released.
 *
 * If memcg is bound to a traditional hierarchy, the css of root_mem_cgroup
 * is वापसed.
 */
काष्ठा cgroup_subsys_state *mem_cgroup_css_from_page(काष्ठा page *page)
अणु
	काष्ठा mem_cgroup *memcg;

	memcg = page_memcg(page);

	अगर (!memcg || !cgroup_subsys_on_dfl(memory_cgrp_subsys))
		memcg = root_mem_cgroup;

	वापस &memcg->css;
पूर्ण

/**
 * page_cgroup_ino - वापस inode number of the memcg a page is अक्षरged to
 * @page: the page
 *
 * Look up the बंदst online ancestor of the memory cgroup @page is अक्षरged to
 * and वापस its inode number or 0 अगर @page is not अक्षरged to any cgroup. It
 * is safe to call this function without holding a reference to @page.
 *
 * Note, this function is inherently racy, because there is nothing to prevent
 * the cgroup inode from getting torn करोwn and potentially पुनः_स्मृतिated a moment
 * after page_cgroup_ino() वापसs, so it only should be used by callers that
 * करो not care (such as procfs पूर्णांकerfaces).
 */
ino_t page_cgroup_ino(काष्ठा page *page)
अणु
	काष्ठा mem_cgroup *memcg;
	अचिन्हित दीर्घ ino = 0;

	rcu_पढ़ो_lock();
	memcg = page_memcg_check(page);

	जबतक (memcg && !(memcg->css.flags & CSS_ONLINE))
		memcg = parent_mem_cgroup(memcg);
	अगर (memcg)
		ino = cgroup_ino(memcg->css.cgroup);
	rcu_पढ़ो_unlock();
	वापस ino;
पूर्ण

अटल काष्ठा mem_cgroup_per_node *
mem_cgroup_page_nodeinfo(काष्ठा mem_cgroup *memcg, काष्ठा page *page)
अणु
	पूर्णांक nid = page_to_nid(page);

	वापस memcg->nodeinfo[nid];
पूर्ण

अटल काष्ठा mem_cgroup_tree_per_node *
soft_limit_tree_node(पूर्णांक nid)
अणु
	वापस soft_limit_tree.rb_tree_per_node[nid];
पूर्ण

अटल काष्ठा mem_cgroup_tree_per_node *
soft_limit_tree_from_page(काष्ठा page *page)
अणु
	पूर्णांक nid = page_to_nid(page);

	वापस soft_limit_tree.rb_tree_per_node[nid];
पूर्ण

अटल व्योम __mem_cgroup_insert_exceeded(काष्ठा mem_cgroup_per_node *mz,
					 काष्ठा mem_cgroup_tree_per_node *mctz,
					 अचिन्हित दीर्घ new_usage_in_excess)
अणु
	काष्ठा rb_node **p = &mctz->rb_root.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा mem_cgroup_per_node *mz_node;
	bool righपंचांगost = true;

	अगर (mz->on_tree)
		वापस;

	mz->usage_in_excess = new_usage_in_excess;
	अगर (!mz->usage_in_excess)
		वापस;
	जबतक (*p) अणु
		parent = *p;
		mz_node = rb_entry(parent, काष्ठा mem_cgroup_per_node,
					tree_node);
		अगर (mz->usage_in_excess < mz_node->usage_in_excess) अणु
			p = &(*p)->rb_left;
			righपंचांगost = false;
		पूर्ण अन्यथा अणु
			p = &(*p)->rb_right;
		पूर्ण
	पूर्ण

	अगर (righपंचांगost)
		mctz->rb_righपंचांगost = &mz->tree_node;

	rb_link_node(&mz->tree_node, parent, p);
	rb_insert_color(&mz->tree_node, &mctz->rb_root);
	mz->on_tree = true;
पूर्ण

अटल व्योम __mem_cgroup_हटाओ_exceeded(काष्ठा mem_cgroup_per_node *mz,
					 काष्ठा mem_cgroup_tree_per_node *mctz)
अणु
	अगर (!mz->on_tree)
		वापस;

	अगर (&mz->tree_node == mctz->rb_righपंचांगost)
		mctz->rb_righपंचांगost = rb_prev(&mz->tree_node);

	rb_erase(&mz->tree_node, &mctz->rb_root);
	mz->on_tree = false;
पूर्ण

अटल व्योम mem_cgroup_हटाओ_exceeded(काष्ठा mem_cgroup_per_node *mz,
				       काष्ठा mem_cgroup_tree_per_node *mctz)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mctz->lock, flags);
	__mem_cgroup_हटाओ_exceeded(mz, mctz);
	spin_unlock_irqrestore(&mctz->lock, flags);
पूर्ण

अटल अचिन्हित दीर्घ soft_limit_excess(काष्ठा mem_cgroup *memcg)
अणु
	अचिन्हित दीर्घ nr_pages = page_counter_पढ़ो(&memcg->memory);
	अचिन्हित दीर्घ soft_limit = READ_ONCE(memcg->soft_limit);
	अचिन्हित दीर्घ excess = 0;

	अगर (nr_pages > soft_limit)
		excess = nr_pages - soft_limit;

	वापस excess;
पूर्ण

अटल व्योम mem_cgroup_update_tree(काष्ठा mem_cgroup *memcg, काष्ठा page *page)
अणु
	अचिन्हित दीर्घ excess;
	काष्ठा mem_cgroup_per_node *mz;
	काष्ठा mem_cgroup_tree_per_node *mctz;

	mctz = soft_limit_tree_from_page(page);
	अगर (!mctz)
		वापस;
	/*
	 * Necessary to update all ancestors when hierarchy is used.
	 * because their event counter is not touched.
	 */
	क्रम (; memcg; memcg = parent_mem_cgroup(memcg)) अणु
		mz = mem_cgroup_page_nodeinfo(memcg, page);
		excess = soft_limit_excess(memcg);
		/*
		 * We have to update the tree अगर mz is on RB-tree or
		 * mem is over its softlimit.
		 */
		अगर (excess || mz->on_tree) अणु
			अचिन्हित दीर्घ flags;

			spin_lock_irqsave(&mctz->lock, flags);
			/* अगर on-tree, हटाओ it */
			अगर (mz->on_tree)
				__mem_cgroup_हटाओ_exceeded(mz, mctz);
			/*
			 * Insert again. mz->usage_in_excess will be updated.
			 * If excess is 0, no tree ops.
			 */
			__mem_cgroup_insert_exceeded(mz, mctz, excess);
			spin_unlock_irqrestore(&mctz->lock, flags);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mem_cgroup_हटाओ_from_trees(काष्ठा mem_cgroup *memcg)
अणु
	काष्ठा mem_cgroup_tree_per_node *mctz;
	काष्ठा mem_cgroup_per_node *mz;
	पूर्णांक nid;

	क्रम_each_node(nid) अणु
		mz = memcg->nodeinfo[nid];
		mctz = soft_limit_tree_node(nid);
		अगर (mctz)
			mem_cgroup_हटाओ_exceeded(mz, mctz);
	पूर्ण
पूर्ण

अटल काष्ठा mem_cgroup_per_node *
__mem_cgroup_largest_soft_limit_node(काष्ठा mem_cgroup_tree_per_node *mctz)
अणु
	काष्ठा mem_cgroup_per_node *mz;

retry:
	mz = शून्य;
	अगर (!mctz->rb_righपंचांगost)
		जाओ करोne;		/* Nothing to reclaim from */

	mz = rb_entry(mctz->rb_righपंचांगost,
		      काष्ठा mem_cgroup_per_node, tree_node);
	/*
	 * Remove the node now but someone अन्यथा can add it back,
	 * we will to add it back at the end of reclaim to its correct
	 * position in the tree.
	 */
	__mem_cgroup_हटाओ_exceeded(mz, mctz);
	अगर (!soft_limit_excess(mz->memcg) ||
	    !css_tryget(&mz->memcg->css))
		जाओ retry;
करोne:
	वापस mz;
पूर्ण

अटल काष्ठा mem_cgroup_per_node *
mem_cgroup_largest_soft_limit_node(काष्ठा mem_cgroup_tree_per_node *mctz)
अणु
	काष्ठा mem_cgroup_per_node *mz;

	spin_lock_irq(&mctz->lock);
	mz = __mem_cgroup_largest_soft_limit_node(mctz);
	spin_unlock_irq(&mctz->lock);
	वापस mz;
पूर्ण

/**
 * __mod_memcg_state - update cgroup memory statistics
 * @memcg: the memory cgroup
 * @idx: the stat item - can be क्रमागत memcg_stat_item or क्रमागत node_stat_item
 * @val: delta to add to the counter, can be negative
 */
व्योम __mod_memcg_state(काष्ठा mem_cgroup *memcg, पूर्णांक idx, पूर्णांक val)
अणु
	अगर (mem_cgroup_disabled())
		वापस;

	__this_cpu_add(memcg->vmstats_percpu->state[idx], val);
	cgroup_rstat_updated(memcg->css.cgroup, smp_processor_id());
पूर्ण

/* idx can be of type क्रमागत memcg_stat_item or node_stat_item. */
अटल अचिन्हित दीर्घ memcg_page_state(काष्ठा mem_cgroup *memcg, पूर्णांक idx)
अणु
	दीर्घ x = READ_ONCE(memcg->vmstats.state[idx]);
#अगर_घोषित CONFIG_SMP
	अगर (x < 0)
		x = 0;
#पूर्ण_अगर
	वापस x;
पूर्ण

/* idx can be of type क्रमागत memcg_stat_item or node_stat_item. */
अटल अचिन्हित दीर्घ memcg_page_state_local(काष्ठा mem_cgroup *memcg, पूर्णांक idx)
अणु
	दीर्घ x = 0;
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		x += per_cpu(memcg->vmstats_percpu->state[idx], cpu);
#अगर_घोषित CONFIG_SMP
	अगर (x < 0)
		x = 0;
#पूर्ण_अगर
	वापस x;
पूर्ण

अटल काष्ठा mem_cgroup_per_node *
parent_nodeinfo(काष्ठा mem_cgroup_per_node *pn, पूर्णांक nid)
अणु
	काष्ठा mem_cgroup *parent;

	parent = parent_mem_cgroup(pn->memcg);
	अगर (!parent)
		वापस शून्य;
	वापस parent->nodeinfo[nid];
पूर्ण

व्योम __mod_memcg_lruvec_state(काष्ठा lruvec *lruvec, क्रमागत node_stat_item idx,
			      पूर्णांक val)
अणु
	काष्ठा mem_cgroup_per_node *pn;
	काष्ठा mem_cgroup *memcg;
	दीर्घ x, threshold = MEMCG_CHARGE_BATCH;

	pn = container_of(lruvec, काष्ठा mem_cgroup_per_node, lruvec);
	memcg = pn->memcg;

	/* Update memcg */
	__mod_memcg_state(memcg, idx, val);

	/* Update lruvec */
	__this_cpu_add(pn->lruvec_stat_local->count[idx], val);

	अगर (vmstat_item_in_bytes(idx))
		threshold <<= PAGE_SHIFT;

	x = val + __this_cpu_पढ़ो(pn->lruvec_stat_cpu->count[idx]);
	अगर (unlikely(असल(x) > threshold)) अणु
		pg_data_t *pgdat = lruvec_pgdat(lruvec);
		काष्ठा mem_cgroup_per_node *pi;

		क्रम (pi = pn; pi; pi = parent_nodeinfo(pi, pgdat->node_id))
			atomic_दीर्घ_add(x, &pi->lruvec_stat[idx]);
		x = 0;
	पूर्ण
	__this_cpu_ग_लिखो(pn->lruvec_stat_cpu->count[idx], x);
पूर्ण

/**
 * __mod_lruvec_state - update lruvec memory statistics
 * @lruvec: the lruvec
 * @idx: the stat item
 * @val: delta to add to the counter, can be negative
 *
 * The lruvec is the पूर्णांकersection of the NUMA node and a cgroup. This
 * function updates the all three counters that are affected by a
 * change of state at this level: per-node, per-cgroup, per-lruvec.
 */
व्योम __mod_lruvec_state(काष्ठा lruvec *lruvec, क्रमागत node_stat_item idx,
			पूर्णांक val)
अणु
	/* Update node */
	__mod_node_page_state(lruvec_pgdat(lruvec), idx, val);

	/* Update memcg and lruvec */
	अगर (!mem_cgroup_disabled())
		__mod_memcg_lruvec_state(lruvec, idx, val);
पूर्ण

व्योम __mod_lruvec_page_state(काष्ठा page *page, क्रमागत node_stat_item idx,
			     पूर्णांक val)
अणु
	काष्ठा page *head = compound_head(page); /* rmap on tail pages */
	काष्ठा mem_cgroup *memcg;
	pg_data_t *pgdat = page_pgdat(page);
	काष्ठा lruvec *lruvec;

	rcu_पढ़ो_lock();
	memcg = page_memcg(head);
	/* Untracked pages have no memcg, no lruvec. Update only the node */
	अगर (!memcg) अणु
		rcu_पढ़ो_unlock();
		__mod_node_page_state(pgdat, idx, val);
		वापस;
	पूर्ण

	lruvec = mem_cgroup_lruvec(memcg, pgdat);
	__mod_lruvec_state(lruvec, idx, val);
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(__mod_lruvec_page_state);

व्योम __mod_lruvec_kmem_state(व्योम *p, क्रमागत node_stat_item idx, पूर्णांक val)
अणु
	pg_data_t *pgdat = page_pgdat(virt_to_page(p));
	काष्ठा mem_cgroup *memcg;
	काष्ठा lruvec *lruvec;

	rcu_पढ़ो_lock();
	memcg = mem_cgroup_from_obj(p);

	/*
	 * Untracked pages have no memcg, no lruvec. Update only the
	 * node. If we reparent the slab objects to the root memcg,
	 * when we मुक्त the slab object, we need to update the per-memcg
	 * vmstats to keep it correct क्रम the root memcg.
	 */
	अगर (!memcg) अणु
		__mod_node_page_state(pgdat, idx, val);
	पूर्ण अन्यथा अणु
		lruvec = mem_cgroup_lruvec(memcg, pgdat);
		__mod_lruvec_state(lruvec, idx, val);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * __count_memcg_events - account VM events in a cgroup
 * @memcg: the memory cgroup
 * @idx: the event item
 * @count: the number of events that occurred
 */
व्योम __count_memcg_events(काष्ठा mem_cgroup *memcg, क्रमागत vm_event_item idx,
			  अचिन्हित दीर्घ count)
अणु
	अगर (mem_cgroup_disabled())
		वापस;

	__this_cpu_add(memcg->vmstats_percpu->events[idx], count);
	cgroup_rstat_updated(memcg->css.cgroup, smp_processor_id());
पूर्ण

अटल अचिन्हित दीर्घ memcg_events(काष्ठा mem_cgroup *memcg, पूर्णांक event)
अणु
	वापस READ_ONCE(memcg->vmstats.events[event]);
पूर्ण

अटल अचिन्हित दीर्घ memcg_events_local(काष्ठा mem_cgroup *memcg, पूर्णांक event)
अणु
	दीर्घ x = 0;
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		x += per_cpu(memcg->vmstats_percpu->events[event], cpu);
	वापस x;
पूर्ण

अटल व्योम mem_cgroup_अक्षरge_statistics(काष्ठा mem_cgroup *memcg,
					 काष्ठा page *page,
					 पूर्णांक nr_pages)
अणु
	/* pagein of a big page is an event. So, ignore page size */
	अगर (nr_pages > 0)
		__count_memcg_events(memcg, PGPGIN, 1);
	अन्यथा अणु
		__count_memcg_events(memcg, PGPGOUT, 1);
		nr_pages = -nr_pages; /* क्रम event */
	पूर्ण

	__this_cpu_add(memcg->vmstats_percpu->nr_page_events, nr_pages);
पूर्ण

अटल bool mem_cgroup_event_ratelimit(काष्ठा mem_cgroup *memcg,
				       क्रमागत mem_cgroup_events_target target)
अणु
	अचिन्हित दीर्घ val, next;

	val = __this_cpu_पढ़ो(memcg->vmstats_percpu->nr_page_events);
	next = __this_cpu_पढ़ो(memcg->vmstats_percpu->tarमाला_लो[target]);
	/* from समय_after() in jअगरfies.h */
	अगर ((दीर्घ)(next - val) < 0) अणु
		चयन (target) अणु
		हाल MEM_CGROUP_TARGET_THRESH:
			next = val + THRESHOLDS_EVENTS_TARGET;
			अवरोध;
		हाल MEM_CGROUP_TARGET_SOFTLIMIT:
			next = val + SOFTLIMIT_EVENTS_TARGET;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		__this_cpu_ग_लिखो(memcg->vmstats_percpu->tarमाला_लो[target], next);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * Check events in order.
 *
 */
अटल व्योम memcg_check_events(काष्ठा mem_cgroup *memcg, काष्ठा page *page)
अणु
	/* threshold event is triggered in finer grain than soft limit */
	अगर (unlikely(mem_cgroup_event_ratelimit(memcg,
						MEM_CGROUP_TARGET_THRESH))) अणु
		bool करो_softlimit;

		करो_softlimit = mem_cgroup_event_ratelimit(memcg,
						MEM_CGROUP_TARGET_SOFTLIMIT);
		mem_cgroup_threshold(memcg);
		अगर (unlikely(करो_softlimit))
			mem_cgroup_update_tree(memcg, page);
	पूर्ण
पूर्ण

काष्ठा mem_cgroup *mem_cgroup_from_task(काष्ठा task_काष्ठा *p)
अणु
	/*
	 * mm_update_next_owner() may clear mm->owner to शून्य
	 * अगर it races with swapoff, page migration, etc.
	 * So this can be called with p == शून्य.
	 */
	अगर (unlikely(!p))
		वापस शून्य;

	वापस mem_cgroup_from_css(task_css(p, memory_cgrp_id));
पूर्ण
EXPORT_SYMBOL(mem_cgroup_from_task);

/**
 * get_mem_cgroup_from_mm: Obtain a reference on given mm_काष्ठा's memcg.
 * @mm: mm from which memcg should be extracted. It can be शून्य.
 *
 * Obtain a reference on mm->memcg and वापसs it अगर successful. Otherwise
 * root_mem_cgroup is वापसed. However अगर mem_cgroup is disabled, शून्य is
 * वापसed.
 */
काष्ठा mem_cgroup *get_mem_cgroup_from_mm(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा mem_cgroup *memcg;

	अगर (mem_cgroup_disabled())
		वापस शून्य;

	rcu_पढ़ो_lock();
	करो अणु
		/*
		 * Page cache insertions can happen without an
		 * actual mm context, e.g. during disk probing
		 * on boot, loopback IO, acct() ग_लिखोs etc.
		 */
		अगर (unlikely(!mm))
			memcg = root_mem_cgroup;
		अन्यथा अणु
			memcg = mem_cgroup_from_task(rcu_dereference(mm->owner));
			अगर (unlikely(!memcg))
				memcg = root_mem_cgroup;
		पूर्ण
	पूर्ण जबतक (!css_tryget(&memcg->css));
	rcu_पढ़ो_unlock();
	वापस memcg;
पूर्ण
EXPORT_SYMBOL(get_mem_cgroup_from_mm);

अटल __always_अंतरभूत काष्ठा mem_cgroup *active_memcg(व्योम)
अणु
	अगर (in_पूर्णांकerrupt())
		वापस this_cpu_पढ़ो(पूर्णांक_active_memcg);
	अन्यथा
		वापस current->active_memcg;
पूर्ण

अटल __always_अंतरभूत bool memcg_kmem_bypass(व्योम)
अणु
	/* Allow remote memcg अक्षरging from any context. */
	अगर (unlikely(active_memcg()))
		वापस false;

	/* Memcg to अक्षरge can't be determined. */
	अगर (in_पूर्णांकerrupt() || !current->mm || (current->flags & PF_KTHREAD))
		वापस true;

	वापस false;
पूर्ण

/**
 * mem_cgroup_iter - iterate over memory cgroup hierarchy
 * @root: hierarchy root
 * @prev: previously वापसed memcg, शून्य on first invocation
 * @reclaim: cookie क्रम shared reclaim walks, शून्य क्रम full walks
 *
 * Returns references to children of the hierarchy below @root, or
 * @root itself, or %शून्य after a full round-trip.
 *
 * Caller must pass the वापस value in @prev on subsequent
 * invocations क्रम reference counting, or use mem_cgroup_iter_अवरोध()
 * to cancel a hierarchy walk beक्रमe the round-trip is complete.
 *
 * Reclaimers can specअगरy a node in @reclaim to भागide up the memcgs
 * in the hierarchy among all concurrent reclaimers operating on the
 * same node.
 */
काष्ठा mem_cgroup *mem_cgroup_iter(काष्ठा mem_cgroup *root,
				   काष्ठा mem_cgroup *prev,
				   काष्ठा mem_cgroup_reclaim_cookie *reclaim)
अणु
	काष्ठा mem_cgroup_reclaim_iter *iter;
	काष्ठा cgroup_subsys_state *css = शून्य;
	काष्ठा mem_cgroup *memcg = शून्य;
	काष्ठा mem_cgroup *pos = शून्य;

	अगर (mem_cgroup_disabled())
		वापस शून्य;

	अगर (!root)
		root = root_mem_cgroup;

	अगर (prev && !reclaim)
		pos = prev;

	rcu_पढ़ो_lock();

	अगर (reclaim) अणु
		काष्ठा mem_cgroup_per_node *mz;

		mz = root->nodeinfo[reclaim->pgdat->node_id];
		iter = &mz->iter;

		अगर (prev && reclaim->generation != iter->generation)
			जाओ out_unlock;

		जबतक (1) अणु
			pos = READ_ONCE(iter->position);
			अगर (!pos || css_tryget(&pos->css))
				अवरोध;
			/*
			 * css reference reached zero, so iter->position will
			 * be cleared by ->css_released. However, we should not
			 * rely on this happening soon, because ->css_released
			 * is called from a work queue, and by busy-रुकोing we
			 * might block it. So we clear iter->position right
			 * away.
			 */
			(व्योम)cmpxchg(&iter->position, pos, शून्य);
		पूर्ण
	पूर्ण

	अगर (pos)
		css = &pos->css;

	क्रम (;;) अणु
		css = css_next_descendant_pre(css, &root->css);
		अगर (!css) अणु
			/*
			 * Reclaimers share the hierarchy walk, and a
			 * new one might jump in right at the end of
			 * the hierarchy - make sure they see at least
			 * one group and restart from the beginning.
			 */
			अगर (!prev)
				जारी;
			अवरोध;
		पूर्ण

		/*
		 * Verअगरy the css and acquire a reference.  The root
		 * is provided by the caller, so we know it's alive
		 * and kicking, and करोn't take an extra reference.
		 */
		memcg = mem_cgroup_from_css(css);

		अगर (css == &root->css)
			अवरोध;

		अगर (css_tryget(css))
			अवरोध;

		memcg = शून्य;
	पूर्ण

	अगर (reclaim) अणु
		/*
		 * The position could have alपढ़ोy been updated by a competing
		 * thपढ़ो, so check that the value hasn't changed since we पढ़ो
		 * it to aव्योम reclaiming from the same cgroup twice.
		 */
		(व्योम)cmpxchg(&iter->position, pos, memcg);

		अगर (pos)
			css_put(&pos->css);

		अगर (!memcg)
			iter->generation++;
		अन्यथा अगर (!prev)
			reclaim->generation = iter->generation;
	पूर्ण

out_unlock:
	rcu_पढ़ो_unlock();
	अगर (prev && prev != root)
		css_put(&prev->css);

	वापस memcg;
पूर्ण

/**
 * mem_cgroup_iter_अवरोध - पात a hierarchy walk prematurely
 * @root: hierarchy root
 * @prev: last visited hierarchy member as वापसed by mem_cgroup_iter()
 */
व्योम mem_cgroup_iter_अवरोध(काष्ठा mem_cgroup *root,
			   काष्ठा mem_cgroup *prev)
अणु
	अगर (!root)
		root = root_mem_cgroup;
	अगर (prev && prev != root)
		css_put(&prev->css);
पूर्ण

अटल व्योम __invalidate_reclaim_iterators(काष्ठा mem_cgroup *from,
					काष्ठा mem_cgroup *dead_memcg)
अणु
	काष्ठा mem_cgroup_reclaim_iter *iter;
	काष्ठा mem_cgroup_per_node *mz;
	पूर्णांक nid;

	क्रम_each_node(nid) अणु
		mz = from->nodeinfo[nid];
		iter = &mz->iter;
		cmpxchg(&iter->position, dead_memcg, शून्य);
	पूर्ण
पूर्ण

अटल व्योम invalidate_reclaim_iterators(काष्ठा mem_cgroup *dead_memcg)
अणु
	काष्ठा mem_cgroup *memcg = dead_memcg;
	काष्ठा mem_cgroup *last;

	करो अणु
		__invalidate_reclaim_iterators(memcg, dead_memcg);
		last = memcg;
	पूर्ण जबतक ((memcg = parent_mem_cgroup(memcg)));

	/*
	 * When cgruop1 non-hierarchy mode is used,
	 * parent_mem_cgroup() करोes not walk all the way up to the
	 * cgroup root (root_mem_cgroup). So we have to handle
	 * dead_memcg from cgroup root separately.
	 */
	अगर (last != root_mem_cgroup)
		__invalidate_reclaim_iterators(root_mem_cgroup,
						dead_memcg);
पूर्ण

/**
 * mem_cgroup_scan_tasks - iterate over tasks of a memory cgroup hierarchy
 * @memcg: hierarchy root
 * @fn: function to call क्रम each task
 * @arg: argument passed to @fn
 *
 * This function iterates over tasks attached to @memcg or to any of its
 * descendants and calls @fn क्रम each task. If @fn वापसs a non-zero
 * value, the function अवरोधs the iteration loop and वापसs the value.
 * Otherwise, it will iterate over all tasks and वापस 0.
 *
 * This function must not be called क्रम the root memory cgroup.
 */
पूर्णांक mem_cgroup_scan_tasks(काष्ठा mem_cgroup *memcg,
			  पूर्णांक (*fn)(काष्ठा task_काष्ठा *, व्योम *), व्योम *arg)
अणु
	काष्ठा mem_cgroup *iter;
	पूर्णांक ret = 0;

	BUG_ON(memcg == root_mem_cgroup);

	क्रम_each_mem_cgroup_tree(iter, memcg) अणु
		काष्ठा css_task_iter it;
		काष्ठा task_काष्ठा *task;

		css_task_iter_start(&iter->css, CSS_TASK_ITER_PROCS, &it);
		जबतक (!ret && (task = css_task_iter_next(&it)))
			ret = fn(task, arg);
		css_task_iter_end(&it);
		अगर (ret) अणु
			mem_cgroup_iter_अवरोध(memcg, iter);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_VM
व्योम lruvec_memcg_debug(काष्ठा lruvec *lruvec, काष्ठा page *page)
अणु
	काष्ठा mem_cgroup *memcg;

	अगर (mem_cgroup_disabled())
		वापस;

	memcg = page_memcg(page);

	अगर (!memcg)
		VM_BUG_ON_PAGE(lruvec_memcg(lruvec) != root_mem_cgroup, page);
	अन्यथा
		VM_BUG_ON_PAGE(lruvec_memcg(lruvec) != memcg, page);
पूर्ण
#पूर्ण_अगर

/**
 * lock_page_lruvec - lock and वापस lruvec क्रम a given page.
 * @page: the page
 *
 * These functions are safe to use under any of the following conditions:
 * - page locked
 * - PageLRU cleared
 * - lock_page_memcg()
 * - page->_refcount is zero
 */
काष्ठा lruvec *lock_page_lruvec(काष्ठा page *page)
अणु
	काष्ठा lruvec *lruvec;
	काष्ठा pglist_data *pgdat = page_pgdat(page);

	lruvec = mem_cgroup_page_lruvec(page, pgdat);
	spin_lock(&lruvec->lru_lock);

	lruvec_memcg_debug(lruvec, page);

	वापस lruvec;
पूर्ण

काष्ठा lruvec *lock_page_lruvec_irq(काष्ठा page *page)
अणु
	काष्ठा lruvec *lruvec;
	काष्ठा pglist_data *pgdat = page_pgdat(page);

	lruvec = mem_cgroup_page_lruvec(page, pgdat);
	spin_lock_irq(&lruvec->lru_lock);

	lruvec_memcg_debug(lruvec, page);

	वापस lruvec;
पूर्ण

काष्ठा lruvec *lock_page_lruvec_irqsave(काष्ठा page *page, अचिन्हित दीर्घ *flags)
अणु
	काष्ठा lruvec *lruvec;
	काष्ठा pglist_data *pgdat = page_pgdat(page);

	lruvec = mem_cgroup_page_lruvec(page, pgdat);
	spin_lock_irqsave(&lruvec->lru_lock, *flags);

	lruvec_memcg_debug(lruvec, page);

	वापस lruvec;
पूर्ण

/**
 * mem_cgroup_update_lru_size - account क्रम adding or removing an lru page
 * @lruvec: mem_cgroup per zone lru vector
 * @lru: index of lru list the page is sitting on
 * @zid: zone id of the accounted pages
 * @nr_pages: positive when adding or negative when removing
 *
 * This function must be called under lru_lock, just beक्रमe a page is added
 * to or just after a page is हटाओd from an lru list (that ordering being
 * so as to allow it to check that lru_size 0 is consistent with list_empty).
 */
व्योम mem_cgroup_update_lru_size(काष्ठा lruvec *lruvec, क्रमागत lru_list lru,
				पूर्णांक zid, पूर्णांक nr_pages)
अणु
	काष्ठा mem_cgroup_per_node *mz;
	अचिन्हित दीर्घ *lru_size;
	दीर्घ size;

	अगर (mem_cgroup_disabled())
		वापस;

	mz = container_of(lruvec, काष्ठा mem_cgroup_per_node, lruvec);
	lru_size = &mz->lru_zone_size[zid][lru];

	अगर (nr_pages < 0)
		*lru_size += nr_pages;

	size = *lru_size;
	अगर (WARN_ONCE(size < 0,
		"%s(%p, %d, %d): lru_size %ld\n",
		__func__, lruvec, lru, nr_pages, size)) अणु
		VM_BUG_ON(1);
		*lru_size = 0;
	पूर्ण

	अगर (nr_pages > 0)
		*lru_size += nr_pages;
पूर्ण

/**
 * mem_cgroup_margin - calculate अक्षरgeable space of a memory cgroup
 * @memcg: the memory cgroup
 *
 * Returns the maximum amount of memory @mem can be अक्षरged with, in
 * pages.
 */
अटल अचिन्हित दीर्घ mem_cgroup_margin(काष्ठा mem_cgroup *memcg)
अणु
	अचिन्हित दीर्घ margin = 0;
	अचिन्हित दीर्घ count;
	अचिन्हित दीर्घ limit;

	count = page_counter_पढ़ो(&memcg->memory);
	limit = READ_ONCE(memcg->memory.max);
	अगर (count < limit)
		margin = limit - count;

	अगर (करो_memsw_account()) अणु
		count = page_counter_पढ़ो(&memcg->memsw);
		limit = READ_ONCE(memcg->memsw.max);
		अगर (count < limit)
			margin = min(margin, limit - count);
		अन्यथा
			margin = 0;
	पूर्ण

	वापस margin;
पूर्ण

/*
 * A routine क्रम checking "mem" is under move_account() or not.
 *
 * Checking a cgroup is mc.from or mc.to or under hierarchy of
 * moving cgroups. This is क्रम रुकोing at high-memory pressure
 * caused by "move".
 */
अटल bool mem_cgroup_under_move(काष्ठा mem_cgroup *memcg)
अणु
	काष्ठा mem_cgroup *from;
	काष्ठा mem_cgroup *to;
	bool ret = false;
	/*
	 * Unlike task_move routines, we access mc.to, mc.from not under
	 * mutual exclusion by cgroup_mutex. Here, we take spinlock instead.
	 */
	spin_lock(&mc.lock);
	from = mc.from;
	to = mc.to;
	अगर (!from)
		जाओ unlock;

	ret = mem_cgroup_is_descendant(from, memcg) ||
		mem_cgroup_is_descendant(to, memcg);
unlock:
	spin_unlock(&mc.lock);
	वापस ret;
पूर्ण

अटल bool mem_cgroup_रुको_acct_move(काष्ठा mem_cgroup *memcg)
अणु
	अगर (mc.moving_task && current != mc.moving_task) अणु
		अगर (mem_cgroup_under_move(memcg)) अणु
			DEFINE_WAIT(रुको);
			prepare_to_रुको(&mc.रुकोq, &रुको, TASK_INTERRUPTIBLE);
			/* moving अक्षरge context might have finished. */
			अगर (mc.moving_task)
				schedule();
			finish_रुको(&mc.रुकोq, &रुको);
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

काष्ठा memory_stat अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक idx;
पूर्ण;

अटल स्थिर काष्ठा memory_stat memory_stats[] = अणु
	अणु "anon",			NR_ANON_MAPPED			पूर्ण,
	अणु "file",			NR_खाता_PAGES			पूर्ण,
	अणु "kernel_stack",		NR_KERNEL_STACK_KB		पूर्ण,
	अणु "pagetables",			NR_PAGETABLE			पूर्ण,
	अणु "percpu",			MEMCG_PERCPU_B			पूर्ण,
	अणु "sock",			MEMCG_SOCK			पूर्ण,
	अणु "shmem",			NR_SHMEM			पूर्ण,
	अणु "file_mapped",		NR_खाता_MAPPED			पूर्ण,
	अणु "file_dirty",			NR_खाता_सूचीTY			पूर्ण,
	अणु "file_writeback",		NR_WRITEBACK			पूर्ण,
#अगर_घोषित CONFIG_SWAP
	अणु "swapcached",			NR_SWAPCACHE			पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
	अणु "anon_thp",			NR_ANON_THPS			पूर्ण,
	अणु "file_thp",			NR_खाता_THPS			पूर्ण,
	अणु "shmem_thp",			NR_SHMEM_THPS			पूर्ण,
#पूर्ण_अगर
	अणु "inactive_anon",		NR_INACTIVE_ANON		पूर्ण,
	अणु "active_anon",		NR_ACTIVE_ANON			पूर्ण,
	अणु "inactive_file",		NR_INACTIVE_खाता		पूर्ण,
	अणु "active_file",		NR_ACTIVE_खाता			पूर्ण,
	अणु "unevictable",		NR_UNEVICTABLE			पूर्ण,
	अणु "slab_reclaimable",		NR_SLAB_RECLAIMABLE_B		पूर्ण,
	अणु "slab_unreclaimable",		NR_SLAB_UNRECLAIMABLE_B		पूर्ण,

	/* The memory events */
	अणु "workingset_refault_anon",	WORKINGSET_REFAULT_ANON		पूर्ण,
	अणु "workingset_refault_file",	WORKINGSET_REFAULT_खाता		पूर्ण,
	अणु "workingset_activate_anon",	WORKINGSET_ACTIVATE_ANON	पूर्ण,
	अणु "workingset_activate_file",	WORKINGSET_ACTIVATE_खाता	पूर्ण,
	अणु "workingset_restore_anon",	WORKINGSET_RESTORE_ANON		पूर्ण,
	अणु "workingset_restore_file",	WORKINGSET_RESTORE_खाता		पूर्ण,
	अणु "workingset_nodereclaim",	WORKINGSET_NODERECLAIM		पूर्ण,
पूर्ण;

/* Translate stat items to the correct unit क्रम memory.stat output */
अटल पूर्णांक memcg_page_state_unit(पूर्णांक item)
अणु
	चयन (item) अणु
	हाल MEMCG_PERCPU_B:
	हाल NR_SLAB_RECLAIMABLE_B:
	हाल NR_SLAB_UNRECLAIMABLE_B:
	हाल WORKINGSET_REFAULT_ANON:
	हाल WORKINGSET_REFAULT_खाता:
	हाल WORKINGSET_ACTIVATE_ANON:
	हाल WORKINGSET_ACTIVATE_खाता:
	हाल WORKINGSET_RESTORE_ANON:
	हाल WORKINGSET_RESTORE_खाता:
	हाल WORKINGSET_NODERECLAIM:
		वापस 1;
	हाल NR_KERNEL_STACK_KB:
		वापस SZ_1K;
	शेष:
		वापस PAGE_SIZE;
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ memcg_page_state_output(काष्ठा mem_cgroup *memcg,
						    पूर्णांक item)
अणु
	वापस memcg_page_state(memcg, item) * memcg_page_state_unit(item);
पूर्ण

अटल अक्षर *memory_stat_क्रमmat(काष्ठा mem_cgroup *memcg)
अणु
	काष्ठा seq_buf s;
	पूर्णांक i;

	seq_buf_init(&s, kदो_स्मृति(PAGE_SIZE, GFP_KERNEL), PAGE_SIZE);
	अगर (!s.buffer)
		वापस शून्य;

	/*
	 * Provide statistics on the state of the memory subप्रणाली as
	 * well as cumulative event counters that show past behavior.
	 *
	 * This list is ordered following a combination of these gradients:
	 * 1) generic big picture -> specअगरics and details
	 * 2) reflecting userspace activity -> reflecting kernel heuristics
	 *
	 * Current memory state:
	 */
	cgroup_rstat_flush(memcg->css.cgroup);

	क्रम (i = 0; i < ARRAY_SIZE(memory_stats); i++) अणु
		u64 size;

		size = memcg_page_state_output(memcg, memory_stats[i].idx);
		seq_buf_म_लिखो(&s, "%s %llu\n", memory_stats[i].name, size);

		अगर (unlikely(memory_stats[i].idx == NR_SLAB_UNRECLAIMABLE_B)) अणु
			size += memcg_page_state_output(memcg,
							NR_SLAB_RECLAIMABLE_B);
			seq_buf_म_लिखो(&s, "slab %llu\n", size);
		पूर्ण
	पूर्ण

	/* Accumulated memory events */

	seq_buf_म_लिखो(&s, "%s %lu\n", vm_event_name(PGFAULT),
		       memcg_events(memcg, PGFAULT));
	seq_buf_म_लिखो(&s, "%s %lu\n", vm_event_name(PGMAJFAULT),
		       memcg_events(memcg, PGMAJFAULT));
	seq_buf_म_लिखो(&s, "%s %lu\n",  vm_event_name(PGREFILL),
		       memcg_events(memcg, PGREFILL));
	seq_buf_म_लिखो(&s, "pgscan %lu\n",
		       memcg_events(memcg, PGSCAN_KSWAPD) +
		       memcg_events(memcg, PGSCAN_सूचीECT));
	seq_buf_म_लिखो(&s, "pgsteal %lu\n",
		       memcg_events(memcg, PGSTEAL_KSWAPD) +
		       memcg_events(memcg, PGSTEAL_सूचीECT));
	seq_buf_म_लिखो(&s, "%s %lu\n", vm_event_name(PGACTIVATE),
		       memcg_events(memcg, PGACTIVATE));
	seq_buf_म_लिखो(&s, "%s %lu\n", vm_event_name(PGDEACTIVATE),
		       memcg_events(memcg, PGDEACTIVATE));
	seq_buf_म_लिखो(&s, "%s %lu\n", vm_event_name(PGLAZYFREE),
		       memcg_events(memcg, PGLAZYFREE));
	seq_buf_म_लिखो(&s, "%s %lu\n", vm_event_name(PGLAZYFREED),
		       memcg_events(memcg, PGLAZYFREED));

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
	seq_buf_म_लिखो(&s, "%s %lu\n", vm_event_name(THP_FAULT_ALLOC),
		       memcg_events(memcg, THP_FAULT_ALLOC));
	seq_buf_म_लिखो(&s, "%s %lu\n", vm_event_name(THP_COLLAPSE_ALLOC),
		       memcg_events(memcg, THP_COLLAPSE_ALLOC));
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */

	/* The above should easily fit पूर्णांकo one page */
	WARN_ON_ONCE(seq_buf_has_overflowed(&s));

	वापस s.buffer;
पूर्ण

#घोषणा K(x) ((x) << (PAGE_SHIFT-10))
/**
 * mem_cgroup_prपूर्णांक_oom_context: Prपूर्णांक OOM inक्रमmation relevant to
 * memory controller.
 * @memcg: The memory cgroup that went over limit
 * @p: Task that is going to be समाप्तed
 *
 * NOTE: @memcg and @p's mem_cgroup can be dअगरferent when hierarchy is
 * enabled
 */
व्योम mem_cgroup_prपूर्णांक_oom_context(काष्ठा mem_cgroup *memcg, काष्ठा task_काष्ठा *p)
अणु
	rcu_पढ़ो_lock();

	अगर (memcg) अणु
		pr_cont(",oom_memcg=");
		pr_cont_cgroup_path(memcg->css.cgroup);
	पूर्ण अन्यथा
		pr_cont(",global_oom");
	अगर (p) अणु
		pr_cont(",task_memcg=");
		pr_cont_cgroup_path(task_cgroup(p, memory_cgrp_id));
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * mem_cgroup_prपूर्णांक_oom_meminfo: Prपूर्णांक OOM memory inक्रमmation relevant to
 * memory controller.
 * @memcg: The memory cgroup that went over limit
 */
व्योम mem_cgroup_prपूर्णांक_oom_meminfo(काष्ठा mem_cgroup *memcg)
अणु
	अक्षर *buf;

	pr_info("memory: usage %llukB, limit %llukB, failcnt %lu\n",
		K((u64)page_counter_पढ़ो(&memcg->memory)),
		K((u64)READ_ONCE(memcg->memory.max)), memcg->memory.failcnt);
	अगर (cgroup_subsys_on_dfl(memory_cgrp_subsys))
		pr_info("swap: usage %llukB, limit %llukB, failcnt %lu\n",
			K((u64)page_counter_पढ़ो(&memcg->swap)),
			K((u64)READ_ONCE(memcg->swap.max)), memcg->swap.failcnt);
	अन्यथा अणु
		pr_info("memory+swap: usage %llukB, limit %llukB, failcnt %lu\n",
			K((u64)page_counter_पढ़ो(&memcg->memsw)),
			K((u64)memcg->memsw.max), memcg->memsw.failcnt);
		pr_info("kmem: usage %llukB, limit %llukB, failcnt %lu\n",
			K((u64)page_counter_पढ़ो(&memcg->kmem)),
			K((u64)memcg->kmem.max), memcg->kmem.failcnt);
	पूर्ण

	pr_info("Memory cgroup stats for ");
	pr_cont_cgroup_path(memcg->css.cgroup);
	pr_cont(":");
	buf = memory_stat_क्रमmat(memcg);
	अगर (!buf)
		वापस;
	pr_info("%s", buf);
	kमुक्त(buf);
पूर्ण

/*
 * Return the memory (and swap, अगर configured) limit क्रम a memcg.
 */
अचिन्हित दीर्घ mem_cgroup_get_max(काष्ठा mem_cgroup *memcg)
अणु
	अचिन्हित दीर्घ max = READ_ONCE(memcg->memory.max);

	अगर (cgroup_subsys_on_dfl(memory_cgrp_subsys)) अणु
		अगर (mem_cgroup_swappiness(memcg))
			max += min(READ_ONCE(memcg->swap.max),
				   (अचिन्हित दीर्घ)total_swap_pages);
	पूर्ण अन्यथा अणु /* v1 */
		अगर (mem_cgroup_swappiness(memcg)) अणु
			/* Calculate swap excess capacity from memsw limit */
			अचिन्हित दीर्घ swap = READ_ONCE(memcg->memsw.max) - max;

			max += min(swap, (अचिन्हित दीर्घ)total_swap_pages);
		पूर्ण
	पूर्ण
	वापस max;
पूर्ण

अचिन्हित दीर्घ mem_cgroup_size(काष्ठा mem_cgroup *memcg)
अणु
	वापस page_counter_पढ़ो(&memcg->memory);
पूर्ण

अटल bool mem_cgroup_out_of_memory(काष्ठा mem_cgroup *memcg, gfp_t gfp_mask,
				     पूर्णांक order)
अणु
	काष्ठा oom_control oc = अणु
		.zonelist = शून्य,
		.nodemask = शून्य,
		.memcg = memcg,
		.gfp_mask = gfp_mask,
		.order = order,
	पूर्ण;
	bool ret = true;

	अगर (mutex_lock_समाप्तable(&oom_lock))
		वापस true;

	अगर (mem_cgroup_margin(memcg) >= (1 << order))
		जाओ unlock;

	/*
	 * A few thपढ़ोs which were not रुकोing at mutex_lock_समाप्तable() can
	 * fail to bail out. Thereक्रमe, check again after holding oom_lock.
	 */
	ret = should_क्रमce_अक्षरge() || out_of_memory(&oc);

unlock:
	mutex_unlock(&oom_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक mem_cgroup_soft_reclaim(काष्ठा mem_cgroup *root_memcg,
				   pg_data_t *pgdat,
				   gfp_t gfp_mask,
				   अचिन्हित दीर्घ *total_scanned)
अणु
	काष्ठा mem_cgroup *victim = शून्य;
	पूर्णांक total = 0;
	पूर्णांक loop = 0;
	अचिन्हित दीर्घ excess;
	अचिन्हित दीर्घ nr_scanned;
	काष्ठा mem_cgroup_reclaim_cookie reclaim = अणु
		.pgdat = pgdat,
	पूर्ण;

	excess = soft_limit_excess(root_memcg);

	जबतक (1) अणु
		victim = mem_cgroup_iter(root_memcg, victim, &reclaim);
		अगर (!victim) अणु
			loop++;
			अगर (loop >= 2) अणु
				/*
				 * If we have not been able to reclaim
				 * anything, it might because there are
				 * no reclaimable pages under this hierarchy
				 */
				अगर (!total)
					अवरोध;
				/*
				 * We want to करो more targeted reclaim.
				 * excess >> 2 is not to excessive so as to
				 * reclaim too much, nor too less that we keep
				 * coming back to reclaim from this cgroup
				 */
				अगर (total >= (excess >> 2) ||
					(loop > MEM_CGROUP_MAX_RECLAIM_LOOPS))
					अवरोध;
			पूर्ण
			जारी;
		पूर्ण
		total += mem_cgroup_shrink_node(victim, gfp_mask, false,
					pgdat, &nr_scanned);
		*total_scanned += nr_scanned;
		अगर (!soft_limit_excess(root_memcg))
			अवरोध;
	पूर्ण
	mem_cgroup_iter_अवरोध(root_memcg, victim);
	वापस total;
पूर्ण

#अगर_घोषित CONFIG_LOCKDEP
अटल काष्ठा lockdep_map memcg_oom_lock_dep_map = अणु
	.name = "memcg_oom_lock",
पूर्ण;
#पूर्ण_अगर

अटल DEFINE_SPINLOCK(memcg_oom_lock);

/*
 * Check OOM-Killer is alपढ़ोy running under our hierarchy.
 * If someone is running, वापस false.
 */
अटल bool mem_cgroup_oom_trylock(काष्ठा mem_cgroup *memcg)
अणु
	काष्ठा mem_cgroup *iter, *failed = शून्य;

	spin_lock(&memcg_oom_lock);

	क्रम_each_mem_cgroup_tree(iter, memcg) अणु
		अगर (iter->oom_lock) अणु
			/*
			 * this subtree of our hierarchy is alपढ़ोy locked
			 * so we cannot give a lock.
			 */
			failed = iter;
			mem_cgroup_iter_अवरोध(memcg, iter);
			अवरोध;
		पूर्ण अन्यथा
			iter->oom_lock = true;
	पूर्ण

	अगर (failed) अणु
		/*
		 * OK, we failed to lock the whole subtree so we have
		 * to clean up what we set up to the failing subtree
		 */
		क्रम_each_mem_cgroup_tree(iter, memcg) अणु
			अगर (iter == failed) अणु
				mem_cgroup_iter_अवरोध(memcg, iter);
				अवरोध;
			पूर्ण
			iter->oom_lock = false;
		पूर्ण
	पूर्ण अन्यथा
		mutex_acquire(&memcg_oom_lock_dep_map, 0, 1, _RET_IP_);

	spin_unlock(&memcg_oom_lock);

	वापस !failed;
पूर्ण

अटल व्योम mem_cgroup_oom_unlock(काष्ठा mem_cgroup *memcg)
अणु
	काष्ठा mem_cgroup *iter;

	spin_lock(&memcg_oom_lock);
	mutex_release(&memcg_oom_lock_dep_map, _RET_IP_);
	क्रम_each_mem_cgroup_tree(iter, memcg)
		iter->oom_lock = false;
	spin_unlock(&memcg_oom_lock);
पूर्ण

अटल व्योम mem_cgroup_mark_under_oom(काष्ठा mem_cgroup *memcg)
अणु
	काष्ठा mem_cgroup *iter;

	spin_lock(&memcg_oom_lock);
	क्रम_each_mem_cgroup_tree(iter, memcg)
		iter->under_oom++;
	spin_unlock(&memcg_oom_lock);
पूर्ण

अटल व्योम mem_cgroup_unmark_under_oom(काष्ठा mem_cgroup *memcg)
अणु
	काष्ठा mem_cgroup *iter;

	/*
	 * Be careful about under_oom underflows because a child memcg
	 * could have been added after mem_cgroup_mark_under_oom.
	 */
	spin_lock(&memcg_oom_lock);
	क्रम_each_mem_cgroup_tree(iter, memcg)
		अगर (iter->under_oom > 0)
			iter->under_oom--;
	spin_unlock(&memcg_oom_lock);
पूर्ण

अटल DECLARE_WAIT_QUEUE_HEAD(memcg_oom_रुकोq);

काष्ठा oom_रुको_info अणु
	काष्ठा mem_cgroup *memcg;
	रुको_queue_entry_t	रुको;
पूर्ण;

अटल पूर्णांक memcg_oom_wake_function(रुको_queue_entry_t *रुको,
	अचिन्हित mode, पूर्णांक sync, व्योम *arg)
अणु
	काष्ठा mem_cgroup *wake_memcg = (काष्ठा mem_cgroup *)arg;
	काष्ठा mem_cgroup *oom_रुको_memcg;
	काष्ठा oom_रुको_info *oom_रुको_info;

	oom_रुको_info = container_of(रुको, काष्ठा oom_रुको_info, रुको);
	oom_रुको_memcg = oom_रुको_info->memcg;

	अगर (!mem_cgroup_is_descendant(wake_memcg, oom_रुको_memcg) &&
	    !mem_cgroup_is_descendant(oom_रुको_memcg, wake_memcg))
		वापस 0;
	वापस स्वतःहटाओ_wake_function(रुको, mode, sync, arg);
पूर्ण

अटल व्योम memcg_oom_recover(काष्ठा mem_cgroup *memcg)
अणु
	/*
	 * For the following lockless ->under_oom test, the only required
	 * guarantee is that it must see the state निश्चितed by an OOM when
	 * this function is called as a result of userland actions
	 * triggered by the notअगरication of the OOM.  This is trivially
	 * achieved by invoking mem_cgroup_mark_under_oom() beक्रमe
	 * triggering notअगरication.
	 */
	अगर (memcg && memcg->under_oom)
		__wake_up(&memcg_oom_रुकोq, TASK_NORMAL, 0, memcg);
पूर्ण

क्रमागत oom_status अणु
	OOM_SUCCESS,
	OOM_FAILED,
	OOM_ASYNC,
	OOM_SKIPPED
पूर्ण;

अटल क्रमागत oom_status mem_cgroup_oom(काष्ठा mem_cgroup *memcg, gfp_t mask, पूर्णांक order)
अणु
	क्रमागत oom_status ret;
	bool locked;

	अगर (order > PAGE_ALLOC_COSTLY_ORDER)
		वापस OOM_SKIPPED;

	memcg_memory_event(memcg, MEMCG_OOM);

	/*
	 * We are in the middle of the अक्षरge context here, so we
	 * करोn't want to block when potentially sitting on a callstack
	 * that holds all kinds of fileप्रणाली and mm locks.
	 *
	 * cgroup1 allows disabling the OOM समाप्तer and रुकोing क्रम outside
	 * handling until the अक्षरge can succeed; remember the context and put
	 * the task to sleep at the end of the page fault when all locks are
	 * released.
	 *
	 * On the other hand, in-kernel OOM समाप्तer allows क्रम an async victim
	 * memory reclaim (oom_reaper) and that means that we are not solely
	 * relying on the oom victim to make a क्रमward progress and we can
	 * invoke the oom समाप्तer here.
	 *
	 * Please note that mem_cgroup_out_of_memory might fail to find a
	 * victim and then we have to bail out from the अक्षरge path.
	 */
	अगर (memcg->oom_समाप्त_disable) अणु
		अगर (!current->in_user_fault)
			वापस OOM_SKIPPED;
		css_get(&memcg->css);
		current->memcg_in_oom = memcg;
		current->memcg_oom_gfp_mask = mask;
		current->memcg_oom_order = order;

		वापस OOM_ASYNC;
	पूर्ण

	mem_cgroup_mark_under_oom(memcg);

	locked = mem_cgroup_oom_trylock(memcg);

	अगर (locked)
		mem_cgroup_oom_notअगरy(memcg);

	mem_cgroup_unmark_under_oom(memcg);
	अगर (mem_cgroup_out_of_memory(memcg, mask, order))
		ret = OOM_SUCCESS;
	अन्यथा
		ret = OOM_FAILED;

	अगर (locked)
		mem_cgroup_oom_unlock(memcg);

	वापस ret;
पूर्ण

/**
 * mem_cgroup_oom_synchronize - complete memcg OOM handling
 * @handle: actually समाप्त/रुको or just clean up the OOM state
 *
 * This has to be called at the end of a page fault अगर the memcg OOM
 * handler was enabled.
 *
 * Memcg supports userspace OOM handling where failed allocations must
 * sleep on a रुकोqueue until the userspace task resolves the
 * situation.  Sleeping directly in the अक्षरge context with all kinds
 * of locks held is not a good idea, instead we remember an OOM state
 * in the task and mem_cgroup_oom_synchronize() has to be called at
 * the end of the page fault to complete the OOM handling.
 *
 * Returns %true अगर an ongoing memcg OOM situation was detected and
 * completed, %false otherwise.
 */
bool mem_cgroup_oom_synchronize(bool handle)
अणु
	काष्ठा mem_cgroup *memcg = current->memcg_in_oom;
	काष्ठा oom_रुको_info oरुको;
	bool locked;

	/* OOM is global, करो not handle */
	अगर (!memcg)
		वापस false;

	अगर (!handle)
		जाओ cleanup;

	oरुको.memcg = memcg;
	oरुको.रुको.flags = 0;
	oरुको.रुको.func = memcg_oom_wake_function;
	oरुको.रुको.निजी = current;
	INIT_LIST_HEAD(&oरुको.रुको.entry);

	prepare_to_रुको(&memcg_oom_रुकोq, &oरुको.रुको, TASK_KILLABLE);
	mem_cgroup_mark_under_oom(memcg);

	locked = mem_cgroup_oom_trylock(memcg);

	अगर (locked)
		mem_cgroup_oom_notअगरy(memcg);

	अगर (locked && !memcg->oom_समाप्त_disable) अणु
		mem_cgroup_unmark_under_oom(memcg);
		finish_रुको(&memcg_oom_रुकोq, &oरुको.रुको);
		mem_cgroup_out_of_memory(memcg, current->memcg_oom_gfp_mask,
					 current->memcg_oom_order);
	पूर्ण अन्यथा अणु
		schedule();
		mem_cgroup_unmark_under_oom(memcg);
		finish_रुको(&memcg_oom_रुकोq, &oरुको.रुको);
	पूर्ण

	अगर (locked) अणु
		mem_cgroup_oom_unlock(memcg);
		/*
		 * There is no guarantee that an OOM-lock contender
		 * sees the wakeups triggered by the OOM समाप्त
		 * unअक्षरges.  Wake any sleepers explicitly.
		 */
		memcg_oom_recover(memcg);
	पूर्ण
cleanup:
	current->memcg_in_oom = शून्य;
	css_put(&memcg->css);
	वापस true;
पूर्ण

/**
 * mem_cgroup_get_oom_group - get a memory cgroup to clean up after OOM
 * @victim: task to be समाप्तed by the OOM समाप्तer
 * @oom_करोमुख्य: memcg in हाल of memcg OOM, शून्य in हाल of प्रणाली-wide OOM
 *
 * Returns a poपूर्णांकer to a memory cgroup, which has to be cleaned up
 * by समाप्तing all beदीर्घing OOM-समाप्तable tasks.
 *
 * Caller has to call mem_cgroup_put() on the वापसed non-शून्य memcg.
 */
काष्ठा mem_cgroup *mem_cgroup_get_oom_group(काष्ठा task_काष्ठा *victim,
					    काष्ठा mem_cgroup *oom_करोमुख्य)
अणु
	काष्ठा mem_cgroup *oom_group = शून्य;
	काष्ठा mem_cgroup *memcg;

	अगर (!cgroup_subsys_on_dfl(memory_cgrp_subsys))
		वापस शून्य;

	अगर (!oom_करोमुख्य)
		oom_करोमुख्य = root_mem_cgroup;

	rcu_पढ़ो_lock();

	memcg = mem_cgroup_from_task(victim);
	अगर (memcg == root_mem_cgroup)
		जाओ out;

	/*
	 * If the victim task has been asynchronously moved to a dअगरferent
	 * memory cgroup, we might end up समाप्तing tasks outside oom_करोमुख्य.
	 * In this हाल it's better to ignore memory.group.oom.
	 */
	अगर (unlikely(!mem_cgroup_is_descendant(memcg, oom_करोमुख्य)))
		जाओ out;

	/*
	 * Traverse the memory cgroup hierarchy from the victim task's
	 * cgroup up to the OOMing cgroup (or root) to find the
	 * highest-level memory cgroup with oom.group set.
	 */
	क्रम (; memcg; memcg = parent_mem_cgroup(memcg)) अणु
		अगर (memcg->oom_group)
			oom_group = memcg;

		अगर (memcg == oom_करोमुख्य)
			अवरोध;
	पूर्ण

	अगर (oom_group)
		css_get(&oom_group->css);
out:
	rcu_पढ़ो_unlock();

	वापस oom_group;
पूर्ण

व्योम mem_cgroup_prपूर्णांक_oom_group(काष्ठा mem_cgroup *memcg)
अणु
	pr_info("Tasks in ");
	pr_cont_cgroup_path(memcg->css.cgroup);
	pr_cont(" are going to be killed due to memory.oom.group set\n");
पूर्ण

/**
 * lock_page_memcg - lock a page and memcg binding
 * @page: the page
 *
 * This function protects unlocked LRU pages from being moved to
 * another cgroup.
 *
 * It ensures lअगरeसमय of the locked memcg. Caller is responsible
 * क्रम the lअगरeसमय of the page.
 */
व्योम lock_page_memcg(काष्ठा page *page)
अणु
	काष्ठा page *head = compound_head(page); /* rmap on tail pages */
	काष्ठा mem_cgroup *memcg;
	अचिन्हित दीर्घ flags;

	/*
	 * The RCU lock is held throughout the transaction.  The fast
	 * path can get away without acquiring the memcg->move_lock
	 * because page moving starts with an RCU grace period.
         */
	rcu_पढ़ो_lock();

	अगर (mem_cgroup_disabled())
		वापस;
again:
	memcg = page_memcg(head);
	अगर (unlikely(!memcg))
		वापस;

#अगर_घोषित CONFIG_PROVE_LOCKING
	local_irq_save(flags);
	might_lock(&memcg->move_lock);
	local_irq_restore(flags);
#पूर्ण_अगर

	अगर (atomic_पढ़ो(&memcg->moving_account) <= 0)
		वापस;

	spin_lock_irqsave(&memcg->move_lock, flags);
	अगर (memcg != page_memcg(head)) अणु
		spin_unlock_irqrestore(&memcg->move_lock, flags);
		जाओ again;
	पूर्ण

	/*
	 * When अक्षरge migration first begins, we can have multiple
	 * critical sections holding the fast-path RCU lock and one
	 * holding the slowpath move_lock. Track the task who has the
	 * move_lock क्रम unlock_page_memcg().
	 */
	memcg->move_lock_task = current;
	memcg->move_lock_flags = flags;
पूर्ण
EXPORT_SYMBOL(lock_page_memcg);

अटल व्योम __unlock_page_memcg(काष्ठा mem_cgroup *memcg)
अणु
	अगर (memcg && memcg->move_lock_task == current) अणु
		अचिन्हित दीर्घ flags = memcg->move_lock_flags;

		memcg->move_lock_task = शून्य;
		memcg->move_lock_flags = 0;

		spin_unlock_irqrestore(&memcg->move_lock, flags);
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

/**
 * unlock_page_memcg - unlock a page and memcg binding
 * @page: the page
 */
व्योम unlock_page_memcg(काष्ठा page *page)
अणु
	काष्ठा page *head = compound_head(page);

	__unlock_page_memcg(page_memcg(head));
पूर्ण
EXPORT_SYMBOL(unlock_page_memcg);

काष्ठा memcg_stock_pcp अणु
	काष्ठा mem_cgroup *cached; /* this never be root cgroup */
	अचिन्हित पूर्णांक nr_pages;

#अगर_घोषित CONFIG_MEMCG_KMEM
	काष्ठा obj_cgroup *cached_objcg;
	अचिन्हित पूर्णांक nr_bytes;
#पूर्ण_अगर

	काष्ठा work_काष्ठा work;
	अचिन्हित दीर्घ flags;
#घोषणा FLUSHING_CACHED_CHARGE	0
पूर्ण;
अटल DEFINE_PER_CPU(काष्ठा memcg_stock_pcp, memcg_stock);
अटल DEFINE_MUTEX(percpu_अक्षरge_mutex);

#अगर_घोषित CONFIG_MEMCG_KMEM
अटल व्योम drain_obj_stock(काष्ठा memcg_stock_pcp *stock);
अटल bool obj_stock_flush_required(काष्ठा memcg_stock_pcp *stock,
				     काष्ठा mem_cgroup *root_memcg);

#अन्यथा
अटल अंतरभूत व्योम drain_obj_stock(काष्ठा memcg_stock_pcp *stock)
अणु
पूर्ण
अटल bool obj_stock_flush_required(काष्ठा memcg_stock_pcp *stock,
				     काष्ठा mem_cgroup *root_memcg)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

/**
 * consume_stock: Try to consume stocked अक्षरge on this cpu.
 * @memcg: memcg to consume from.
 * @nr_pages: how many pages to अक्षरge.
 *
 * The अक्षरges will only happen अगर @memcg matches the current cpu's memcg
 * stock, and at least @nr_pages are available in that stock.  Failure to
 * service an allocation will refill the stock.
 *
 * वापसs true अगर successful, false otherwise.
 */
अटल bool consume_stock(काष्ठा mem_cgroup *memcg, अचिन्हित पूर्णांक nr_pages)
अणु
	काष्ठा memcg_stock_pcp *stock;
	अचिन्हित दीर्घ flags;
	bool ret = false;

	अगर (nr_pages > MEMCG_CHARGE_BATCH)
		वापस ret;

	local_irq_save(flags);

	stock = this_cpu_ptr(&memcg_stock);
	अगर (memcg == stock->cached && stock->nr_pages >= nr_pages) अणु
		stock->nr_pages -= nr_pages;
		ret = true;
	पूर्ण

	local_irq_restore(flags);

	वापस ret;
पूर्ण

/*
 * Returns stocks cached in percpu and reset cached inक्रमmation.
 */
अटल व्योम drain_stock(काष्ठा memcg_stock_pcp *stock)
अणु
	काष्ठा mem_cgroup *old = stock->cached;

	अगर (!old)
		वापस;

	अगर (stock->nr_pages) अणु
		page_counter_unअक्षरge(&old->memory, stock->nr_pages);
		अगर (करो_memsw_account())
			page_counter_unअक्षरge(&old->memsw, stock->nr_pages);
		stock->nr_pages = 0;
	पूर्ण

	css_put(&old->css);
	stock->cached = शून्य;
पूर्ण

अटल व्योम drain_local_stock(काष्ठा work_काष्ठा *dummy)
अणु
	काष्ठा memcg_stock_pcp *stock;
	अचिन्हित दीर्घ flags;

	/*
	 * The only protection from memory hotplug vs. drain_stock races is
	 * that we always operate on local CPU stock here with IRQ disabled
	 */
	local_irq_save(flags);

	stock = this_cpu_ptr(&memcg_stock);
	drain_obj_stock(stock);
	drain_stock(stock);
	clear_bit(FLUSHING_CACHED_CHARGE, &stock->flags);

	local_irq_restore(flags);
पूर्ण

/*
 * Cache अक्षरges(val) to local per_cpu area.
 * This will be consumed by consume_stock() function, later.
 */
अटल व्योम refill_stock(काष्ठा mem_cgroup *memcg, अचिन्हित पूर्णांक nr_pages)
अणु
	काष्ठा memcg_stock_pcp *stock;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	stock = this_cpu_ptr(&memcg_stock);
	अगर (stock->cached != memcg) अणु /* reset अगर necessary */
		drain_stock(stock);
		css_get(&memcg->css);
		stock->cached = memcg;
	पूर्ण
	stock->nr_pages += nr_pages;

	अगर (stock->nr_pages > MEMCG_CHARGE_BATCH)
		drain_stock(stock);

	local_irq_restore(flags);
पूर्ण

/*
 * Drains all per-CPU अक्षरge caches क्रम given root_memcg resp. subtree
 * of the hierarchy under it.
 */
अटल व्योम drain_all_stock(काष्ठा mem_cgroup *root_memcg)
अणु
	पूर्णांक cpu, curcpu;

	/* If someone's alपढ़ोy draining, aव्योम adding running more workers. */
	अगर (!mutex_trylock(&percpu_अक्षरge_mutex))
		वापस;
	/*
	 * Notअगरy other cpus that प्रणाली-wide "drain" is running
	 * We करो not care about races with the cpu hotplug because cpu करोwn
	 * as well as workers from this path always operate on the local
	 * per-cpu data. CPU up करोesn't touch memcg_stock at all.
	 */
	curcpu = get_cpu();
	क्रम_each_online_cpu(cpu) अणु
		काष्ठा memcg_stock_pcp *stock = &per_cpu(memcg_stock, cpu);
		काष्ठा mem_cgroup *memcg;
		bool flush = false;

		rcu_पढ़ो_lock();
		memcg = stock->cached;
		अगर (memcg && stock->nr_pages &&
		    mem_cgroup_is_descendant(memcg, root_memcg))
			flush = true;
		अगर (obj_stock_flush_required(stock, root_memcg))
			flush = true;
		rcu_पढ़ो_unlock();

		अगर (flush &&
		    !test_and_set_bit(FLUSHING_CACHED_CHARGE, &stock->flags)) अणु
			अगर (cpu == curcpu)
				drain_local_stock(&stock->work);
			अन्यथा
				schedule_work_on(cpu, &stock->work);
		पूर्ण
	पूर्ण
	put_cpu();
	mutex_unlock(&percpu_अक्षरge_mutex);
पूर्ण

अटल व्योम memcg_flush_lruvec_page_state(काष्ठा mem_cgroup *memcg, पूर्णांक cpu)
अणु
	पूर्णांक nid;

	क्रम_each_node(nid) अणु
		काष्ठा mem_cgroup_per_node *pn = memcg->nodeinfo[nid];
		अचिन्हित दीर्घ stat[NR_VM_NODE_STAT_ITEMS];
		काष्ठा batched_lruvec_stat *lstatc;
		पूर्णांक i;

		lstatc = per_cpu_ptr(pn->lruvec_stat_cpu, cpu);
		क्रम (i = 0; i < NR_VM_NODE_STAT_ITEMS; i++) अणु
			stat[i] = lstatc->count[i];
			lstatc->count[i] = 0;
		पूर्ण

		करो अणु
			क्रम (i = 0; i < NR_VM_NODE_STAT_ITEMS; i++)
				atomic_दीर्घ_add(stat[i], &pn->lruvec_stat[i]);
		पूर्ण जबतक ((pn = parent_nodeinfo(pn, nid)));
	पूर्ण
पूर्ण

अटल पूर्णांक memcg_hotplug_cpu_dead(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा memcg_stock_pcp *stock;
	काष्ठा mem_cgroup *memcg;

	stock = &per_cpu(memcg_stock, cpu);
	drain_stock(stock);

	क्रम_each_mem_cgroup(memcg)
		memcg_flush_lruvec_page_state(memcg, cpu);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ reclaim_high(काष्ठा mem_cgroup *memcg,
				  अचिन्हित पूर्णांक nr_pages,
				  gfp_t gfp_mask)
अणु
	अचिन्हित दीर्घ nr_reclaimed = 0;

	करो अणु
		अचिन्हित दीर्घ pflags;

		अगर (page_counter_पढ़ो(&memcg->memory) <=
		    READ_ONCE(memcg->memory.high))
			जारी;

		memcg_memory_event(memcg, MEMCG_HIGH);

		psi_memstall_enter(&pflags);
		nr_reclaimed += try_to_मुक्त_mem_cgroup_pages(memcg, nr_pages,
							     gfp_mask, true);
		psi_memstall_leave(&pflags);
	पूर्ण जबतक ((memcg = parent_mem_cgroup(memcg)) &&
		 !mem_cgroup_is_root(memcg));

	वापस nr_reclaimed;
पूर्ण

अटल व्योम high_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mem_cgroup *memcg;

	memcg = container_of(work, काष्ठा mem_cgroup, high_work);
	reclaim_high(memcg, MEMCG_CHARGE_BATCH, GFP_KERNEL);
पूर्ण

/*
 * Clamp the maximum sleep समय per allocation batch to 2 seconds. This is
 * enough to still cause a signअगरicant slowकरोwn in most हालs, जबतक still
 * allowing diagnostics and tracing to proceed without becoming stuck.
 */
#घोषणा MEMCG_MAX_HIGH_DELAY_JIFFIES (2UL*HZ)

/*
 * When calculating the delay, we use these either side of the exponentiation to
 * मुख्यtain precision and scale to a reasonable number of jअगरfies (see the table
 * below.
 *
 * - MEMCG_DELAY_PRECISION_SHIFT: Extra precision bits जबतक translating the
 *   overage ratio to a delay.
 * - MEMCG_DELAY_SCALING_SHIFT: The number of bits to scale करोwn the
 *   proposed penalty in order to reduce to a reasonable number of jअगरfies, and
 *   to produce a reasonable delay curve.
 *
 * MEMCG_DELAY_SCALING_SHIFT just happens to be a number that produces a
 * reasonable delay curve compared to precision-adjusted overage, not
 * penalising heavily at first, but still making sure that growth beyond the
 * limit penalises misbehaviour cgroups by slowing them करोwn exponentially. For
 * example, with a high of 100 megabytes:
 *
 *  +-------+------------------------+
 *  | usage | समय to allocate in ms |
 *  +-------+------------------------+
 *  | 100M  |                      0 |
 *  | 101M  |                      6 |
 *  | 102M  |                     25 |
 *  | 103M  |                     57 |
 *  | 104M  |                    102 |
 *  | 105M  |                    159 |
 *  | 106M  |                    230 |
 *  | 107M  |                    313 |
 *  | 108M  |                    409 |
 *  | 109M  |                    518 |
 *  | 110M  |                    639 |
 *  | 111M  |                    774 |
 *  | 112M  |                    921 |
 *  | 113M  |                   1081 |
 *  | 114M  |                   1254 |
 *  | 115M  |                   1439 |
 *  | 116M  |                   1638 |
 *  | 117M  |                   1849 |
 *  | 118M  |                   2000 |
 *  | 119M  |                   2000 |
 *  | 120M  |                   2000 |
 *  +-------+------------------------+
 */
 #घोषणा MEMCG_DELAY_PRECISION_SHIFT 20
 #घोषणा MEMCG_DELAY_SCALING_SHIFT 14

अटल u64 calculate_overage(अचिन्हित दीर्घ usage, अचिन्हित दीर्घ high)
अणु
	u64 overage;

	अगर (usage <= high)
		वापस 0;

	/*
	 * Prevent भागision by 0 in overage calculation by acting as अगर
	 * it was a threshold of 1 page
	 */
	high = max(high, 1UL);

	overage = usage - high;
	overage <<= MEMCG_DELAY_PRECISION_SHIFT;
	वापस भाग64_u64(overage, high);
पूर्ण

अटल u64 mem_find_max_overage(काष्ठा mem_cgroup *memcg)
अणु
	u64 overage, max_overage = 0;

	करो अणु
		overage = calculate_overage(page_counter_पढ़ो(&memcg->memory),
					    READ_ONCE(memcg->memory.high));
		max_overage = max(overage, max_overage);
	पूर्ण जबतक ((memcg = parent_mem_cgroup(memcg)) &&
		 !mem_cgroup_is_root(memcg));

	वापस max_overage;
पूर्ण

अटल u64 swap_find_max_overage(काष्ठा mem_cgroup *memcg)
अणु
	u64 overage, max_overage = 0;

	करो अणु
		overage = calculate_overage(page_counter_पढ़ो(&memcg->swap),
					    READ_ONCE(memcg->swap.high));
		अगर (overage)
			memcg_memory_event(memcg, MEMCG_SWAP_HIGH);
		max_overage = max(overage, max_overage);
	पूर्ण जबतक ((memcg = parent_mem_cgroup(memcg)) &&
		 !mem_cgroup_is_root(memcg));

	वापस max_overage;
पूर्ण

/*
 * Get the number of jअगरfies that we should penalise a mischievous cgroup which
 * is exceeding its memory.high by checking both it and its ancestors.
 */
अटल अचिन्हित दीर्घ calculate_high_delay(काष्ठा mem_cgroup *memcg,
					  अचिन्हित पूर्णांक nr_pages,
					  u64 max_overage)
अणु
	अचिन्हित दीर्घ penalty_jअगरfies;

	अगर (!max_overage)
		वापस 0;

	/*
	 * We use overage compared to memory.high to calculate the number of
	 * jअगरfies to sleep (penalty_jअगरfies). Ideally this value should be
	 * fairly lenient on small overages, and increasingly harsh when the
	 * memcg in question makes it clear that it has no पूर्णांकention of stopping
	 * its crazy behaviour, so we exponentially increase the delay based on
	 * overage amount.
	 */
	penalty_jअगरfies = max_overage * max_overage * HZ;
	penalty_jअगरfies >>= MEMCG_DELAY_PRECISION_SHIFT;
	penalty_jअगरfies >>= MEMCG_DELAY_SCALING_SHIFT;

	/*
	 * Factor in the task's own contribution to the overage, such that four
	 * N-sized allocations are throttled approximately the same as one
	 * 4N-sized allocation.
	 *
	 * MEMCG_CHARGE_BATCH pages is nominal, so work out how much smaller or
	 * larger the current अक्षरge patch is than that.
	 */
	वापस penalty_jअगरfies * nr_pages / MEMCG_CHARGE_BATCH;
पूर्ण

/*
 * Scheduled by try_अक्षरge() to be executed from the userland वापस path
 * and reclaims memory over the high limit.
 */
व्योम mem_cgroup_handle_over_high(व्योम)
अणु
	अचिन्हित दीर्घ penalty_jअगरfies;
	अचिन्हित दीर्घ pflags;
	अचिन्हित दीर्घ nr_reclaimed;
	अचिन्हित पूर्णांक nr_pages = current->memcg_nr_pages_over_high;
	पूर्णांक nr_retries = MAX_RECLAIM_RETRIES;
	काष्ठा mem_cgroup *memcg;
	bool in_retry = false;

	अगर (likely(!nr_pages))
		वापस;

	memcg = get_mem_cgroup_from_mm(current->mm);
	current->memcg_nr_pages_over_high = 0;

retry_reclaim:
	/*
	 * The allocating task should reclaim at least the batch size, but क्रम
	 * subsequent retries we only want to करो what's necessary to prevent oom
	 * or breaching resource isolation.
	 *
	 * This is distinct from memory.max or page allocator behaviour because
	 * memory.high is currently batched, whereas memory.max and the page
	 * allocator run every समय an allocation is made.
	 */
	nr_reclaimed = reclaim_high(memcg,
				    in_retry ? SWAP_CLUSTER_MAX : nr_pages,
				    GFP_KERNEL);

	/*
	 * memory.high is breached and reclaim is unable to keep up. Throttle
	 * allocators proactively to slow करोwn excessive growth.
	 */
	penalty_jअगरfies = calculate_high_delay(memcg, nr_pages,
					       mem_find_max_overage(memcg));

	penalty_jअगरfies += calculate_high_delay(memcg, nr_pages,
						swap_find_max_overage(memcg));

	/*
	 * Clamp the max delay per usermode वापस so as to still keep the
	 * application moving क्रमwards and also permit diagnostics, albeit
	 * extremely slowly.
	 */
	penalty_jअगरfies = min(penalty_jअगरfies, MEMCG_MAX_HIGH_DELAY_JIFFIES);

	/*
	 * Don't sleep अगर the amount of jअगरfies this memcg owes us is so low
	 * that it's not even worth करोing, in an attempt to be nice to those who
	 * go only a small amount over their memory.high value and maybe haven't
	 * been aggressively reclaimed enough yet.
	 */
	अगर (penalty_jअगरfies <= HZ / 100)
		जाओ out;

	/*
	 * If reclaim is making क्रमward progress but we're still over
	 * memory.high, we want to encourage that rather than करोing allocator
	 * throttling.
	 */
	अगर (nr_reclaimed || nr_retries--) अणु
		in_retry = true;
		जाओ retry_reclaim;
	पूर्ण

	/*
	 * If we निकास early, we're guaranteed to die (since
	 * schedule_समयout_समाप्तable sets TASK_KILLABLE). This means we करोn't
	 * need to account क्रम any ill-begotten jअगरfies to pay them off later.
	 */
	psi_memstall_enter(&pflags);
	schedule_समयout_समाप्तable(penalty_jअगरfies);
	psi_memstall_leave(&pflags);

out:
	css_put(&memcg->css);
पूर्ण

अटल पूर्णांक try_अक्षरge(काष्ठा mem_cgroup *memcg, gfp_t gfp_mask,
		      अचिन्हित पूर्णांक nr_pages)
अणु
	अचिन्हित पूर्णांक batch = max(MEMCG_CHARGE_BATCH, nr_pages);
	पूर्णांक nr_retries = MAX_RECLAIM_RETRIES;
	काष्ठा mem_cgroup *mem_over_limit;
	काष्ठा page_counter *counter;
	क्रमागत oom_status oom_status;
	अचिन्हित दीर्घ nr_reclaimed;
	bool may_swap = true;
	bool drained = false;
	अचिन्हित दीर्घ pflags;

	अगर (mem_cgroup_is_root(memcg))
		वापस 0;
retry:
	अगर (consume_stock(memcg, nr_pages))
		वापस 0;

	अगर (!करो_memsw_account() ||
	    page_counter_try_अक्षरge(&memcg->memsw, batch, &counter)) अणु
		अगर (page_counter_try_अक्षरge(&memcg->memory, batch, &counter))
			जाओ करोne_restock;
		अगर (करो_memsw_account())
			page_counter_unअक्षरge(&memcg->memsw, batch);
		mem_over_limit = mem_cgroup_from_counter(counter, memory);
	पूर्ण अन्यथा अणु
		mem_over_limit = mem_cgroup_from_counter(counter, memsw);
		may_swap = false;
	पूर्ण

	अगर (batch > nr_pages) अणु
		batch = nr_pages;
		जाओ retry;
	पूर्ण

	/*
	 * Memcg करोesn't have a dedicated reserve क्रम atomic
	 * allocations. But like the global atomic pool, we need to
	 * put the burden of reclaim on regular allocation requests
	 * and let these go through as privileged allocations.
	 */
	अगर (gfp_mask & __GFP_ATOMIC)
		जाओ क्रमce;

	/*
	 * Unlike in global OOM situations, memcg is not in a physical
	 * memory लघुage.  Allow dying and OOM-समाप्तed tasks to
	 * bypass the last अक्षरges so that they can निकास quickly and
	 * मुक्त their memory.
	 */
	अगर (unlikely(should_क्रमce_अक्षरge()))
		जाओ क्रमce;

	/*
	 * Prevent unbounded recursion when reclaim operations need to
	 * allocate memory. This might exceed the limits temporarily,
	 * but we prefer facilitating memory reclaim and getting back
	 * under the limit over triggering OOM समाप्तs in these हालs.
	 */
	अगर (unlikely(current->flags & PF_MEMALLOC))
		जाओ क्रमce;

	अगर (unlikely(task_in_memcg_oom(current)))
		जाओ nomem;

	अगर (!gfpflags_allow_blocking(gfp_mask))
		जाओ nomem;

	memcg_memory_event(mem_over_limit, MEMCG_MAX);

	psi_memstall_enter(&pflags);
	nr_reclaimed = try_to_मुक्त_mem_cgroup_pages(mem_over_limit, nr_pages,
						    gfp_mask, may_swap);
	psi_memstall_leave(&pflags);

	अगर (mem_cgroup_margin(mem_over_limit) >= nr_pages)
		जाओ retry;

	अगर (!drained) अणु
		drain_all_stock(mem_over_limit);
		drained = true;
		जाओ retry;
	पूर्ण

	अगर (gfp_mask & __GFP_NORETRY)
		जाओ nomem;
	/*
	 * Even though the limit is exceeded at this poपूर्णांक, reclaim
	 * may have been able to मुक्त some pages.  Retry the अक्षरge
	 * beक्रमe समाप्तing the task.
	 *
	 * Only क्रम regular pages, though: huge pages are rather
	 * unlikely to succeed so बंद to the limit, and we fall back
	 * to regular pages anyway in हाल of failure.
	 */
	अगर (nr_reclaimed && nr_pages <= (1 << PAGE_ALLOC_COSTLY_ORDER))
		जाओ retry;
	/*
	 * At task move, अक्षरge accounts can be करोubly counted. So, it's
	 * better to रुको until the end of task_move अगर something is going on.
	 */
	अगर (mem_cgroup_रुको_acct_move(mem_over_limit))
		जाओ retry;

	अगर (nr_retries--)
		जाओ retry;

	अगर (gfp_mask & __GFP_RETRY_MAYFAIL)
		जाओ nomem;

	अगर (fatal_संकेत_pending(current))
		जाओ क्रमce;

	/*
	 * keep retrying as दीर्घ as the memcg oom समाप्तer is able to make
	 * a क्रमward progress or bypass the अक्षरge अगर the oom समाप्तer
	 * couldn't make any progress.
	 */
	oom_status = mem_cgroup_oom(mem_over_limit, gfp_mask,
		       get_order(nr_pages * PAGE_SIZE));
	चयन (oom_status) अणु
	हाल OOM_SUCCESS:
		nr_retries = MAX_RECLAIM_RETRIES;
		जाओ retry;
	हाल OOM_FAILED:
		जाओ क्रमce;
	शेष:
		जाओ nomem;
	पूर्ण
nomem:
	अगर (!(gfp_mask & __GFP_NOFAIL))
		वापस -ENOMEM;
क्रमce:
	/*
	 * The allocation either can't fail or will lead to more memory
	 * being मुक्तd very soon.  Allow memory usage go over the limit
	 * temporarily by क्रमce अक्षरging it.
	 */
	page_counter_अक्षरge(&memcg->memory, nr_pages);
	अगर (करो_memsw_account())
		page_counter_अक्षरge(&memcg->memsw, nr_pages);

	वापस 0;

करोne_restock:
	अगर (batch > nr_pages)
		refill_stock(memcg, batch - nr_pages);

	/*
	 * If the hierarchy is above the normal consumption range, schedule
	 * reclaim on वापसing to userland.  We can perक्रमm reclaim here
	 * अगर __GFP_RECLAIM but let's always punt क्रम simplicity and so that
	 * GFP_KERNEL can consistently be used during reclaim.  @memcg is
	 * not recorded as it most likely matches current's and won't
	 * change in the meanसमय.  As high limit is checked again beक्रमe
	 * reclaim, the cost of mismatch is negligible.
	 */
	करो अणु
		bool mem_high, swap_high;

		mem_high = page_counter_पढ़ो(&memcg->memory) >
			READ_ONCE(memcg->memory.high);
		swap_high = page_counter_पढ़ो(&memcg->swap) >
			READ_ONCE(memcg->swap.high);

		/* Don't bother a अक्रमom पूर्णांकerrupted task */
		अगर (in_पूर्णांकerrupt()) अणु
			अगर (mem_high) अणु
				schedule_work(&memcg->high_work);
				अवरोध;
			पूर्ण
			जारी;
		पूर्ण

		अगर (mem_high || swap_high) अणु
			/*
			 * The allocating tasks in this cgroup will need to करो
			 * reclaim or be throttled to prevent further growth
			 * of the memory or swap footprपूर्णांकs.
			 *
			 * Target some best-efक्रमt fairness between the tasks,
			 * and distribute reclaim work and delay penalties
			 * based on how much each task is actually allocating.
			 */
			current->memcg_nr_pages_over_high += batch;
			set_notअगरy_resume(current);
			अवरोध;
		पूर्ण
	पूर्ण जबतक ((memcg = parent_mem_cgroup(memcg)));

	वापस 0;
पूर्ण

#अगर defined(CONFIG_MEMCG_KMEM) || defined(CONFIG_MMU)
अटल व्योम cancel_अक्षरge(काष्ठा mem_cgroup *memcg, अचिन्हित पूर्णांक nr_pages)
अणु
	अगर (mem_cgroup_is_root(memcg))
		वापस;

	page_counter_unअक्षरge(&memcg->memory, nr_pages);
	अगर (करो_memsw_account())
		page_counter_unअक्षरge(&memcg->memsw, nr_pages);
पूर्ण
#पूर्ण_अगर

अटल व्योम commit_अक्षरge(काष्ठा page *page, काष्ठा mem_cgroup *memcg)
अणु
	VM_BUG_ON_PAGE(page_memcg(page), page);
	/*
	 * Any of the following ensures page's memcg stability:
	 *
	 * - the page lock
	 * - LRU isolation
	 * - lock_page_memcg()
	 * - exclusive reference
	 */
	page->memcg_data = (अचिन्हित दीर्घ)memcg;
पूर्ण

अटल काष्ठा mem_cgroup *get_mem_cgroup_from_objcg(काष्ठा obj_cgroup *objcg)
अणु
	काष्ठा mem_cgroup *memcg;

	rcu_पढ़ो_lock();
retry:
	memcg = obj_cgroup_memcg(objcg);
	अगर (unlikely(!css_tryget(&memcg->css)))
		जाओ retry;
	rcu_पढ़ो_unlock();

	वापस memcg;
पूर्ण

#अगर_घोषित CONFIG_MEMCG_KMEM
पूर्णांक memcg_alloc_page_obj_cgroups(काष्ठा page *page, काष्ठा kmem_cache *s,
				 gfp_t gfp, bool new_page)
अणु
	अचिन्हित पूर्णांक objects = objs_per_slab_page(s, page);
	अचिन्हित दीर्घ memcg_data;
	व्योम *vec;

	vec = kसुस्मृति_node(objects, माप(काष्ठा obj_cgroup *), gfp,
			   page_to_nid(page));
	अगर (!vec)
		वापस -ENOMEM;

	memcg_data = (अचिन्हित दीर्घ) vec | MEMCG_DATA_OBJCGS;
	अगर (new_page) अणु
		/*
		 * If the slab page is bअक्रम new and nobody can yet access
		 * it's memcg_data, no synchronization is required and
		 * memcg_data can be simply asचिन्हित.
		 */
		page->memcg_data = memcg_data;
	पूर्ण अन्यथा अगर (cmpxchg(&page->memcg_data, 0, memcg_data)) अणु
		/*
		 * If the slab page is alपढ़ोy in use, somebody can allocate
		 * and assign obj_cgroups in parallel. In this हाल the existing
		 * objcg vector should be reused.
		 */
		kमुक्त(vec);
		वापस 0;
	पूर्ण

	kmemleak_not_leak(vec);
	वापस 0;
पूर्ण

/*
 * Returns a poपूर्णांकer to the memory cgroup to which the kernel object is अक्षरged.
 *
 * A passed kernel object can be a slab object or a generic kernel page, so
 * dअगरferent mechanisms क्रम getting the memory cgroup poपूर्णांकer should be used.
 * In certain हालs (e.g. kernel stacks or large kदो_स्मृतिs with SLUB) the caller
 * can not know क्रम sure how the kernel object is implemented.
 * mem_cgroup_from_obj() can be safely used in such हालs.
 *
 * The caller must ensure the memcg lअगरeसमय, e.g. by taking rcu_पढ़ो_lock(),
 * cgroup_mutex, etc.
 */
काष्ठा mem_cgroup *mem_cgroup_from_obj(व्योम *p)
अणु
	काष्ठा page *page;

	अगर (mem_cgroup_disabled())
		वापस शून्य;

	page = virt_to_head_page(p);

	/*
	 * Slab objects are accounted inभागidually, not per-page.
	 * Memcg membership data क्रम each inभागidual object is saved in
	 * the page->obj_cgroups.
	 */
	अगर (page_objcgs_check(page)) अणु
		काष्ठा obj_cgroup *objcg;
		अचिन्हित पूर्णांक off;

		off = obj_to_index(page->slab_cache, page, p);
		objcg = page_objcgs(page)[off];
		अगर (objcg)
			वापस obj_cgroup_memcg(objcg);

		वापस शून्य;
	पूर्ण

	/*
	 * page_memcg_check() is used here, because page_has_obj_cgroups()
	 * check above could fail because the object cgroups vector wasn't set
	 * at that moment, but it can be set concurrently.
	 * page_memcg_check(page) will guarantee that a proper memory
	 * cgroup poपूर्णांकer or शून्य will be वापसed.
	 */
	वापस page_memcg_check(page);
पूर्ण

__always_अंतरभूत काष्ठा obj_cgroup *get_obj_cgroup_from_current(व्योम)
अणु
	काष्ठा obj_cgroup *objcg = शून्य;
	काष्ठा mem_cgroup *memcg;

	अगर (memcg_kmem_bypass())
		वापस शून्य;

	rcu_पढ़ो_lock();
	अगर (unlikely(active_memcg()))
		memcg = active_memcg();
	अन्यथा
		memcg = mem_cgroup_from_task(current);

	क्रम (; memcg != root_mem_cgroup; memcg = parent_mem_cgroup(memcg)) अणु
		objcg = rcu_dereference(memcg->objcg);
		अगर (objcg && obj_cgroup_tryget(objcg))
			अवरोध;
		objcg = शून्य;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस objcg;
पूर्ण

अटल पूर्णांक memcg_alloc_cache_id(व्योम)
अणु
	पूर्णांक id, size;
	पूर्णांक err;

	id = ida_simple_get(&memcg_cache_ida,
			    0, MEMCG_CACHES_MAX_SIZE, GFP_KERNEL);
	अगर (id < 0)
		वापस id;

	अगर (id < memcg_nr_cache_ids)
		वापस id;

	/*
	 * There's no space क्रम the new id in memcg_caches arrays,
	 * so we have to grow them.
	 */
	करोwn_ग_लिखो(&memcg_cache_ids_sem);

	size = 2 * (id + 1);
	अगर (size < MEMCG_CACHES_MIN_SIZE)
		size = MEMCG_CACHES_MIN_SIZE;
	अन्यथा अगर (size > MEMCG_CACHES_MAX_SIZE)
		size = MEMCG_CACHES_MAX_SIZE;

	err = memcg_update_all_list_lrus(size);
	अगर (!err)
		memcg_nr_cache_ids = size;

	up_ग_लिखो(&memcg_cache_ids_sem);

	अगर (err) अणु
		ida_simple_हटाओ(&memcg_cache_ida, id);
		वापस err;
	पूर्ण
	वापस id;
पूर्ण

अटल व्योम memcg_मुक्त_cache_id(पूर्णांक id)
अणु
	ida_simple_हटाओ(&memcg_cache_ida, id);
पूर्ण

/*
 * obj_cgroup_unअक्षरge_pages: unअक्षरge a number of kernel pages from a objcg
 * @objcg: object cgroup to unअक्षरge
 * @nr_pages: number of pages to unअक्षरge
 */
अटल व्योम obj_cgroup_unअक्षरge_pages(काष्ठा obj_cgroup *objcg,
				      अचिन्हित पूर्णांक nr_pages)
अणु
	काष्ठा mem_cgroup *memcg;

	memcg = get_mem_cgroup_from_objcg(objcg);

	अगर (!cgroup_subsys_on_dfl(memory_cgrp_subsys))
		page_counter_unअक्षरge(&memcg->kmem, nr_pages);
	refill_stock(memcg, nr_pages);

	css_put(&memcg->css);
पूर्ण

/*
 * obj_cgroup_अक्षरge_pages: अक्षरge a number of kernel pages to a objcg
 * @objcg: object cgroup to अक्षरge
 * @gfp: reclaim mode
 * @nr_pages: number of pages to अक्षरge
 *
 * Returns 0 on success, an error code on failure.
 */
अटल पूर्णांक obj_cgroup_अक्षरge_pages(काष्ठा obj_cgroup *objcg, gfp_t gfp,
				   अचिन्हित पूर्णांक nr_pages)
अणु
	काष्ठा page_counter *counter;
	काष्ठा mem_cgroup *memcg;
	पूर्णांक ret;

	memcg = get_mem_cgroup_from_objcg(objcg);

	ret = try_अक्षरge(memcg, gfp, nr_pages);
	अगर (ret)
		जाओ out;

	अगर (!cgroup_subsys_on_dfl(memory_cgrp_subsys) &&
	    !page_counter_try_अक्षरge(&memcg->kmem, nr_pages, &counter)) अणु

		/*
		 * Enक्रमce __GFP_NOFAIL allocation because callers are not
		 * prepared to see failures and likely करो not have any failure
		 * handling code.
		 */
		अगर (gfp & __GFP_NOFAIL) अणु
			page_counter_अक्षरge(&memcg->kmem, nr_pages);
			जाओ out;
		पूर्ण
		cancel_अक्षरge(memcg, nr_pages);
		ret = -ENOMEM;
	पूर्ण
out:
	css_put(&memcg->css);

	वापस ret;
पूर्ण

/**
 * __memcg_kmem_अक्षरge_page: अक्षरge a kmem page to the current memory cgroup
 * @page: page to अक्षरge
 * @gfp: reclaim mode
 * @order: allocation order
 *
 * Returns 0 on success, an error code on failure.
 */
पूर्णांक __memcg_kmem_अक्षरge_page(काष्ठा page *page, gfp_t gfp, पूर्णांक order)
अणु
	काष्ठा obj_cgroup *objcg;
	पूर्णांक ret = 0;

	objcg = get_obj_cgroup_from_current();
	अगर (objcg) अणु
		ret = obj_cgroup_अक्षरge_pages(objcg, gfp, 1 << order);
		अगर (!ret) अणु
			page->memcg_data = (अचिन्हित दीर्घ)objcg |
				MEMCG_DATA_KMEM;
			वापस 0;
		पूर्ण
		obj_cgroup_put(objcg);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * __memcg_kmem_unअक्षरge_page: unअक्षरge a kmem page
 * @page: page to unअक्षरge
 * @order: allocation order
 */
व्योम __memcg_kmem_unअक्षरge_page(काष्ठा page *page, पूर्णांक order)
अणु
	काष्ठा obj_cgroup *objcg;
	अचिन्हित पूर्णांक nr_pages = 1 << order;

	अगर (!PageMemcgKmem(page))
		वापस;

	objcg = __page_objcg(page);
	obj_cgroup_unअक्षरge_pages(objcg, nr_pages);
	page->memcg_data = 0;
	obj_cgroup_put(objcg);
पूर्ण

अटल bool consume_obj_stock(काष्ठा obj_cgroup *objcg, अचिन्हित पूर्णांक nr_bytes)
अणु
	काष्ठा memcg_stock_pcp *stock;
	अचिन्हित दीर्घ flags;
	bool ret = false;

	local_irq_save(flags);

	stock = this_cpu_ptr(&memcg_stock);
	अगर (objcg == stock->cached_objcg && stock->nr_bytes >= nr_bytes) अणु
		stock->nr_bytes -= nr_bytes;
		ret = true;
	पूर्ण

	local_irq_restore(flags);

	वापस ret;
पूर्ण

अटल व्योम drain_obj_stock(काष्ठा memcg_stock_pcp *stock)
अणु
	काष्ठा obj_cgroup *old = stock->cached_objcg;

	अगर (!old)
		वापस;

	अगर (stock->nr_bytes) अणु
		अचिन्हित पूर्णांक nr_pages = stock->nr_bytes >> PAGE_SHIFT;
		अचिन्हित पूर्णांक nr_bytes = stock->nr_bytes & (PAGE_SIZE - 1);

		अगर (nr_pages)
			obj_cgroup_unअक्षरge_pages(old, nr_pages);

		/*
		 * The leftover is flushed to the centralized per-memcg value.
		 * On the next attempt to refill obj stock it will be moved
		 * to a per-cpu stock (probably, on an other CPU), see
		 * refill_obj_stock().
		 *
		 * How often it's flushed is a trade-off between the memory
		 * limit enक्रमcement accuracy and potential CPU contention,
		 * so it might be changed in the future.
		 */
		atomic_add(nr_bytes, &old->nr_अक्षरged_bytes);
		stock->nr_bytes = 0;
	पूर्ण

	obj_cgroup_put(old);
	stock->cached_objcg = शून्य;
पूर्ण

अटल bool obj_stock_flush_required(काष्ठा memcg_stock_pcp *stock,
				     काष्ठा mem_cgroup *root_memcg)
अणु
	काष्ठा mem_cgroup *memcg;

	अगर (stock->cached_objcg) अणु
		memcg = obj_cgroup_memcg(stock->cached_objcg);
		अगर (memcg && mem_cgroup_is_descendant(memcg, root_memcg))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम refill_obj_stock(काष्ठा obj_cgroup *objcg, अचिन्हित पूर्णांक nr_bytes)
अणु
	काष्ठा memcg_stock_pcp *stock;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	stock = this_cpu_ptr(&memcg_stock);
	अगर (stock->cached_objcg != objcg) अणु /* reset अगर necessary */
		drain_obj_stock(stock);
		obj_cgroup_get(objcg);
		stock->cached_objcg = objcg;
		stock->nr_bytes = atomic_xchg(&objcg->nr_अक्षरged_bytes, 0);
	पूर्ण
	stock->nr_bytes += nr_bytes;

	अगर (stock->nr_bytes > PAGE_SIZE)
		drain_obj_stock(stock);

	local_irq_restore(flags);
पूर्ण

पूर्णांक obj_cgroup_अक्षरge(काष्ठा obj_cgroup *objcg, gfp_t gfp, माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक nr_pages, nr_bytes;
	पूर्णांक ret;

	अगर (consume_obj_stock(objcg, size))
		वापस 0;

	/*
	 * In theory, memcg->nr_अक्षरged_bytes can have enough
	 * pre-अक्षरged bytes to satisfy the allocation. However,
	 * flushing memcg->nr_अक्षरged_bytes requires two atomic
	 * operations, and memcg->nr_अक्षरged_bytes can't be big,
	 * so it's better to ignore it and try grab some new pages.
	 * memcg->nr_अक्षरged_bytes will be flushed in
	 * refill_obj_stock(), called from this function or
	 * independently later.
	 */
	nr_pages = size >> PAGE_SHIFT;
	nr_bytes = size & (PAGE_SIZE - 1);

	अगर (nr_bytes)
		nr_pages += 1;

	ret = obj_cgroup_अक्षरge_pages(objcg, gfp, nr_pages);
	अगर (!ret && nr_bytes)
		refill_obj_stock(objcg, PAGE_SIZE - nr_bytes);

	वापस ret;
पूर्ण

व्योम obj_cgroup_unअक्षरge(काष्ठा obj_cgroup *objcg, माप_प्रकार size)
अणु
	refill_obj_stock(objcg, size);
पूर्ण

#पूर्ण_अगर /* CONFIG_MEMCG_KMEM */

/*
 * Because page_memcg(head) is not set on tails, set it now.
 */
व्योम split_page_memcg(काष्ठा page *head, अचिन्हित पूर्णांक nr)
अणु
	काष्ठा mem_cgroup *memcg = page_memcg(head);
	पूर्णांक i;

	अगर (mem_cgroup_disabled() || !memcg)
		वापस;

	क्रम (i = 1; i < nr; i++)
		head[i].memcg_data = head->memcg_data;

	अगर (PageMemcgKmem(head))
		obj_cgroup_get_many(__page_objcg(head), nr - 1);
	अन्यथा
		css_get_many(&memcg->css, nr - 1);
पूर्ण

#अगर_घोषित CONFIG_MEMCG_SWAP
/**
 * mem_cgroup_move_swap_account - move swap अक्षरge and swap_cgroup's record.
 * @entry: swap entry to be moved
 * @from:  mem_cgroup which the entry is moved from
 * @to:  mem_cgroup which the entry is moved to
 *
 * It succeeds only when the swap_cgroup's record क्रम this entry is the same
 * as the mem_cgroup's id of @from.
 *
 * Returns 0 on success, -EINVAL on failure.
 *
 * The caller must have अक्षरged to @to, IOW, called page_counter_अक्षरge() about
 * both res and memsw, and called css_get().
 */
अटल पूर्णांक mem_cgroup_move_swap_account(swp_entry_t entry,
				काष्ठा mem_cgroup *from, काष्ठा mem_cgroup *to)
अणु
	अचिन्हित लघु old_id, new_id;

	old_id = mem_cgroup_id(from);
	new_id = mem_cgroup_id(to);

	अगर (swap_cgroup_cmpxchg(entry, old_id, new_id) == old_id) अणु
		mod_memcg_state(from, MEMCG_SWAP, -1);
		mod_memcg_state(to, MEMCG_SWAP, 1);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक mem_cgroup_move_swap_account(swp_entry_t entry,
				काष्ठा mem_cgroup *from, काष्ठा mem_cgroup *to)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

अटल DEFINE_MUTEX(memcg_max_mutex);

अटल पूर्णांक mem_cgroup_resize_max(काष्ठा mem_cgroup *memcg,
				 अचिन्हित दीर्घ max, bool memsw)
अणु
	bool enlarge = false;
	bool drained = false;
	पूर्णांक ret;
	bool limits_invariant;
	काष्ठा page_counter *counter = memsw ? &memcg->memsw : &memcg->memory;

	करो अणु
		अगर (संकेत_pending(current)) अणु
			ret = -EINTR;
			अवरोध;
		पूर्ण

		mutex_lock(&memcg_max_mutex);
		/*
		 * Make sure that the new limit (memsw or memory limit) करोesn't
		 * अवरोध our basic invariant rule memory.max <= memsw.max.
		 */
		limits_invariant = memsw ? max >= READ_ONCE(memcg->memory.max) :
					   max <= memcg->memsw.max;
		अगर (!limits_invariant) अणु
			mutex_unlock(&memcg_max_mutex);
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (max > counter->max)
			enlarge = true;
		ret = page_counter_set_max(counter, max);
		mutex_unlock(&memcg_max_mutex);

		अगर (!ret)
			अवरोध;

		अगर (!drained) अणु
			drain_all_stock(memcg);
			drained = true;
			जारी;
		पूर्ण

		अगर (!try_to_मुक्त_mem_cgroup_pages(memcg, 1,
					GFP_KERNEL, !memsw)) अणु
			ret = -EBUSY;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (true);

	अगर (!ret && enlarge)
		memcg_oom_recover(memcg);

	वापस ret;
पूर्ण

अचिन्हित दीर्घ mem_cgroup_soft_limit_reclaim(pg_data_t *pgdat, पूर्णांक order,
					    gfp_t gfp_mask,
					    अचिन्हित दीर्घ *total_scanned)
अणु
	अचिन्हित दीर्घ nr_reclaimed = 0;
	काष्ठा mem_cgroup_per_node *mz, *next_mz = शून्य;
	अचिन्हित दीर्घ reclaimed;
	पूर्णांक loop = 0;
	काष्ठा mem_cgroup_tree_per_node *mctz;
	अचिन्हित दीर्घ excess;
	अचिन्हित दीर्घ nr_scanned;

	अगर (order > 0)
		वापस 0;

	mctz = soft_limit_tree_node(pgdat->node_id);

	/*
	 * Do not even bother to check the largest node अगर the root
	 * is empty. Do it lockless to prevent lock bouncing. Races
	 * are acceptable as soft limit is best efक्रमt anyway.
	 */
	अगर (!mctz || RB_EMPTY_ROOT(&mctz->rb_root))
		वापस 0;

	/*
	 * This loop can run a जबतक, specially अगर mem_cgroup's continuously
	 * keep exceeding their soft limit and putting the प्रणाली under
	 * pressure
	 */
	करो अणु
		अगर (next_mz)
			mz = next_mz;
		अन्यथा
			mz = mem_cgroup_largest_soft_limit_node(mctz);
		अगर (!mz)
			अवरोध;

		nr_scanned = 0;
		reclaimed = mem_cgroup_soft_reclaim(mz->memcg, pgdat,
						    gfp_mask, &nr_scanned);
		nr_reclaimed += reclaimed;
		*total_scanned += nr_scanned;
		spin_lock_irq(&mctz->lock);
		__mem_cgroup_हटाओ_exceeded(mz, mctz);

		/*
		 * If we failed to reclaim anything from this memory cgroup
		 * it is समय to move on to the next cgroup
		 */
		next_mz = शून्य;
		अगर (!reclaimed)
			next_mz = __mem_cgroup_largest_soft_limit_node(mctz);

		excess = soft_limit_excess(mz->memcg);
		/*
		 * One school of thought says that we should not add
		 * back the node to the tree अगर reclaim वापसs 0.
		 * But our reclaim could वापस 0, simply because due
		 * to priority we are exposing a smaller subset of
		 * memory to reclaim from. Consider this as a दीर्घer
		 * term TODO.
		 */
		/* If excess == 0, no tree ops */
		__mem_cgroup_insert_exceeded(mz, mctz, excess);
		spin_unlock_irq(&mctz->lock);
		css_put(&mz->memcg->css);
		loop++;
		/*
		 * Could not reclaim anything and there are no more
		 * mem cgroups to try or we seem to be looping without
		 * reclaiming anything.
		 */
		अगर (!nr_reclaimed &&
			(next_mz == शून्य ||
			loop > MEM_CGROUP_MAX_SOFT_LIMIT_RECLAIM_LOOPS))
			अवरोध;
	पूर्ण जबतक (!nr_reclaimed);
	अगर (next_mz)
		css_put(&next_mz->memcg->css);
	वापस nr_reclaimed;
पूर्ण

/*
 * Reclaims as many pages from the given memcg as possible.
 *
 * Caller is responsible क्रम holding css reference क्रम memcg.
 */
अटल पूर्णांक mem_cgroup_क्रमce_empty(काष्ठा mem_cgroup *memcg)
अणु
	पूर्णांक nr_retries = MAX_RECLAIM_RETRIES;

	/* we call try-to-मुक्त pages क्रम make this cgroup empty */
	lru_add_drain_all();

	drain_all_stock(memcg);

	/* try to मुक्त all pages in this cgroup */
	जबतक (nr_retries && page_counter_पढ़ो(&memcg->memory)) अणु
		पूर्णांक progress;

		अगर (संकेत_pending(current))
			वापस -EINTR;

		progress = try_to_मुक्त_mem_cgroup_pages(memcg, 1,
							GFP_KERNEL, true);
		अगर (!progress) अणु
			nr_retries--;
			/* maybe some ग_लिखोback is necessary */
			congestion_रुको(BLK_RW_ASYNC, HZ/10);
		पूर्ण

	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार mem_cgroup_क्रमce_empty_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
					    अक्षर *buf, माप_प्रकार nbytes,
					    loff_t off)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_css(of_css(of));

	अगर (mem_cgroup_is_root(memcg))
		वापस -EINVAL;
	वापस mem_cgroup_क्रमce_empty(memcg) ?: nbytes;
पूर्ण

अटल u64 mem_cgroup_hierarchy_पढ़ो(काष्ठा cgroup_subsys_state *css,
				     काष्ठा cftype *cft)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक mem_cgroup_hierarchy_ग_लिखो(काष्ठा cgroup_subsys_state *css,
				      काष्ठा cftype *cft, u64 val)
अणु
	अगर (val == 1)
		वापस 0;

	pr_warn_once("Non-hierarchical mode is deprecated. "
		     "Please report your usecase to linux-mm@kvack.org if you "
		     "depend on this functionality.\n");

	वापस -EINVAL;
पूर्ण

अटल अचिन्हित दीर्घ mem_cgroup_usage(काष्ठा mem_cgroup *memcg, bool swap)
अणु
	अचिन्हित दीर्घ val;

	अगर (mem_cgroup_is_root(memcg)) अणु
		cgroup_rstat_flush(memcg->css.cgroup);
		val = memcg_page_state(memcg, NR_खाता_PAGES) +
			memcg_page_state(memcg, NR_ANON_MAPPED);
		अगर (swap)
			val += memcg_page_state(memcg, MEMCG_SWAP);
	पूर्ण अन्यथा अणु
		अगर (!swap)
			val = page_counter_पढ़ो(&memcg->memory);
		अन्यथा
			val = page_counter_पढ़ो(&memcg->memsw);
	पूर्ण
	वापस val;
पूर्ण

क्रमागत अणु
	RES_USAGE,
	RES_LIMIT,
	RES_MAX_USAGE,
	RES_FAILCNT,
	RES_SOFT_LIMIT,
पूर्ण;

अटल u64 mem_cgroup_पढ़ो_u64(काष्ठा cgroup_subsys_state *css,
			       काष्ठा cftype *cft)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_css(css);
	काष्ठा page_counter *counter;

	चयन (MEMखाता_TYPE(cft->निजी)) अणु
	हाल _MEM:
		counter = &memcg->memory;
		अवरोध;
	हाल _MEMSWAP:
		counter = &memcg->memsw;
		अवरोध;
	हाल _KMEM:
		counter = &memcg->kmem;
		अवरोध;
	हाल _TCP:
		counter = &memcg->tcpmem;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	चयन (MEMखाता_ATTR(cft->निजी)) अणु
	हाल RES_USAGE:
		अगर (counter == &memcg->memory)
			वापस (u64)mem_cgroup_usage(memcg, false) * PAGE_SIZE;
		अगर (counter == &memcg->memsw)
			वापस (u64)mem_cgroup_usage(memcg, true) * PAGE_SIZE;
		वापस (u64)page_counter_पढ़ो(counter) * PAGE_SIZE;
	हाल RES_LIMIT:
		वापस (u64)counter->max * PAGE_SIZE;
	हाल RES_MAX_USAGE:
		वापस (u64)counter->watermark * PAGE_SIZE;
	हाल RES_FAILCNT:
		वापस counter->failcnt;
	हाल RES_SOFT_LIMIT:
		वापस (u64)memcg->soft_limit * PAGE_SIZE;
	शेष:
		BUG();
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_MEMCG_KMEM
अटल पूर्णांक memcg_online_kmem(काष्ठा mem_cgroup *memcg)
अणु
	काष्ठा obj_cgroup *objcg;
	पूर्णांक memcg_id;

	अगर (cgroup_memory_nokmem)
		वापस 0;

	BUG_ON(memcg->kmemcg_id >= 0);
	BUG_ON(memcg->kmem_state);

	memcg_id = memcg_alloc_cache_id();
	अगर (memcg_id < 0)
		वापस memcg_id;

	objcg = obj_cgroup_alloc();
	अगर (!objcg) अणु
		memcg_मुक्त_cache_id(memcg_id);
		वापस -ENOMEM;
	पूर्ण
	objcg->memcg = memcg;
	rcu_assign_poपूर्णांकer(memcg->objcg, objcg);

	अटल_branch_enable(&memcg_kmem_enabled_key);

	memcg->kmemcg_id = memcg_id;
	memcg->kmem_state = KMEM_ONLINE;

	वापस 0;
पूर्ण

अटल व्योम memcg_offline_kmem(काष्ठा mem_cgroup *memcg)
अणु
	काष्ठा cgroup_subsys_state *css;
	काष्ठा mem_cgroup *parent, *child;
	पूर्णांक kmemcg_id;

	अगर (memcg->kmem_state != KMEM_ONLINE)
		वापस;

	memcg->kmem_state = KMEM_ALLOCATED;

	parent = parent_mem_cgroup(memcg);
	अगर (!parent)
		parent = root_mem_cgroup;

	memcg_reparent_objcgs(memcg, parent);

	kmemcg_id = memcg->kmemcg_id;
	BUG_ON(kmemcg_id < 0);

	/*
	 * Change kmemcg_id of this cgroup and all its descendants to the
	 * parent's id, and then move all entries from this cgroup's list_lrus
	 * to ones of the parent. After we have finished, all list_lrus
	 * corresponding to this cgroup are guaranteed to reमुख्य empty. The
	 * ordering is imposed by list_lru_node->lock taken by
	 * memcg_drain_all_list_lrus().
	 */
	rcu_पढ़ो_lock(); /* can be called from css_मुक्त w/o cgroup_mutex */
	css_क्रम_each_descendant_pre(css, &memcg->css) अणु
		child = mem_cgroup_from_css(css);
		BUG_ON(child->kmemcg_id != kmemcg_id);
		child->kmemcg_id = parent->kmemcg_id;
	पूर्ण
	rcu_पढ़ो_unlock();

	memcg_drain_all_list_lrus(kmemcg_id, parent);

	memcg_मुक्त_cache_id(kmemcg_id);
पूर्ण

अटल व्योम memcg_मुक्त_kmem(काष्ठा mem_cgroup *memcg)
अणु
	/* css_alloc() failed, offlining didn't happen */
	अगर (unlikely(memcg->kmem_state == KMEM_ONLINE))
		memcg_offline_kmem(memcg);
पूर्ण
#अन्यथा
अटल पूर्णांक memcg_online_kmem(काष्ठा mem_cgroup *memcg)
अणु
	वापस 0;
पूर्ण
अटल व्योम memcg_offline_kmem(काष्ठा mem_cgroup *memcg)
अणु
पूर्ण
अटल व्योम memcg_मुक्त_kmem(काष्ठा mem_cgroup *memcg)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_MEMCG_KMEM */

अटल पूर्णांक memcg_update_kmem_max(काष्ठा mem_cgroup *memcg,
				 अचिन्हित दीर्घ max)
अणु
	पूर्णांक ret;

	mutex_lock(&memcg_max_mutex);
	ret = page_counter_set_max(&memcg->kmem, max);
	mutex_unlock(&memcg_max_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक memcg_update_tcp_max(काष्ठा mem_cgroup *memcg, अचिन्हित दीर्घ max)
अणु
	पूर्णांक ret;

	mutex_lock(&memcg_max_mutex);

	ret = page_counter_set_max(&memcg->tcpmem, max);
	अगर (ret)
		जाओ out;

	अगर (!memcg->tcpmem_active) अणु
		/*
		 * The active flag needs to be written after the अटल_key
		 * update. This is what guarantees that the socket activation
		 * function is the last one to run. See mem_cgroup_sk_alloc()
		 * क्रम details, and note that we करोn't mark any socket as
		 * beदीर्घing to this memcg until that flag is up.
		 *
		 * We need to करो this, because अटल_keys will span multiple
		 * sites, but we can't control their order. If we mark a socket
		 * as accounted, but the accounting functions are not patched in
		 * yet, we'll lose accounting.
		 *
		 * We never race with the पढ़ोers in mem_cgroup_sk_alloc(),
		 * because when this value change, the code to process it is not
		 * patched in yet.
		 */
		अटल_branch_inc(&memcg_sockets_enabled_key);
		memcg->tcpmem_active = true;
	पूर्ण
out:
	mutex_unlock(&memcg_max_mutex);
	वापस ret;
पूर्ण

/*
 * The user of this function is...
 * RES_LIMIT.
 */
अटल sमाप_प्रकार mem_cgroup_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
				अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_css(of_css(of));
	अचिन्हित दीर्घ nr_pages;
	पूर्णांक ret;

	buf = म_मालाip(buf);
	ret = page_counter_memparse(buf, "-1", &nr_pages);
	अगर (ret)
		वापस ret;

	चयन (MEMखाता_ATTR(of_cft(of)->निजी)) अणु
	हाल RES_LIMIT:
		अगर (mem_cgroup_is_root(memcg)) अणु /* Can't set limit on root */
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		चयन (MEMखाता_TYPE(of_cft(of)->निजी)) अणु
		हाल _MEM:
			ret = mem_cgroup_resize_max(memcg, nr_pages, false);
			अवरोध;
		हाल _MEMSWAP:
			ret = mem_cgroup_resize_max(memcg, nr_pages, true);
			अवरोध;
		हाल _KMEM:
			pr_warn_once("kmem.limit_in_bytes is deprecated and will be removed. "
				     "Please report your usecase to linux-mm@kvack.org if you "
				     "depend on this functionality.\n");
			ret = memcg_update_kmem_max(memcg, nr_pages);
			अवरोध;
		हाल _TCP:
			ret = memcg_update_tcp_max(memcg, nr_pages);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल RES_SOFT_LIMIT:
		memcg->soft_limit = nr_pages;
		ret = 0;
		अवरोध;
	पूर्ण
	वापस ret ?: nbytes;
पूर्ण

अटल sमाप_प्रकार mem_cgroup_reset(काष्ठा kernfs_खोलो_file *of, अक्षर *buf,
				माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_css(of_css(of));
	काष्ठा page_counter *counter;

	चयन (MEMखाता_TYPE(of_cft(of)->निजी)) अणु
	हाल _MEM:
		counter = &memcg->memory;
		अवरोध;
	हाल _MEMSWAP:
		counter = &memcg->memsw;
		अवरोध;
	हाल _KMEM:
		counter = &memcg->kmem;
		अवरोध;
	हाल _TCP:
		counter = &memcg->tcpmem;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	चयन (MEMखाता_ATTR(of_cft(of)->निजी)) अणु
	हाल RES_MAX_USAGE:
		page_counter_reset_watermark(counter);
		अवरोध;
	हाल RES_FAILCNT:
		counter->failcnt = 0;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	वापस nbytes;
पूर्ण

अटल u64 mem_cgroup_move_अक्षरge_पढ़ो(काष्ठा cgroup_subsys_state *css,
					काष्ठा cftype *cft)
अणु
	वापस mem_cgroup_from_css(css)->move_अक्षरge_at_immigrate;
पूर्ण

#अगर_घोषित CONFIG_MMU
अटल पूर्णांक mem_cgroup_move_अक्षरge_ग_लिखो(काष्ठा cgroup_subsys_state *css,
					काष्ठा cftype *cft, u64 val)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_css(css);

	अगर (val & ~MOVE_MASK)
		वापस -EINVAL;

	/*
	 * No kind of locking is needed in here, because ->can_attach() will
	 * check this value once in the beginning of the process, and then carry
	 * on with stale data. This means that changes to this value will only
	 * affect task migrations starting after the change.
	 */
	memcg->move_अक्षरge_at_immigrate = val;
	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक mem_cgroup_move_अक्षरge_ग_लिखो(काष्ठा cgroup_subsys_state *css,
					काष्ठा cftype *cft, u64 val)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NUMA

#घोषणा LRU_ALL_खाता (BIT(LRU_INACTIVE_खाता) | BIT(LRU_ACTIVE_खाता))
#घोषणा LRU_ALL_ANON (BIT(LRU_INACTIVE_ANON) | BIT(LRU_ACTIVE_ANON))
#घोषणा LRU_ALL	     ((1 << NR_LRU_LISTS) - 1)

अटल अचिन्हित दीर्घ mem_cgroup_node_nr_lru_pages(काष्ठा mem_cgroup *memcg,
				पूर्णांक nid, अचिन्हित पूर्णांक lru_mask, bool tree)
अणु
	काष्ठा lruvec *lruvec = mem_cgroup_lruvec(memcg, NODE_DATA(nid));
	अचिन्हित दीर्घ nr = 0;
	क्रमागत lru_list lru;

	VM_BUG_ON((अचिन्हित)nid >= nr_node_ids);

	क्रम_each_lru(lru) अणु
		अगर (!(BIT(lru) & lru_mask))
			जारी;
		अगर (tree)
			nr += lruvec_page_state(lruvec, NR_LRU_BASE + lru);
		अन्यथा
			nr += lruvec_page_state_local(lruvec, NR_LRU_BASE + lru);
	पूर्ण
	वापस nr;
पूर्ण

अटल अचिन्हित दीर्घ mem_cgroup_nr_lru_pages(काष्ठा mem_cgroup *memcg,
					     अचिन्हित पूर्णांक lru_mask,
					     bool tree)
अणु
	अचिन्हित दीर्घ nr = 0;
	क्रमागत lru_list lru;

	क्रम_each_lru(lru) अणु
		अगर (!(BIT(lru) & lru_mask))
			जारी;
		अगर (tree)
			nr += memcg_page_state(memcg, NR_LRU_BASE + lru);
		अन्यथा
			nr += memcg_page_state_local(memcg, NR_LRU_BASE + lru);
	पूर्ण
	वापस nr;
पूर्ण

अटल पूर्णांक memcg_numa_stat_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा numa_stat अणु
		स्थिर अक्षर *name;
		अचिन्हित पूर्णांक lru_mask;
	पूर्ण;

	अटल स्थिर काष्ठा numa_stat stats[] = अणु
		अणु "total", LRU_ALL पूर्ण,
		अणु "file", LRU_ALL_खाता पूर्ण,
		अणु "anon", LRU_ALL_ANON पूर्ण,
		अणु "unevictable", BIT(LRU_UNEVICTABLE) पूर्ण,
	पूर्ण;
	स्थिर काष्ठा numa_stat *stat;
	पूर्णांक nid;
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_seq(m);

	cgroup_rstat_flush(memcg->css.cgroup);

	क्रम (stat = stats; stat < stats + ARRAY_SIZE(stats); stat++) अणु
		seq_म_लिखो(m, "%s=%lu", stat->name,
			   mem_cgroup_nr_lru_pages(memcg, stat->lru_mask,
						   false));
		क्रम_each_node_state(nid, N_MEMORY)
			seq_म_लिखो(m, " N%d=%lu", nid,
				   mem_cgroup_node_nr_lru_pages(memcg, nid,
							stat->lru_mask, false));
		seq_अ_दो(m, '\n');
	पूर्ण

	क्रम (stat = stats; stat < stats + ARRAY_SIZE(stats); stat++) अणु

		seq_म_लिखो(m, "hierarchical_%s=%lu", stat->name,
			   mem_cgroup_nr_lru_pages(memcg, stat->lru_mask,
						   true));
		क्रम_each_node_state(nid, N_MEMORY)
			seq_म_लिखो(m, " N%d=%lu", nid,
				   mem_cgroup_node_nr_lru_pages(memcg, nid,
							stat->lru_mask, true));
		seq_अ_दो(m, '\n');
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA */

अटल स्थिर अचिन्हित पूर्णांक memcg1_stats[] = अणु
	NR_खाता_PAGES,
	NR_ANON_MAPPED,
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
	NR_ANON_THPS,
#पूर्ण_अगर
	NR_SHMEM,
	NR_खाता_MAPPED,
	NR_खाता_सूचीTY,
	NR_WRITEBACK,
	MEMCG_SWAP,
पूर्ण;

अटल स्थिर अक्षर *स्थिर memcg1_stat_names[] = अणु
	"cache",
	"rss",
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
	"rss_huge",
#पूर्ण_अगर
	"shmem",
	"mapped_file",
	"dirty",
	"writeback",
	"swap",
पूर्ण;

/* Universal VM events cgroup1 shows, original sort order */
अटल स्थिर अचिन्हित पूर्णांक memcg1_events[] = अणु
	PGPGIN,
	PGPGOUT,
	PGFAULT,
	PGMAJFAULT,
पूर्ण;

अटल पूर्णांक memcg_stat_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_seq(m);
	अचिन्हित दीर्घ memory, memsw;
	काष्ठा mem_cgroup *mi;
	अचिन्हित पूर्णांक i;

	BUILD_BUG_ON(ARRAY_SIZE(memcg1_stat_names) != ARRAY_SIZE(memcg1_stats));

	cgroup_rstat_flush(memcg->css.cgroup);

	क्रम (i = 0; i < ARRAY_SIZE(memcg1_stats); i++) अणु
		अचिन्हित दीर्घ nr;

		अगर (memcg1_stats[i] == MEMCG_SWAP && !करो_memsw_account())
			जारी;
		nr = memcg_page_state_local(memcg, memcg1_stats[i]);
		seq_म_लिखो(m, "%s %lu\n", memcg1_stat_names[i], nr * PAGE_SIZE);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(memcg1_events); i++)
		seq_म_लिखो(m, "%s %lu\n", vm_event_name(memcg1_events[i]),
			   memcg_events_local(memcg, memcg1_events[i]));

	क्रम (i = 0; i < NR_LRU_LISTS; i++)
		seq_म_लिखो(m, "%s %lu\n", lru_list_name(i),
			   memcg_page_state_local(memcg, NR_LRU_BASE + i) *
			   PAGE_SIZE);

	/* Hierarchical inक्रमmation */
	memory = memsw = PAGE_COUNTER_MAX;
	क्रम (mi = memcg; mi; mi = parent_mem_cgroup(mi)) अणु
		memory = min(memory, READ_ONCE(mi->memory.max));
		memsw = min(memsw, READ_ONCE(mi->memsw.max));
	पूर्ण
	seq_म_लिखो(m, "hierarchical_memory_limit %llu\n",
		   (u64)memory * PAGE_SIZE);
	अगर (करो_memsw_account())
		seq_म_लिखो(m, "hierarchical_memsw_limit %llu\n",
			   (u64)memsw * PAGE_SIZE);

	क्रम (i = 0; i < ARRAY_SIZE(memcg1_stats); i++) अणु
		अचिन्हित दीर्घ nr;

		अगर (memcg1_stats[i] == MEMCG_SWAP && !करो_memsw_account())
			जारी;
		nr = memcg_page_state(memcg, memcg1_stats[i]);
		seq_म_लिखो(m, "total_%s %llu\n", memcg1_stat_names[i],
						(u64)nr * PAGE_SIZE);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(memcg1_events); i++)
		seq_म_लिखो(m, "total_%s %llu\n",
			   vm_event_name(memcg1_events[i]),
			   (u64)memcg_events(memcg, memcg1_events[i]));

	क्रम (i = 0; i < NR_LRU_LISTS; i++)
		seq_म_लिखो(m, "total_%s %llu\n", lru_list_name(i),
			   (u64)memcg_page_state(memcg, NR_LRU_BASE + i) *
			   PAGE_SIZE);

#अगर_घोषित CONFIG_DEBUG_VM
	अणु
		pg_data_t *pgdat;
		काष्ठा mem_cgroup_per_node *mz;
		अचिन्हित दीर्घ anon_cost = 0;
		अचिन्हित दीर्घ file_cost = 0;

		क्रम_each_online_pgdat(pgdat) अणु
			mz = memcg->nodeinfo[pgdat->node_id];

			anon_cost += mz->lruvec.anon_cost;
			file_cost += mz->lruvec.file_cost;
		पूर्ण
		seq_म_लिखो(m, "anon_cost %lu\n", anon_cost);
		seq_म_लिखो(m, "file_cost %lu\n", file_cost);
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल u64 mem_cgroup_swappiness_पढ़ो(काष्ठा cgroup_subsys_state *css,
				      काष्ठा cftype *cft)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_css(css);

	वापस mem_cgroup_swappiness(memcg);
पूर्ण

अटल पूर्णांक mem_cgroup_swappiness_ग_लिखो(काष्ठा cgroup_subsys_state *css,
				       काष्ठा cftype *cft, u64 val)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_css(css);

	अगर (val > 100)
		वापस -EINVAL;

	अगर (!mem_cgroup_is_root(memcg))
		memcg->swappiness = val;
	अन्यथा
		vm_swappiness = val;

	वापस 0;
पूर्ण

अटल व्योम __mem_cgroup_threshold(काष्ठा mem_cgroup *memcg, bool swap)
अणु
	काष्ठा mem_cgroup_threshold_ary *t;
	अचिन्हित दीर्घ usage;
	पूर्णांक i;

	rcu_पढ़ो_lock();
	अगर (!swap)
		t = rcu_dereference(memcg->thresholds.primary);
	अन्यथा
		t = rcu_dereference(memcg->memsw_thresholds.primary);

	अगर (!t)
		जाओ unlock;

	usage = mem_cgroup_usage(memcg, swap);

	/*
	 * current_threshold poपूर्णांकs to threshold just below or equal to usage.
	 * If it's not true, a threshold was crossed after last
	 * call of __mem_cgroup_threshold().
	 */
	i = t->current_threshold;

	/*
	 * Iterate backward over array of thresholds starting from
	 * current_threshold and check अगर a threshold is crossed.
	 * If none of thresholds below usage is crossed, we पढ़ो
	 * only one element of the array here.
	 */
	क्रम (; i >= 0 && unlikely(t->entries[i].threshold > usage); i--)
		eventfd_संकेत(t->entries[i].eventfd, 1);

	/* i = current_threshold + 1 */
	i++;

	/*
	 * Iterate क्रमward over array of thresholds starting from
	 * current_threshold+1 and check अगर a threshold is crossed.
	 * If none of thresholds above usage is crossed, we पढ़ो
	 * only one element of the array here.
	 */
	क्रम (; i < t->size && unlikely(t->entries[i].threshold <= usage); i++)
		eventfd_संकेत(t->entries[i].eventfd, 1);

	/* Update current_threshold */
	t->current_threshold = i - 1;
unlock:
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम mem_cgroup_threshold(काष्ठा mem_cgroup *memcg)
अणु
	जबतक (memcg) अणु
		__mem_cgroup_threshold(memcg, false);
		अगर (करो_memsw_account())
			__mem_cgroup_threshold(memcg, true);

		memcg = parent_mem_cgroup(memcg);
	पूर्ण
पूर्ण

अटल पूर्णांक compare_thresholds(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा mem_cgroup_threshold *_a = a;
	स्थिर काष्ठा mem_cgroup_threshold *_b = b;

	अगर (_a->threshold > _b->threshold)
		वापस 1;

	अगर (_a->threshold < _b->threshold)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक mem_cgroup_oom_notअगरy_cb(काष्ठा mem_cgroup *memcg)
अणु
	काष्ठा mem_cgroup_eventfd_list *ev;

	spin_lock(&memcg_oom_lock);

	list_क्रम_each_entry(ev, &memcg->oom_notअगरy, list)
		eventfd_संकेत(ev->eventfd, 1);

	spin_unlock(&memcg_oom_lock);
	वापस 0;
पूर्ण

अटल व्योम mem_cgroup_oom_notअगरy(काष्ठा mem_cgroup *memcg)
अणु
	काष्ठा mem_cgroup *iter;

	क्रम_each_mem_cgroup_tree(iter, memcg)
		mem_cgroup_oom_notअगरy_cb(iter);
पूर्ण

अटल पूर्णांक __mem_cgroup_usage_रेजिस्टर_event(काष्ठा mem_cgroup *memcg,
	काष्ठा eventfd_ctx *eventfd, स्थिर अक्षर *args, क्रमागत res_type type)
अणु
	काष्ठा mem_cgroup_thresholds *thresholds;
	काष्ठा mem_cgroup_threshold_ary *new;
	अचिन्हित दीर्घ threshold;
	अचिन्हित दीर्घ usage;
	पूर्णांक i, size, ret;

	ret = page_counter_memparse(args, "-1", &threshold);
	अगर (ret)
		वापस ret;

	mutex_lock(&memcg->thresholds_lock);

	अगर (type == _MEM) अणु
		thresholds = &memcg->thresholds;
		usage = mem_cgroup_usage(memcg, false);
	पूर्ण अन्यथा अगर (type == _MEMSWAP) अणु
		thresholds = &memcg->memsw_thresholds;
		usage = mem_cgroup_usage(memcg, true);
	पूर्ण अन्यथा
		BUG();

	/* Check अगर a threshold crossed beक्रमe adding a new one */
	अगर (thresholds->primary)
		__mem_cgroup_threshold(memcg, type == _MEMSWAP);

	size = thresholds->primary ? thresholds->primary->size + 1 : 1;

	/* Allocate memory क्रम new array of thresholds */
	new = kदो_स्मृति(काष्ठा_size(new, entries, size), GFP_KERNEL);
	अगर (!new) अणु
		ret = -ENOMEM;
		जाओ unlock;
	पूर्ण
	new->size = size;

	/* Copy thresholds (अगर any) to new array */
	अगर (thresholds->primary)
		स_नकल(new->entries, thresholds->primary->entries,
		       flex_array_size(new, entries, size - 1));

	/* Add new threshold */
	new->entries[size - 1].eventfd = eventfd;
	new->entries[size - 1].threshold = threshold;

	/* Sort thresholds. Registering of new threshold isn't समय-critical */
	sort(new->entries, size, माप(*new->entries),
			compare_thresholds, शून्य);

	/* Find current threshold */
	new->current_threshold = -1;
	क्रम (i = 0; i < size; i++) अणु
		अगर (new->entries[i].threshold <= usage) अणु
			/*
			 * new->current_threshold will not be used until
			 * rcu_assign_poपूर्णांकer(), so it's safe to increment
			 * it here.
			 */
			++new->current_threshold;
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण

	/* Free old spare buffer and save old primary buffer as spare */
	kमुक्त(thresholds->spare);
	thresholds->spare = thresholds->primary;

	rcu_assign_poपूर्णांकer(thresholds->primary, new);

	/* To be sure that nobody uses thresholds */
	synchronize_rcu();

unlock:
	mutex_unlock(&memcg->thresholds_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक mem_cgroup_usage_रेजिस्टर_event(काष्ठा mem_cgroup *memcg,
	काष्ठा eventfd_ctx *eventfd, स्थिर अक्षर *args)
अणु
	वापस __mem_cgroup_usage_रेजिस्टर_event(memcg, eventfd, args, _MEM);
पूर्ण

अटल पूर्णांक memsw_cgroup_usage_रेजिस्टर_event(काष्ठा mem_cgroup *memcg,
	काष्ठा eventfd_ctx *eventfd, स्थिर अक्षर *args)
अणु
	वापस __mem_cgroup_usage_रेजिस्टर_event(memcg, eventfd, args, _MEMSWAP);
पूर्ण

अटल व्योम __mem_cgroup_usage_unरेजिस्टर_event(काष्ठा mem_cgroup *memcg,
	काष्ठा eventfd_ctx *eventfd, क्रमागत res_type type)
अणु
	काष्ठा mem_cgroup_thresholds *thresholds;
	काष्ठा mem_cgroup_threshold_ary *new;
	अचिन्हित दीर्घ usage;
	पूर्णांक i, j, size, entries;

	mutex_lock(&memcg->thresholds_lock);

	अगर (type == _MEM) अणु
		thresholds = &memcg->thresholds;
		usage = mem_cgroup_usage(memcg, false);
	पूर्ण अन्यथा अगर (type == _MEMSWAP) अणु
		thresholds = &memcg->memsw_thresholds;
		usage = mem_cgroup_usage(memcg, true);
	पूर्ण अन्यथा
		BUG();

	अगर (!thresholds->primary)
		जाओ unlock;

	/* Check अगर a threshold crossed beक्रमe removing */
	__mem_cgroup_threshold(memcg, type == _MEMSWAP);

	/* Calculate new number of threshold */
	size = entries = 0;
	क्रम (i = 0; i < thresholds->primary->size; i++) अणु
		अगर (thresholds->primary->entries[i].eventfd != eventfd)
			size++;
		अन्यथा
			entries++;
	पूर्ण

	new = thresholds->spare;

	/* If no items related to eventfd have been cleared, nothing to करो */
	अगर (!entries)
		जाओ unlock;

	/* Set thresholds array to शून्य अगर we करोn't have thresholds */
	अगर (!size) अणु
		kमुक्त(new);
		new = शून्य;
		जाओ swap_buffers;
	पूर्ण

	new->size = size;

	/* Copy thresholds and find current threshold */
	new->current_threshold = -1;
	क्रम (i = 0, j = 0; i < thresholds->primary->size; i++) अणु
		अगर (thresholds->primary->entries[i].eventfd == eventfd)
			जारी;

		new->entries[j] = thresholds->primary->entries[i];
		अगर (new->entries[j].threshold <= usage) अणु
			/*
			 * new->current_threshold will not be used
			 * until rcu_assign_poपूर्णांकer(), so it's safe to increment
			 * it here.
			 */
			++new->current_threshold;
		पूर्ण
		j++;
	पूर्ण

swap_buffers:
	/* Swap primary and spare array */
	thresholds->spare = thresholds->primary;

	rcu_assign_poपूर्णांकer(thresholds->primary, new);

	/* To be sure that nobody uses thresholds */
	synchronize_rcu();

	/* If all events are unरेजिस्टरed, मुक्त the spare array */
	अगर (!new) अणु
		kमुक्त(thresholds->spare);
		thresholds->spare = शून्य;
	पूर्ण
unlock:
	mutex_unlock(&memcg->thresholds_lock);
पूर्ण

अटल व्योम mem_cgroup_usage_unरेजिस्टर_event(काष्ठा mem_cgroup *memcg,
	काष्ठा eventfd_ctx *eventfd)
अणु
	वापस __mem_cgroup_usage_unरेजिस्टर_event(memcg, eventfd, _MEM);
पूर्ण

अटल व्योम memsw_cgroup_usage_unरेजिस्टर_event(काष्ठा mem_cgroup *memcg,
	काष्ठा eventfd_ctx *eventfd)
अणु
	वापस __mem_cgroup_usage_unरेजिस्टर_event(memcg, eventfd, _MEMSWAP);
पूर्ण

अटल पूर्णांक mem_cgroup_oom_रेजिस्टर_event(काष्ठा mem_cgroup *memcg,
	काष्ठा eventfd_ctx *eventfd, स्थिर अक्षर *args)
अणु
	काष्ठा mem_cgroup_eventfd_list *event;

	event = kदो_स्मृति(माप(*event),	GFP_KERNEL);
	अगर (!event)
		वापस -ENOMEM;

	spin_lock(&memcg_oom_lock);

	event->eventfd = eventfd;
	list_add(&event->list, &memcg->oom_notअगरy);

	/* alपढ़ोy in OOM ? */
	अगर (memcg->under_oom)
		eventfd_संकेत(eventfd, 1);
	spin_unlock(&memcg_oom_lock);

	वापस 0;
पूर्ण

अटल व्योम mem_cgroup_oom_unरेजिस्टर_event(काष्ठा mem_cgroup *memcg,
	काष्ठा eventfd_ctx *eventfd)
अणु
	काष्ठा mem_cgroup_eventfd_list *ev, *पंचांगp;

	spin_lock(&memcg_oom_lock);

	list_क्रम_each_entry_safe(ev, पंचांगp, &memcg->oom_notअगरy, list) अणु
		अगर (ev->eventfd == eventfd) अणु
			list_del(&ev->list);
			kमुक्त(ev);
		पूर्ण
	पूर्ण

	spin_unlock(&memcg_oom_lock);
पूर्ण

अटल पूर्णांक mem_cgroup_oom_control_पढ़ो(काष्ठा seq_file *sf, व्योम *v)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_seq(sf);

	seq_म_लिखो(sf, "oom_kill_disable %d\n", memcg->oom_समाप्त_disable);
	seq_म_लिखो(sf, "under_oom %d\n", (bool)memcg->under_oom);
	seq_म_लिखो(sf, "oom_kill %lu\n",
		   atomic_दीर्घ_पढ़ो(&memcg->memory_events[MEMCG_OOM_KILL]));
	वापस 0;
पूर्ण

अटल पूर्णांक mem_cgroup_oom_control_ग_लिखो(काष्ठा cgroup_subsys_state *css,
	काष्ठा cftype *cft, u64 val)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_css(css);

	/* cannot set to root cgroup and only 0 and 1 are allowed */
	अगर (mem_cgroup_is_root(memcg) || !((val == 0) || (val == 1)))
		वापस -EINVAL;

	memcg->oom_समाप्त_disable = val;
	अगर (!val)
		memcg_oom_recover(memcg);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_CGROUP_WRITEBACK

#समावेश <trace/events/ग_लिखोback.h>

अटल पूर्णांक memcg_wb_करोमुख्य_init(काष्ठा mem_cgroup *memcg, gfp_t gfp)
अणु
	वापस wb_करोमुख्य_init(&memcg->cgwb_करोमुख्य, gfp);
पूर्ण

अटल व्योम memcg_wb_करोमुख्य_निकास(काष्ठा mem_cgroup *memcg)
अणु
	wb_करोमुख्य_निकास(&memcg->cgwb_करोमुख्य);
पूर्ण

अटल व्योम memcg_wb_करोमुख्य_size_changed(काष्ठा mem_cgroup *memcg)
अणु
	wb_करोमुख्य_size_changed(&memcg->cgwb_करोमुख्य);
पूर्ण

काष्ठा wb_करोमुख्य *mem_cgroup_wb_करोमुख्य(काष्ठा bdi_ग_लिखोback *wb)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_css(wb->memcg_css);

	अगर (!memcg->css.parent)
		वापस शून्य;

	वापस &memcg->cgwb_करोमुख्य;
पूर्ण

/**
 * mem_cgroup_wb_stats - retrieve ग_लिखोback related stats from its memcg
 * @wb: bdi_ग_लिखोback in question
 * @pfilepages: out parameter क्रम number of file pages
 * @pheadroom: out parameter क्रम number of allocatable pages according to memcg
 * @pdirty: out parameter क्रम number of dirty pages
 * @pग_लिखोback: out parameter क्रम number of pages under ग_लिखोback
 *
 * Determine the numbers of file, headroom, dirty, and ग_लिखोback pages in
 * @wb's memcg.  File, dirty and ग_लिखोback are self-explanatory.  Headroom
 * is a bit more involved.
 *
 * A memcg's headroom is "min(max, high) - used".  In the hierarchy, the
 * headroom is calculated as the lowest headroom of itself and the
 * ancestors.  Note that this करोesn't consider the actual amount of
 * available memory in the प्रणाली.  The caller should further cap
 * *@pheadroom accordingly.
 */
व्योम mem_cgroup_wb_stats(काष्ठा bdi_ग_लिखोback *wb, अचिन्हित दीर्घ *pfilepages,
			 अचिन्हित दीर्घ *pheadroom, अचिन्हित दीर्घ *pdirty,
			 अचिन्हित दीर्घ *pग_लिखोback)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_css(wb->memcg_css);
	काष्ठा mem_cgroup *parent;

	cgroup_rstat_flush_irqsafe(memcg->css.cgroup);

	*pdirty = memcg_page_state(memcg, NR_खाता_सूचीTY);
	*pग_लिखोback = memcg_page_state(memcg, NR_WRITEBACK);
	*pfilepages = memcg_page_state(memcg, NR_INACTIVE_खाता) +
			memcg_page_state(memcg, NR_ACTIVE_खाता);

	*pheadroom = PAGE_COUNTER_MAX;
	जबतक ((parent = parent_mem_cgroup(memcg))) अणु
		अचिन्हित दीर्घ उच्चमानing = min(READ_ONCE(memcg->memory.max),
					    READ_ONCE(memcg->memory.high));
		अचिन्हित दीर्घ used = page_counter_पढ़ो(&memcg->memory);

		*pheadroom = min(*pheadroom, उच्चमानing - min(उच्चमानing, used));
		memcg = parent;
	पूर्ण
पूर्ण

/*
 * Foreign dirty flushing
 *
 * There's an inherent mismatch between memcg and ग_लिखोback.  The क्रमmer
 * tracks ownership per-page जबतक the latter per-inode.  This was a
 * deliberate design decision because honoring per-page ownership in the
 * ग_लिखोback path is complicated, may lead to higher CPU and IO overheads
 * and deemed unnecessary given that ग_लिखो-sharing an inode across
 * dअगरferent cgroups isn't a common use-हाल.
 *
 * Combined with inode majority-ग_लिखोr ownership चयनing, this works well
 * enough in most हालs but there are some pathological हालs.  For
 * example, let's say there are two cgroups A and B which keep writing to
 * dअगरferent but confined parts of the same inode.  B owns the inode and
 * A's memory is limited far below B's.  A's dirty ratio can rise enough to
 * trigger balance_dirty_pages() sleeps but B's can be low enough to aव्योम
 * triggering background ग_लिखोback.  A will be slowed करोwn without a way to
 * make ग_लिखोback of the dirty pages happen.
 *
 * Conditions like the above can lead to a cgroup getting repeatedly and
 * severely throttled after making some progress after each
 * dirty_expire_पूर्णांकerval जबतक the underlying IO device is almost
 * completely idle.
 *
 * Solving this problem completely requires matching the ownership tracking
 * granularities between memcg and ग_लिखोback in either direction.  However,
 * the more egregious behaviors can be aव्योमed by simply remembering the
 * most recent क्रमeign dirtying events and initiating remote flushes on
 * them when local ग_लिखोback isn't enough to keep the memory clean enough.
 *
 * The following two functions implement such mechanism.  When a क्रमeign
 * page - a page whose memcg and ग_लिखोback ownerships करोn't match - is
 * dirtied, mem_cgroup_track_क्रमeign_dirty() records the inode owning
 * bdi_ग_लिखोback on the page owning memcg.  When balance_dirty_pages()
 * decides that the memcg needs to sleep due to high dirty ratio, it calls
 * mem_cgroup_flush_क्रमeign() which queues ग_लिखोback on the recorded
 * क्रमeign bdi_ग_लिखोbacks which haven't expired.  Both the numbers of
 * recorded bdi_ग_लिखोbacks and concurrent in-flight क्रमeign ग_लिखोbacks are
 * limited to MEMCG_CGWB_FRN_CNT.
 *
 * The mechanism only remembers IDs and करोesn't hold any object references.
 * As being wrong occasionally करोesn't matter, updates and accesses to the
 * records are lockless and racy.
 */
व्योम mem_cgroup_track_क्रमeign_dirty_slowpath(काष्ठा page *page,
					     काष्ठा bdi_ग_लिखोback *wb)
अणु
	काष्ठा mem_cgroup *memcg = page_memcg(page);
	काष्ठा memcg_cgwb_frn *frn;
	u64 now = get_jअगरfies_64();
	u64 oldest_at = now;
	पूर्णांक oldest = -1;
	पूर्णांक i;

	trace_track_क्रमeign_dirty(page, wb);

	/*
	 * Pick the slot to use.  If there is alपढ़ोy a slot क्रम @wb, keep
	 * using it.  If not replace the oldest one which isn't being
	 * written out.
	 */
	क्रम (i = 0; i < MEMCG_CGWB_FRN_CNT; i++) अणु
		frn = &memcg->cgwb_frn[i];
		अगर (frn->bdi_id == wb->bdi->id &&
		    frn->memcg_id == wb->memcg_css->id)
			अवरोध;
		अगर (समय_beक्रमe64(frn->at, oldest_at) &&
		    atomic_पढ़ो(&frn->करोne.cnt) == 1) अणु
			oldest = i;
			oldest_at = frn->at;
		पूर्ण
	पूर्ण

	अगर (i < MEMCG_CGWB_FRN_CNT) अणु
		/*
		 * Re-using an existing one.  Update बारtamp lazily to
		 * aव्योम making the cacheline hot.  We want them to be
		 * reasonably up-to-date and signअगरicantly लघुer than
		 * dirty_expire_पूर्णांकerval as that's what expires the record.
		 * Use the लघुer of 1s and dirty_expire_पूर्णांकerval / 8.
		 */
		अचिन्हित दीर्घ update_पूर्णांकv =
			min_t(अचिन्हित दीर्घ, HZ,
			      msecs_to_jअगरfies(dirty_expire_पूर्णांकerval * 10) / 8);

		अगर (समय_beक्रमe64(frn->at, now - update_पूर्णांकv))
			frn->at = now;
	पूर्ण अन्यथा अगर (oldest >= 0) अणु
		/* replace the oldest मुक्त one */
		frn = &memcg->cgwb_frn[oldest];
		frn->bdi_id = wb->bdi->id;
		frn->memcg_id = wb->memcg_css->id;
		frn->at = now;
	पूर्ण
पूर्ण

/* issue क्रमeign ग_लिखोback flushes क्रम recorded क्रमeign dirtying events */
व्योम mem_cgroup_flush_क्रमeign(काष्ठा bdi_ग_लिखोback *wb)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_css(wb->memcg_css);
	अचिन्हित दीर्घ पूर्णांकv = msecs_to_jअगरfies(dirty_expire_पूर्णांकerval * 10);
	u64 now = jअगरfies_64;
	पूर्णांक i;

	क्रम (i = 0; i < MEMCG_CGWB_FRN_CNT; i++) अणु
		काष्ठा memcg_cgwb_frn *frn = &memcg->cgwb_frn[i];

		/*
		 * If the record is older than dirty_expire_पूर्णांकerval,
		 * ग_लिखोback on it has alपढ़ोy started.  No need to kick it
		 * off again.  Also, करोn't start a new one if there's
		 * alपढ़ोy one in flight.
		 */
		अगर (समय_after64(frn->at, now - पूर्णांकv) &&
		    atomic_पढ़ो(&frn->करोne.cnt) == 1) अणु
			frn->at = 0;
			trace_flush_क्रमeign(wb, frn->bdi_id, frn->memcg_id);
			cgroup_ग_लिखोback_by_id(frn->bdi_id, frn->memcg_id, 0,
					       WB_REASON_FOREIGN_FLUSH,
					       &frn->करोne);
		पूर्ण
	पूर्ण
पूर्ण

#अन्यथा	/* CONFIG_CGROUP_WRITEBACK */

अटल पूर्णांक memcg_wb_करोमुख्य_init(काष्ठा mem_cgroup *memcg, gfp_t gfp)
अणु
	वापस 0;
पूर्ण

अटल व्योम memcg_wb_करोमुख्य_निकास(काष्ठा mem_cgroup *memcg)
अणु
पूर्ण

अटल व्योम memcg_wb_करोमुख्य_size_changed(काष्ठा mem_cgroup *memcg)
अणु
पूर्ण

#पूर्ण_अगर	/* CONFIG_CGROUP_WRITEBACK */

/*
 * DO NOT USE IN NEW खाताS.
 *
 * "cgroup.event_control" implementation.
 *
 * This is way over-engineered.  It tries to support fully configurable
 * events क्रम each user.  Such level of flexibility is completely
 * unnecessary especially in the light of the planned unअगरied hierarchy.
 *
 * Please deprecate this and replace with something simpler अगर at all
 * possible.
 */

/*
 * Unरेजिस्टर event and मुक्त resources.
 *
 * Gets called from workqueue.
 */
अटल व्योम memcg_event_हटाओ(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mem_cgroup_event *event =
		container_of(work, काष्ठा mem_cgroup_event, हटाओ);
	काष्ठा mem_cgroup *memcg = event->memcg;

	हटाओ_रुको_queue(event->wqh, &event->रुको);

	event->unरेजिस्टर_event(memcg, event->eventfd);

	/* Notअगरy userspace the event is going away. */
	eventfd_संकेत(event->eventfd, 1);

	eventfd_ctx_put(event->eventfd);
	kमुक्त(event);
	css_put(&memcg->css);
पूर्ण

/*
 * Gets called on EPOLLHUP on eventfd when user बंदs it.
 *
 * Called with wqh->lock held and पूर्णांकerrupts disabled.
 */
अटल पूर्णांक memcg_event_wake(रुको_queue_entry_t *रुको, अचिन्हित mode,
			    पूर्णांक sync, व्योम *key)
अणु
	काष्ठा mem_cgroup_event *event =
		container_of(रुको, काष्ठा mem_cgroup_event, रुको);
	काष्ठा mem_cgroup *memcg = event->memcg;
	__poll_t flags = key_to_poll(key);

	अगर (flags & EPOLLHUP) अणु
		/*
		 * If the event has been detached at cgroup removal, we
		 * can simply वापस knowing the other side will cleanup
		 * क्रम us.
		 *
		 * We can't race against event मुक्तing since the other
		 * side will require wqh->lock via हटाओ_रुको_queue(),
		 * which we hold.
		 */
		spin_lock(&memcg->event_list_lock);
		अगर (!list_empty(&event->list)) अणु
			list_del_init(&event->list);
			/*
			 * We are in atomic context, but cgroup_event_हटाओ()
			 * may sleep, so we have to call it in workqueue.
			 */
			schedule_work(&event->हटाओ);
		पूर्ण
		spin_unlock(&memcg->event_list_lock);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम memcg_event_ptable_queue_proc(काष्ठा file *file,
		रुको_queue_head_t *wqh, poll_table *pt)
अणु
	काष्ठा mem_cgroup_event *event =
		container_of(pt, काष्ठा mem_cgroup_event, pt);

	event->wqh = wqh;
	add_रुको_queue(wqh, &event->रुको);
पूर्ण

/*
 * DO NOT USE IN NEW खाताS.
 *
 * Parse input and रेजिस्टर new cgroup event handler.
 *
 * Input must be in क्रमmat '<event_fd> <control_fd> <args>'.
 * Interpretation of args is defined by control file implementation.
 */
अटल sमाप_प्रकार memcg_ग_लिखो_event_control(काष्ठा kernfs_खोलो_file *of,
					 अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा cgroup_subsys_state *css = of_css(of);
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_css(css);
	काष्ठा mem_cgroup_event *event;
	काष्ठा cgroup_subsys_state *cfile_css;
	अचिन्हित पूर्णांक efd, cfd;
	काष्ठा fd efile;
	काष्ठा fd cfile;
	स्थिर अक्षर *name;
	अक्षर *endp;
	पूर्णांक ret;

	buf = म_मालाip(buf);

	efd = simple_म_से_अदीर्घ(buf, &endp, 10);
	अगर (*endp != ' ')
		वापस -EINVAL;
	buf = endp + 1;

	cfd = simple_म_से_अदीर्घ(buf, &endp, 10);
	अगर ((*endp != ' ') && (*endp != '\0'))
		वापस -EINVAL;
	buf = endp + 1;

	event = kzalloc(माप(*event), GFP_KERNEL);
	अगर (!event)
		वापस -ENOMEM;

	event->memcg = memcg;
	INIT_LIST_HEAD(&event->list);
	init_poll_funcptr(&event->pt, memcg_event_ptable_queue_proc);
	init_रुकोqueue_func_entry(&event->रुको, memcg_event_wake);
	INIT_WORK(&event->हटाओ, memcg_event_हटाओ);

	efile = fdget(efd);
	अगर (!efile.file) अणु
		ret = -EBADF;
		जाओ out_kमुक्त;
	पूर्ण

	event->eventfd = eventfd_ctx_fileget(efile.file);
	अगर (IS_ERR(event->eventfd)) अणु
		ret = PTR_ERR(event->eventfd);
		जाओ out_put_efile;
	पूर्ण

	cfile = fdget(cfd);
	अगर (!cfile.file) अणु
		ret = -EBADF;
		जाओ out_put_eventfd;
	पूर्ण

	/* the process need पढ़ो permission on control file */
	/* AV: shouldn't we check that it's been खोलोed क्रम पढ़ो instead? */
	ret = file_permission(cfile.file, MAY_READ);
	अगर (ret < 0)
		जाओ out_put_cfile;

	/*
	 * Determine the event callbacks and set them in @event.  This used
	 * to be करोne via काष्ठा cftype but cgroup core no दीर्घer knows
	 * about these events.  The following is crude but the whole thing
	 * is क्रम compatibility anyway.
	 *
	 * DO NOT ADD NEW खाताS.
	 */
	name = cfile.file->f_path.dentry->d_name.name;

	अगर (!म_भेद(name, "memory.usage_in_bytes")) अणु
		event->रेजिस्टर_event = mem_cgroup_usage_रेजिस्टर_event;
		event->unरेजिस्टर_event = mem_cgroup_usage_unरेजिस्टर_event;
	पूर्ण अन्यथा अगर (!म_भेद(name, "memory.oom_control")) अणु
		event->रेजिस्टर_event = mem_cgroup_oom_रेजिस्टर_event;
		event->unरेजिस्टर_event = mem_cgroup_oom_unरेजिस्टर_event;
	पूर्ण अन्यथा अगर (!म_भेद(name, "memory.pressure_level")) अणु
		event->रेजिस्टर_event = vmpressure_रेजिस्टर_event;
		event->unरेजिस्टर_event = vmpressure_unरेजिस्टर_event;
	पूर्ण अन्यथा अगर (!म_भेद(name, "memory.memsw.usage_in_bytes")) अणु
		event->रेजिस्टर_event = memsw_cgroup_usage_रेजिस्टर_event;
		event->unरेजिस्टर_event = memsw_cgroup_usage_unरेजिस्टर_event;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		जाओ out_put_cfile;
	पूर्ण

	/*
	 * Verअगरy @cfile should beदीर्घ to @css.  Also, reमुख्यing events are
	 * स्वतःmatically हटाओd on cgroup deकाष्ठाion but the removal is
	 * asynchronous, so take an extra ref on @css.
	 */
	cfile_css = css_tryget_online_from_dir(cfile.file->f_path.dentry->d_parent,
					       &memory_cgrp_subsys);
	ret = -EINVAL;
	अगर (IS_ERR(cfile_css))
		जाओ out_put_cfile;
	अगर (cfile_css != css) अणु
		css_put(cfile_css);
		जाओ out_put_cfile;
	पूर्ण

	ret = event->रेजिस्टर_event(memcg, event->eventfd, buf);
	अगर (ret)
		जाओ out_put_css;

	vfs_poll(efile.file, &event->pt);

	spin_lock(&memcg->event_list_lock);
	list_add(&event->list, &memcg->event_list);
	spin_unlock(&memcg->event_list_lock);

	fdput(cfile);
	fdput(efile);

	वापस nbytes;

out_put_css:
	css_put(css);
out_put_cfile:
	fdput(cfile);
out_put_eventfd:
	eventfd_ctx_put(event->eventfd);
out_put_efile:
	fdput(efile);
out_kमुक्त:
	kमुक्त(event);

	वापस ret;
पूर्ण

अटल काष्ठा cftype mem_cgroup_legacy_files[] = अणु
	अणु
		.name = "usage_in_bytes",
		.निजी = MEMखाता_PRIVATE(_MEM, RES_USAGE),
		.पढ़ो_u64 = mem_cgroup_पढ़ो_u64,
	पूर्ण,
	अणु
		.name = "max_usage_in_bytes",
		.निजी = MEMखाता_PRIVATE(_MEM, RES_MAX_USAGE),
		.ग_लिखो = mem_cgroup_reset,
		.पढ़ो_u64 = mem_cgroup_पढ़ो_u64,
	पूर्ण,
	अणु
		.name = "limit_in_bytes",
		.निजी = MEMखाता_PRIVATE(_MEM, RES_LIMIT),
		.ग_लिखो = mem_cgroup_ग_लिखो,
		.पढ़ो_u64 = mem_cgroup_पढ़ो_u64,
	पूर्ण,
	अणु
		.name = "soft_limit_in_bytes",
		.निजी = MEMखाता_PRIVATE(_MEM, RES_SOFT_LIMIT),
		.ग_लिखो = mem_cgroup_ग_लिखो,
		.पढ़ो_u64 = mem_cgroup_पढ़ो_u64,
	पूर्ण,
	अणु
		.name = "failcnt",
		.निजी = MEMखाता_PRIVATE(_MEM, RES_FAILCNT),
		.ग_लिखो = mem_cgroup_reset,
		.पढ़ो_u64 = mem_cgroup_पढ़ो_u64,
	पूर्ण,
	अणु
		.name = "stat",
		.seq_show = memcg_stat_show,
	पूर्ण,
	अणु
		.name = "force_empty",
		.ग_लिखो = mem_cgroup_क्रमce_empty_ग_लिखो,
	पूर्ण,
	अणु
		.name = "use_hierarchy",
		.ग_लिखो_u64 = mem_cgroup_hierarchy_ग_लिखो,
		.पढ़ो_u64 = mem_cgroup_hierarchy_पढ़ो,
	पूर्ण,
	अणु
		.name = "cgroup.event_control",		/* XXX: क्रम compat */
		.ग_लिखो = memcg_ग_लिखो_event_control,
		.flags = CFTYPE_NO_PREFIX | CFTYPE_WORLD_WRITABLE,
	पूर्ण,
	अणु
		.name = "swappiness",
		.पढ़ो_u64 = mem_cgroup_swappiness_पढ़ो,
		.ग_लिखो_u64 = mem_cgroup_swappiness_ग_लिखो,
	पूर्ण,
	अणु
		.name = "move_charge_at_immigrate",
		.पढ़ो_u64 = mem_cgroup_move_अक्षरge_पढ़ो,
		.ग_लिखो_u64 = mem_cgroup_move_अक्षरge_ग_लिखो,
	पूर्ण,
	अणु
		.name = "oom_control",
		.seq_show = mem_cgroup_oom_control_पढ़ो,
		.ग_लिखो_u64 = mem_cgroup_oom_control_ग_लिखो,
		.निजी = MEMखाता_PRIVATE(_OOM_TYPE, OOM_CONTROL),
	पूर्ण,
	अणु
		.name = "pressure_level",
	पूर्ण,
#अगर_घोषित CONFIG_NUMA
	अणु
		.name = "numa_stat",
		.seq_show = memcg_numa_stat_show,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.name = "kmem.limit_in_bytes",
		.निजी = MEMखाता_PRIVATE(_KMEM, RES_LIMIT),
		.ग_लिखो = mem_cgroup_ग_लिखो,
		.पढ़ो_u64 = mem_cgroup_पढ़ो_u64,
	पूर्ण,
	अणु
		.name = "kmem.usage_in_bytes",
		.निजी = MEMखाता_PRIVATE(_KMEM, RES_USAGE),
		.पढ़ो_u64 = mem_cgroup_पढ़ो_u64,
	पूर्ण,
	अणु
		.name = "kmem.failcnt",
		.निजी = MEMखाता_PRIVATE(_KMEM, RES_FAILCNT),
		.ग_लिखो = mem_cgroup_reset,
		.पढ़ो_u64 = mem_cgroup_पढ़ो_u64,
	पूर्ण,
	अणु
		.name = "kmem.max_usage_in_bytes",
		.निजी = MEMखाता_PRIVATE(_KMEM, RES_MAX_USAGE),
		.ग_लिखो = mem_cgroup_reset,
		.पढ़ो_u64 = mem_cgroup_पढ़ो_u64,
	पूर्ण,
#अगर defined(CONFIG_MEMCG_KMEM) && \
	(defined(CONFIG_SLAB) || defined(CONFIG_SLUB_DEBUG))
	अणु
		.name = "kmem.slabinfo",
		.seq_show = memcg_slab_show,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.name = "kmem.tcp.limit_in_bytes",
		.निजी = MEMखाता_PRIVATE(_TCP, RES_LIMIT),
		.ग_लिखो = mem_cgroup_ग_लिखो,
		.पढ़ो_u64 = mem_cgroup_पढ़ो_u64,
	पूर्ण,
	अणु
		.name = "kmem.tcp.usage_in_bytes",
		.निजी = MEMखाता_PRIVATE(_TCP, RES_USAGE),
		.पढ़ो_u64 = mem_cgroup_पढ़ो_u64,
	पूर्ण,
	अणु
		.name = "kmem.tcp.failcnt",
		.निजी = MEMखाता_PRIVATE(_TCP, RES_FAILCNT),
		.ग_लिखो = mem_cgroup_reset,
		.पढ़ो_u64 = mem_cgroup_पढ़ो_u64,
	पूर्ण,
	अणु
		.name = "kmem.tcp.max_usage_in_bytes",
		.निजी = MEMखाता_PRIVATE(_TCP, RES_MAX_USAGE),
		.ग_लिखो = mem_cgroup_reset,
		.पढ़ो_u64 = mem_cgroup_पढ़ो_u64,
	पूर्ण,
	अणु पूर्ण,	/* terminate */
पूर्ण;

/*
 * Private memory cgroup IDR
 *
 * Swap-out records and page cache shaकरोw entries need to store memcg
 * references in स्थिरrained space, so we मुख्यtain an ID space that is
 * limited to 16 bit (MEM_CGROUP_ID_MAX), limiting the total number of
 * memory-controlled cgroups to 64k.
 *
 * However, there usually are many references to the offline CSS after
 * the cgroup has been destroyed, such as page cache or reclaimable
 * slab objects, that करोn't need to hang on to the ID. We want to keep
 * those dead CSS from occupying IDs, or we might quickly exhaust the
 * relatively small ID space and prevent the creation of new cgroups
 * even when there are much fewer than 64k cgroups - possibly none.
 *
 * Maपूर्णांकain a निजी 16-bit ID space क्रम memcg, and allow the ID to
 * be मुक्तd and recycled when it's no दीर्घer needed, which is usually
 * when the CSS is offlined.
 *
 * The only exception to that are records of swapped out पंचांगpfs/shmem
 * pages that need to be attributed to live ancestors on swapin. But
 * those references are manageable from userspace.
 */

अटल DEFINE_IDR(mem_cgroup_idr);

अटल व्योम mem_cgroup_id_हटाओ(काष्ठा mem_cgroup *memcg)
अणु
	अगर (memcg->id.id > 0) अणु
		idr_हटाओ(&mem_cgroup_idr, memcg->id.id);
		memcg->id.id = 0;
	पूर्ण
पूर्ण

अटल व्योम __maybe_unused mem_cgroup_id_get_many(काष्ठा mem_cgroup *memcg,
						  अचिन्हित पूर्णांक n)
अणु
	refcount_add(n, &memcg->id.ref);
पूर्ण

अटल व्योम mem_cgroup_id_put_many(काष्ठा mem_cgroup *memcg, अचिन्हित पूर्णांक n)
अणु
	अगर (refcount_sub_and_test(n, &memcg->id.ref)) अणु
		mem_cgroup_id_हटाओ(memcg);

		/* Memcg ID pins CSS */
		css_put(&memcg->css);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम mem_cgroup_id_put(काष्ठा mem_cgroup *memcg)
अणु
	mem_cgroup_id_put_many(memcg, 1);
पूर्ण

/**
 * mem_cgroup_from_id - look up a memcg from a memcg id
 * @id: the memcg id to look up
 *
 * Caller must hold rcu_पढ़ो_lock().
 */
काष्ठा mem_cgroup *mem_cgroup_from_id(अचिन्हित लघु id)
अणु
	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());
	वापस idr_find(&mem_cgroup_idr, id);
पूर्ण

अटल पूर्णांक alloc_mem_cgroup_per_node_info(काष्ठा mem_cgroup *memcg, पूर्णांक node)
अणु
	काष्ठा mem_cgroup_per_node *pn;
	पूर्णांक पंचांगp = node;
	/*
	 * This routine is called against possible nodes.
	 * But it's BUG to call kदो_स्मृति() against offline node.
	 *
	 * TODO: this routine can waste much memory क्रम nodes which will
	 *       never be onlined. It's better to use memory hotplug callback
	 *       function.
	 */
	अगर (!node_state(node, N_NORMAL_MEMORY))
		पंचांगp = -1;
	pn = kzalloc_node(माप(*pn), GFP_KERNEL, पंचांगp);
	अगर (!pn)
		वापस 1;

	pn->lruvec_stat_local = alloc_percpu_gfp(काष्ठा lruvec_stat,
						 GFP_KERNEL_ACCOUNT);
	अगर (!pn->lruvec_stat_local) अणु
		kमुक्त(pn);
		वापस 1;
	पूर्ण

	pn->lruvec_stat_cpu = alloc_percpu_gfp(काष्ठा batched_lruvec_stat,
					       GFP_KERNEL_ACCOUNT);
	अगर (!pn->lruvec_stat_cpu) अणु
		मुक्त_percpu(pn->lruvec_stat_local);
		kमुक्त(pn);
		वापस 1;
	पूर्ण

	lruvec_init(&pn->lruvec);
	pn->usage_in_excess = 0;
	pn->on_tree = false;
	pn->memcg = memcg;

	memcg->nodeinfo[node] = pn;
	वापस 0;
पूर्ण

अटल व्योम मुक्त_mem_cgroup_per_node_info(काष्ठा mem_cgroup *memcg, पूर्णांक node)
अणु
	काष्ठा mem_cgroup_per_node *pn = memcg->nodeinfo[node];

	अगर (!pn)
		वापस;

	मुक्त_percpu(pn->lruvec_stat_cpu);
	मुक्त_percpu(pn->lruvec_stat_local);
	kमुक्त(pn);
पूर्ण

अटल व्योम __mem_cgroup_मुक्त(काष्ठा mem_cgroup *memcg)
अणु
	पूर्णांक node;

	क्रम_each_node(node)
		मुक्त_mem_cgroup_per_node_info(memcg, node);
	मुक्त_percpu(memcg->vmstats_percpu);
	kमुक्त(memcg);
पूर्ण

अटल व्योम mem_cgroup_मुक्त(काष्ठा mem_cgroup *memcg)
अणु
	पूर्णांक cpu;

	memcg_wb_करोमुख्य_निकास(memcg);
	/*
	 * Flush percpu lruvec stats to guarantee the value
	 * correctness on parent's and all ancestor levels.
	 */
	क्रम_each_online_cpu(cpu)
		memcg_flush_lruvec_page_state(memcg, cpu);
	__mem_cgroup_मुक्त(memcg);
पूर्ण

अटल काष्ठा mem_cgroup *mem_cgroup_alloc(व्योम)
अणु
	काष्ठा mem_cgroup *memcg;
	अचिन्हित पूर्णांक size;
	पूर्णांक node;
	पूर्णांक __maybe_unused i;
	दीर्घ error = -ENOMEM;

	size = माप(काष्ठा mem_cgroup);
	size += nr_node_ids * माप(काष्ठा mem_cgroup_per_node *);

	memcg = kzalloc(size, GFP_KERNEL);
	अगर (!memcg)
		वापस ERR_PTR(error);

	memcg->id.id = idr_alloc(&mem_cgroup_idr, शून्य,
				 1, MEM_CGROUP_ID_MAX,
				 GFP_KERNEL);
	अगर (memcg->id.id < 0) अणु
		error = memcg->id.id;
		जाओ fail;
	पूर्ण

	memcg->vmstats_percpu = alloc_percpu_gfp(काष्ठा memcg_vmstats_percpu,
						 GFP_KERNEL_ACCOUNT);
	अगर (!memcg->vmstats_percpu)
		जाओ fail;

	क्रम_each_node(node)
		अगर (alloc_mem_cgroup_per_node_info(memcg, node))
			जाओ fail;

	अगर (memcg_wb_करोमुख्य_init(memcg, GFP_KERNEL))
		जाओ fail;

	INIT_WORK(&memcg->high_work, high_work_func);
	INIT_LIST_HEAD(&memcg->oom_notअगरy);
	mutex_init(&memcg->thresholds_lock);
	spin_lock_init(&memcg->move_lock);
	vmpressure_init(&memcg->vmpressure);
	INIT_LIST_HEAD(&memcg->event_list);
	spin_lock_init(&memcg->event_list_lock);
	memcg->socket_pressure = jअगरfies;
#अगर_घोषित CONFIG_MEMCG_KMEM
	memcg->kmemcg_id = -1;
	INIT_LIST_HEAD(&memcg->objcg_list);
#पूर्ण_अगर
#अगर_घोषित CONFIG_CGROUP_WRITEBACK
	INIT_LIST_HEAD(&memcg->cgwb_list);
	क्रम (i = 0; i < MEMCG_CGWB_FRN_CNT; i++)
		memcg->cgwb_frn[i].करोne =
			__WB_COMPLETION_INIT(&memcg_cgwb_frn_रुकोq);
#पूर्ण_अगर
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
	spin_lock_init(&memcg->deferred_split_queue.split_queue_lock);
	INIT_LIST_HEAD(&memcg->deferred_split_queue.split_queue);
	memcg->deferred_split_queue.split_queue_len = 0;
#पूर्ण_अगर
	idr_replace(&mem_cgroup_idr, memcg, memcg->id.id);
	वापस memcg;
fail:
	mem_cgroup_id_हटाओ(memcg);
	__mem_cgroup_मुक्त(memcg);
	वापस ERR_PTR(error);
पूर्ण

अटल काष्ठा cgroup_subsys_state * __ref
mem_cgroup_css_alloc(काष्ठा cgroup_subsys_state *parent_css)
अणु
	काष्ठा mem_cgroup *parent = mem_cgroup_from_css(parent_css);
	काष्ठा mem_cgroup *memcg, *old_memcg;
	दीर्घ error = -ENOMEM;

	old_memcg = set_active_memcg(parent);
	memcg = mem_cgroup_alloc();
	set_active_memcg(old_memcg);
	अगर (IS_ERR(memcg))
		वापस ERR_CAST(memcg);

	page_counter_set_high(&memcg->memory, PAGE_COUNTER_MAX);
	memcg->soft_limit = PAGE_COUNTER_MAX;
	page_counter_set_high(&memcg->swap, PAGE_COUNTER_MAX);
	अगर (parent) अणु
		memcg->swappiness = mem_cgroup_swappiness(parent);
		memcg->oom_समाप्त_disable = parent->oom_समाप्त_disable;

		page_counter_init(&memcg->memory, &parent->memory);
		page_counter_init(&memcg->swap, &parent->swap);
		page_counter_init(&memcg->kmem, &parent->kmem);
		page_counter_init(&memcg->tcpmem, &parent->tcpmem);
	पूर्ण अन्यथा अणु
		page_counter_init(&memcg->memory, शून्य);
		page_counter_init(&memcg->swap, शून्य);
		page_counter_init(&memcg->kmem, शून्य);
		page_counter_init(&memcg->tcpmem, शून्य);

		root_mem_cgroup = memcg;
		वापस &memcg->css;
	पूर्ण

	/* The following stuff करोes not apply to the root */
	error = memcg_online_kmem(memcg);
	अगर (error)
		जाओ fail;

	अगर (cgroup_subsys_on_dfl(memory_cgrp_subsys) && !cgroup_memory_nosocket)
		अटल_branch_inc(&memcg_sockets_enabled_key);

	वापस &memcg->css;
fail:
	mem_cgroup_id_हटाओ(memcg);
	mem_cgroup_मुक्त(memcg);
	वापस ERR_PTR(error);
पूर्ण

अटल पूर्णांक mem_cgroup_css_online(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_css(css);

	/*
	 * A memcg must be visible क्रम expand_shrinker_info()
	 * by the समय the maps are allocated. So, we allocate maps
	 * here, when क्रम_each_mem_cgroup() can't skip it.
	 */
	अगर (alloc_shrinker_info(memcg)) अणु
		mem_cgroup_id_हटाओ(memcg);
		वापस -ENOMEM;
	पूर्ण

	/* Online state pins memcg ID, memcg ID pins CSS */
	refcount_set(&memcg->id.ref, 1);
	css_get(css);
	वापस 0;
पूर्ण

अटल व्योम mem_cgroup_css_offline(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_css(css);
	काष्ठा mem_cgroup_event *event, *पंचांगp;

	/*
	 * Unरेजिस्टर events and notअगरy userspace.
	 * Notअगरy userspace about cgroup removing only after सूची_हटाओ of cgroup
	 * directory to aव्योम race between userspace and kernelspace.
	 */
	spin_lock(&memcg->event_list_lock);
	list_क्रम_each_entry_safe(event, पंचांगp, &memcg->event_list, list) अणु
		list_del_init(&event->list);
		schedule_work(&event->हटाओ);
	पूर्ण
	spin_unlock(&memcg->event_list_lock);

	page_counter_set_min(&memcg->memory, 0);
	page_counter_set_low(&memcg->memory, 0);

	memcg_offline_kmem(memcg);
	reparent_shrinker_deferred(memcg);
	wb_memcg_offline(memcg);

	drain_all_stock(memcg);

	mem_cgroup_id_put(memcg);
पूर्ण

अटल व्योम mem_cgroup_css_released(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_css(css);

	invalidate_reclaim_iterators(memcg);
पूर्ण

अटल व्योम mem_cgroup_css_मुक्त(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_css(css);
	पूर्णांक __maybe_unused i;

#अगर_घोषित CONFIG_CGROUP_WRITEBACK
	क्रम (i = 0; i < MEMCG_CGWB_FRN_CNT; i++)
		wb_रुको_क्रम_completion(&memcg->cgwb_frn[i].करोne);
#पूर्ण_अगर
	अगर (cgroup_subsys_on_dfl(memory_cgrp_subsys) && !cgroup_memory_nosocket)
		अटल_branch_dec(&memcg_sockets_enabled_key);

	अगर (!cgroup_subsys_on_dfl(memory_cgrp_subsys) && memcg->tcpmem_active)
		अटल_branch_dec(&memcg_sockets_enabled_key);

	vmpressure_cleanup(&memcg->vmpressure);
	cancel_work_sync(&memcg->high_work);
	mem_cgroup_हटाओ_from_trees(memcg);
	मुक्त_shrinker_info(memcg);
	memcg_मुक्त_kmem(memcg);
	mem_cgroup_मुक्त(memcg);
पूर्ण

/**
 * mem_cgroup_css_reset - reset the states of a mem_cgroup
 * @css: the target css
 *
 * Reset the states of the mem_cgroup associated with @css.  This is
 * invoked when the userland requests disabling on the शेष hierarchy
 * but the memcg is pinned through dependency.  The memcg should stop
 * applying policies and should revert to the vanilla state as it may be
 * made visible again.
 *
 * The current implementation only resets the essential configurations.
 * This needs to be expanded to cover all the visible parts.
 */
अटल व्योम mem_cgroup_css_reset(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_css(css);

	page_counter_set_max(&memcg->memory, PAGE_COUNTER_MAX);
	page_counter_set_max(&memcg->swap, PAGE_COUNTER_MAX);
	page_counter_set_max(&memcg->kmem, PAGE_COUNTER_MAX);
	page_counter_set_max(&memcg->tcpmem, PAGE_COUNTER_MAX);
	page_counter_set_min(&memcg->memory, 0);
	page_counter_set_low(&memcg->memory, 0);
	page_counter_set_high(&memcg->memory, PAGE_COUNTER_MAX);
	memcg->soft_limit = PAGE_COUNTER_MAX;
	page_counter_set_high(&memcg->swap, PAGE_COUNTER_MAX);
	memcg_wb_करोमुख्य_size_changed(memcg);
पूर्ण

अटल व्योम mem_cgroup_css_rstat_flush(काष्ठा cgroup_subsys_state *css, पूर्णांक cpu)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_css(css);
	काष्ठा mem_cgroup *parent = parent_mem_cgroup(memcg);
	काष्ठा memcg_vmstats_percpu *statc;
	दीर्घ delta, v;
	पूर्णांक i;

	statc = per_cpu_ptr(memcg->vmstats_percpu, cpu);

	क्रम (i = 0; i < MEMCG_NR_STAT; i++) अणु
		/*
		 * Collect the aggregated propagation counts of groups
		 * below us. We're in a per-cpu loop here and this is
		 * a global counter, so the first cycle will get them.
		 */
		delta = memcg->vmstats.state_pending[i];
		अगर (delta)
			memcg->vmstats.state_pending[i] = 0;

		/* Add CPU changes on this level since the last flush */
		v = READ_ONCE(statc->state[i]);
		अगर (v != statc->state_prev[i]) अणु
			delta += v - statc->state_prev[i];
			statc->state_prev[i] = v;
		पूर्ण

		अगर (!delta)
			जारी;

		/* Aggregate counts on this level and propagate upwards */
		memcg->vmstats.state[i] += delta;
		अगर (parent)
			parent->vmstats.state_pending[i] += delta;
	पूर्ण

	क्रम (i = 0; i < NR_VM_EVENT_ITEMS; i++) अणु
		delta = memcg->vmstats.events_pending[i];
		अगर (delta)
			memcg->vmstats.events_pending[i] = 0;

		v = READ_ONCE(statc->events[i]);
		अगर (v != statc->events_prev[i]) अणु
			delta += v - statc->events_prev[i];
			statc->events_prev[i] = v;
		पूर्ण

		अगर (!delta)
			जारी;

		memcg->vmstats.events[i] += delta;
		अगर (parent)
			parent->vmstats.events_pending[i] += delta;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_MMU
/* Handlers क्रम move अक्षरge at task migration. */
अटल पूर्णांक mem_cgroup_करो_preअक्षरge(अचिन्हित दीर्घ count)
अणु
	पूर्णांक ret;

	/* Try a single bulk अक्षरge without reclaim first, kswapd may wake */
	ret = try_अक्षरge(mc.to, GFP_KERNEL & ~__GFP_सूचीECT_RECLAIM, count);
	अगर (!ret) अणु
		mc.preअक्षरge += count;
		वापस ret;
	पूर्ण

	/* Try अक्षरges one by one with reclaim, but करो not retry */
	जबतक (count--) अणु
		ret = try_अक्षरge(mc.to, GFP_KERNEL | __GFP_NORETRY, 1);
		अगर (ret)
			वापस ret;
		mc.preअक्षरge++;
		cond_resched();
	पूर्ण
	वापस 0;
पूर्ण

जोड़ mc_target अणु
	काष्ठा page	*page;
	swp_entry_t	ent;
पूर्ण;

क्रमागत mc_target_type अणु
	MC_TARGET_NONE = 0,
	MC_TARGET_PAGE,
	MC_TARGET_SWAP,
	MC_TARGET_DEVICE,
पूर्ण;

अटल काष्ठा page *mc_handle_present_pte(काष्ठा vm_area_काष्ठा *vma,
						अचिन्हित दीर्घ addr, pte_t ptent)
अणु
	काष्ठा page *page = vm_normal_page(vma, addr, ptent);

	अगर (!page || !page_mapped(page))
		वापस शून्य;
	अगर (PageAnon(page)) अणु
		अगर (!(mc.flags & MOVE_ANON))
			वापस शून्य;
	पूर्ण अन्यथा अणु
		अगर (!(mc.flags & MOVE_खाता))
			वापस शून्य;
	पूर्ण
	अगर (!get_page_unless_zero(page))
		वापस शून्य;

	वापस page;
पूर्ण

#अगर defined(CONFIG_SWAP) || defined(CONFIG_DEVICE_PRIVATE)
अटल काष्ठा page *mc_handle_swap_pte(काष्ठा vm_area_काष्ठा *vma,
			pte_t ptent, swp_entry_t *entry)
अणु
	काष्ठा page *page = शून्य;
	swp_entry_t ent = pte_to_swp_entry(ptent);

	अगर (!(mc.flags & MOVE_ANON))
		वापस शून्य;

	/*
	 * Handle MEMORY_DEVICE_PRIVATE which are ZONE_DEVICE page beदीर्घing to
	 * a device and because they are not accessible by CPU they are store
	 * as special swap entry in the CPU page table.
	 */
	अगर (is_device_निजी_entry(ent)) अणु
		page = device_निजी_entry_to_page(ent);
		/*
		 * MEMORY_DEVICE_PRIVATE means ZONE_DEVICE page and which have
		 * a refcount of 1 when मुक्त (unlike normal page)
		 */
		अगर (!page_ref_add_unless(page, 1, 1))
			वापस शून्य;
		वापस page;
	पूर्ण

	अगर (non_swap_entry(ent))
		वापस शून्य;

	/*
	 * Because lookup_swap_cache() updates some statistics counter,
	 * we call find_get_page() with swapper_space directly.
	 */
	page = find_get_page(swap_address_space(ent), swp_offset(ent));
	entry->val = ent.val;

	वापस page;
पूर्ण
#अन्यथा
अटल काष्ठा page *mc_handle_swap_pte(काष्ठा vm_area_काष्ठा *vma,
			pte_t ptent, swp_entry_t *entry)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा page *mc_handle_file_pte(काष्ठा vm_area_काष्ठा *vma,
			अचिन्हित दीर्घ addr, pte_t ptent, swp_entry_t *entry)
अणु
	अगर (!vma->vm_file) /* anonymous vma */
		वापस शून्य;
	अगर (!(mc.flags & MOVE_खाता))
		वापस शून्य;

	/* page is moved even अगर it's not RSS of this task(page-faulted). */
	/* shmem/पंचांगpfs may report page out on swap: account क्रम that too. */
	वापस find_get_incore_page(vma->vm_file->f_mapping,
			linear_page_index(vma, addr));
पूर्ण

/**
 * mem_cgroup_move_account - move account of the page
 * @page: the page
 * @compound: अक्षरge the page as compound or small page
 * @from: mem_cgroup which the page is moved from.
 * @to:	mem_cgroup which the page is moved to. @from != @to.
 *
 * The caller must make sure the page is not on LRU (isolate_page() is useful.)
 *
 * This function करोesn't do "charge" to new cgroup and doesn't करो "uncharge"
 * from old cgroup.
 */
अटल पूर्णांक mem_cgroup_move_account(काष्ठा page *page,
				   bool compound,
				   काष्ठा mem_cgroup *from,
				   काष्ठा mem_cgroup *to)
अणु
	काष्ठा lruvec *from_vec, *to_vec;
	काष्ठा pglist_data *pgdat;
	अचिन्हित पूर्णांक nr_pages = compound ? thp_nr_pages(page) : 1;
	पूर्णांक ret;

	VM_BUG_ON(from == to);
	VM_BUG_ON_PAGE(PageLRU(page), page);
	VM_BUG_ON(compound && !PageTransHuge(page));

	/*
	 * Prevent mem_cgroup_migrate() from looking at
	 * page's memory cgroup of its source page जबतक we change it.
	 */
	ret = -EBUSY;
	अगर (!trylock_page(page))
		जाओ out;

	ret = -EINVAL;
	अगर (page_memcg(page) != from)
		जाओ out_unlock;

	pgdat = page_pgdat(page);
	from_vec = mem_cgroup_lruvec(from, pgdat);
	to_vec = mem_cgroup_lruvec(to, pgdat);

	lock_page_memcg(page);

	अगर (PageAnon(page)) अणु
		अगर (page_mapped(page)) अणु
			__mod_lruvec_state(from_vec, NR_ANON_MAPPED, -nr_pages);
			__mod_lruvec_state(to_vec, NR_ANON_MAPPED, nr_pages);
			अगर (PageTransHuge(page)) अणु
				__mod_lruvec_state(from_vec, NR_ANON_THPS,
						   -nr_pages);
				__mod_lruvec_state(to_vec, NR_ANON_THPS,
						   nr_pages);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		__mod_lruvec_state(from_vec, NR_खाता_PAGES, -nr_pages);
		__mod_lruvec_state(to_vec, NR_खाता_PAGES, nr_pages);

		अगर (PageSwapBacked(page)) अणु
			__mod_lruvec_state(from_vec, NR_SHMEM, -nr_pages);
			__mod_lruvec_state(to_vec, NR_SHMEM, nr_pages);
		पूर्ण

		अगर (page_mapped(page)) अणु
			__mod_lruvec_state(from_vec, NR_खाता_MAPPED, -nr_pages);
			__mod_lruvec_state(to_vec, NR_खाता_MAPPED, nr_pages);
		पूर्ण

		अगर (PageDirty(page)) अणु
			काष्ठा address_space *mapping = page_mapping(page);

			अगर (mapping_can_ग_लिखोback(mapping)) अणु
				__mod_lruvec_state(from_vec, NR_खाता_सूचीTY,
						   -nr_pages);
				__mod_lruvec_state(to_vec, NR_खाता_सूचीTY,
						   nr_pages);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (PageWriteback(page)) अणु
		__mod_lruvec_state(from_vec, NR_WRITEBACK, -nr_pages);
		__mod_lruvec_state(to_vec, NR_WRITEBACK, nr_pages);
	पूर्ण

	/*
	 * All state has been migrated, let's चयन to the new memcg.
	 *
	 * It is safe to change page's memcg here because the page
	 * is referenced, अक्षरged, isolated, and locked: we can't race
	 * with (un)अक्षरging, migration, LRU putback, or anything अन्यथा
	 * that would rely on a stable page's memory cgroup.
	 *
	 * Note that lock_page_memcg is a memcg lock, not a page lock,
	 * to save space. As soon as we चयन page's memory cgroup to a
	 * new memcg that isn't locked, the above state can change
	 * concurrently again. Make sure we're truly करोne with it.
	 */
	smp_mb();

	css_get(&to->css);
	css_put(&from->css);

	page->memcg_data = (अचिन्हित दीर्घ)to;

	__unlock_page_memcg(from);

	ret = 0;

	local_irq_disable();
	mem_cgroup_अक्षरge_statistics(to, page, nr_pages);
	memcg_check_events(to, page);
	mem_cgroup_अक्षरge_statistics(from, page, -nr_pages);
	memcg_check_events(from, page);
	local_irq_enable();
out_unlock:
	unlock_page(page);
out:
	वापस ret;
पूर्ण

/**
 * get_mctgt_type - get target type of moving अक्षरge
 * @vma: the vma the pte to be checked beदीर्घs
 * @addr: the address corresponding to the pte to be checked
 * @ptent: the pte to be checked
 * @target: the poपूर्णांकer the target page or swap ent will be stored(can be शून्य)
 *
 * Returns
 *   0(MC_TARGET_NONE): अगर the pte is not a target क्रम move अक्षरge.
 *   1(MC_TARGET_PAGE): अगर the page corresponding to this pte is a target क्रम
 *     move अक्षरge. अगर @target is not शून्य, the page is stored in target->page
 *     with extra refcnt got(Callers should handle it).
 *   2(MC_TARGET_SWAP): अगर the swap entry corresponding to this pte is a
 *     target क्रम अक्षरge migration. अगर @target is not शून्य, the entry is stored
 *     in target->ent.
 *   3(MC_TARGET_DEVICE): like MC_TARGET_PAGE  but page is MEMORY_DEVICE_PRIVATE
 *     (so ZONE_DEVICE page and thus not on the lru).
 *     For now we such page is अक्षरge like a regular page would be as क्रम all
 *     पूर्णांकent and purposes it is just special memory taking the place of a
 *     regular page.
 *
 *     See Documentations/vm/hmm.txt and include/linux/hmm.h
 *
 * Called with pte lock held.
 */

अटल क्रमागत mc_target_type get_mctgt_type(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ addr, pte_t ptent, जोड़ mc_target *target)
अणु
	काष्ठा page *page = शून्य;
	क्रमागत mc_target_type ret = MC_TARGET_NONE;
	swp_entry_t ent = अणु .val = 0 पूर्ण;

	अगर (pte_present(ptent))
		page = mc_handle_present_pte(vma, addr, ptent);
	अन्यथा अगर (is_swap_pte(ptent))
		page = mc_handle_swap_pte(vma, ptent, &ent);
	अन्यथा अगर (pte_none(ptent))
		page = mc_handle_file_pte(vma, addr, ptent, &ent);

	अगर (!page && !ent.val)
		वापस ret;
	अगर (page) अणु
		/*
		 * Do only loose check w/o serialization.
		 * mem_cgroup_move_account() checks the page is valid or
		 * not under LRU exclusion.
		 */
		अगर (page_memcg(page) == mc.from) अणु
			ret = MC_TARGET_PAGE;
			अगर (is_device_निजी_page(page))
				ret = MC_TARGET_DEVICE;
			अगर (target)
				target->page = page;
		पूर्ण
		अगर (!ret || !target)
			put_page(page);
	पूर्ण
	/*
	 * There is a swap entry and a page करोesn't exist or isn't अक्षरged.
	 * But we cannot move a tail-page in a THP.
	 */
	अगर (ent.val && !ret && (!page || !PageTransCompound(page)) &&
	    mem_cgroup_id(mc.from) == lookup_swap_cgroup_id(ent)) अणु
		ret = MC_TARGET_SWAP;
		अगर (target)
			target->ent = ent;
	पूर्ण
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
/*
 * We करोn't consider PMD mapped swapping or file mapped pages because THP करोes
 * not support them क्रम now.
 * Caller should make sure that pmd_trans_huge(pmd) is true.
 */
अटल क्रमागत mc_target_type get_mctgt_type_thp(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ addr, pmd_t pmd, जोड़ mc_target *target)
अणु
	काष्ठा page *page = शून्य;
	क्रमागत mc_target_type ret = MC_TARGET_NONE;

	अगर (unlikely(is_swap_pmd(pmd))) अणु
		VM_BUG_ON(thp_migration_supported() &&
				  !is_pmd_migration_entry(pmd));
		वापस ret;
	पूर्ण
	page = pmd_page(pmd);
	VM_BUG_ON_PAGE(!page || !PageHead(page), page);
	अगर (!(mc.flags & MOVE_ANON))
		वापस ret;
	अगर (page_memcg(page) == mc.from) अणु
		ret = MC_TARGET_PAGE;
		अगर (target) अणु
			get_page(page);
			target->page = page;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण
#अन्यथा
अटल अंतरभूत क्रमागत mc_target_type get_mctgt_type_thp(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ addr, pmd_t pmd, जोड़ mc_target *target)
अणु
	वापस MC_TARGET_NONE;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक mem_cgroup_count_preअक्षरge_pte_range(pmd_t *pmd,
					अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
					काष्ठा mm_walk *walk)
अणु
	काष्ठा vm_area_काष्ठा *vma = walk->vma;
	pte_t *pte;
	spinlock_t *ptl;

	ptl = pmd_trans_huge_lock(pmd, vma);
	अगर (ptl) अणु
		/*
		 * Note their can not be MC_TARGET_DEVICE क्रम now as we करो not
		 * support transparent huge page with MEMORY_DEVICE_PRIVATE but
		 * this might change.
		 */
		अगर (get_mctgt_type_thp(vma, addr, *pmd, शून्य) == MC_TARGET_PAGE)
			mc.preअक्षरge += HPAGE_PMD_NR;
		spin_unlock(ptl);
		वापस 0;
	पूर्ण

	अगर (pmd_trans_unstable(pmd))
		वापस 0;
	pte = pte_offset_map_lock(vma->vm_mm, pmd, addr, &ptl);
	क्रम (; addr != end; pte++, addr += PAGE_SIZE)
		अगर (get_mctgt_type(vma, addr, *pte, शून्य))
			mc.preअक्षरge++;	/* increment preअक्षरge temporarily */
	pte_unmap_unlock(pte - 1, ptl);
	cond_resched();

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mm_walk_ops preअक्षरge_walk_ops = अणु
	.pmd_entry	= mem_cgroup_count_preअक्षरge_pte_range,
पूर्ण;

अटल अचिन्हित दीर्घ mem_cgroup_count_preअक्षरge(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ preअक्षरge;

	mmap_पढ़ो_lock(mm);
	walk_page_range(mm, 0, mm->highest_vm_end, &preअक्षरge_walk_ops, शून्य);
	mmap_पढ़ो_unlock(mm);

	preअक्षरge = mc.preअक्षरge;
	mc.preअक्षरge = 0;

	वापस preअक्षरge;
पूर्ण

अटल पूर्णांक mem_cgroup_preअक्षरge_mc(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ preअक्षरge = mem_cgroup_count_preअक्षरge(mm);

	VM_BUG_ON(mc.moving_task);
	mc.moving_task = current;
	वापस mem_cgroup_करो_preअक्षरge(preअक्षरge);
पूर्ण

/* cancels all extra अक्षरges on mc.from and mc.to, and wakes up all रुकोers. */
अटल व्योम __mem_cgroup_clear_mc(व्योम)
अणु
	काष्ठा mem_cgroup *from = mc.from;
	काष्ठा mem_cgroup *to = mc.to;

	/* we must unअक्षरge all the leftover preअक्षरges from mc.to */
	अगर (mc.preअक्षरge) अणु
		cancel_अक्षरge(mc.to, mc.preअक्षरge);
		mc.preअक्षरge = 0;
	पूर्ण
	/*
	 * we didn't unअक्षरge from mc.from at mem_cgroup_move_account(), so
	 * we must unअक्षरge here.
	 */
	अगर (mc.moved_अक्षरge) अणु
		cancel_अक्षरge(mc.from, mc.moved_अक्षरge);
		mc.moved_अक्षरge = 0;
	पूर्ण
	/* we must fixup refcnts and अक्षरges */
	अगर (mc.moved_swap) अणु
		/* unअक्षरge swap account from the old cgroup */
		अगर (!mem_cgroup_is_root(mc.from))
			page_counter_unअक्षरge(&mc.from->memsw, mc.moved_swap);

		mem_cgroup_id_put_many(mc.from, mc.moved_swap);

		/*
		 * we अक्षरged both to->memory and to->memsw, so we
		 * should unअक्षरge to->memory.
		 */
		अगर (!mem_cgroup_is_root(mc.to))
			page_counter_unअक्षरge(&mc.to->memory, mc.moved_swap);

		mc.moved_swap = 0;
	पूर्ण
	memcg_oom_recover(from);
	memcg_oom_recover(to);
	wake_up_all(&mc.रुकोq);
पूर्ण

अटल व्योम mem_cgroup_clear_mc(व्योम)
अणु
	काष्ठा mm_काष्ठा *mm = mc.mm;

	/*
	 * we must clear moving_task beक्रमe waking up रुकोers at the end of
	 * task migration.
	 */
	mc.moving_task = शून्य;
	__mem_cgroup_clear_mc();
	spin_lock(&mc.lock);
	mc.from = शून्य;
	mc.to = शून्य;
	mc.mm = शून्य;
	spin_unlock(&mc.lock);

	mmput(mm);
पूर्ण

अटल पूर्णांक mem_cgroup_can_attach(काष्ठा cgroup_taskset *tset)
अणु
	काष्ठा cgroup_subsys_state *css;
	काष्ठा mem_cgroup *memcg = शून्य; /* unneeded init to make gcc happy */
	काष्ठा mem_cgroup *from;
	काष्ठा task_काष्ठा *leader, *p;
	काष्ठा mm_काष्ठा *mm;
	अचिन्हित दीर्घ move_flags;
	पूर्णांक ret = 0;

	/* अक्षरge immigration isn't supported on the शेष hierarchy */
	अगर (cgroup_subsys_on_dfl(memory_cgrp_subsys))
		वापस 0;

	/*
	 * Multi-process migrations only happen on the शेष hierarchy
	 * where अक्षरge immigration is not used.  Perक्रमm अक्षरge
	 * immigration अगर @tset contains a leader and whine अगर there are
	 * multiple.
	 */
	p = शून्य;
	cgroup_taskset_क्रम_each_leader(leader, css, tset) अणु
		WARN_ON_ONCE(p);
		p = leader;
		memcg = mem_cgroup_from_css(css);
	पूर्ण
	अगर (!p)
		वापस 0;

	/*
	 * We are now committed to this value whatever it is. Changes in this
	 * tunable will only affect upcoming migrations, not the current one.
	 * So we need to save it, and keep it going.
	 */
	move_flags = READ_ONCE(memcg->move_अक्षरge_at_immigrate);
	अगर (!move_flags)
		वापस 0;

	from = mem_cgroup_from_task(p);

	VM_BUG_ON(from == memcg);

	mm = get_task_mm(p);
	अगर (!mm)
		वापस 0;
	/* We move अक्षरges only when we move a owner of the mm */
	अगर (mm->owner == p) अणु
		VM_BUG_ON(mc.from);
		VM_BUG_ON(mc.to);
		VM_BUG_ON(mc.preअक्षरge);
		VM_BUG_ON(mc.moved_अक्षरge);
		VM_BUG_ON(mc.moved_swap);

		spin_lock(&mc.lock);
		mc.mm = mm;
		mc.from = from;
		mc.to = memcg;
		mc.flags = move_flags;
		spin_unlock(&mc.lock);
		/* We set mc.moving_task later */

		ret = mem_cgroup_preअक्षरge_mc(mm);
		अगर (ret)
			mem_cgroup_clear_mc();
	पूर्ण अन्यथा अणु
		mmput(mm);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम mem_cgroup_cancel_attach(काष्ठा cgroup_taskset *tset)
अणु
	अगर (mc.to)
		mem_cgroup_clear_mc();
पूर्ण

अटल पूर्णांक mem_cgroup_move_अक्षरge_pte_range(pmd_t *pmd,
				अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				काष्ठा mm_walk *walk)
अणु
	पूर्णांक ret = 0;
	काष्ठा vm_area_काष्ठा *vma = walk->vma;
	pte_t *pte;
	spinlock_t *ptl;
	क्रमागत mc_target_type target_type;
	जोड़ mc_target target;
	काष्ठा page *page;

	ptl = pmd_trans_huge_lock(pmd, vma);
	अगर (ptl) अणु
		अगर (mc.preअक्षरge < HPAGE_PMD_NR) अणु
			spin_unlock(ptl);
			वापस 0;
		पूर्ण
		target_type = get_mctgt_type_thp(vma, addr, *pmd, &target);
		अगर (target_type == MC_TARGET_PAGE) अणु
			page = target.page;
			अगर (!isolate_lru_page(page)) अणु
				अगर (!mem_cgroup_move_account(page, true,
							     mc.from, mc.to)) अणु
					mc.preअक्षरge -= HPAGE_PMD_NR;
					mc.moved_अक्षरge += HPAGE_PMD_NR;
				पूर्ण
				putback_lru_page(page);
			पूर्ण
			put_page(page);
		पूर्ण अन्यथा अगर (target_type == MC_TARGET_DEVICE) अणु
			page = target.page;
			अगर (!mem_cgroup_move_account(page, true,
						     mc.from, mc.to)) अणु
				mc.preअक्षरge -= HPAGE_PMD_NR;
				mc.moved_अक्षरge += HPAGE_PMD_NR;
			पूर्ण
			put_page(page);
		पूर्ण
		spin_unlock(ptl);
		वापस 0;
	पूर्ण

	अगर (pmd_trans_unstable(pmd))
		वापस 0;
retry:
	pte = pte_offset_map_lock(vma->vm_mm, pmd, addr, &ptl);
	क्रम (; addr != end; addr += PAGE_SIZE) अणु
		pte_t ptent = *(pte++);
		bool device = false;
		swp_entry_t ent;

		अगर (!mc.preअक्षरge)
			अवरोध;

		चयन (get_mctgt_type(vma, addr, ptent, &target)) अणु
		हाल MC_TARGET_DEVICE:
			device = true;
			fallthrough;
		हाल MC_TARGET_PAGE:
			page = target.page;
			/*
			 * We can have a part of the split pmd here. Moving it
			 * can be करोne but it would be too convoluted so simply
			 * ignore such a partial THP and keep it in original
			 * memcg. There should be somebody mapping the head.
			 */
			अगर (PageTransCompound(page))
				जाओ put;
			अगर (!device && isolate_lru_page(page))
				जाओ put;
			अगर (!mem_cgroup_move_account(page, false,
						mc.from, mc.to)) अणु
				mc.preअक्षरge--;
				/* we unअक्षरge from mc.from later. */
				mc.moved_अक्षरge++;
			पूर्ण
			अगर (!device)
				putback_lru_page(page);
put:			/* get_mctgt_type() माला_लो the page */
			put_page(page);
			अवरोध;
		हाल MC_TARGET_SWAP:
			ent = target.ent;
			अगर (!mem_cgroup_move_swap_account(ent, mc.from, mc.to)) अणु
				mc.preअक्षरge--;
				mem_cgroup_id_get_many(mc.to, 1);
				/* we fixup other refcnts and अक्षरges later. */
				mc.moved_swap++;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	pte_unmap_unlock(pte - 1, ptl);
	cond_resched();

	अगर (addr != end) अणु
		/*
		 * We have consumed all preअक्षरges we got in can_attach().
		 * We try अक्षरge one by one, but करोn't करो any additional
		 * अक्षरges to mc.to अगर we have failed in अक्षरge once in attach()
		 * phase.
		 */
		ret = mem_cgroup_करो_preअक्षरge(1);
		अगर (!ret)
			जाओ retry;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा mm_walk_ops अक्षरge_walk_ops = अणु
	.pmd_entry	= mem_cgroup_move_अक्षरge_pte_range,
पूर्ण;

अटल व्योम mem_cgroup_move_अक्षरge(व्योम)
अणु
	lru_add_drain_all();
	/*
	 * Signal lock_page_memcg() to take the memcg's move_lock
	 * जबतक we're moving its pages to another memcg. Then रुको
	 * क्रम alपढ़ोy started RCU-only updates to finish.
	 */
	atomic_inc(&mc.from->moving_account);
	synchronize_rcu();
retry:
	अगर (unlikely(!mmap_पढ़ो_trylock(mc.mm))) अणु
		/*
		 * Someone who are holding the mmap_lock might be रुकोing in
		 * रुकोq. So we cancel all extra अक्षरges, wake up all रुकोers,
		 * and retry. Because we cancel preअक्षरges, we might not be able
		 * to move enough अक्षरges, but moving अक्षरge is a best-efक्रमt
		 * feature anyway, so it wouldn't be a big problem.
		 */
		__mem_cgroup_clear_mc();
		cond_resched();
		जाओ retry;
	पूर्ण
	/*
	 * When we have consumed all preअक्षरges and failed in करोing
	 * additional अक्षरge, the page walk just पातs.
	 */
	walk_page_range(mc.mm, 0, mc.mm->highest_vm_end, &अक्षरge_walk_ops,
			शून्य);

	mmap_पढ़ो_unlock(mc.mm);
	atomic_dec(&mc.from->moving_account);
पूर्ण

अटल व्योम mem_cgroup_move_task(व्योम)
अणु
	अगर (mc.to) अणु
		mem_cgroup_move_अक्षरge();
		mem_cgroup_clear_mc();
	पूर्ण
पूर्ण
#अन्यथा	/* !CONFIG_MMU */
अटल पूर्णांक mem_cgroup_can_attach(काष्ठा cgroup_taskset *tset)
अणु
	वापस 0;
पूर्ण
अटल व्योम mem_cgroup_cancel_attach(काष्ठा cgroup_taskset *tset)
अणु
पूर्ण
अटल व्योम mem_cgroup_move_task(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक seq_माला_दो_memcg_tunable(काष्ठा seq_file *m, अचिन्हित दीर्घ value)
अणु
	अगर (value == PAGE_COUNTER_MAX)
		seq_माला_दो(m, "max\n");
	अन्यथा
		seq_म_लिखो(m, "%llu\n", (u64)value * PAGE_SIZE);

	वापस 0;
पूर्ण

अटल u64 memory_current_पढ़ो(काष्ठा cgroup_subsys_state *css,
			       काष्ठा cftype *cft)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_css(css);

	वापस (u64)page_counter_पढ़ो(&memcg->memory) * PAGE_SIZE;
पूर्ण

अटल पूर्णांक memory_min_show(काष्ठा seq_file *m, व्योम *v)
अणु
	वापस seq_माला_दो_memcg_tunable(m,
		READ_ONCE(mem_cgroup_from_seq(m)->memory.min));
पूर्ण

अटल sमाप_प्रकार memory_min_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
				अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_css(of_css(of));
	अचिन्हित दीर्घ min;
	पूर्णांक err;

	buf = म_मालाip(buf);
	err = page_counter_memparse(buf, "max", &min);
	अगर (err)
		वापस err;

	page_counter_set_min(&memcg->memory, min);

	वापस nbytes;
पूर्ण

अटल पूर्णांक memory_low_show(काष्ठा seq_file *m, व्योम *v)
अणु
	वापस seq_माला_दो_memcg_tunable(m,
		READ_ONCE(mem_cgroup_from_seq(m)->memory.low));
पूर्ण

अटल sमाप_प्रकार memory_low_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
				अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_css(of_css(of));
	अचिन्हित दीर्घ low;
	पूर्णांक err;

	buf = म_मालाip(buf);
	err = page_counter_memparse(buf, "max", &low);
	अगर (err)
		वापस err;

	page_counter_set_low(&memcg->memory, low);

	वापस nbytes;
पूर्ण

अटल पूर्णांक memory_high_show(काष्ठा seq_file *m, व्योम *v)
अणु
	वापस seq_माला_दो_memcg_tunable(m,
		READ_ONCE(mem_cgroup_from_seq(m)->memory.high));
पूर्ण

अटल sमाप_प्रकार memory_high_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
				 अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_css(of_css(of));
	अचिन्हित पूर्णांक nr_retries = MAX_RECLAIM_RETRIES;
	bool drained = false;
	अचिन्हित दीर्घ high;
	पूर्णांक err;

	buf = म_मालाip(buf);
	err = page_counter_memparse(buf, "max", &high);
	अगर (err)
		वापस err;

	page_counter_set_high(&memcg->memory, high);

	क्रम (;;) अणु
		अचिन्हित दीर्घ nr_pages = page_counter_पढ़ो(&memcg->memory);
		अचिन्हित दीर्घ reclaimed;

		अगर (nr_pages <= high)
			अवरोध;

		अगर (संकेत_pending(current))
			अवरोध;

		अगर (!drained) अणु
			drain_all_stock(memcg);
			drained = true;
			जारी;
		पूर्ण

		reclaimed = try_to_मुक्त_mem_cgroup_pages(memcg, nr_pages - high,
							 GFP_KERNEL, true);

		अगर (!reclaimed && !nr_retries--)
			अवरोध;
	पूर्ण

	memcg_wb_करोमुख्य_size_changed(memcg);
	वापस nbytes;
पूर्ण

अटल पूर्णांक memory_max_show(काष्ठा seq_file *m, व्योम *v)
अणु
	वापस seq_माला_दो_memcg_tunable(m,
		READ_ONCE(mem_cgroup_from_seq(m)->memory.max));
पूर्ण

अटल sमाप_प्रकार memory_max_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
				अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_css(of_css(of));
	अचिन्हित पूर्णांक nr_reclaims = MAX_RECLAIM_RETRIES;
	bool drained = false;
	अचिन्हित दीर्घ max;
	पूर्णांक err;

	buf = म_मालाip(buf);
	err = page_counter_memparse(buf, "max", &max);
	अगर (err)
		वापस err;

	xchg(&memcg->memory.max, max);

	क्रम (;;) अणु
		अचिन्हित दीर्घ nr_pages = page_counter_पढ़ो(&memcg->memory);

		अगर (nr_pages <= max)
			अवरोध;

		अगर (संकेत_pending(current))
			अवरोध;

		अगर (!drained) अणु
			drain_all_stock(memcg);
			drained = true;
			जारी;
		पूर्ण

		अगर (nr_reclaims) अणु
			अगर (!try_to_मुक्त_mem_cgroup_pages(memcg, nr_pages - max,
							  GFP_KERNEL, true))
				nr_reclaims--;
			जारी;
		पूर्ण

		memcg_memory_event(memcg, MEMCG_OOM);
		अगर (!mem_cgroup_out_of_memory(memcg, GFP_KERNEL, 0))
			अवरोध;
	पूर्ण

	memcg_wb_करोमुख्य_size_changed(memcg);
	वापस nbytes;
पूर्ण

अटल व्योम __memory_events_show(काष्ठा seq_file *m, atomic_दीर्घ_t *events)
अणु
	seq_म_लिखो(m, "low %lu\n", atomic_दीर्घ_पढ़ो(&events[MEMCG_LOW]));
	seq_म_लिखो(m, "high %lu\n", atomic_दीर्घ_पढ़ो(&events[MEMCG_HIGH]));
	seq_म_लिखो(m, "max %lu\n", atomic_दीर्घ_पढ़ो(&events[MEMCG_MAX]));
	seq_म_लिखो(m, "oom %lu\n", atomic_दीर्घ_पढ़ो(&events[MEMCG_OOM]));
	seq_म_लिखो(m, "oom_kill %lu\n",
		   atomic_दीर्घ_पढ़ो(&events[MEMCG_OOM_KILL]));
पूर्ण

अटल पूर्णांक memory_events_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_seq(m);

	__memory_events_show(m, memcg->memory_events);
	वापस 0;
पूर्ण

अटल पूर्णांक memory_events_local_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_seq(m);

	__memory_events_show(m, memcg->memory_events_local);
	वापस 0;
पूर्ण

अटल पूर्णांक memory_stat_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_seq(m);
	अक्षर *buf;

	buf = memory_stat_क्रमmat(memcg);
	अगर (!buf)
		वापस -ENOMEM;
	seq_माला_दो(m, buf);
	kमुक्त(buf);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NUMA
अटल अंतरभूत अचिन्हित दीर्घ lruvec_page_state_output(काष्ठा lruvec *lruvec,
						     पूर्णांक item)
अणु
	वापस lruvec_page_state(lruvec, item) * memcg_page_state_unit(item);
पूर्ण

अटल पूर्णांक memory_numa_stat_show(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक i;
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_seq(m);

	क्रम (i = 0; i < ARRAY_SIZE(memory_stats); i++) अणु
		पूर्णांक nid;

		अगर (memory_stats[i].idx >= NR_VM_NODE_STAT_ITEMS)
			जारी;

		seq_म_लिखो(m, "%s", memory_stats[i].name);
		क्रम_each_node_state(nid, N_MEMORY) अणु
			u64 size;
			काष्ठा lruvec *lruvec;

			lruvec = mem_cgroup_lruvec(memcg, NODE_DATA(nid));
			size = lruvec_page_state_output(lruvec,
							memory_stats[i].idx);
			seq_म_लिखो(m, " N%d=%llu", nid, size);
		पूर्ण
		seq_अ_दो(m, '\n');
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक memory_oom_group_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_seq(m);

	seq_म_लिखो(m, "%d\n", memcg->oom_group);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार memory_oom_group_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
				      अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_css(of_css(of));
	पूर्णांक ret, oom_group;

	buf = म_मालाip(buf);
	अगर (!buf)
		वापस -EINVAL;

	ret = kstrtoपूर्णांक(buf, 0, &oom_group);
	अगर (ret)
		वापस ret;

	अगर (oom_group != 0 && oom_group != 1)
		वापस -EINVAL;

	memcg->oom_group = oom_group;

	वापस nbytes;
पूर्ण

अटल काष्ठा cftype memory_files[] = अणु
	अणु
		.name = "current",
		.flags = CFTYPE_NOT_ON_ROOT,
		.पढ़ो_u64 = memory_current_पढ़ो,
	पूर्ण,
	अणु
		.name = "min",
		.flags = CFTYPE_NOT_ON_ROOT,
		.seq_show = memory_min_show,
		.ग_लिखो = memory_min_ग_लिखो,
	पूर्ण,
	अणु
		.name = "low",
		.flags = CFTYPE_NOT_ON_ROOT,
		.seq_show = memory_low_show,
		.ग_लिखो = memory_low_ग_लिखो,
	पूर्ण,
	अणु
		.name = "high",
		.flags = CFTYPE_NOT_ON_ROOT,
		.seq_show = memory_high_show,
		.ग_लिखो = memory_high_ग_लिखो,
	पूर्ण,
	अणु
		.name = "max",
		.flags = CFTYPE_NOT_ON_ROOT,
		.seq_show = memory_max_show,
		.ग_लिखो = memory_max_ग_लिखो,
	पूर्ण,
	अणु
		.name = "events",
		.flags = CFTYPE_NOT_ON_ROOT,
		.file_offset = दुरत्व(काष्ठा mem_cgroup, events_file),
		.seq_show = memory_events_show,
	पूर्ण,
	अणु
		.name = "events.local",
		.flags = CFTYPE_NOT_ON_ROOT,
		.file_offset = दुरत्व(काष्ठा mem_cgroup, events_local_file),
		.seq_show = memory_events_local_show,
	पूर्ण,
	अणु
		.name = "stat",
		.seq_show = memory_stat_show,
	पूर्ण,
#अगर_घोषित CONFIG_NUMA
	अणु
		.name = "numa_stat",
		.seq_show = memory_numa_stat_show,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.name = "oom.group",
		.flags = CFTYPE_NOT_ON_ROOT | CFTYPE_NS_DELEGATABLE,
		.seq_show = memory_oom_group_show,
		.ग_लिखो = memory_oom_group_ग_लिखो,
	पूर्ण,
	अणु पूर्ण	/* terminate */
पूर्ण;

काष्ठा cgroup_subsys memory_cgrp_subsys = अणु
	.css_alloc = mem_cgroup_css_alloc,
	.css_online = mem_cgroup_css_online,
	.css_offline = mem_cgroup_css_offline,
	.css_released = mem_cgroup_css_released,
	.css_मुक्त = mem_cgroup_css_मुक्त,
	.css_reset = mem_cgroup_css_reset,
	.css_rstat_flush = mem_cgroup_css_rstat_flush,
	.can_attach = mem_cgroup_can_attach,
	.cancel_attach = mem_cgroup_cancel_attach,
	.post_attach = mem_cgroup_move_task,
	.dfl_cftypes = memory_files,
	.legacy_cftypes = mem_cgroup_legacy_files,
	.early_init = 0,
पूर्ण;

/*
 * This function calculates an inभागidual cgroup's effective
 * protection which is derived from its own memory.min/low, its
 * parent's and siblings' settings, as well as the actual memory
 * distribution in the tree.
 *
 * The following rules apply to the effective protection values:
 *
 * 1. At the first level of reclaim, effective protection is equal to
 *    the declared protection in memory.min and memory.low.
 *
 * 2. To enable safe delegation of the protection configuration, at
 *    subsequent levels the effective protection is capped to the
 *    parent's effective protection.
 *
 * 3. To make complex and dynamic subtrees easier to configure, the
 *    user is allowed to overcommit the declared protection at a given
 *    level. If that is the हाल, the parent's effective protection is
 *    distributed to the children in proportion to how much protection
 *    they have declared and how much of it they are utilizing.
 *
 *    This makes distribution proportional, but also work-conserving:
 *    अगर one cgroup claims much more protection than it uses memory,
 *    the unused reमुख्यder is available to its siblings.
 *
 * 4. Conversely, when the declared protection is undercommitted at a
 *    given level, the distribution of the larger parental protection
 *    budget is NOT proportional. A cgroup's protection from a sibling
 *    is capped to its own memory.min/low setting.
 *
 * 5. However, to allow protecting recursive subtrees from each other
 *    without having to declare each inभागidual cgroup's fixed share
 *    of the ancestor's claim to protection, any unutilized -
 *    "floating" - protection from up the tree is distributed in
 *    proportion to each cgroup's *usage*. This makes the protection
 *    neutral wrt sibling cgroups and lets them compete मुक्तly over
 *    the shared parental protection budget, but it protects the
 *    subtree as a whole from neighboring subtrees.
 *
 * Note that 4. and 5. are not in conflict: 4. is about protecting
 * against immediate siblings whereas 5. is about protecting against
 * neighboring subtrees.
 */
अटल अचिन्हित दीर्घ effective_protection(अचिन्हित दीर्घ usage,
					  अचिन्हित दीर्घ parent_usage,
					  अचिन्हित दीर्घ setting,
					  अचिन्हित दीर्घ parent_effective,
					  अचिन्हित दीर्घ siblings_रक्षित)
अणु
	अचिन्हित दीर्घ रक्षित;
	अचिन्हित दीर्घ ep;

	रक्षित = min(usage, setting);
	/*
	 * If all cgroups at this level combined claim and use more
	 * protection then what the parent afक्रमds them, distribute
	 * shares in proportion to utilization.
	 *
	 * We are using actual utilization rather than the अटलally
	 * claimed protection in order to be work-conserving: claimed
	 * but unused protection is available to siblings that would
	 * otherwise get a smaller chunk than what they claimed.
	 */
	अगर (siblings_रक्षित > parent_effective)
		वापस रक्षित * parent_effective / siblings_रक्षित;

	/*
	 * Ok, utilized protection of all children is within what the
	 * parent afक्रमds them, so we know whatever this child claims
	 * and utilizes is effectively रक्षित.
	 *
	 * If there is unरक्षित usage beyond this value, reclaim
	 * will apply pressure in proportion to that amount.
	 *
	 * If there is unutilized protection, the cgroup will be fully
	 * shielded from reclaim, but we करो वापस a smaller value क्रम
	 * protection than what the group could enjoy in theory. This
	 * is okay. With the overcommit distribution above, effective
	 * protection is always dependent on how memory is actually
	 * consumed among the siblings anyway.
	 */
	ep = रक्षित;

	/*
	 * If the children aren't claiming (all of) the protection
	 * afक्रमded to them by the parent, distribute the reमुख्यder in
	 * proportion to the (unरक्षित) memory of each cgroup. That
	 * way, cgroups that aren't explicitly prioritized wrt each
	 * other compete मुक्तly over the allowance, but they are
	 * collectively रक्षित from neighboring trees.
	 *
	 * We're using unरक्षित memory क्रम the weight so that अगर
	 * some cgroups DO claim explicit protection, we करोn't protect
	 * the same bytes twice.
	 *
	 * Check both usage and parent_usage against the respective
	 * रक्षित values. One should imply the other, but they
	 * aren't पढ़ो atomically - make sure the भागision is sane.
	 */
	अगर (!(cgrp_dfl_root.flags & CGRP_ROOT_MEMORY_RECURSIVE_PROT))
		वापस ep;
	अगर (parent_effective > siblings_रक्षित &&
	    parent_usage > siblings_रक्षित &&
	    usage > रक्षित) अणु
		अचिन्हित दीर्घ unclaimed;

		unclaimed = parent_effective - siblings_रक्षित;
		unclaimed *= usage - रक्षित;
		unclaimed /= parent_usage - siblings_रक्षित;

		ep += unclaimed;
	पूर्ण

	वापस ep;
पूर्ण

/**
 * mem_cgroup_रक्षित - check अगर memory consumption is in the normal range
 * @root: the top ancestor of the sub-tree being checked
 * @memcg: the memory cgroup to check
 *
 * WARNING: This function is not stateless! It can only be used as part
 *          of a top-करोwn tree iteration, not क्रम isolated queries.
 */
व्योम mem_cgroup_calculate_protection(काष्ठा mem_cgroup *root,
				     काष्ठा mem_cgroup *memcg)
अणु
	अचिन्हित दीर्घ usage, parent_usage;
	काष्ठा mem_cgroup *parent;

	अगर (mem_cgroup_disabled())
		वापस;

	अगर (!root)
		root = root_mem_cgroup;

	/*
	 * Effective values of the reclaim tarमाला_लो are ignored so they
	 * can be stale. Have a look at mem_cgroup_protection क्रम more
	 * details.
	 * TODO: calculation should be more robust so that we करो not need
	 * that special casing.
	 */
	अगर (memcg == root)
		वापस;

	usage = page_counter_पढ़ो(&memcg->memory);
	अगर (!usage)
		वापस;

	parent = parent_mem_cgroup(memcg);
	/* No parent means a non-hierarchical mode on v1 memcg */
	अगर (!parent)
		वापस;

	अगर (parent == root) अणु
		memcg->memory.emin = READ_ONCE(memcg->memory.min);
		memcg->memory.elow = READ_ONCE(memcg->memory.low);
		वापस;
	पूर्ण

	parent_usage = page_counter_पढ़ो(&parent->memory);

	WRITE_ONCE(memcg->memory.emin, effective_protection(usage, parent_usage,
			READ_ONCE(memcg->memory.min),
			READ_ONCE(parent->memory.emin),
			atomic_दीर्घ_पढ़ो(&parent->memory.children_min_usage)));

	WRITE_ONCE(memcg->memory.elow, effective_protection(usage, parent_usage,
			READ_ONCE(memcg->memory.low),
			READ_ONCE(parent->memory.elow),
			atomic_दीर्घ_पढ़ो(&parent->memory.children_low_usage)));
पूर्ण

अटल पूर्णांक __mem_cgroup_अक्षरge(काष्ठा page *page, काष्ठा mem_cgroup *memcg,
			       gfp_t gfp)
अणु
	अचिन्हित पूर्णांक nr_pages = thp_nr_pages(page);
	पूर्णांक ret;

	ret = try_अक्षरge(memcg, gfp, nr_pages);
	अगर (ret)
		जाओ out;

	css_get(&memcg->css);
	commit_अक्षरge(page, memcg);

	local_irq_disable();
	mem_cgroup_अक्षरge_statistics(memcg, page, nr_pages);
	memcg_check_events(memcg, page);
	local_irq_enable();
out:
	वापस ret;
पूर्ण

/**
 * mem_cgroup_अक्षरge - अक्षरge a newly allocated page to a cgroup
 * @page: page to अक्षरge
 * @mm: mm context of the victim
 * @gfp_mask: reclaim mode
 *
 * Try to अक्षरge @page to the memcg that @mm beदीर्घs to, reclaiming
 * pages according to @gfp_mask अगर necessary.
 *
 * Do not use this क्रम pages allocated क्रम swapin.
 *
 * Returns 0 on success. Otherwise, an error code is वापसed.
 */
पूर्णांक mem_cgroup_अक्षरge(काष्ठा page *page, काष्ठा mm_काष्ठा *mm, gfp_t gfp_mask)
अणु
	काष्ठा mem_cgroup *memcg;
	पूर्णांक ret;

	अगर (mem_cgroup_disabled())
		वापस 0;

	memcg = get_mem_cgroup_from_mm(mm);
	ret = __mem_cgroup_अक्षरge(page, memcg, gfp_mask);
	css_put(&memcg->css);

	वापस ret;
पूर्ण

/**
 * mem_cgroup_swapin_अक्षरge_page - अक्षरge a newly allocated page क्रम swapin
 * @page: page to अक्षरge
 * @mm: mm context of the victim
 * @gfp: reclaim mode
 * @entry: swap entry क्रम which the page is allocated
 *
 * This function अक्षरges a page allocated क्रम swapin. Please call this beक्रमe
 * adding the page to the swapcache.
 *
 * Returns 0 on success. Otherwise, an error code is वापसed.
 */
पूर्णांक mem_cgroup_swapin_अक्षरge_page(काष्ठा page *page, काष्ठा mm_काष्ठा *mm,
				  gfp_t gfp, swp_entry_t entry)
अणु
	काष्ठा mem_cgroup *memcg;
	अचिन्हित लघु id;
	पूर्णांक ret;

	अगर (mem_cgroup_disabled())
		वापस 0;

	id = lookup_swap_cgroup_id(entry);
	rcu_पढ़ो_lock();
	memcg = mem_cgroup_from_id(id);
	अगर (!memcg || !css_tryget_online(&memcg->css))
		memcg = get_mem_cgroup_from_mm(mm);
	rcu_पढ़ो_unlock();

	ret = __mem_cgroup_अक्षरge(page, memcg, gfp);

	css_put(&memcg->css);
	वापस ret;
पूर्ण

/*
 * mem_cgroup_swapin_unअक्षरge_swap - unअक्षरge swap slot
 * @entry: swap entry क्रम which the page is अक्षरged
 *
 * Call this function after successfully adding the अक्षरged page to swapcache.
 *
 * Note: This function assumes the page क्रम which swap slot is being unअक्षरged
 * is order 0 page.
 */
व्योम mem_cgroup_swapin_unअक्षरge_swap(swp_entry_t entry)
अणु
	/*
	 * Cgroup1's unअगरied memory+swap counter has been अक्षरged with the
	 * new swapcache page, finish the transfer by unअक्षरging the swap
	 * slot. The swap slot would also get unअक्षरged when it dies, but
	 * it can stick around indefinitely and we'd count the page twice
	 * the entire समय.
	 *
	 * Cgroup2 has separate resource counters क्रम memory and swap,
	 * so this is a non-issue here. Memory and swap अक्षरge lअगरeबार
	 * correspond 1:1 to page and swap slot lअगरeबार: we अक्षरge the
	 * page to memory here, and unअक्षरge swap when the slot is मुक्तd.
	 */
	अगर (!mem_cgroup_disabled() && करो_memsw_account()) अणु
		/*
		 * The swap entry might not get मुक्तd क्रम a दीर्घ समय,
		 * let's not रुको क्रम it.  The page alपढ़ोy received a
		 * memory+swap अक्षरge, drop the swap entry duplicate.
		 */
		mem_cgroup_unअक्षरge_swap(entry, 1);
	पूर्ण
पूर्ण

काष्ठा unअक्षरge_gather अणु
	काष्ठा mem_cgroup *memcg;
	अचिन्हित दीर्घ nr_memory;
	अचिन्हित दीर्घ pgpgout;
	अचिन्हित दीर्घ nr_kmem;
	काष्ठा page *dummy_page;
पूर्ण;

अटल अंतरभूत व्योम unअक्षरge_gather_clear(काष्ठा unअक्षरge_gather *ug)
अणु
	स_रखो(ug, 0, माप(*ug));
पूर्ण

अटल व्योम unअक्षरge_batch(स्थिर काष्ठा unअक्षरge_gather *ug)
अणु
	अचिन्हित दीर्घ flags;

	अगर (ug->nr_memory) अणु
		page_counter_unअक्षरge(&ug->memcg->memory, ug->nr_memory);
		अगर (करो_memsw_account())
			page_counter_unअक्षरge(&ug->memcg->memsw, ug->nr_memory);
		अगर (!cgroup_subsys_on_dfl(memory_cgrp_subsys) && ug->nr_kmem)
			page_counter_unअक्षरge(&ug->memcg->kmem, ug->nr_kmem);
		memcg_oom_recover(ug->memcg);
	पूर्ण

	local_irq_save(flags);
	__count_memcg_events(ug->memcg, PGPGOUT, ug->pgpgout);
	__this_cpu_add(ug->memcg->vmstats_percpu->nr_page_events, ug->nr_memory);
	memcg_check_events(ug->memcg, ug->dummy_page);
	local_irq_restore(flags);

	/* drop reference from unअक्षरge_page */
	css_put(&ug->memcg->css);
पूर्ण

अटल व्योम unअक्षरge_page(काष्ठा page *page, काष्ठा unअक्षरge_gather *ug)
अणु
	अचिन्हित दीर्घ nr_pages;
	काष्ठा mem_cgroup *memcg;
	काष्ठा obj_cgroup *objcg;

	VM_BUG_ON_PAGE(PageLRU(page), page);

	/*
	 * Nobody should be changing or seriously looking at
	 * page memcg or objcg at this poपूर्णांक, we have fully
	 * exclusive access to the page.
	 */
	अगर (PageMemcgKmem(page)) अणु
		objcg = __page_objcg(page);
		/*
		 * This get matches the put at the end of the function and
		 * kmem pages करो not hold memcg references anymore.
		 */
		memcg = get_mem_cgroup_from_objcg(objcg);
	पूर्ण अन्यथा अणु
		memcg = __page_memcg(page);
	पूर्ण

	अगर (!memcg)
		वापस;

	अगर (ug->memcg != memcg) अणु
		अगर (ug->memcg) अणु
			unअक्षरge_batch(ug);
			unअक्षरge_gather_clear(ug);
		पूर्ण
		ug->memcg = memcg;
		ug->dummy_page = page;

		/* pairs with css_put in unअक्षरge_batch */
		css_get(&memcg->css);
	पूर्ण

	nr_pages = compound_nr(page);

	अगर (PageMemcgKmem(page)) अणु
		ug->nr_memory += nr_pages;
		ug->nr_kmem += nr_pages;

		page->memcg_data = 0;
		obj_cgroup_put(objcg);
	पूर्ण अन्यथा अणु
		/* LRU pages aren't accounted at the root level */
		अगर (!mem_cgroup_is_root(memcg))
			ug->nr_memory += nr_pages;
		ug->pgpgout++;

		page->memcg_data = 0;
	पूर्ण

	css_put(&memcg->css);
पूर्ण

/**
 * mem_cgroup_unअक्षरge - unअक्षरge a page
 * @page: page to unअक्षरge
 *
 * Unअक्षरge a page previously अक्षरged with mem_cgroup_अक्षरge().
 */
व्योम mem_cgroup_unअक्षरge(काष्ठा page *page)
अणु
	काष्ठा unअक्षरge_gather ug;

	अगर (mem_cgroup_disabled())
		वापस;

	/* Don't touch page->lru of any अक्रमom page, pre-check: */
	अगर (!page_memcg(page))
		वापस;

	unअक्षरge_gather_clear(&ug);
	unअक्षरge_page(page, &ug);
	unअक्षरge_batch(&ug);
पूर्ण

/**
 * mem_cgroup_unअक्षरge_list - unअक्षरge a list of page
 * @page_list: list of pages to unअक्षरge
 *
 * Unअक्षरge a list of pages previously अक्षरged with
 * mem_cgroup_अक्षरge().
 */
व्योम mem_cgroup_unअक्षरge_list(काष्ठा list_head *page_list)
अणु
	काष्ठा unअक्षरge_gather ug;
	काष्ठा page *page;

	अगर (mem_cgroup_disabled())
		वापस;

	unअक्षरge_gather_clear(&ug);
	list_क्रम_each_entry(page, page_list, lru)
		unअक्षरge_page(page, &ug);
	अगर (ug.memcg)
		unअक्षरge_batch(&ug);
पूर्ण

/**
 * mem_cgroup_migrate - अक्षरge a page's replacement
 * @oldpage: currently circulating page
 * @newpage: replacement page
 *
 * Charge @newpage as a replacement page क्रम @oldpage. @oldpage will
 * be unअक्षरged upon मुक्त.
 *
 * Both pages must be locked, @newpage->mapping must be set up.
 */
व्योम mem_cgroup_migrate(काष्ठा page *oldpage, काष्ठा page *newpage)
अणु
	काष्ठा mem_cgroup *memcg;
	अचिन्हित पूर्णांक nr_pages;
	अचिन्हित दीर्घ flags;

	VM_BUG_ON_PAGE(!PageLocked(oldpage), oldpage);
	VM_BUG_ON_PAGE(!PageLocked(newpage), newpage);
	VM_BUG_ON_PAGE(PageAnon(oldpage) != PageAnon(newpage), newpage);
	VM_BUG_ON_PAGE(PageTransHuge(oldpage) != PageTransHuge(newpage),
		       newpage);

	अगर (mem_cgroup_disabled())
		वापस;

	/* Page cache replacement: new page alपढ़ोy अक्षरged? */
	अगर (page_memcg(newpage))
		वापस;

	memcg = page_memcg(oldpage);
	VM_WARN_ON_ONCE_PAGE(!memcg, oldpage);
	अगर (!memcg)
		वापस;

	/* Force-अक्षरge the new page. The old one will be मुक्तd soon */
	nr_pages = thp_nr_pages(newpage);

	page_counter_अक्षरge(&memcg->memory, nr_pages);
	अगर (करो_memsw_account())
		page_counter_अक्षरge(&memcg->memsw, nr_pages);

	css_get(&memcg->css);
	commit_अक्षरge(newpage, memcg);

	local_irq_save(flags);
	mem_cgroup_अक्षरge_statistics(memcg, newpage, nr_pages);
	memcg_check_events(memcg, newpage);
	local_irq_restore(flags);
पूर्ण

DEFINE_STATIC_KEY_FALSE(memcg_sockets_enabled_key);
EXPORT_SYMBOL(memcg_sockets_enabled_key);

व्योम mem_cgroup_sk_alloc(काष्ठा sock *sk)
अणु
	काष्ठा mem_cgroup *memcg;

	अगर (!mem_cgroup_sockets_enabled)
		वापस;

	/* Do not associate the sock with unrelated पूर्णांकerrupted task's memcg. */
	अगर (in_पूर्णांकerrupt())
		वापस;

	rcu_पढ़ो_lock();
	memcg = mem_cgroup_from_task(current);
	अगर (memcg == root_mem_cgroup)
		जाओ out;
	अगर (!cgroup_subsys_on_dfl(memory_cgrp_subsys) && !memcg->tcpmem_active)
		जाओ out;
	अगर (css_tryget(&memcg->css))
		sk->sk_memcg = memcg;
out:
	rcu_पढ़ो_unlock();
पूर्ण

व्योम mem_cgroup_sk_मुक्त(काष्ठा sock *sk)
अणु
	अगर (sk->sk_memcg)
		css_put(&sk->sk_memcg->css);
पूर्ण

/**
 * mem_cgroup_अक्षरge_skmem - अक्षरge socket memory
 * @memcg: memcg to अक्षरge
 * @nr_pages: number of pages to अक्षरge
 *
 * Charges @nr_pages to @memcg. Returns %true अगर the अक्षरge fit within
 * @memcg's configured limit, %false अगर the अक्षरge had to be क्रमced.
 */
bool mem_cgroup_अक्षरge_skmem(काष्ठा mem_cgroup *memcg, अचिन्हित पूर्णांक nr_pages)
अणु
	gfp_t gfp_mask = GFP_KERNEL;

	अगर (!cgroup_subsys_on_dfl(memory_cgrp_subsys)) अणु
		काष्ठा page_counter *fail;

		अगर (page_counter_try_अक्षरge(&memcg->tcpmem, nr_pages, &fail)) अणु
			memcg->tcpmem_pressure = 0;
			वापस true;
		पूर्ण
		page_counter_अक्षरge(&memcg->tcpmem, nr_pages);
		memcg->tcpmem_pressure = 1;
		वापस false;
	पूर्ण

	/* Don't block in the packet receive path */
	अगर (in_softirq())
		gfp_mask = GFP_NOWAIT;

	mod_memcg_state(memcg, MEMCG_SOCK, nr_pages);

	अगर (try_अक्षरge(memcg, gfp_mask, nr_pages) == 0)
		वापस true;

	try_अक्षरge(memcg, gfp_mask|__GFP_NOFAIL, nr_pages);
	वापस false;
पूर्ण

/**
 * mem_cgroup_unअक्षरge_skmem - unअक्षरge socket memory
 * @memcg: memcg to unअक्षरge
 * @nr_pages: number of pages to unअक्षरge
 */
व्योम mem_cgroup_unअक्षरge_skmem(काष्ठा mem_cgroup *memcg, अचिन्हित पूर्णांक nr_pages)
अणु
	अगर (!cgroup_subsys_on_dfl(memory_cgrp_subsys)) अणु
		page_counter_unअक्षरge(&memcg->tcpmem, nr_pages);
		वापस;
	पूर्ण

	mod_memcg_state(memcg, MEMCG_SOCK, -nr_pages);

	refill_stock(memcg, nr_pages);
पूर्ण

अटल पूर्णांक __init cgroup_memory(अक्षर *s)
अणु
	अक्षर *token;

	जबतक ((token = strsep(&s, ",")) != शून्य) अणु
		अगर (!*token)
			जारी;
		अगर (!म_भेद(token, "nosocket"))
			cgroup_memory_nosocket = true;
		अगर (!म_भेद(token, "nokmem"))
			cgroup_memory_nokmem = true;
	पूर्ण
	वापस 0;
पूर्ण
__setup("cgroup.memory=", cgroup_memory);

/*
 * subsys_initcall() क्रम memory controller.
 *
 * Some parts like memcg_hotplug_cpu_dead() have to be initialized from this
 * context because of lock dependencies (cgroup_lock -> cpu hotplug) but
 * basically everything that करोesn't depend on a specअगरic mem_cgroup काष्ठाure
 * should be initialized from here.
 */
अटल पूर्णांक __init mem_cgroup_init(व्योम)
अणु
	पूर्णांक cpu, node;

	/*
	 * Currently s32 type (can refer to काष्ठा batched_lruvec_stat) is
	 * used क्रम per-memcg-per-cpu caching of per-node statistics. In order
	 * to work fine, we should make sure that the overfill threshold can't
	 * exceed S32_MAX / PAGE_SIZE.
	 */
	BUILD_BUG_ON(MEMCG_CHARGE_BATCH > S32_MAX / PAGE_SIZE);

	cpuhp_setup_state_nocalls(CPUHP_MM_MEMCQ_DEAD, "mm/memctrl:dead", शून्य,
				  memcg_hotplug_cpu_dead);

	क्रम_each_possible_cpu(cpu)
		INIT_WORK(&per_cpu_ptr(&memcg_stock, cpu)->work,
			  drain_local_stock);

	क्रम_each_node(node) अणु
		काष्ठा mem_cgroup_tree_per_node *rtpn;

		rtpn = kzalloc_node(माप(*rtpn), GFP_KERNEL,
				    node_online(node) ? node : NUMA_NO_NODE);

		rtpn->rb_root = RB_ROOT;
		rtpn->rb_righपंचांगost = शून्य;
		spin_lock_init(&rtpn->lock);
		soft_limit_tree.rb_tree_per_node[node] = rtpn;
	पूर्ण

	वापस 0;
पूर्ण
subsys_initcall(mem_cgroup_init);

#अगर_घोषित CONFIG_MEMCG_SWAP
अटल काष्ठा mem_cgroup *mem_cgroup_id_get_online(काष्ठा mem_cgroup *memcg)
अणु
	जबतक (!refcount_inc_not_zero(&memcg->id.ref)) अणु
		/*
		 * The root cgroup cannot be destroyed, so it's refcount must
		 * always be >= 1.
		 */
		अगर (WARN_ON_ONCE(memcg == root_mem_cgroup)) अणु
			VM_BUG_ON(1);
			अवरोध;
		पूर्ण
		memcg = parent_mem_cgroup(memcg);
		अगर (!memcg)
			memcg = root_mem_cgroup;
	पूर्ण
	वापस memcg;
पूर्ण

/**
 * mem_cgroup_swapout - transfer a memsw अक्षरge to swap
 * @page: page whose memsw अक्षरge to transfer
 * @entry: swap entry to move the अक्षरge to
 *
 * Transfer the memsw अक्षरge of @page to @entry.
 */
व्योम mem_cgroup_swapout(काष्ठा page *page, swp_entry_t entry)
अणु
	काष्ठा mem_cgroup *memcg, *swap_memcg;
	अचिन्हित पूर्णांक nr_entries;
	अचिन्हित लघु oldid;

	VM_BUG_ON_PAGE(PageLRU(page), page);
	VM_BUG_ON_PAGE(page_count(page), page);

	अगर (mem_cgroup_disabled())
		वापस;

	अगर (cgroup_subsys_on_dfl(memory_cgrp_subsys))
		वापस;

	memcg = page_memcg(page);

	VM_WARN_ON_ONCE_PAGE(!memcg, page);
	अगर (!memcg)
		वापस;

	/*
	 * In हाल the memcg owning these pages has been offlined and करोesn't
	 * have an ID allocated to it anymore, अक्षरge the बंदst online
	 * ancestor क्रम the swap instead and transfer the memory+swap अक्षरge.
	 */
	swap_memcg = mem_cgroup_id_get_online(memcg);
	nr_entries = thp_nr_pages(page);
	/* Get references क्रम the tail pages, too */
	अगर (nr_entries > 1)
		mem_cgroup_id_get_many(swap_memcg, nr_entries - 1);
	oldid = swap_cgroup_record(entry, mem_cgroup_id(swap_memcg),
				   nr_entries);
	VM_BUG_ON_PAGE(oldid, page);
	mod_memcg_state(swap_memcg, MEMCG_SWAP, nr_entries);

	page->memcg_data = 0;

	अगर (!mem_cgroup_is_root(memcg))
		page_counter_unअक्षरge(&memcg->memory, nr_entries);

	अगर (!cgroup_memory_noswap && memcg != swap_memcg) अणु
		अगर (!mem_cgroup_is_root(swap_memcg))
			page_counter_अक्षरge(&swap_memcg->memsw, nr_entries);
		page_counter_unअक्षरge(&memcg->memsw, nr_entries);
	पूर्ण

	/*
	 * Interrupts should be disabled here because the caller holds the
	 * i_pages lock which is taken with पूर्णांकerrupts-off. It is
	 * important here to have the पूर्णांकerrupts disabled because it is the
	 * only synchronisation we have क्रम updating the per-CPU variables.
	 */
	VM_BUG_ON(!irqs_disabled());
	mem_cgroup_अक्षरge_statistics(memcg, page, -nr_entries);
	memcg_check_events(memcg, page);

	css_put(&memcg->css);
पूर्ण

/**
 * mem_cgroup_try_अक्षरge_swap - try अक्षरging swap space क्रम a page
 * @page: page being added to swap
 * @entry: swap entry to अक्षरge
 *
 * Try to अक्षरge @page's memcg क्रम the swap space at @entry.
 *
 * Returns 0 on success, -ENOMEM on failure.
 */
पूर्णांक mem_cgroup_try_अक्षरge_swap(काष्ठा page *page, swp_entry_t entry)
अणु
	अचिन्हित पूर्णांक nr_pages = thp_nr_pages(page);
	काष्ठा page_counter *counter;
	काष्ठा mem_cgroup *memcg;
	अचिन्हित लघु oldid;

	अगर (mem_cgroup_disabled())
		वापस 0;

	अगर (!cgroup_subsys_on_dfl(memory_cgrp_subsys))
		वापस 0;

	memcg = page_memcg(page);

	VM_WARN_ON_ONCE_PAGE(!memcg, page);
	अगर (!memcg)
		वापस 0;

	अगर (!entry.val) अणु
		memcg_memory_event(memcg, MEMCG_SWAP_FAIL);
		वापस 0;
	पूर्ण

	memcg = mem_cgroup_id_get_online(memcg);

	अगर (!cgroup_memory_noswap && !mem_cgroup_is_root(memcg) &&
	    !page_counter_try_अक्षरge(&memcg->swap, nr_pages, &counter)) अणु
		memcg_memory_event(memcg, MEMCG_SWAP_MAX);
		memcg_memory_event(memcg, MEMCG_SWAP_FAIL);
		mem_cgroup_id_put(memcg);
		वापस -ENOMEM;
	पूर्ण

	/* Get references क्रम the tail pages, too */
	अगर (nr_pages > 1)
		mem_cgroup_id_get_many(memcg, nr_pages - 1);
	oldid = swap_cgroup_record(entry, mem_cgroup_id(memcg), nr_pages);
	VM_BUG_ON_PAGE(oldid, page);
	mod_memcg_state(memcg, MEMCG_SWAP, nr_pages);

	वापस 0;
पूर्ण

/**
 * mem_cgroup_unअक्षरge_swap - unअक्षरge swap space
 * @entry: swap entry to unअक्षरge
 * @nr_pages: the amount of swap space to unअक्षरge
 */
व्योम mem_cgroup_unअक्षरge_swap(swp_entry_t entry, अचिन्हित पूर्णांक nr_pages)
अणु
	काष्ठा mem_cgroup *memcg;
	अचिन्हित लघु id;

	id = swap_cgroup_record(entry, 0, nr_pages);
	rcu_पढ़ो_lock();
	memcg = mem_cgroup_from_id(id);
	अगर (memcg) अणु
		अगर (!cgroup_memory_noswap && !mem_cgroup_is_root(memcg)) अणु
			अगर (cgroup_subsys_on_dfl(memory_cgrp_subsys))
				page_counter_unअक्षरge(&memcg->swap, nr_pages);
			अन्यथा
				page_counter_unअक्षरge(&memcg->memsw, nr_pages);
		पूर्ण
		mod_memcg_state(memcg, MEMCG_SWAP, -nr_pages);
		mem_cgroup_id_put_many(memcg, nr_pages);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

दीर्घ mem_cgroup_get_nr_swap_pages(काष्ठा mem_cgroup *memcg)
अणु
	दीर्घ nr_swap_pages = get_nr_swap_pages();

	अगर (cgroup_memory_noswap || !cgroup_subsys_on_dfl(memory_cgrp_subsys))
		वापस nr_swap_pages;
	क्रम (; memcg != root_mem_cgroup; memcg = parent_mem_cgroup(memcg))
		nr_swap_pages = min_t(दीर्घ, nr_swap_pages,
				      READ_ONCE(memcg->swap.max) -
				      page_counter_पढ़ो(&memcg->swap));
	वापस nr_swap_pages;
पूर्ण

bool mem_cgroup_swap_full(काष्ठा page *page)
अणु
	काष्ठा mem_cgroup *memcg;

	VM_BUG_ON_PAGE(!PageLocked(page), page);

	अगर (vm_swap_full())
		वापस true;
	अगर (cgroup_memory_noswap || !cgroup_subsys_on_dfl(memory_cgrp_subsys))
		वापस false;

	memcg = page_memcg(page);
	अगर (!memcg)
		वापस false;

	क्रम (; memcg != root_mem_cgroup; memcg = parent_mem_cgroup(memcg)) अणु
		अचिन्हित दीर्घ usage = page_counter_पढ़ो(&memcg->swap);

		अगर (usage * 2 >= READ_ONCE(memcg->swap.high) ||
		    usage * 2 >= READ_ONCE(memcg->swap.max))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक __init setup_swap_account(अक्षर *s)
अणु
	अगर (!म_भेद(s, "1"))
		cgroup_memory_noswap = false;
	अन्यथा अगर (!म_भेद(s, "0"))
		cgroup_memory_noswap = true;
	वापस 1;
पूर्ण
__setup("swapaccount=", setup_swap_account);

अटल u64 swap_current_पढ़ो(काष्ठा cgroup_subsys_state *css,
			     काष्ठा cftype *cft)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_css(css);

	वापस (u64)page_counter_पढ़ो(&memcg->swap) * PAGE_SIZE;
पूर्ण

अटल पूर्णांक swap_high_show(काष्ठा seq_file *m, व्योम *v)
अणु
	वापस seq_माला_दो_memcg_tunable(m,
		READ_ONCE(mem_cgroup_from_seq(m)->swap.high));
पूर्ण

अटल sमाप_प्रकार swap_high_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
			       अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_css(of_css(of));
	अचिन्हित दीर्घ high;
	पूर्णांक err;

	buf = म_मालाip(buf);
	err = page_counter_memparse(buf, "max", &high);
	अगर (err)
		वापस err;

	page_counter_set_high(&memcg->swap, high);

	वापस nbytes;
पूर्ण

अटल पूर्णांक swap_max_show(काष्ठा seq_file *m, व्योम *v)
अणु
	वापस seq_माला_दो_memcg_tunable(m,
		READ_ONCE(mem_cgroup_from_seq(m)->swap.max));
पूर्ण

अटल sमाप_प्रकार swap_max_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
			      अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_css(of_css(of));
	अचिन्हित दीर्घ max;
	पूर्णांक err;

	buf = म_मालाip(buf);
	err = page_counter_memparse(buf, "max", &max);
	अगर (err)
		वापस err;

	xchg(&memcg->swap.max, max);

	वापस nbytes;
पूर्ण

अटल पूर्णांक swap_events_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_seq(m);

	seq_म_लिखो(m, "high %lu\n",
		   atomic_दीर्घ_पढ़ो(&memcg->memory_events[MEMCG_SWAP_HIGH]));
	seq_म_लिखो(m, "max %lu\n",
		   atomic_दीर्घ_पढ़ो(&memcg->memory_events[MEMCG_SWAP_MAX]));
	seq_म_लिखो(m, "fail %lu\n",
		   atomic_दीर्घ_पढ़ो(&memcg->memory_events[MEMCG_SWAP_FAIL]));

	वापस 0;
पूर्ण

अटल काष्ठा cftype swap_files[] = अणु
	अणु
		.name = "swap.current",
		.flags = CFTYPE_NOT_ON_ROOT,
		.पढ़ो_u64 = swap_current_पढ़ो,
	पूर्ण,
	अणु
		.name = "swap.high",
		.flags = CFTYPE_NOT_ON_ROOT,
		.seq_show = swap_high_show,
		.ग_लिखो = swap_high_ग_लिखो,
	पूर्ण,
	अणु
		.name = "swap.max",
		.flags = CFTYPE_NOT_ON_ROOT,
		.seq_show = swap_max_show,
		.ग_लिखो = swap_max_ग_लिखो,
	पूर्ण,
	अणु
		.name = "swap.events",
		.flags = CFTYPE_NOT_ON_ROOT,
		.file_offset = दुरत्व(काष्ठा mem_cgroup, swap_events_file),
		.seq_show = swap_events_show,
	पूर्ण,
	अणु पूर्ण	/* terminate */
पूर्ण;

अटल काष्ठा cftype memsw_files[] = अणु
	अणु
		.name = "memsw.usage_in_bytes",
		.निजी = MEMखाता_PRIVATE(_MEMSWAP, RES_USAGE),
		.पढ़ो_u64 = mem_cgroup_पढ़ो_u64,
	पूर्ण,
	अणु
		.name = "memsw.max_usage_in_bytes",
		.निजी = MEMखाता_PRIVATE(_MEMSWAP, RES_MAX_USAGE),
		.ग_लिखो = mem_cgroup_reset,
		.पढ़ो_u64 = mem_cgroup_पढ़ो_u64,
	पूर्ण,
	अणु
		.name = "memsw.limit_in_bytes",
		.निजी = MEMखाता_PRIVATE(_MEMSWAP, RES_LIMIT),
		.ग_लिखो = mem_cgroup_ग_लिखो,
		.पढ़ो_u64 = mem_cgroup_पढ़ो_u64,
	पूर्ण,
	अणु
		.name = "memsw.failcnt",
		.निजी = MEMखाता_PRIVATE(_MEMSWAP, RES_FAILCNT),
		.ग_लिखो = mem_cgroup_reset,
		.पढ़ो_u64 = mem_cgroup_पढ़ो_u64,
	पूर्ण,
	अणु पूर्ण,	/* terminate */
पूर्ण;

/*
 * If mem_cgroup_swap_init() is implemented as a subsys_initcall()
 * instead of a core_initcall(), this could mean cgroup_memory_noswap still
 * reमुख्यs set to false even when memcg is disabled via "cgroup_disable=memory"
 * boot parameter. This may result in premature OOPS inside
 * mem_cgroup_get_nr_swap_pages() function in corner हालs.
 */
अटल पूर्णांक __init mem_cgroup_swap_init(व्योम)
अणु
	/* No memory control -> no swap control */
	अगर (mem_cgroup_disabled())
		cgroup_memory_noswap = true;

	अगर (cgroup_memory_noswap)
		वापस 0;

	WARN_ON(cgroup_add_dfl_cftypes(&memory_cgrp_subsys, swap_files));
	WARN_ON(cgroup_add_legacy_cftypes(&memory_cgrp_subsys, memsw_files));

	वापस 0;
पूर्ण
core_initcall(mem_cgroup_swap_init);

#पूर्ण_अगर /* CONFIG_MEMCG_SWAP */
