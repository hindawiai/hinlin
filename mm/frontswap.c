<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Frontswap frontend
 *
 * This code provides the generic "frontend" layer to call a matching
 * "backend" driver implementation of frontswap.  See
 * Documentation/vm/frontswap.rst क्रम more inक्रमmation.
 *
 * Copyright (C) 2009-2012 Oracle Corp.  All rights reserved.
 * Author: Dan Magenheimer
 */

#समावेश <linux/mman.h>
#समावेश <linux/swap.h>
#समावेश <linux/swapops.h>
#समावेश <linux/security.h>
#समावेश <linux/module.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/frontswap.h>
#समावेश <linux/swapfile.h>

DEFINE_STATIC_KEY_FALSE(frontswap_enabled_key);

/*
 * frontswap_ops are added by frontswap_रेजिस्टर_ops, and provide the
 * frontswap "backend" implementation functions.  Multiple implementations
 * may be रेजिस्टरed, but implementations can never deरेजिस्टर.  This
 * is a simple singly-linked list of all रेजिस्टरed implementations.
 */
अटल काष्ठा frontswap_ops *frontswap_ops __पढ़ो_mostly;

#घोषणा क्रम_each_frontswap_ops(ops)		\
	क्रम ((ops) = frontswap_ops; (ops); (ops) = (ops)->next)

/*
 * If enabled, frontswap_store will वापस failure even on success.  As
 * a result, the swap subप्रणाली will always ग_लिखो the page to swap, in
 * effect converting frontswap पूर्णांकo a ग_लिखोthrough cache.  In this mode,
 * there is no direct reduction in swap ग_लिखोs, but a frontswap backend
 * can unilaterally "reclaim" any pages in use with no data loss, thus
 * providing increases control over maximum memory usage due to frontswap.
 */
अटल bool frontswap_ग_लिखोthrough_enabled __पढ़ो_mostly;

/*
 * If enabled, the underlying पंचांगem implementation is capable of करोing
 * exclusive माला_लो, so frontswap_load, on a successful पंचांगem_get must
 * mark the page as no दीर्घer in frontswap AND mark it dirty.
 */
अटल bool frontswap_पंचांगem_exclusive_माला_लो_enabled __पढ़ो_mostly;

#अगर_घोषित CONFIG_DEBUG_FS
/*
 * Counters available via /sys/kernel/debug/frontswap (अगर debugfs is
 * properly configured).  These are क्रम inक्रमmation only so are not रक्षित
 * against increment races.
 */
अटल u64 frontswap_loads;
अटल u64 frontswap_succ_stores;
अटल u64 frontswap_failed_stores;
अटल u64 frontswap_invalidates;

अटल अंतरभूत व्योम inc_frontswap_loads(व्योम)
अणु
	data_race(frontswap_loads++);
पूर्ण
अटल अंतरभूत व्योम inc_frontswap_succ_stores(व्योम)
अणु
	data_race(frontswap_succ_stores++);
पूर्ण
अटल अंतरभूत व्योम inc_frontswap_failed_stores(व्योम)
अणु
	data_race(frontswap_failed_stores++);
