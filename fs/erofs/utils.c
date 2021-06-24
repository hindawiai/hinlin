<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2018 HUAWEI, Inc.
 *             https://www.huawei.com/
 * Created by Gao Xiang <gaoxiang25@huawei.com>
 */
#समावेश "internal.h"
#समावेश <linux/pagevec.h>

काष्ठा page *erofs_allocpage(काष्ठा list_head *pool, gfp_t gfp)
अणु
	काष्ठा page *page;

	अगर (!list_empty(pool)) अणु
		page = lru_to_page(pool);
		DBG_BUGON(page_ref_count(page) != 1);
		list_del(&page->lru);
	पूर्ण अन्यथा अणु
		page = alloc_page(gfp);
	पूर्ण
	वापस page;
पूर्ण

#अगर_घोषित CONFIG_EROFS_FS_ZIP
/* global shrink count (क्रम all mounted EROFS instances) */
अटल atomic_दीर्घ_t erofs_global_shrink_cnt;

अटल पूर्णांक erofs_workgroup_get(काष्ठा erofs_workgroup *grp)
अणु
	पूर्णांक o;

repeat:
	o = erofs_रुको_on_workgroup_मुक्तzed(grp);
	अगर (o <= 0)
		वापस -1;

	अगर (atomic_cmpxchg(&grp->refcount, o, o + 1) != o)
		जाओ repeat;

	/* decrease refcount paired by erofs_workgroup_put */
	अगर (o == 1)
		atomic_दीर्घ_dec(&erofs_global_shrink_cnt);
	वापस 0;
पूर्ण

काष्ठा erofs_workgroup *erofs_find_workgroup(काष्ठा super_block *sb,
					     pgoff_t index)
अणु
	काष्ठा erofs_sb_info *sbi = EROFS_SB(sb);
	काष्ठा erofs_workgroup *grp;

repeat:
	rcu_पढ़ो_lock();
	grp = xa_load(&sbi->managed_pslots, index);
	अगर (grp) अणु
		अगर (erofs_workgroup_get(grp)) अणु
			/* prefer to relax rcu पढ़ो side */
			rcu_पढ़ो_unlock();
			जाओ repeat;
		पूर्ण

		DBG_BUGON(index != grp->index);
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस grp;
पूर्ण

काष्ठा erofs_workgroup *erofs_insert_workgroup(काष्ठा super_block *sb,
					       काष्ठा erofs_workgroup *grp)
अणु
	काष्ठा erofs_sb_info *स्थिर sbi = EROFS_SB(sb);
	काष्ठा erofs_workgroup *pre;

	/*
	 * Bump up a reference count beक्रमe making this visible
	 * to others क्रम the XArray in order to aव्योम potential
	 * UAF without serialized by xa_lock.
	 */
	atomic_inc(&grp->refcount);

repeat:
	xa_lock(&sbi->managed_pslots);
	pre = __xa_cmpxchg(&sbi->managed_pslots, grp->index,
			   शून्य, grp, GFP_NOFS);
	अगर (pre) अणु
		अगर (xa_is_err(pre)) अणु
			pre = ERR_PTR(xa_err(pre));
		पूर्ण अन्यथा अगर (erofs_workgroup_get(pre)) अणु
			/* try to legitimize the current in-tree one */
			xa_unlock(&sbi->managed_pslots);
			cond_resched();
			जाओ repeat;
		पूर्ण
		atomic_dec(&grp->refcount);
		grp = pre;
	पूर्ण
	xa_unlock(&sbi->managed_pslots);
	वापस grp;
पूर्ण

अटल व्योम  __erofs_workgroup_मुक्त(काष्ठा erofs_workgroup *grp)
अणु
	atomic_दीर्घ_dec(&erofs_global_shrink_cnt);
	erofs_workgroup_मुक्त_rcu(grp);
पूर्ण

पूर्णांक erofs_workgroup_put(काष्ठा erofs_workgroup *grp)
अणु
	पूर्णांक count = atomic_dec_वापस(&grp->refcount);

	अगर (count == 1)
		atomic_दीर्घ_inc(&erofs_global_shrink_cnt);
	अन्यथा अगर (!count)
		__erofs_workgroup_मुक्त(grp);
	वापस count;
पूर्ण

अटल bool erofs_try_to_release_workgroup(काष्ठा erofs_sb_info *sbi,
					   काष्ठा erofs_workgroup *grp)
अणु
	/*
	 * If managed cache is on, refcount of workgroups
	 * themselves could be < 0 (मुक्तzed). In other words,
	 * there is no guarantee that all refcounts > 0.
	 */
	अगर (!erofs_workgroup_try_to_मुक्तze(grp, 1))
		वापस false;

	/*
	 * Note that all cached pages should be unattached
	 * beक्रमe deleted from the XArray. Otherwise some
	 * cached pages could be still attached to the orphan
	 * old workgroup when the new one is available in the tree.
	 */
	अगर (erofs_try_to_मुक्त_all_cached_pages(sbi, grp)) अणु
		erofs_workgroup_unमुक्तze(grp, 1);
		वापस false;
	पूर्ण

	/*
	 * It's impossible to fail after the workgroup is मुक्तzed,
	 * however in order to aव्योम some race conditions, add a
	 * DBG_BUGON to observe this in advance.
	 */
	DBG_BUGON(xa_erase(&sbi->managed_pslots, grp->index) != grp);

	/* last refcount should be connected with its managed pslot.  */
	erofs_workgroup_unमुक्तze(grp, 0);
	__erofs_workgroup_मुक्त(grp);
	वापस true;
