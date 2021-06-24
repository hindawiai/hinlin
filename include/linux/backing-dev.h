<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/linux/backing-dev.h
 *
 * low-level device inक्रमmation and state which is propagated up through
 * to high-level code.
 */

#अगर_अघोषित _LINUX_BACKING_DEV_H
#घोषणा _LINUX_BACKING_DEV_H

#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/sched.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/device.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/blk-cgroup.h>
#समावेश <linux/backing-dev-defs.h>
#समावेश <linux/slab.h>

अटल अंतरभूत काष्ठा backing_dev_info *bdi_get(काष्ठा backing_dev_info *bdi)
अणु
	kref_get(&bdi->refcnt);
	वापस bdi;
पूर्ण

काष्ठा backing_dev_info *bdi_get_by_id(u64 id);
व्योम bdi_put(काष्ठा backing_dev_info *bdi);

__म_लिखो(2, 3)
पूर्णांक bdi_रेजिस्टर(काष्ठा backing_dev_info *bdi, स्थिर अक्षर *fmt, ...);
__म_लिखो(2, 0)
पूर्णांक bdi_रेजिस्टर_va(काष्ठा backing_dev_info *bdi, स्थिर अक्षर *fmt,
		    बहु_सूची args);
व्योम bdi_set_owner(काष्ठा backing_dev_info *bdi, काष्ठा device *owner);
व्योम bdi_unरेजिस्टर(काष्ठा backing_dev_info *bdi);

काष्ठा backing_dev_info *bdi_alloc(पूर्णांक node_id);

व्योम wb_start_background_ग_लिखोback(काष्ठा bdi_ग_लिखोback *wb);
व्योम wb_workfn(काष्ठा work_काष्ठा *work);
व्योम wb_wakeup_delayed(काष्ठा bdi_ग_लिखोback *wb);

व्योम wb_रुको_क्रम_completion(काष्ठा wb_completion *करोne);

बाह्य spinlock_t bdi_lock;
बाह्य काष्ठा list_head bdi_list;

बाह्य काष्ठा workqueue_काष्ठा *bdi_wq;
बाह्य काष्ठा workqueue_काष्ठा *bdi_async_bio_wq;

अटल अंतरभूत bool wb_has_dirty_io(काष्ठा bdi_ग_लिखोback *wb)
अणु
	वापस test_bit(WB_has_dirty_io, &wb->state);
पूर्ण

अटल अंतरभूत bool bdi_has_dirty_io(काष्ठा backing_dev_info *bdi)
अणु
	/*
	 * @bdi->tot_ग_लिखो_bandwidth is guaranteed to be > 0 अगर there are
	 * any dirty wbs.  See wb_update_ग_लिखो_bandwidth().
	 */
	वापस atomic_दीर्घ_पढ़ो(&bdi->tot_ग_लिखो_bandwidth);
पूर्ण

अटल अंतरभूत व्योम __add_wb_stat(काष्ठा bdi_ग_लिखोback *wb,
				 क्रमागत wb_stat_item item, s64 amount)
अणु
	percpu_counter_add_batch(&wb->stat[item], amount, WB_STAT_BATCH);
पूर्ण

अटल अंतरभूत व्योम inc_wb_stat(काष्ठा bdi_ग_लिखोback *wb, क्रमागत wb_stat_item item)
अणु
	__add_wb_stat(wb, item, 1);
पूर्ण

अटल अंतरभूत व्योम dec_wb_stat(काष्ठा bdi_ग_लिखोback *wb, क्रमागत wb_stat_item item)
अणु
	__add_wb_stat(wb, item, -1);
पूर्ण

अटल अंतरभूत s64 wb_stat(काष्ठा bdi_ग_लिखोback *wb, क्रमागत wb_stat_item item)
अणु
	वापस percpu_counter_पढ़ो_positive(&wb->stat[item]);
पूर्ण

अटल अंतरभूत s64 wb_stat_sum(काष्ठा bdi_ग_लिखोback *wb, क्रमागत wb_stat_item item)
अणु
	वापस percpu_counter_sum_positive(&wb->stat[item]);
पूर्ण

बाह्य व्योम wb_ग_लिखोout_inc(काष्ठा bdi_ग_लिखोback *wb);

/*
 * maximal error of a stat counter.
 */
अटल अंतरभूत अचिन्हित दीर्घ wb_stat_error(व्योम)
अणु
#अगर_घोषित CONFIG_SMP
	वापस nr_cpu_ids * WB_STAT_BATCH;
#अन्यथा
	वापस 1;