पूर्ण
अटल अंतरभूत व्योम inc_frontswap_invalidates(व्योम)
अणु
	data_race(frontswap_invalidates++);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम inc_frontswap_loads(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम inc_frontswap_succ_stores(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम inc_frontswap_failed_stores(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम inc_frontswap_invalidates(व्योम) अणु पूर्ण
#पूर्ण_अगर

/*
 * Due to the asynchronous nature of the backends loading potentially
 * _after_ the swap प्रणाली has been activated, we have chokepoपूर्णांकs
 * on all frontswap functions to not call the backend until the backend
 * has रेजिस्टरed.
 *
 * This would not guards us against the user deciding to call swapoff right as
 * we are calling the backend to initialize (so swapon is in action).
 * Fortunately क्रम us, the swapon_mutex has been taken by the callee so we are
 * OK. The other scenario where calls to frontswap_store (called via
 * swap_ग_लिखोpage) is racing with frontswap_invalidate_area (called via
 * swapoff) is again guarded by the swap subप्रणाली.
 *
 * While no backend is रेजिस्टरed all calls to frontswap_[store|load|
 * invalidate_area|invalidate_page] are ignored or fail.
 *
 * The समय between the backend being रेजिस्टरed and the swap file प्रणाली
 * calling the backend (via the frontswap_* functions) is indeterminate as
 * frontswap_ops is not atomic_t (or a value guarded by a spinlock).
 * That is OK as we are comक्रमtable missing some of these calls to the newly
 * रेजिस्टरed backend.
 *
 * Obviously the opposite (unloading the backend) must be करोne after all
 * the frontswap_[store|load|invalidate_area|invalidate_page] start
 * ignoring or failing the requests.  However, there is currently no way
 * to unload a backend once it is रेजिस्टरed.
 */

/*
 * Register operations क्रम frontswap
 */
व्योम frontswap_रेजिस्टर_ops(काष्ठा frontswap_ops *ops)
अणु
	DECLARE_BITMAP(a, MAX_SWAPखाताS);
	DECLARE_BITMAP(b, MAX_SWAPखाताS);
	काष्ठा swap_info_काष्ठा *si;
	अचिन्हित पूर्णांक i;

	biपंचांगap_zero(a, MAX_SWAPखाताS);
	biपंचांगap_zero(b, MAX_SWAPखाताS);

	spin_lock(&swap_lock);
	plist_क्रम_each_entry(si, &swap_active_head, list) अणु
		अगर (!WARN_ON(!si->frontswap_map))
			set_bit(si->type, a);
	पूर्ण
	spin_unlock(&swap_lock);

	/* the new ops needs to know the currently active swap devices */
	क्रम_each_set_bit(i, a, MAX_SWAPखाताS)
		ops->init(i);

	/*
	 * Setting frontswap_ops must happen after the ops->init() calls
	 * above; cmpxchg implies smp_mb() which will ensure the init is
	 * complete at this poपूर्णांक.
	 */
	करो अणु
		ops->next = frontswap_ops;
	पूर्ण जबतक (cmpxchg(&frontswap_ops, ops->next, ops) != ops->next);

	अटल_branch_inc(&frontswap_enabled_key);

	spin_lock(&swap_lock);
	plist_क्रम_each_entry(si, &swap_active_head, list) अणु
		अगर (si->frontswap_map)
			set_bit(si->type, b);
	पूर्ण
	spin_unlock(&swap_lock);

	/*
	 * On the very unlikely chance that a swap device was added or
	 * हटाओd between setting the "a" list bits and the ops init
	 * calls, we re-check and करो init or invalidate क्रम any changed
	 * bits.
	 */
	अगर (unlikely(!biपंचांगap_equal(a, b, MAX_SWAPखाताS))) अणु
		क्रम (i = 0; i < MAX_SWAPखाताS; i++) अणु
			अगर (!test_bit(i, a) && test_bit(i, b))
				ops->init(i);
			अन्यथा अगर (test_bit(i, a) && !test_bit(i, b))
				ops->invalidate_area(i);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(frontswap_रेजिस्टर_ops);

/*
 * Enable/disable frontswap ग_लिखोthrough (see above).
 */
व्योम frontswap_ग_लिखोthrough(bool enable)
अणु
	frontswap_ग_लिखोthrough_enabled = enable;
पूर्ण
EXPORT_SYMBOL(frontswap_ग_लिखोthrough);

/*
 * Enable/disable frontswap exclusive माला_लो (see above).
 */
व्योम frontswap_पंचांगem_exclusive_माला_लो(bool enable)
अणु
	frontswap_पंचांगem_exclusive_माला_लो_enabled = enable;
पूर्ण
EXPORT_SYMBOL(frontswap_पंचांगem_exclusive_माला_लो);

/*
 * Called when a swap device is swapon'd.
 */
व्योम __frontswap_init(अचिन्हित type, अचिन्हित दीर्घ *map)
अणु
	काष्ठा swap_info_काष्ठा *sis = swap_info[type];
	काष्ठा frontswap_ops *ops;

	VM_BUG_ON(sis == शून्य);

	/*
	 * p->frontswap is a biपंचांगap that we MUST have to figure out which page
	 * has gone in frontswap. Without it there is no poपूर्णांक of continuing.
	 */
	अगर (WARN_ON(!map))
		वापस;
	/*
	 * Irregardless of whether the frontswap backend has been loaded
	 * beक्रमe this function or it will be later, we _MUST_ have the
	 * p->frontswap set to something valid to work properly.
	 */
	frontswap_map_set(sis, map);

	क्रम_each_frontswap_ops(ops)
		ops->init(type);
पूर्ण
EXPORT_SYMBOL(__frontswap_init);

bool __frontswap_test(काष्ठा swap_info_काष्ठा *sis,
				pgoff_t offset)
अणु
	अगर (sis->frontswap_map)
		वापस test_bit(offset, sis->frontswap_map);
	वापस false;
पूर्ण
EXPORT_SYMBOL(__frontswap_test);

अटल अंतरभूत व्योम __frontswap_set(काष्ठा swap_info_काष्ठा *sis,
				   pgoff_t offset)
अणु
	set_bit(offset, sis->frontswap_map);
	atomic_inc(&sis->frontswap_pages);
पूर्ण

अटल अंतरभूत व्योम __frontswap_clear(काष्ठा swap_info_काष्ठा *sis,
				     pgoff_t offset)
अणु
	clear_bit(offset, sis->frontswap_map);
	atomic_dec(&sis->frontswap_pages);
पूर्ण

/*
 * "Store" data from a page to frontswap and associate it with the page's
 * swaptype and offset.  Page must be locked and in the swap cache.
 * If frontswap alपढ़ोy contains a page with matching swaptype and
 * offset, the frontswap implementation may either overग_लिखो the data and
 * वापस success or invalidate the page from frontswap and वापस failure.
 */
पूर्णांक __frontswap_store(काष्ठा page *page)
अणु
	पूर्णांक ret = -1;
	swp_entry_t entry = अणु .val = page_निजी(page), पूर्ण;
	पूर्णांक type = swp_type(entry);
	काष्ठा swap_info_काष्ठा *sis = swap_info[type];
	pgoff_t offset = swp_offset(entry);
	काष्ठा frontswap_ops *ops;

	VM_BUG_ON(!frontswap_ops);
	VM_BUG_ON(!PageLocked(page));
	VM_BUG_ON(sis == शून्य);

	/*
	 * If a dup, we must हटाओ the old page first; we can't leave the
	 * old page no matter अगर the store of the new page succeeds or fails,
	 * and we can't rely on the new page replacing the old page as we may
	 * not store to the same implementation that contains the old page.
	 */
	अगर (__frontswap_test(sis, offset)) अणु
		__frontswap_clear(sis, offset);
		क्रम_each_frontswap_ops(ops)
			ops->invalidate_page(type, offset);
	पूर्ण

	/* Try to store in each implementation, until one succeeds. */
	क्रम_each_frontswap_ops(ops) अणु
		ret = ops->store(type, offset, page);
		अगर (!ret) /* successful store */
			अवरोध;
	पूर्ण
	अगर (ret == 0) अणु
		__frontswap_set(sis, offset);
		inc_frontswap_succ_stores();
	पूर्ण अन्यथा अणु
		inc_frontswap_failed_stores();
	पूर्ण
	अगर (frontswap_ग_लिखोthrough_enabled)
		/* report failure so swap also ग_लिखोs to swap device */
		ret = -1;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(__frontswap_store);

/*
 * "Get" data from frontswap associated with swaptype and offset that were
 * specअगरied when the data was put to frontswap and use it to fill the
 * specअगरied page with data. Page must be locked and in the swap cache.
 */
पूर्णांक __frontswap_load(काष्ठा page *page)
अणु
	पूर्णांक ret = -1;
	swp_entry_t entry = अणु .val = page_निजी(page), पूर्ण;
	पूर्णांक type = swp_type(entry);
	काष्ठा swap_info_काष्ठा *sis = swap_info[type];
	pgoff_t offset = swp_offset(entry);
	काष्ठा frontswap_ops *ops;

	VM_BUG_ON(!frontswap_ops);
	VM_BUG_ON(!PageLocked(page));
	VM_BUG_ON(sis == शून्य);

	अगर (!__frontswap_test(sis, offset))
		वापस -1;

	/* Try loading from each implementation, until one succeeds. */
	क्रम_each_frontswap_ops(ops) अणु
		ret = ops->load(type, offset, page);
		अगर (!ret) /* successful load */
			अवरोध;
	पूर्ण
	अगर (ret == 0) अणु
		inc_frontswap_loads();
		अगर (frontswap_पंचांगem_exclusive_माला_लो_enabled) अणु
			SetPageDirty(page);
			__frontswap_clear(sis, offset);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(__frontswap_load);

/*
 * Invalidate any data from frontswap associated with the specअगरied swaptype
 * and offset so that a subsequent "get" will fail.
 */
व्योम __frontswap_invalidate_page(अचिन्हित type, pgoff_t offset)
अणु
	काष्ठा swap_info_काष्ठा *sis = swap_info[type];
	काष्ठा frontswap_ops *ops;

	VM_BUG_ON(!frontswap_ops);
	VM_BUG_ON(sis == शून्य);

	अगर (!__frontswap_test(sis, offset))
		वापस;

	क्रम_each_frontswap_ops(ops)
		ops->invalidate_page(type, offset);
	__frontswap_clear(sis, offset);
	inc_frontswap_invalidates();
पूर्ण
EXPORT_SYMBOL(__frontswap_invalidate_page);

/*
 * Invalidate all data from frontswap associated with all offsets क्रम the
 * specअगरied swaptype.
 */
व्योम __frontswap_invalidate_area(अचिन्हित type)
अणु
	काष्ठा swap_info_काष्ठा *sis = swap_info[type];
	काष्ठा frontswap_ops *ops;

	VM_BUG_ON(!frontswap_ops);
	VM_BUG_ON(sis == शून्य);

	अगर (sis->frontswap_map == शून्य)
		वापस;

	क्रम_each_frontswap_ops(ops)
		ops->invalidate_area(type);
	atomic_set(&sis->frontswap_pages, 0);
	biपंचांगap_zero(sis->frontswap_map, sis->max);
पूर्ण
EXPORT_SYMBOL(__frontswap_invalidate_area);

अटल अचिन्हित दीर्घ __frontswap_curr_pages(व्योम)
अणु
	अचिन्हित दीर्घ totalpages = 0;
	काष्ठा swap_info_काष्ठा *si = शून्य;

	निश्चित_spin_locked(&swap_lock);
	plist_क्रम_each_entry(si, &swap_active_head, list)
		totalpages += atomic_पढ़ो(&si->frontswap_pages);
	वापस totalpages;
पूर्ण

अटल पूर्णांक __frontswap_unuse_pages(अचिन्हित दीर्घ total, अचिन्हित दीर्घ *unused,
					पूर्णांक *swapid)
अणु
	पूर्णांक ret = -EINVAL;
	काष्ठा swap_info_काष्ठा *si = शून्य;
	पूर्णांक si_frontswap_pages;
	अचिन्हित दीर्घ total_pages_to_unuse = total;
	अचिन्हित दीर्घ pages = 0, pages_to_unuse = 0;

	निश्चित_spin_locked(&swap_lock);
	plist_क्रम_each_entry(si, &swap_active_head, list) अणु
		si_frontswap_pages = atomic_पढ़ो(&si->frontswap_pages);
		अगर (total_pages_to_unuse < si_frontswap_pages) अणु
			pages = pages_to_unuse = total_pages_to_unuse;
		पूर्ण अन्यथा अणु
			pages = si_frontswap_pages;
			pages_to_unuse = 0; /* unuse all */
		पूर्ण
		/* ensure there is enough RAM to fetch pages from frontswap */
		अगर (security_vm_enough_memory_mm(current->mm, pages)) अणु
			ret = -ENOMEM;
			जारी;
		पूर्ण
		vm_unacct_memory(pages);
		*unused = pages_to_unuse;
		*swapid = si->type;
		ret = 0;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Used to check अगर it's necessary and feasible to unuse pages.
 * Return 1 when nothing to करो, 0 when need to shrink pages,
 * error code when there is an error.
 */
अटल पूर्णांक __frontswap_shrink(अचिन्हित दीर्घ target_pages,
				अचिन्हित दीर्घ *pages_to_unuse,
				पूर्णांक *type)
अणु
	अचिन्हित दीर्घ total_pages = 0, total_pages_to_unuse;

	निश्चित_spin_locked(&swap_lock);

	total_pages = __frontswap_curr_pages();
	अगर (total_pages <= target_pages) अणु
		/* Nothing to करो */
		*pages_to_unuse = 0;
		वापस 1;
	पूर्ण
	total_pages_to_unuse = total_pages - target_pages;
	वापस __frontswap_unuse_pages(total_pages_to_unuse, pages_to_unuse, type);
पूर्ण

/*
 * Frontswap, like a true swap device, may unnecessarily retain pages
 * under certain circumstances; "shrink" frontswap is essentially a
 * "partial swapoff" and works by calling try_to_unuse to attempt to
 * unuse enough frontswap pages to attempt to -- subject to memory
 * स्थिरraपूर्णांकs -- reduce the number of pages in frontswap to the
 * number given in the parameter target_pages.
 */
व्योम frontswap_shrink(अचिन्हित दीर्घ target_pages)
अणु
	अचिन्हित दीर्घ pages_to_unuse = 0;
	पूर्णांक type, ret;

	/*
	 * we करोn't want to hold swap_lock जबतक करोing a very
	 * lengthy try_to_unuse, but swap_list may change
	 * so restart scan from swap_active_head each समय
	 */
	spin_lock(&swap_lock);
	ret = __frontswap_shrink(target_pages, &pages_to_unuse, &type);
	spin_unlock(&swap_lock);
	अगर (ret == 0)
		try_to_unuse(type, true, pages_to_unuse);
	वापस;
पूर्ण
EXPORT_SYMBOL(frontswap_shrink);

/*
 * Count and वापस the number of frontswap pages across all
 * swap devices.  This is exported so that backend drivers can
 * determine current usage without पढ़ोing debugfs.
 */
अचिन्हित दीर्घ frontswap_curr_pages(व्योम)
अणु
	अचिन्हित दीर्घ totalpages = 0;

	spin_lock(&swap_lock);
	totalpages = __frontswap_curr_pages();
	spin_unlock(&swap_lock);

	वापस totalpages;
पूर्ण
EXPORT_SYMBOL(frontswap_curr_pages);

अटल पूर्णांक __init init_frontswap(व्योम)
अणु
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *root = debugfs_create_dir("frontswap", शून्य);
	अगर (root == शून्य)
		वापस -ENXIO;
	debugfs_create_u64("loads", 0444, root, &frontswap_loads);
	debugfs_create_u64("succ_stores", 0444, root, &frontswap_succ_stores);
	debugfs_create_u64("failed_stores", 0444, root,
			   &frontswap_failed_stores);
	debugfs_create_u64("invalidates", 0444, root, &frontswap_invalidates);
#पूर्ण_अगर
	वापस 0;
पूर्ण

module_init(init_frontswap);