पूर्ण

अटल अचिन्हित दीर्घ erofs_shrink_workstation(काष्ठा erofs_sb_info *sbi,
					      अचिन्हित दीर्घ nr_shrink)
अणु
	काष्ठा erofs_workgroup *grp;
	अचिन्हित पूर्णांक मुक्तd = 0;
	अचिन्हित दीर्घ index;

	xa_क्रम_each(&sbi->managed_pslots, index, grp) अणु
		/* try to shrink each valid workgroup */
		अगर (!erofs_try_to_release_workgroup(sbi, grp))
			जारी;

		++मुक्तd;
		अगर (!--nr_shrink)
			अवरोध;
	पूर्ण
	वापस मुक्तd;
पूर्ण

/* रक्षित by 'erofs_sb_list_lock' */
अटल अचिन्हित पूर्णांक shrinker_run_no;

/* protects the mounted 'erofs_sb_list' */
अटल DEFINE_SPINLOCK(erofs_sb_list_lock);
अटल LIST_HEAD(erofs_sb_list);

व्योम erofs_shrinker_रेजिस्टर(काष्ठा super_block *sb)
अणु
	काष्ठा erofs_sb_info *sbi = EROFS_SB(sb);

	mutex_init(&sbi->umount_mutex);

	spin_lock(&erofs_sb_list_lock);
	list_add(&sbi->list, &erofs_sb_list);
	spin_unlock(&erofs_sb_list_lock);
पूर्ण

व्योम erofs_shrinker_unरेजिस्टर(काष्ठा super_block *sb)
अणु
	काष्ठा erofs_sb_info *स्थिर sbi = EROFS_SB(sb);

	mutex_lock(&sbi->umount_mutex);
	/* clean up all reमुख्यing workgroups in memory */
	erofs_shrink_workstation(sbi, ~0UL);

	spin_lock(&erofs_sb_list_lock);
	list_del(&sbi->list);
	spin_unlock(&erofs_sb_list_lock);
	mutex_unlock(&sbi->umount_mutex);
पूर्ण

अटल अचिन्हित दीर्घ erofs_shrink_count(काष्ठा shrinker *shrink,
					काष्ठा shrink_control *sc)
अणु
	वापस atomic_दीर्घ_पढ़ो(&erofs_global_shrink_cnt);
पूर्ण

अटल अचिन्हित दीर्घ erofs_shrink_scan(काष्ठा shrinker *shrink,
				       काष्ठा shrink_control *sc)
अणु
	काष्ठा erofs_sb_info *sbi;
	काष्ठा list_head *p;

	अचिन्हित दीर्घ nr = sc->nr_to_scan;
	अचिन्हित पूर्णांक run_no;
	अचिन्हित दीर्घ मुक्तd = 0;

	spin_lock(&erofs_sb_list_lock);
	करो अणु
		run_no = ++shrinker_run_no;
	पूर्ण जबतक (run_no == 0);

	/* Iterate over all mounted superblocks and try to shrink them */
	p = erofs_sb_list.next;
	जबतक (p != &erofs_sb_list) अणु
		sbi = list_entry(p, काष्ठा erofs_sb_info, list);

		/*
		 * We move the ones we करो to the end of the list, so we stop
		 * when we see one we have alपढ़ोy करोne.
		 */
		अगर (sbi->shrinker_run_no == run_no)
			अवरोध;

		अगर (!mutex_trylock(&sbi->umount_mutex)) अणु
			p = p->next;
			जारी;
		पूर्ण

		spin_unlock(&erofs_sb_list_lock);
		sbi->shrinker_run_no = run_no;

		मुक्तd += erofs_shrink_workstation(sbi, nr - मुक्तd);

		spin_lock(&erofs_sb_list_lock);
		/* Get the next list element beक्रमe we move this one */
		p = p->next;

		/*
		 * Move this one to the end of the list to provide some
		 * fairness.
		 */
		list_move_tail(&sbi->list, &erofs_sb_list);
		mutex_unlock(&sbi->umount_mutex);

		अगर (मुक्तd >= nr)
			अवरोध;
	पूर्ण
	spin_unlock(&erofs_sb_list_lock);
	वापस मुक्तd;
पूर्ण

अटल काष्ठा shrinker erofs_shrinker_info = अणु
	.scan_objects = erofs_shrink_scan,
	.count_objects = erofs_shrink_count,
	.seeks = DEFAULT_SEEKS,
पूर्ण;

पूर्णांक __init erofs_init_shrinker(व्योम)
अणु
	वापस रेजिस्टर_shrinker(&erofs_shrinker_info);
पूर्ण

व्योम erofs_निकास_shrinker(व्योम)
अणु
	unरेजिस्टर_shrinker(&erofs_shrinker_info);
पूर्ण
#पूर्ण_अगर	/* !CONFIG_EROFS_FS_ZIP */