#पूर्ण_अगर
पूर्ण

पूर्णांक bdi_set_min_ratio(काष्ठा backing_dev_info *bdi, अचिन्हित पूर्णांक min_ratio);
पूर्णांक bdi_set_max_ratio(काष्ठा backing_dev_info *bdi, अचिन्हित पूर्णांक max_ratio);

/*
 * Flags in backing_dev_info::capability
 *
 * BDI_CAP_WRITEBACK:		Supports dirty page ग_लिखोback, and dirty pages
 *				should contribute to accounting
 * BDI_CAP_WRITEBACK_ACCT:	Automatically account ग_लिखोback pages
 * BDI_CAP_STRICTLIMIT:		Keep number of dirty pages below bdi threshold
 */
#घोषणा BDI_CAP_WRITEBACK		(1 << 0)
#घोषणा BDI_CAP_WRITEBACK_ACCT		(1 << 1)
#घोषणा BDI_CAP_STRICTLIMIT		(1 << 2)

बाह्य काष्ठा backing_dev_info noop_backing_dev_info;

/**
 * ग_लिखोback_in_progress - determine whether there is ग_लिखोback in progress
 * @wb: bdi_ग_लिखोback of पूर्णांकerest
 *
 * Determine whether there is ग_लिखोback रुकोing to be handled against a
 * bdi_ग_लिखोback.
 */
अटल अंतरभूत bool ग_लिखोback_in_progress(काष्ठा bdi_ग_लिखोback *wb)
अणु
	वापस test_bit(WB_ग_लिखोback_running, &wb->state);
पूर्ण

अटल अंतरभूत काष्ठा backing_dev_info *inode_to_bdi(काष्ठा inode *inode)
अणु
	काष्ठा super_block *sb;

	अगर (!inode)
		वापस &noop_backing_dev_info;

	sb = inode->i_sb;
#अगर_घोषित CONFIG_BLOCK
	अगर (sb_is_blkdev_sb(sb))
		वापस I_BDEV(inode)->bd_bdi;
#पूर्ण_अगर
	वापस sb->s_bdi;
पूर्ण

अटल अंतरभूत पूर्णांक wb_congested(काष्ठा bdi_ग_लिखोback *wb, पूर्णांक cong_bits)
अणु
	वापस wb->congested & cong_bits;
पूर्ण

दीर्घ congestion_रुको(पूर्णांक sync, दीर्घ समयout);
दीर्घ रुको_अगरf_congested(पूर्णांक sync, दीर्घ समयout);

अटल अंतरभूत bool mapping_can_ग_लिखोback(काष्ठा address_space *mapping)
अणु
	वापस inode_to_bdi(mapping->host)->capabilities & BDI_CAP_WRITEBACK;
पूर्ण

अटल अंतरभूत पूर्णांक bdi_sched_रुको(व्योम *word)
अणु
	schedule();
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_CGROUP_WRITEBACK

काष्ठा bdi_ग_लिखोback *wb_get_lookup(काष्ठा backing_dev_info *bdi,
				    काष्ठा cgroup_subsys_state *memcg_css);
काष्ठा bdi_ग_लिखोback *wb_get_create(काष्ठा backing_dev_info *bdi,
				    काष्ठा cgroup_subsys_state *memcg_css,
				    gfp_t gfp);
व्योम wb_memcg_offline(काष्ठा mem_cgroup *memcg);
व्योम wb_blkcg_offline(काष्ठा blkcg *blkcg);
पूर्णांक inode_congested(काष्ठा inode *inode, पूर्णांक cong_bits);

/**
 * inode_cgwb_enabled - test whether cgroup ग_लिखोback is enabled on an inode
 * @inode: inode of पूर्णांकerest
 *
 * Cgroup ग_लिखोback requires support from the fileप्रणाली.  Also, both memcg and
 * iocg have to be on the शेष hierarchy.  Test whether all conditions are
 * met.
 *
 * Note that the test result may change dynamically on the same inode
 * depending on how memcg and iocg are configured.
 */
अटल अंतरभूत bool inode_cgwb_enabled(काष्ठा inode *inode)
अणु
	काष्ठा backing_dev_info *bdi = inode_to_bdi(inode);

	वापस cgroup_subsys_on_dfl(memory_cgrp_subsys) &&
		cgroup_subsys_on_dfl(io_cgrp_subsys) &&
		(bdi->capabilities & BDI_CAP_WRITEBACK) &&
		(inode->i_sb->s_अगरlags & SB_I_CGROUPWB);
पूर्ण

/**
 * wb_find_current - find wb क्रम %current on a bdi
 * @bdi: bdi of पूर्णांकerest
 *
 * Find the wb of @bdi which matches both the memcg and blkcg of %current.
 * Must be called under rcu_पढ़ो_lock() which protects the returend wb.
 * शून्य अगर not found.
 */
अटल अंतरभूत काष्ठा bdi_ग_लिखोback *wb_find_current(काष्ठा backing_dev_info *bdi)
अणु
	काष्ठा cgroup_subsys_state *memcg_css;
	काष्ठा bdi_ग_लिखोback *wb;

	memcg_css = task_css(current, memory_cgrp_id);
	अगर (!memcg_css->parent)
		वापस &bdi->wb;

	wb = radix_tree_lookup(&bdi->cgwb_tree, memcg_css->id);

	/*
	 * %current's blkcg equals the effective blkcg of its memcg.  No
	 * need to use the relatively expensive cgroup_get_e_css().
	 */
	अगर (likely(wb && wb->blkcg_css == task_css(current, io_cgrp_id)))
		वापस wb;
	वापस शून्य;
पूर्ण

/**
 * wb_get_create_current - get or create wb क्रम %current on a bdi
 * @bdi: bdi of पूर्णांकerest
 * @gfp: allocation mask
 *
 * Equivalent to wb_get_create() on %current's memcg.  This function is
 * called from a relatively hot path and optimizes the common हालs using
 * wb_find_current().
 */
अटल अंतरभूत काष्ठा bdi_ग_लिखोback *
wb_get_create_current(काष्ठा backing_dev_info *bdi, gfp_t gfp)
अणु
	काष्ठा bdi_ग_लिखोback *wb;

	rcu_पढ़ो_lock();
	wb = wb_find_current(bdi);
	अगर (wb && unlikely(!wb_tryget(wb)))
		wb = शून्य;
	rcu_पढ़ो_unlock();

	अगर (unlikely(!wb)) अणु
		काष्ठा cgroup_subsys_state *memcg_css;

		memcg_css = task_get_css(current, memory_cgrp_id);
		wb = wb_get_create(bdi, memcg_css, gfp);
		css_put(memcg_css);
	पूर्ण
	वापस wb;
पूर्ण

/**
 * inode_to_wb_is_valid - test whether an inode has a wb associated
 * @inode: inode of पूर्णांकerest
 *
 * Returns %true अगर @inode has a wb associated.  May be called without any
 * locking.
 */
अटल अंतरभूत bool inode_to_wb_is_valid(काष्ठा inode *inode)
अणु
	वापस inode->i_wb;
पूर्ण

/**
 * inode_to_wb - determine the wb of an inode
 * @inode: inode of पूर्णांकerest
 *
 * Returns the wb @inode is currently associated with.  The caller must be
 * holding either @inode->i_lock, the i_pages lock, or the
 * associated wb's list_lock.
 */
अटल अंतरभूत काष्ठा bdi_ग_लिखोback *inode_to_wb(स्थिर काष्ठा inode *inode)
अणु
#अगर_घोषित CONFIG_LOCKDEP
	WARN_ON_ONCE(debug_locks &&
		     (!lockdep_is_held(&inode->i_lock) &&
		      !lockdep_is_held(&inode->i_mapping->i_pages.xa_lock) &&
		      !lockdep_is_held(&inode->i_wb->list_lock)));
#पूर्ण_अगर
	वापस inode->i_wb;
पूर्ण

/**
 * unlocked_inode_to_wb_begin - begin unlocked inode wb access transaction
 * @inode: target inode
 * @cookie: output param, to be passed to the end function
 *
 * The caller wants to access the wb associated with @inode but isn't
 * holding inode->i_lock, the i_pages lock or wb->list_lock.  This
 * function determines the wb associated with @inode and ensures that the
 * association करोesn't change until the transaction is finished with
 * unlocked_inode_to_wb_end().
 *
 * The caller must call unlocked_inode_to_wb_end() with *@cookie afterwards and
 * can't sleep during the transaction.  IRQs may or may not be disabled on
 * वापस.
 */
अटल अंतरभूत काष्ठा bdi_ग_लिखोback *
unlocked_inode_to_wb_begin(काष्ठा inode *inode, काष्ठा wb_lock_cookie *cookie)
अणु
	rcu_पढ़ो_lock();

	/*
	 * Paired with store_release in inode_चयन_wbs_work_fn() and
	 * ensures that we see the new wb अगर we see cleared I_WB_SWITCH.
	 */
	cookie->locked = smp_load_acquire(&inode->i_state) & I_WB_SWITCH;

	अगर (unlikely(cookie->locked))
		xa_lock_irqsave(&inode->i_mapping->i_pages, cookie->flags);

	/*
	 * Protected by either !I_WB_SWITCH + rcu_पढ़ो_lock() or the i_pages
	 * lock.  inode_to_wb() will bark.  Deref directly.
	 */
	वापस inode->i_wb;
पूर्ण

/**
 * unlocked_inode_to_wb_end - end inode wb access transaction
 * @inode: target inode
 * @cookie: @cookie from unlocked_inode_to_wb_begin()
 */
अटल अंतरभूत व्योम unlocked_inode_to_wb_end(काष्ठा inode *inode,
					    काष्ठा wb_lock_cookie *cookie)
अणु
	अगर (unlikely(cookie->locked))
		xa_unlock_irqrestore(&inode->i_mapping->i_pages, cookie->flags);

	rcu_पढ़ो_unlock();
पूर्ण

#अन्यथा	/* CONFIG_CGROUP_WRITEBACK */

अटल अंतरभूत bool inode_cgwb_enabled(काष्ठा inode *inode)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा bdi_ग_लिखोback *wb_find_current(काष्ठा backing_dev_info *bdi)
अणु
	वापस &bdi->wb;
पूर्ण

अटल अंतरभूत काष्ठा bdi_ग_लिखोback *
wb_get_create_current(काष्ठा backing_dev_info *bdi, gfp_t gfp)
अणु
	वापस &bdi->wb;
पूर्ण

अटल अंतरभूत bool inode_to_wb_is_valid(काष्ठा inode *inode)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत काष्ठा bdi_ग_लिखोback *inode_to_wb(काष्ठा inode *inode)
अणु
	वापस &inode_to_bdi(inode)->wb;
पूर्ण

अटल अंतरभूत काष्ठा bdi_ग_लिखोback *
unlocked_inode_to_wb_begin(काष्ठा inode *inode, काष्ठा wb_lock_cookie *cookie)
अणु
	वापस inode_to_wb(inode);
पूर्ण

अटल अंतरभूत व्योम unlocked_inode_to_wb_end(काष्ठा inode *inode,
					    काष्ठा wb_lock_cookie *cookie)
अणु
पूर्ण

अटल अंतरभूत व्योम wb_memcg_offline(काष्ठा mem_cgroup *memcg)
अणु
पूर्ण

अटल अंतरभूत व्योम wb_blkcg_offline(काष्ठा blkcg *blkcg)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक inode_congested(काष्ठा inode *inode, पूर्णांक cong_bits)
अणु
	वापस wb_congested(&inode_to_bdi(inode)->wb, cong_bits);
पूर्ण

#पूर्ण_अगर	/* CONFIG_CGROUP_WRITEBACK */

अटल अंतरभूत पूर्णांक inode_पढ़ो_congested(काष्ठा inode *inode)
अणु
	वापस inode_congested(inode, 1 << WB_sync_congested);
पूर्ण

अटल अंतरभूत पूर्णांक inode_ग_लिखो_congested(काष्ठा inode *inode)
अणु
	वापस inode_congested(inode, 1 << WB_async_congested);
पूर्ण

अटल अंतरभूत पूर्णांक inode_rw_congested(काष्ठा inode *inode)
अणु
	वापस inode_congested(inode, (1 << WB_sync_congested) |
				      (1 << WB_async_congested));
पूर्ण

अटल अंतरभूत पूर्णांक bdi_congested(काष्ठा backing_dev_info *bdi, पूर्णांक cong_bits)
अणु
	वापस wb_congested(&bdi->wb, cong_bits);
पूर्ण

अटल अंतरभूत पूर्णांक bdi_पढ़ो_congested(काष्ठा backing_dev_info *bdi)
अणु
	वापस bdi_congested(bdi, 1 << WB_sync_congested);
पूर्ण

अटल अंतरभूत पूर्णांक bdi_ग_लिखो_congested(काष्ठा backing_dev_info *bdi)
अणु
	वापस bdi_congested(bdi, 1 << WB_async_congested);
पूर्ण

अटल अंतरभूत पूर्णांक bdi_rw_congested(काष्ठा backing_dev_info *bdi)
अणु
	वापस bdi_congested(bdi, (1 << WB_sync_congested) |
				  (1 << WB_async_congested));
पूर्ण

स्थिर अक्षर *bdi_dev_name(काष्ठा backing_dev_info *bdi);

#पूर्ण_अगर	/* _LINUX_BACKING_DEV_H */
