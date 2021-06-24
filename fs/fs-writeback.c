<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * fs/fs-ग_लिखोback.c
 *
 * Copyright (C) 2002, Linus Torvalds.
 *
 * Contains all the functions related to writing back and रुकोing
 * upon dirty inodes against superblocks, and writing back dirty
 * pages against inodes.  ie: data ग_लिखोback.  Writeout of the
 * inode itself is not handled here.
 *
 * 10Apr2002	Andrew Morton
 *		Split out of fs/inode.c
 *		Additions क्रम address_space-based ग_लिखोback
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/device.h>
#समावेश <linux/memcontrol.h>
#समावेश "internal.h"

/*
 * 4MB minimal ग_लिखो chunk size
 */
#घोषणा MIN_WRITEBACK_PAGES	(4096UL >> (PAGE_SHIFT - 10))

/*
 * Passed पूर्णांकo wb_ग_लिखोback(), essentially a subset of ग_लिखोback_control
 */
काष्ठा wb_ग_लिखोback_work अणु
	दीर्घ nr_pages;
	काष्ठा super_block *sb;
	क्रमागत ग_लिखोback_sync_modes sync_mode;
	अचिन्हित पूर्णांक tagged_ग_लिखोpages:1;
	अचिन्हित पूर्णांक क्रम_kupdate:1;
	अचिन्हित पूर्णांक range_cyclic:1;
	अचिन्हित पूर्णांक क्रम_background:1;
	अचिन्हित पूर्णांक क्रम_sync:1;	/* sync(2) WB_SYNC_ALL ग_लिखोback */
	अचिन्हित पूर्णांक स्वतः_मुक्त:1;	/* मुक्त on completion */
	क्रमागत wb_reason reason;		/* why was ग_लिखोback initiated? */

	काष्ठा list_head list;		/* pending work list */
	काष्ठा wb_completion *करोne;	/* set अगर the caller रुकोs */
पूर्ण;

/*
 * If an inode is स्थिरantly having its pages dirtied, but then the
 * updates stop dirtyसमय_expire_पूर्णांकerval seconds in the past, it's
 * possible क्रम the worst हाल समय between when an inode has its
 * बारtamps updated and when they finally get written out to be two
 * dirtyसमय_expire_पूर्णांकervals.  We set the शेष to 12 hours (in
 * seconds), which means most of the समय inodes will have their
 * बारtamps written to disk after 12 hours, but in the worst हाल a
 * few inodes might not their बारtamps updated क्रम 24 hours.
 */
अचिन्हित पूर्णांक dirtyसमय_expire_पूर्णांकerval = 12 * 60 * 60;

अटल अंतरभूत काष्ठा inode *wb_inode(काष्ठा list_head *head)
अणु
	वापस list_entry(head, काष्ठा inode, i_io_list);
पूर्ण

/*
 * Include the creation of the trace poपूर्णांकs after defining the
 * wb_ग_लिखोback_work काष्ठाure and अंतरभूत functions so that the definition
 * reमुख्यs local to this file.
 */
#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/ग_लिखोback.h>

EXPORT_TRACEPOINT_SYMBOL_GPL(wbc_ग_लिखोpage);

अटल bool wb_io_lists_populated(काष्ठा bdi_ग_लिखोback *wb)
अणु
	अगर (wb_has_dirty_io(wb)) अणु
		वापस false;
	पूर्ण अन्यथा अणु
		set_bit(WB_has_dirty_io, &wb->state);
		WARN_ON_ONCE(!wb->avg_ग_लिखो_bandwidth);
		atomic_दीर्घ_add(wb->avg_ग_लिखो_bandwidth,
				&wb->bdi->tot_ग_लिखो_bandwidth);
		वापस true;
	पूर्ण
पूर्ण

अटल व्योम wb_io_lists_depopulated(काष्ठा bdi_ग_लिखोback *wb)
अणु
	अगर (wb_has_dirty_io(wb) && list_empty(&wb->b_dirty) &&
	    list_empty(&wb->b_io) && list_empty(&wb->b_more_io)) अणु
		clear_bit(WB_has_dirty_io, &wb->state);
		WARN_ON_ONCE(atomic_दीर्घ_sub_वापस(wb->avg_ग_लिखो_bandwidth,
					&wb->bdi->tot_ग_लिखो_bandwidth) < 0);
	पूर्ण
पूर्ण

/**
 * inode_io_list_move_locked - move an inode onto a bdi_ग_लिखोback IO list
 * @inode: inode to be moved
 * @wb: target bdi_ग_लिखोback
 * @head: one of @wb->b_अणुdirty|io|more_io|dirty_समयपूर्ण
 *
 * Move @inode->i_io_list to @list of @wb and set %WB_has_dirty_io.
 * Returns %true अगर @inode is the first occupant of the !dirty_समय IO
 * lists; otherwise, %false.
 */
अटल bool inode_io_list_move_locked(काष्ठा inode *inode,
				      काष्ठा bdi_ग_लिखोback *wb,
				      काष्ठा list_head *head)
अणु
	निश्चित_spin_locked(&wb->list_lock);

	list_move(&inode->i_io_list, head);

	/* dirty_समय करोesn't count as dirty_io until expiration */
	अगर (head != &wb->b_dirty_समय)
		वापस wb_io_lists_populated(wb);

	wb_io_lists_depopulated(wb);
	वापस false;
पूर्ण

/**
 * inode_io_list_del_locked - हटाओ an inode from its bdi_ग_लिखोback IO list
 * @inode: inode to be हटाओd
 * @wb: bdi_ग_लिखोback @inode is being हटाओd from
 *
 * Remove @inode which may be on one of @wb->b_अणुdirty|io|more_ioपूर्ण lists and
 * clear %WB_has_dirty_io अगर all are empty afterwards.
 */
अटल व्योम inode_io_list_del_locked(काष्ठा inode *inode,
				     काष्ठा bdi_ग_लिखोback *wb)
अणु
	निश्चित_spin_locked(&wb->list_lock);
	निश्चित_spin_locked(&inode->i_lock);

	inode->i_state &= ~I_SYNC_QUEUED;
	list_del_init(&inode->i_io_list);
	wb_io_lists_depopulated(wb);
पूर्ण

अटल व्योम wb_wakeup(काष्ठा bdi_ग_लिखोback *wb)
अणु
	spin_lock_bh(&wb->work_lock);
	अगर (test_bit(WB_रेजिस्टरed, &wb->state))
		mod_delayed_work(bdi_wq, &wb->dwork, 0);
	spin_unlock_bh(&wb->work_lock);
पूर्ण

अटल व्योम finish_ग_लिखोback_work(काष्ठा bdi_ग_लिखोback *wb,
				  काष्ठा wb_ग_लिखोback_work *work)
अणु
	काष्ठा wb_completion *करोne = work->करोne;

	अगर (work->स्वतः_मुक्त)
		kमुक्त(work);
	अगर (करोne) अणु
		रुको_queue_head_t *रुकोq = करोne->रुकोq;

		/* @करोne can't be accessed after the following dec */
		अगर (atomic_dec_and_test(&करोne->cnt))
			wake_up_all(रुकोq);
	पूर्ण
पूर्ण

अटल व्योम wb_queue_work(काष्ठा bdi_ग_लिखोback *wb,
			  काष्ठा wb_ग_लिखोback_work *work)
अणु
	trace_ग_लिखोback_queue(wb, work);

	अगर (work->करोne)
		atomic_inc(&work->करोne->cnt);

	spin_lock_bh(&wb->work_lock);

	अगर (test_bit(WB_रेजिस्टरed, &wb->state)) अणु
		list_add_tail(&work->list, &wb->work_list);
		mod_delayed_work(bdi_wq, &wb->dwork, 0);
	पूर्ण अन्यथा
		finish_ग_लिखोback_work(wb, work);

	spin_unlock_bh(&wb->work_lock);
पूर्ण

/**
 * wb_रुको_क्रम_completion - रुको क्रम completion of bdi_ग_लिखोback_works
 * @करोne: target wb_completion
 *
 * Wait क्रम one or more work items issued to @bdi with their ->करोne field
 * set to @करोne, which should have been initialized with
 * DEFINE_WB_COMPLETION().  This function वापसs after all such work items
 * are completed.  Work items which are रुकोed upon aren't मुक्तd
 * स्वतःmatically on completion.
 */
व्योम wb_रुको_क्रम_completion(काष्ठा wb_completion *करोne)
अणु
	atomic_dec(&करोne->cnt);		/* put करोwn the initial count */
	रुको_event(*करोne->रुकोq, !atomic_पढ़ो(&करोne->cnt));
पूर्ण

#अगर_घोषित CONFIG_CGROUP_WRITEBACK

/*
 * Parameters क्रम क्रमeign inode detection, see wbc_detach_inode() to see
 * how they're used.
 *
 * These paramters are inherently heuristical as the detection target
 * itself is fuzzy.  All we want to करो is detaching an inode from the
 * current owner अगर it's being written to by some other cgroups too much.
 *
 * The current cgroup ग_लिखोback is built on the assumption that multiple
 * cgroups writing to the same inode concurrently is very rare and a mode
 * of operation which isn't well supported.  As such, the goal is not
 * taking too दीर्घ when a dअगरferent cgroup takes over an inode जबतक
 * aव्योमing too aggressive flip-flops from occasional क्रमeign ग_लिखोs.
 *
 * We record, very roughly, 2s worth of IO समय history and अगर more than
 * half of that is क्रमeign, trigger the चयन.  The recording is quantized
 * to 16 slots.  To aव्योम tiny ग_लिखोs from swinging the decision too much,
 * ग_लिखोs smaller than 1/8 of avg size are ignored.
 */
#घोषणा WB_FRN_TIME_SHIFT	13	/* 1s = 2^13, upto 8 secs w/ 16bit */
#घोषणा WB_FRN_TIME_AVG_SHIFT	3	/* avg = avg * 7/8 + new * 1/8 */
#घोषणा WB_FRN_TIME_CUT_DIV	8	/* ignore rounds < avg / 8 */
#घोषणा WB_FRN_TIME_PERIOD	(2 * (1 << WB_FRN_TIME_SHIFT))	/* 2s */

#घोषणा WB_FRN_HIST_SLOTS	16	/* inode->i_wb_frn_history is 16bit */
#घोषणा WB_FRN_HIST_UNIT	(WB_FRN_TIME_PERIOD / WB_FRN_HIST_SLOTS)
					/* each slot's duration is 2s / 16 */
#घोषणा WB_FRN_HIST_THR_SLOTS	(WB_FRN_HIST_SLOTS / 2)
					/* अगर क्रमeign slots >= 8, चयन */
#घोषणा WB_FRN_HIST_MAX_SLOTS	(WB_FRN_HIST_THR_SLOTS / 2 + 1)
					/* one round can affect upto 5 slots */
#घोषणा WB_FRN_MAX_IN_FLIGHT	1024	/* करोn't queue too many concurrently */

अटल atomic_t isw_nr_in_flight = ATOMIC_INIT(0);
अटल काष्ठा workqueue_काष्ठा *isw_wq;

व्योम __inode_attach_wb(काष्ठा inode *inode, काष्ठा page *page)
अणु
	काष्ठा backing_dev_info *bdi = inode_to_bdi(inode);
	काष्ठा bdi_ग_लिखोback *wb = शून्य;

	अगर (inode_cgwb_enabled(inode)) अणु
		काष्ठा cgroup_subsys_state *memcg_css;

		अगर (page) अणु
			memcg_css = mem_cgroup_css_from_page(page);
			wb = wb_get_create(bdi, memcg_css, GFP_ATOMIC);
		पूर्ण अन्यथा अणु
			/* must pin memcg_css, see wb_get_create() */
			memcg_css = task_get_css(current, memory_cgrp_id);
			wb = wb_get_create(bdi, memcg_css, GFP_ATOMIC);
			css_put(memcg_css);
		पूर्ण
	पूर्ण

	अगर (!wb)
		wb = &bdi->wb;

	/*
	 * There may be multiple instances of this function racing to
	 * update the same inode.  Use cmpxchg() to tell the winner.
	 */
	अगर (unlikely(cmpxchg(&inode->i_wb, शून्य, wb)))
		wb_put(wb);
पूर्ण
EXPORT_SYMBOL_GPL(__inode_attach_wb);

/**
 * locked_inode_to_wb_and_lock_list - determine a locked inode's wb and lock it
 * @inode: inode of पूर्णांकerest with i_lock held
 *
 * Returns @inode's wb with its list_lock held.  @inode->i_lock must be
 * held on entry and is released on वापस.  The वापसed wb is guaranteed
 * to stay @inode's associated wb until its list_lock is released.
 */
अटल काष्ठा bdi_ग_लिखोback *
locked_inode_to_wb_and_lock_list(काष्ठा inode *inode)
	__releases(&inode->i_lock)
	__acquires(&wb->list_lock)
अणु
	जबतक (true) अणु
		काष्ठा bdi_ग_लिखोback *wb = inode_to_wb(inode);

		/*
		 * inode_to_wb() association is रक्षित by both
		 * @inode->i_lock and @wb->list_lock but list_lock nests
		 * outside i_lock.  Drop i_lock and verअगरy that the
		 * association hasn't changed after acquiring list_lock.
		 */
		wb_get(wb);
		spin_unlock(&inode->i_lock);
		spin_lock(&wb->list_lock);

		/* i_wb may have changed inbetween, can't use inode_to_wb() */
		अगर (likely(wb == inode->i_wb)) अणु
			wb_put(wb);	/* @inode alपढ़ोy has ref */
			वापस wb;
		पूर्ण

		spin_unlock(&wb->list_lock);
		wb_put(wb);
		cpu_relax();
		spin_lock(&inode->i_lock);
	पूर्ण
पूर्ण

/**
 * inode_to_wb_and_lock_list - determine an inode's wb and lock it
 * @inode: inode of पूर्णांकerest
 *
 * Same as locked_inode_to_wb_and_lock_list() but @inode->i_lock isn't held
 * on entry.
 */
अटल काष्ठा bdi_ग_लिखोback *inode_to_wb_and_lock_list(काष्ठा inode *inode)
	__acquires(&wb->list_lock)
अणु
	spin_lock(&inode->i_lock);
	वापस locked_inode_to_wb_and_lock_list(inode);
पूर्ण

काष्ठा inode_चयन_wbs_context अणु
	काष्ठा inode		*inode;
	काष्ठा bdi_ग_लिखोback	*new_wb;

	काष्ठा rcu_head		rcu_head;
	काष्ठा work_काष्ठा	work;
पूर्ण;

अटल व्योम bdi_करोwn_ग_लिखो_wb_चयन_rwsem(काष्ठा backing_dev_info *bdi)
अणु
	करोwn_ग_लिखो(&bdi->wb_चयन_rwsem);
पूर्ण

अटल व्योम bdi_up_ग_लिखो_wb_चयन_rwsem(काष्ठा backing_dev_info *bdi)
अणु
	up_ग_लिखो(&bdi->wb_चयन_rwsem);
पूर्ण

अटल व्योम inode_चयन_wbs_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा inode_चयन_wbs_context *isw =
		container_of(work, काष्ठा inode_चयन_wbs_context, work);
	काष्ठा inode *inode = isw->inode;
	काष्ठा backing_dev_info *bdi = inode_to_bdi(inode);
	काष्ठा address_space *mapping = inode->i_mapping;
	काष्ठा bdi_ग_लिखोback *old_wb = inode->i_wb;
	काष्ठा bdi_ग_लिखोback *new_wb = isw->new_wb;
	XA_STATE(xas, &mapping->i_pages, 0);
	काष्ठा page *page;
	bool चयनed = false;

	/*
	 * If @inode चयनes cgwb membership जबतक sync_inodes_sb() is
	 * being issued, sync_inodes_sb() might miss it.  Synchronize.
	 */
	करोwn_पढ़ो(&bdi->wb_चयन_rwsem);

	/*
	 * By the समय control reaches here, RCU grace period has passed
	 * since I_WB_SWITCH निश्चितion and all wb stat update transactions
	 * between unlocked_inode_to_wb_begin/end() are guaranteed to be
	 * synchronizing against the i_pages lock.
	 *
	 * Grabbing old_wb->list_lock, inode->i_lock and the i_pages lock
	 * gives us exclusion against all wb related operations on @inode
	 * including IO list manipulations and stat updates.
	 */
	अगर (old_wb < new_wb) अणु
		spin_lock(&old_wb->list_lock);
		spin_lock_nested(&new_wb->list_lock, SINGLE_DEPTH_NESTING);
	पूर्ण अन्यथा अणु
		spin_lock(&new_wb->list_lock);
		spin_lock_nested(&old_wb->list_lock, SINGLE_DEPTH_NESTING);
	पूर्ण
	spin_lock(&inode->i_lock);
	xa_lock_irq(&mapping->i_pages);

	/*
	 * Once I_FREEING is visible under i_lock, the eviction path owns
	 * the inode and we shouldn't modअगरy ->i_io_list.
	 */
	अगर (unlikely(inode->i_state & I_FREEING))
		जाओ skip_चयन;

	trace_inode_चयन_wbs(inode, old_wb, new_wb);

	/*
	 * Count and transfer stats.  Note that PAGECACHE_TAG_सूचीTY poपूर्णांकs
	 * to possibly dirty pages जबतक PAGECACHE_TAG_WRITEBACK poपूर्णांकs to
	 * pages actually under ग_लिखोback.
	 */
	xas_क्रम_each_marked(&xas, page, अच_दीर्घ_उच्च, PAGECACHE_TAG_सूचीTY) अणु
		अगर (PageDirty(page)) अणु
			dec_wb_stat(old_wb, WB_RECLAIMABLE);
			inc_wb_stat(new_wb, WB_RECLAIMABLE);
		पूर्ण
	पूर्ण

	xas_set(&xas, 0);
	xas_क्रम_each_marked(&xas, page, अच_दीर्घ_उच्च, PAGECACHE_TAG_WRITEBACK) अणु
		WARN_ON_ONCE(!PageWriteback(page));
		dec_wb_stat(old_wb, WB_WRITEBACK);
		inc_wb_stat(new_wb, WB_WRITEBACK);
	पूर्ण

	wb_get(new_wb);

	/*
	 * Transfer to @new_wb's IO list अगर necessary.  The specअगरic list
	 * @inode was on is ignored and the inode is put on ->b_dirty which
	 * is always correct including from ->b_dirty_समय.  The transfer
	 * preserves @inode->dirtied_when ordering.
	 */
	अगर (!list_empty(&inode->i_io_list)) अणु
		काष्ठा inode *pos;

		inode_io_list_del_locked(inode, old_wb);
		inode->i_wb = new_wb;
		list_क्रम_each_entry(pos, &new_wb->b_dirty, i_io_list)
			अगर (समय_after_eq(inode->dirtied_when,
					  pos->dirtied_when))
				अवरोध;
		inode_io_list_move_locked(inode, new_wb, pos->i_io_list.prev);
	पूर्ण अन्यथा अणु
		inode->i_wb = new_wb;
	पूर्ण

	/* ->i_wb_frn updates may race wbc_detach_inode() but करोesn't matter */
	inode->i_wb_frn_winner = 0;
	inode->i_wb_frn_avg_समय = 0;
	inode->i_wb_frn_history = 0;
	चयनed = true;
skip_चयन:
	/*
	 * Paired with load_acquire in unlocked_inode_to_wb_begin() and
	 * ensures that the new wb is visible अगर they see !I_WB_SWITCH.
	 */
	smp_store_release(&inode->i_state, inode->i_state & ~I_WB_SWITCH);

	xa_unlock_irq(&mapping->i_pages);
	spin_unlock(&inode->i_lock);
	spin_unlock(&new_wb->list_lock);
	spin_unlock(&old_wb->list_lock);

	up_पढ़ो(&bdi->wb_चयन_rwsem);

	अगर (चयनed) अणु
		wb_wakeup(new_wb);
		wb_put(old_wb);
	पूर्ण
	wb_put(new_wb);

	iput(inode);
	kमुक्त(isw);

	atomic_dec(&isw_nr_in_flight);
पूर्ण

अटल व्योम inode_चयन_wbs_rcu_fn(काष्ठा rcu_head *rcu_head)
अणु
	काष्ठा inode_चयन_wbs_context *isw = container_of(rcu_head,
				काष्ठा inode_चयन_wbs_context, rcu_head);

	/* needs to grab bh-unsafe locks, bounce to work item */
	INIT_WORK(&isw->work, inode_चयन_wbs_work_fn);
	queue_work(isw_wq, &isw->work);
पूर्ण

/**
 * inode_चयन_wbs - change the wb association of an inode
 * @inode: target inode
 * @new_wb_id: ID of the new wb
 *
 * Switch @inode's wb association to the wb identअगरied by @new_wb_id.  The
 * चयनing is perक्रमmed asynchronously and may fail silently.
 */
अटल व्योम inode_चयन_wbs(काष्ठा inode *inode, पूर्णांक new_wb_id)
अणु
	काष्ठा backing_dev_info *bdi = inode_to_bdi(inode);
	काष्ठा cgroup_subsys_state *memcg_css;
	काष्ठा inode_चयन_wbs_context *isw;

	/* noop अगर seems to be alपढ़ोy in progress */
	अगर (inode->i_state & I_WB_SWITCH)
		वापस;

	/* aव्योम queueing a new चयन अगर too many are alपढ़ोy in flight */
	अगर (atomic_पढ़ो(&isw_nr_in_flight) > WB_FRN_MAX_IN_FLIGHT)
		वापस;

	isw = kzalloc(माप(*isw), GFP_ATOMIC);
	अगर (!isw)
		वापस;

	/* find and pin the new wb */
	rcu_पढ़ो_lock();
	memcg_css = css_from_id(new_wb_id, &memory_cgrp_subsys);
	अगर (memcg_css)
		isw->new_wb = wb_get_create(bdi, memcg_css, GFP_ATOMIC);
	rcu_पढ़ो_unlock();
	अगर (!isw->new_wb)
		जाओ out_मुक्त;

	/* जबतक holding I_WB_SWITCH, no one अन्यथा can update the association */
	spin_lock(&inode->i_lock);
	अगर (!(inode->i_sb->s_flags & SB_ACTIVE) ||
	    inode->i_state & (I_WB_SWITCH | I_FREEING) ||
	    inode_to_wb(inode) == isw->new_wb) अणु
		spin_unlock(&inode->i_lock);
		जाओ out_मुक्त;
	पूर्ण
	inode->i_state |= I_WB_SWITCH;
	__iget(inode);
	spin_unlock(&inode->i_lock);

	isw->inode = inode;

	/*
	 * In addition to synchronizing among चयनers, I_WB_SWITCH tells
	 * the RCU रक्षित stat update paths to grab the i_page
	 * lock so that stat transfer can synchronize against them.
	 * Let's जारी after I_WB_SWITCH is guaranteed to be visible.
	 */
	call_rcu(&isw->rcu_head, inode_चयन_wbs_rcu_fn);

	atomic_inc(&isw_nr_in_flight);
	वापस;

out_मुक्त:
	अगर (isw->new_wb)
		wb_put(isw->new_wb);
	kमुक्त(isw);
पूर्ण

/**
 * wbc_attach_and_unlock_inode - associate wbc with target inode and unlock it
 * @wbc: ग_लिखोback_control of पूर्णांकerest
 * @inode: target inode
 *
 * @inode is locked and about to be written back under the control of @wbc.
 * Record @inode's ग_लिखोback context पूर्णांकo @wbc and unlock the i_lock.  On
 * ग_लिखोback completion, wbc_detach_inode() should be called.  This is used
 * to track the cgroup ग_लिखोback context.
 */
व्योम wbc_attach_and_unlock_inode(काष्ठा ग_लिखोback_control *wbc,
				 काष्ठा inode *inode)
अणु
	अगर (!inode_cgwb_enabled(inode)) अणु
		spin_unlock(&inode->i_lock);
		वापस;
	पूर्ण

	wbc->wb = inode_to_wb(inode);
	wbc->inode = inode;

	wbc->wb_id = wbc->wb->memcg_css->id;
	wbc->wb_lcand_id = inode->i_wb_frn_winner;
	wbc->wb_tcand_id = 0;
	wbc->wb_bytes = 0;
	wbc->wb_lcand_bytes = 0;
	wbc->wb_tcand_bytes = 0;

	wb_get(wbc->wb);
	spin_unlock(&inode->i_lock);

	/*
	 * A dying wb indicates that either the blkcg associated with the
	 * memcg changed or the associated memcg is dying.  In the first
	 * हाल, a replacement wb should alपढ़ोy be available and we should
	 * refresh the wb immediately.  In the second हाल, trying to
	 * refresh will keep failing.
	 */
	अगर (unlikely(wb_dying(wbc->wb) && !css_is_dying(wbc->wb->memcg_css)))
		inode_चयन_wbs(inode, wbc->wb_id);
पूर्ण
EXPORT_SYMBOL_GPL(wbc_attach_and_unlock_inode);

/**
 * wbc_detach_inode - disassociate wbc from inode and perक्रमm क्रमeign detection
 * @wbc: ग_लिखोback_control of the just finished ग_लिखोback
 *
 * To be called after a ग_लिखोback attempt of an inode finishes and unकरोes
 * wbc_attach_and_unlock_inode().  Can be called under any context.
 *
 * As concurrent ग_लिखो sharing of an inode is expected to be very rare and
 * memcg only tracks page ownership on first-use basis severely confining
 * the usefulness of such sharing, cgroup ग_लिखोback tracks ownership
 * per-inode.  While the support क्रम concurrent ग_लिखो sharing of an inode
 * is deemed unnecessary, an inode being written to by dअगरferent cgroups at
 * dअगरferent poपूर्णांकs in समय is a lot more common, and, more importantly,
 * अक्षरging only by first-use can too पढ़ोily lead to grossly incorrect
 * behaviors (single क्रमeign page can lead to gigabytes of ग_लिखोback to be
 * incorrectly attributed).
 *
 * To resolve this issue, cgroup ग_लिखोback detects the majority dirtier of
 * an inode and transfers the ownership to it.  To aव्योम unnnecessary
 * oscillation, the detection mechanism keeps track of history and gives
 * out the चयन verdict only अगर the क्रमeign usage pattern is stable over
 * a certain amount of समय and/or ग_लिखोback attempts.
 *
 * On each ग_लिखोback attempt, @wbc tries to detect the majority ग_लिखोr
 * using Boyer-Moore majority vote algorithm.  In addition to the byte
 * count from the majority voting, it also counts the bytes written क्रम the
 * current wb and the last round's winner wb (max of last round's current
 * wb, the winner from two rounds ago, and the last round's majority
 * candidate).  Keeping track of the historical winner helps the algorithm
 * to semi-reliably detect the most active ग_लिखोr even when it's not the
 * असलolute majority.
 *
 * Once the winner of the round is determined, whether the winner is
 * क्रमeign or not and how much IO समय the round consumed is recorded in
 * inode->i_wb_frn_history.  If the amount of recorded क्रमeign IO समय is
 * over a certain threshold, the चयन verdict is given.
 */
व्योम wbc_detach_inode(काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा bdi_ग_लिखोback *wb = wbc->wb;
	काष्ठा inode *inode = wbc->inode;
	अचिन्हित दीर्घ avg_समय, max_bytes, max_समय;
	u16 history;
	पूर्णांक max_id;

	अगर (!wb)
		वापस;

	history = inode->i_wb_frn_history;
	avg_समय = inode->i_wb_frn_avg_समय;

	/* pick the winner of this round */
	अगर (wbc->wb_bytes >= wbc->wb_lcand_bytes &&
	    wbc->wb_bytes >= wbc->wb_tcand_bytes) अणु
		max_id = wbc->wb_id;
		max_bytes = wbc->wb_bytes;
	पूर्ण अन्यथा अगर (wbc->wb_lcand_bytes >= wbc->wb_tcand_bytes) अणु
		max_id = wbc->wb_lcand_id;
		max_bytes = wbc->wb_lcand_bytes;
	पूर्ण अन्यथा अणु
		max_id = wbc->wb_tcand_id;
		max_bytes = wbc->wb_tcand_bytes;
	पूर्ण

	/*
	 * Calculate the amount of IO समय the winner consumed and fold it
	 * पूर्णांकo the running average kept per inode.  If the consumed IO
	 * समय is lower than avag / WB_FRN_TIME_CUT_DIV, ignore it क्रम
	 * deciding whether to चयन or not.  This is to prevent one-off
	 * small dirtiers from skewing the verdict.
	 */
	max_समय = DIV_ROUND_UP((max_bytes >> PAGE_SHIFT) << WB_FRN_TIME_SHIFT,
				wb->avg_ग_लिखो_bandwidth);
	अगर (avg_समय)
		avg_समय += (max_समय >> WB_FRN_TIME_AVG_SHIFT) -
			    (avg_समय >> WB_FRN_TIME_AVG_SHIFT);
	अन्यथा
		avg_समय = max_समय;	/* immediate catch up on first run */

	अगर (max_समय >= avg_समय / WB_FRN_TIME_CUT_DIV) अणु
		पूर्णांक slots;

		/*
		 * The चयन verdict is reached अगर क्रमeign wb's consume
		 * more than a certain proportion of IO समय in a
		 * WB_FRN_TIME_PERIOD.  This is loosely tracked by 16 slot
		 * history mask where each bit represents one sixteenth of
		 * the period.  Determine the number of slots to shअगरt पूर्णांकo
		 * history from @max_समय.
		 */
		slots = min(DIV_ROUND_UP(max_समय, WB_FRN_HIST_UNIT),
			    (अचिन्हित दीर्घ)WB_FRN_HIST_MAX_SLOTS);
		history <<= slots;
		अगर (wbc->wb_id != max_id)
			history |= (1U << slots) - 1;

		अगर (history)
			trace_inode_क्रमeign_history(inode, wbc, history);

		/*
		 * Switch अगर the current wb isn't the consistent winner.
		 * If there are multiple बंदly competing dirtiers, the
		 * inode may चयन across them repeatedly over समय, which
		 * is okay.  The मुख्य goal is aव्योमing keeping an inode on
		 * the wrong wb क्रम an extended period of समय.
		 */
		अगर (hweight32(history) > WB_FRN_HIST_THR_SLOTS)
			inode_चयन_wbs(inode, max_id);
	पूर्ण

	/*
	 * Multiple instances of this function may race to update the
	 * following fields but we करोn't mind occassional inaccuracies.
	 */
	inode->i_wb_frn_winner = max_id;
	inode->i_wb_frn_avg_समय = min(avg_समय, (अचिन्हित दीर्घ)U16_MAX);
	inode->i_wb_frn_history = history;

	wb_put(wbc->wb);
	wbc->wb = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(wbc_detach_inode);

/**
 * wbc_account_cgroup_owner - account ग_लिखोback to update inode cgroup ownership
 * @wbc: ग_लिखोback_control of the ग_लिखोback in progress
 * @page: page being written out
 * @bytes: number of bytes being written out
 *
 * @bytes from @page are about to written out during the ग_लिखोback
 * controlled by @wbc.  Keep the book क्रम क्रमeign inode detection.  See
 * wbc_detach_inode().
 */
व्योम wbc_account_cgroup_owner(काष्ठा ग_लिखोback_control *wbc, काष्ठा page *page,
			      माप_प्रकार bytes)
अणु
	काष्ठा cgroup_subsys_state *css;
	पूर्णांक id;

	/*
	 * pageout() path करोesn't attach @wbc to the inode being written
	 * out.  This is पूर्णांकentional as we करोn't want the function to block
	 * behind a slow cgroup.  Ultimately, we want pageout() to kick off
	 * regular ग_लिखोback instead of writing things out itself.
	 */
	अगर (!wbc->wb || wbc->no_cgroup_owner)
		वापस;

	css = mem_cgroup_css_from_page(page);
	/* dead cgroups shouldn't contribute to inode ownership arbitration */
	अगर (!(css->flags & CSS_ONLINE))
		वापस;

	id = css->id;

	अगर (id == wbc->wb_id) अणु
		wbc->wb_bytes += bytes;
		वापस;
	पूर्ण

	अगर (id == wbc->wb_lcand_id)
		wbc->wb_lcand_bytes += bytes;

	/* Boyer-Moore majority vote algorithm */
	अगर (!wbc->wb_tcand_bytes)
		wbc->wb_tcand_id = id;
	अगर (id == wbc->wb_tcand_id)
		wbc->wb_tcand_bytes += bytes;
	अन्यथा
		wbc->wb_tcand_bytes -= min(bytes, wbc->wb_tcand_bytes);
पूर्ण
EXPORT_SYMBOL_GPL(wbc_account_cgroup_owner);

/**
 * inode_congested - test whether an inode is congested
 * @inode: inode to test क्रम congestion (may be शून्य)
 * @cong_bits: mask of WB_[a]sync_congested bits to test
 *
 * Tests whether @inode is congested.  @cong_bits is the mask of congestion
 * bits to test and the वापस value is the mask of set bits.
 *
 * If cgroup ग_लिखोback is enabled क्रम @inode, the congestion state is
 * determined by whether the cgwb (cgroup bdi_ग_लिखोback) क्रम the blkcg
 * associated with @inode is congested; otherwise, the root wb's congestion
 * state is used.
 *
 * @inode is allowed to be शून्य as this function is often called on
 * mapping->host which is शून्य क्रम the swapper space.
 */
पूर्णांक inode_congested(काष्ठा inode *inode, पूर्णांक cong_bits)
अणु
	/*
	 * Once set, ->i_wb never becomes शून्य जबतक the inode is alive.
	 * Start transaction अगरf ->i_wb is visible.
	 */
	अगर (inode && inode_to_wb_is_valid(inode)) अणु
		काष्ठा bdi_ग_लिखोback *wb;
		काष्ठा wb_lock_cookie lock_cookie = अणुपूर्ण;
		bool congested;

		wb = unlocked_inode_to_wb_begin(inode, &lock_cookie);
		congested = wb_congested(wb, cong_bits);
		unlocked_inode_to_wb_end(inode, &lock_cookie);
		वापस congested;
	पूर्ण

	वापस wb_congested(&inode_to_bdi(inode)->wb, cong_bits);
पूर्ण
EXPORT_SYMBOL_GPL(inode_congested);

/**
 * wb_split_bdi_pages - split nr_pages to ग_लिखो according to bandwidth
 * @wb: target bdi_ग_लिखोback to split @nr_pages to
 * @nr_pages: number of pages to ग_लिखो क्रम the whole bdi
 *
 * Split @wb's portion of @nr_pages according to @wb's ग_लिखो bandwidth in
 * relation to the total ग_लिखो bandwidth of all wb's w/ dirty inodes on
 * @wb->bdi.
 */
अटल दीर्घ wb_split_bdi_pages(काष्ठा bdi_ग_लिखोback *wb, दीर्घ nr_pages)
अणु
	अचिन्हित दीर्घ this_bw = wb->avg_ग_लिखो_bandwidth;
	अचिन्हित दीर्घ tot_bw = atomic_दीर्घ_पढ़ो(&wb->bdi->tot_ग_लिखो_bandwidth);

	अगर (nr_pages == दीर्घ_उच्च)
		वापस दीर्घ_उच्च;

	/*
	 * This may be called on clean wb's and proportional distribution
	 * may not make sense, just use the original @nr_pages in those
	 * हालs.  In general, we wanna err on the side of writing more.
	 */
	अगर (!tot_bw || this_bw >= tot_bw)
		वापस nr_pages;
	अन्यथा
		वापस DIV_ROUND_UP_ULL((u64)nr_pages * this_bw, tot_bw);
पूर्ण

/**
 * bdi_split_work_to_wbs - split a wb_ग_लिखोback_work to all wb's of a bdi
 * @bdi: target backing_dev_info
 * @base_work: wb_ग_लिखोback_work to issue
 * @skip_अगर_busy: skip wb's which alपढ़ोy have ग_लिखोback in progress
 *
 * Split and issue @base_work to all wb's (bdi_writeback's) of @bdi which
 * have dirty inodes.  If @base_work->nr_page isn't %LONG_MAX, it's
 * distributed to the busy wbs according to each wb's proportion in the
 * total active ग_लिखो bandwidth of @bdi.
 */
अटल व्योम bdi_split_work_to_wbs(काष्ठा backing_dev_info *bdi,
				  काष्ठा wb_ग_लिखोback_work *base_work,
				  bool skip_अगर_busy)
अणु
	काष्ठा bdi_ग_लिखोback *last_wb = शून्य;
	काष्ठा bdi_ग_लिखोback *wb = list_entry(&bdi->wb_list,
					      काष्ठा bdi_ग_लिखोback, bdi_node);

	might_sleep();
restart:
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_जारी_rcu(wb, &bdi->wb_list, bdi_node) अणु
		DEFINE_WB_COMPLETION(fallback_work_करोne, bdi);
		काष्ठा wb_ग_लिखोback_work fallback_work;
		काष्ठा wb_ग_लिखोback_work *work;
		दीर्घ nr_pages;

		अगर (last_wb) अणु
			wb_put(last_wb);
			last_wb = शून्य;
		पूर्ण

		/* SYNC_ALL ग_लिखोs out I_सूचीTY_TIME too */
		अगर (!wb_has_dirty_io(wb) &&
		    (base_work->sync_mode == WB_SYNC_NONE ||
		     list_empty(&wb->b_dirty_समय)))
			जारी;
		अगर (skip_अगर_busy && ग_लिखोback_in_progress(wb))
			जारी;

		nr_pages = wb_split_bdi_pages(wb, base_work->nr_pages);

		work = kदो_स्मृति(माप(*work), GFP_ATOMIC);
		अगर (work) अणु
			*work = *base_work;
			work->nr_pages = nr_pages;
			work->स्वतः_मुक्त = 1;
			wb_queue_work(wb, work);
			जारी;
		पूर्ण

		/* alloc failed, execute synchronously using on-stack fallback */
		work = &fallback_work;
		*work = *base_work;
		work->nr_pages = nr_pages;
		work->स्वतः_मुक्त = 0;
		work->करोne = &fallback_work_करोne;

		wb_queue_work(wb, work);

		/*
		 * Pin @wb so that it stays on @bdi->wb_list.  This allows
		 * continuing iteration from @wb after dropping and
		 * regrabbing rcu पढ़ो lock.
		 */
		wb_get(wb);
		last_wb = wb;

		rcu_पढ़ो_unlock();
		wb_रुको_क्रम_completion(&fallback_work_करोne);
		जाओ restart;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (last_wb)
		wb_put(last_wb);
पूर्ण

/**
 * cgroup_ग_लिखोback_by_id - initiate cgroup ग_लिखोback from bdi and memcg IDs
 * @bdi_id: target bdi id
 * @memcg_id: target memcg css id
 * @nr: number of pages to ग_लिखो, 0 क्रम best-efक्रमt dirty flushing
 * @reason: reason why some ग_लिखोback work initiated
 * @करोne: target wb_completion
 *
 * Initiate flush of the bdi_ग_लिखोback identअगरied by @bdi_id and @memcg_id
 * with the specअगरied parameters.
 */
पूर्णांक cgroup_ग_लिखोback_by_id(u64 bdi_id, पूर्णांक memcg_id, अचिन्हित दीर्घ nr,
			   क्रमागत wb_reason reason, काष्ठा wb_completion *करोne)
अणु
	काष्ठा backing_dev_info *bdi;
	काष्ठा cgroup_subsys_state *memcg_css;
	काष्ठा bdi_ग_लिखोback *wb;
	काष्ठा wb_ग_लिखोback_work *work;
	पूर्णांक ret;

	/* lookup bdi and memcg */
	bdi = bdi_get_by_id(bdi_id);
	अगर (!bdi)
		वापस -ENOENT;

	rcu_पढ़ो_lock();
	memcg_css = css_from_id(memcg_id, &memory_cgrp_subsys);
	अगर (memcg_css && !css_tryget(memcg_css))
		memcg_css = शून्य;
	rcu_पढ़ो_unlock();
	अगर (!memcg_css) अणु
		ret = -ENOENT;
		जाओ out_bdi_put;
	पूर्ण

	/*
	 * And find the associated wb.  If the wb isn't there alपढ़ोy
	 * there's nothing to flush, don't create one.
	 */
	wb = wb_get_lookup(bdi, memcg_css);
	अगर (!wb) अणु
		ret = -ENOENT;
		जाओ out_css_put;
	पूर्ण

	/*
	 * If @nr is zero, the caller is attempting to ग_लिखो out most of
	 * the currently dirty pages.  Let's take the current dirty page
	 * count and inflate it by 25% which should be large enough to
	 * flush out most dirty pages जबतक aव्योमing getting livelocked by
	 * concurrent dirtiers.
	 */
	अगर (!nr) अणु
		अचिन्हित दीर्घ filepages, headroom, dirty, ग_लिखोback;

		mem_cgroup_wb_stats(wb, &filepages, &headroom, &dirty,
				      &ग_लिखोback);
		nr = dirty * 10 / 8;
	पूर्ण

	/* issue the ग_लिखोback work */
	work = kzalloc(माप(*work), GFP_NOWAIT | __GFP_NOWARN);
	अगर (work) अणु
		work->nr_pages = nr;
		work->sync_mode = WB_SYNC_NONE;
		work->range_cyclic = 1;
		work->reason = reason;
		work->करोne = करोne;
		work->स्वतः_मुक्त = 1;
		wb_queue_work(wb, work);
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = -ENOMEM;
	पूर्ण

	wb_put(wb);
out_css_put:
	css_put(memcg_css);
out_bdi_put:
	bdi_put(bdi);
	वापस ret;
पूर्ण

/**
 * cgroup_ग_लिखोback_umount - flush inode wb चयनes क्रम umount
 *
 * This function is called when a super_block is about to be destroyed and
 * flushes in-flight inode wb चयनes.  An inode wb चयन goes through
 * RCU and then workqueue, so the two need to be flushed in order to ensure
 * that all previously scheduled चयनes are finished.  As wb चयनes are
 * rare occurrences and synchronize_rcu() can take a जबतक, perक्रमm
 * flushing अगरf wb चयनes are in flight.
 */
व्योम cgroup_ग_लिखोback_umount(व्योम)
अणु
	अगर (atomic_पढ़ो(&isw_nr_in_flight)) अणु
		/*
		 * Use rcu_barrier() to रुको क्रम all pending callbacks to
		 * ensure that all in-flight wb चयनes are in the workqueue.
		 */
		rcu_barrier();
		flush_workqueue(isw_wq);
	पूर्ण
पूर्ण

अटल पूर्णांक __init cgroup_ग_लिखोback_init(व्योम)
अणु
	isw_wq = alloc_workqueue("inode_switch_wbs", 0, 0);
	अगर (!isw_wq)
		वापस -ENOMEM;
	वापस 0;
पूर्ण
fs_initcall(cgroup_ग_लिखोback_init);

#अन्यथा	/* CONFIG_CGROUP_WRITEBACK */

अटल व्योम bdi_करोwn_ग_लिखो_wb_चयन_rwsem(काष्ठा backing_dev_info *bdi) अणु पूर्ण
अटल व्योम bdi_up_ग_लिखो_wb_चयन_rwsem(काष्ठा backing_dev_info *bdi) अणु पूर्ण

अटल काष्ठा bdi_ग_लिखोback *
locked_inode_to_wb_and_lock_list(काष्ठा inode *inode)
	__releases(&inode->i_lock)
	__acquires(&wb->list_lock)
अणु
	काष्ठा bdi_ग_लिखोback *wb = inode_to_wb(inode);

	spin_unlock(&inode->i_lock);
	spin_lock(&wb->list_lock);
	वापस wb;
पूर्ण

अटल काष्ठा bdi_ग_लिखोback *inode_to_wb_and_lock_list(काष्ठा inode *inode)
	__acquires(&wb->list_lock)
अणु
	काष्ठा bdi_ग_लिखोback *wb = inode_to_wb(inode);

	spin_lock(&wb->list_lock);
	वापस wb;
पूर्ण

अटल दीर्घ wb_split_bdi_pages(काष्ठा bdi_ग_लिखोback *wb, दीर्घ nr_pages)
अणु
	वापस nr_pages;
पूर्ण

अटल व्योम bdi_split_work_to_wbs(काष्ठा backing_dev_info *bdi,
				  काष्ठा wb_ग_लिखोback_work *base_work,
				  bool skip_अगर_busy)
अणु
	might_sleep();

	अगर (!skip_अगर_busy || !ग_लिखोback_in_progress(&bdi->wb)) अणु
		base_work->स्वतः_मुक्त = 0;
		wb_queue_work(&bdi->wb, base_work);
	पूर्ण
पूर्ण

#पूर्ण_अगर	/* CONFIG_CGROUP_WRITEBACK */

/*
 * Add in the number of potentially dirty inodes, because each inode
 * ग_लिखो can dirty pagecache in the underlying blockdev.
 */
अटल अचिन्हित दीर्घ get_nr_dirty_pages(व्योम)
अणु
	वापस global_node_page_state(NR_खाता_सूचीTY) +
		get_nr_dirty_inodes();
पूर्ण

अटल व्योम wb_start_ग_लिखोback(काष्ठा bdi_ग_लिखोback *wb, क्रमागत wb_reason reason)
अणु
	अगर (!wb_has_dirty_io(wb))
		वापस;

	/*
	 * All callers of this function want to start ग_लिखोback of all
	 * dirty pages. Places like vmscan can call this at a very
	 * high frequency, causing poपूर्णांकless allocations of tons of
	 * work items and keeping the flusher thपढ़ोs busy retrieving
	 * that work. Ensure that we only allow one of them pending and
	 * inflight at the समय.
	 */
	अगर (test_bit(WB_start_all, &wb->state) ||
	    test_and_set_bit(WB_start_all, &wb->state))
		वापस;

	wb->start_all_reason = reason;
	wb_wakeup(wb);
पूर्ण

/**
 * wb_start_background_ग_लिखोback - start background ग_लिखोback
 * @wb: bdi_writback to ग_लिखो from
 *
 * Description:
 *   This makes sure WB_SYNC_NONE background ग_लिखोback happens. When
 *   this function वापसs, it is only guaranteed that क्रम given wb
 *   some IO is happening अगर we are over background dirty threshold.
 *   Caller need not hold sb s_umount semaphore.
 */
व्योम wb_start_background_ग_लिखोback(काष्ठा bdi_ग_लिखोback *wb)
अणु
	/*
	 * We just wake up the flusher thपढ़ो. It will perक्रमm background
	 * ग_लिखोback as soon as there is no other work to करो.
	 */
	trace_ग_लिखोback_wake_background(wb);
	wb_wakeup(wb);
पूर्ण

/*
 * Remove the inode from the ग_लिखोback list it is on.
 */
व्योम inode_io_list_del(काष्ठा inode *inode)
अणु
	काष्ठा bdi_ग_लिखोback *wb;

	wb = inode_to_wb_and_lock_list(inode);
	spin_lock(&inode->i_lock);
	inode_io_list_del_locked(inode, wb);
	spin_unlock(&inode->i_lock);
	spin_unlock(&wb->list_lock);
पूर्ण
EXPORT_SYMBOL(inode_io_list_del);

/*
 * mark an inode as under ग_लिखोback on the sb
 */
व्योम sb_mark_inode_ग_लिखोback(काष्ठा inode *inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	अचिन्हित दीर्घ flags;

	अगर (list_empty(&inode->i_wb_list)) अणु
		spin_lock_irqsave(&sb->s_inode_wblist_lock, flags);
		अगर (list_empty(&inode->i_wb_list)) अणु
			list_add_tail(&inode->i_wb_list, &sb->s_inodes_wb);
			trace_sb_mark_inode_ग_लिखोback(inode);
		पूर्ण
		spin_unlock_irqrestore(&sb->s_inode_wblist_lock, flags);
	पूर्ण
पूर्ण

/*
 * clear an inode as under ग_लिखोback on the sb
 */
व्योम sb_clear_inode_ग_लिखोback(काष्ठा inode *inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	अचिन्हित दीर्घ flags;

	अगर (!list_empty(&inode->i_wb_list)) अणु
		spin_lock_irqsave(&sb->s_inode_wblist_lock, flags);
		अगर (!list_empty(&inode->i_wb_list)) अणु
			list_del_init(&inode->i_wb_list);
			trace_sb_clear_inode_ग_लिखोback(inode);
		पूर्ण
		spin_unlock_irqrestore(&sb->s_inode_wblist_lock, flags);
	पूर्ण
पूर्ण

/*
 * Redirty an inode: set its when-it-was dirtied बारtamp and move it to the
 * furthest end of its superblock's dirty-inode list.
 *
 * Beक्रमe stamping the inode's ->dirtied_when, we check to see whether it is
 * alपढ़ोy the most-recently-dirtied inode on the b_dirty list.  If that is
 * the हाल then the inode must have been redirtied जबतक it was being written
 * out and we करोn't reset its dirtied_when.
 */
अटल व्योम redirty_tail_locked(काष्ठा inode *inode, काष्ठा bdi_ग_लिखोback *wb)
अणु
	निश्चित_spin_locked(&inode->i_lock);

	अगर (!list_empty(&wb->b_dirty)) अणु
		काष्ठा inode *tail;

		tail = wb_inode(wb->b_dirty.next);
		अगर (समय_beक्रमe(inode->dirtied_when, tail->dirtied_when))
			inode->dirtied_when = jअगरfies;
	पूर्ण
	inode_io_list_move_locked(inode, wb, &wb->b_dirty);
	inode->i_state &= ~I_SYNC_QUEUED;
पूर्ण

अटल व्योम redirty_tail(काष्ठा inode *inode, काष्ठा bdi_ग_लिखोback *wb)
अणु
	spin_lock(&inode->i_lock);
	redirty_tail_locked(inode, wb);
	spin_unlock(&inode->i_lock);
पूर्ण

/*
 * requeue inode क्रम re-scanning after bdi->b_io list is exhausted.
 */
अटल व्योम requeue_io(काष्ठा inode *inode, काष्ठा bdi_ग_लिखोback *wb)
अणु
	inode_io_list_move_locked(inode, wb, &wb->b_more_io);
पूर्ण

अटल व्योम inode_sync_complete(काष्ठा inode *inode)
अणु
	inode->i_state &= ~I_SYNC;
	/* If inode is clean an unused, put it पूर्णांकo LRU now... */
	inode_add_lru(inode);
	/* Waiters must see I_SYNC cleared beक्रमe being woken up */
	smp_mb();
	wake_up_bit(&inode->i_state, __I_SYNC);
पूर्ण

अटल bool inode_dirtied_after(काष्ठा inode *inode, अचिन्हित दीर्घ t)
अणु
	bool ret = समय_after(inode->dirtied_when, t);
#अगर_अघोषित CONFIG_64BIT
	/*
	 * For inodes being स्थिरantly redirtied, dirtied_when can get stuck.
	 * It _appears_ to be in the future, but is actually in distant past.
	 * This test is necessary to prevent such wrapped-around relative बार
	 * from permanently stopping the whole bdi ग_लिखोback.
	 */
	ret = ret && समय_beक्रमe_eq(inode->dirtied_when, jअगरfies);
#पूर्ण_अगर
	वापस ret;
पूर्ण

#घोषणा EXPIRE_सूचीTY_ATIME 0x0001

/*
 * Move expired (dirtied beक्रमe dirtied_beक्रमe) dirty inodes from
 * @delaying_queue to @dispatch_queue.
 */
अटल पूर्णांक move_expired_inodes(काष्ठा list_head *delaying_queue,
			       काष्ठा list_head *dispatch_queue,
			       अचिन्हित दीर्घ dirtied_beक्रमe)
अणु
	LIST_HEAD(पंचांगp);
	काष्ठा list_head *pos, *node;
	काष्ठा super_block *sb = शून्य;
	काष्ठा inode *inode;
	पूर्णांक करो_sb_sort = 0;
	पूर्णांक moved = 0;

	जबतक (!list_empty(delaying_queue)) अणु
		inode = wb_inode(delaying_queue->prev);
		अगर (inode_dirtied_after(inode, dirtied_beक्रमe))
			अवरोध;
		list_move(&inode->i_io_list, &पंचांगp);
		moved++;
		spin_lock(&inode->i_lock);
		inode->i_state |= I_SYNC_QUEUED;
		spin_unlock(&inode->i_lock);
		अगर (sb_is_blkdev_sb(inode->i_sb))
			जारी;
		अगर (sb && sb != inode->i_sb)
			करो_sb_sort = 1;
		sb = inode->i_sb;
	पूर्ण

	/* just one sb in list, splice to dispatch_queue and we're करोne */
	अगर (!करो_sb_sort) अणु
		list_splice(&पंचांगp, dispatch_queue);
		जाओ out;
	पूर्ण

	/* Move inodes from one superblock together */
	जबतक (!list_empty(&पंचांगp)) अणु
		sb = wb_inode(पंचांगp.prev)->i_sb;
		list_क्रम_each_prev_safe(pos, node, &पंचांगp) अणु
			inode = wb_inode(pos);
			अगर (inode->i_sb == sb)
				list_move(&inode->i_io_list, dispatch_queue);
		पूर्ण
	पूर्ण
out:
	वापस moved;
पूर्ण

/*
 * Queue all expired dirty inodes क्रम io, eldest first.
 * Beक्रमe
 *         newly dirtied     b_dirty    b_io    b_more_io
 *         =============>    gf         edc     BA
 * After
 *         newly dirtied     b_dirty    b_io    b_more_io
 *         =============>    g          fBAedc
 *                                           |
 *                                           +--> dequeue क्रम IO
 */
अटल व्योम queue_io(काष्ठा bdi_ग_लिखोback *wb, काष्ठा wb_ग_लिखोback_work *work,
		     अचिन्हित दीर्घ dirtied_beक्रमe)
अणु
	पूर्णांक moved;
	अचिन्हित दीर्घ समय_expire_jअगर = dirtied_beक्रमe;

	निश्चित_spin_locked(&wb->list_lock);
	list_splice_init(&wb->b_more_io, &wb->b_io);
	moved = move_expired_inodes(&wb->b_dirty, &wb->b_io, dirtied_beक्रमe);
	अगर (!work->क्रम_sync)
		समय_expire_jअगर = jअगरfies - dirtyसमय_expire_पूर्णांकerval * HZ;
	moved += move_expired_inodes(&wb->b_dirty_समय, &wb->b_io,
				     समय_expire_jअगर);
	अगर (moved)
		wb_io_lists_populated(wb);
	trace_ग_लिखोback_queue_io(wb, work, dirtied_beक्रमe, moved);
पूर्ण

अटल पूर्णांक ग_लिखो_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc)
अणु
	पूर्णांक ret;

	अगर (inode->i_sb->s_op->ग_लिखो_inode && !is_bad_inode(inode)) अणु
		trace_ग_लिखोback_ग_लिखो_inode_start(inode, wbc);
		ret = inode->i_sb->s_op->ग_लिखो_inode(inode, wbc);
		trace_ग_लिखोback_ग_लिखो_inode(inode, wbc);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Wait क्रम ग_लिखोback on an inode to complete. Called with i_lock held.
 * Caller must make sure inode cannot go away when we drop i_lock.
 */
अटल व्योम __inode_रुको_क्रम_ग_लिखोback(काष्ठा inode *inode)
	__releases(inode->i_lock)
	__acquires(inode->i_lock)
अणु
	DEFINE_WAIT_BIT(wq, &inode->i_state, __I_SYNC);
	रुको_queue_head_t *wqh;

	wqh = bit_रुकोqueue(&inode->i_state, __I_SYNC);
	जबतक (inode->i_state & I_SYNC) अणु
		spin_unlock(&inode->i_lock);
		__रुको_on_bit(wqh, &wq, bit_रुको,
			      TASK_UNINTERRUPTIBLE);
		spin_lock(&inode->i_lock);
	पूर्ण
पूर्ण

/*
 * Wait क्रम ग_लिखोback on an inode to complete. Caller must have inode pinned.
 */
व्योम inode_रुको_क्रम_ग_लिखोback(काष्ठा inode *inode)
अणु
	spin_lock(&inode->i_lock);
	__inode_रुको_क्रम_ग_लिखोback(inode);
	spin_unlock(&inode->i_lock);
पूर्ण

/*
 * Sleep until I_SYNC is cleared. This function must be called with i_lock
 * held and drops it. It is aimed क्रम callers not holding any inode reference
 * so once i_lock is dropped, inode can go away.
 */
अटल व्योम inode_sleep_on_ग_लिखोback(काष्ठा inode *inode)
	__releases(inode->i_lock)
अणु
	DEFINE_WAIT(रुको);
	रुको_queue_head_t *wqh = bit_रुकोqueue(&inode->i_state, __I_SYNC);
	पूर्णांक sleep;

	prepare_to_रुको(wqh, &रुको, TASK_UNINTERRUPTIBLE);
	sleep = inode->i_state & I_SYNC;
	spin_unlock(&inode->i_lock);
	अगर (sleep)
		schedule();
	finish_रुको(wqh, &रुको);
पूर्ण

/*
 * Find proper ग_लिखोback list क्रम the inode depending on its current state and
 * possibly also change of its state जबतक we were करोing ग_लिखोback.  Here we
 * handle things such as livelock prevention or fairness of ग_लिखोback among
 * inodes. This function can be called only by flusher thपढ़ो - noone अन्यथा
 * processes all inodes in ग_लिखोback lists and requeueing inodes behind flusher
 * thपढ़ो's back can have unexpected consequences.
 */
अटल व्योम requeue_inode(काष्ठा inode *inode, काष्ठा bdi_ग_लिखोback *wb,
			  काष्ठा ग_लिखोback_control *wbc)
अणु
	अगर (inode->i_state & I_FREEING)
		वापस;

	/*
	 * Sync livelock prevention. Each inode is tagged and synced in one
	 * shot. If still dirty, it will be redirty_tail()'ed below.  Update
	 * the dirty समय to prevent enqueue and sync it again.
	 */
	अगर ((inode->i_state & I_सूचीTY) &&
	    (wbc->sync_mode == WB_SYNC_ALL || wbc->tagged_ग_लिखोpages))
		inode->dirtied_when = jअगरfies;

	अगर (wbc->pages_skipped) अणु
		/*
		 * ग_लिखोback is not making progress due to locked
		 * buffers. Skip this inode क्रम now.
		 */
		redirty_tail_locked(inode, wb);
		वापस;
	पूर्ण

	अगर (mapping_tagged(inode->i_mapping, PAGECACHE_TAG_सूचीTY)) अणु
		/*
		 * We didn't ग_लिखो back all the pages.  nfs_ग_लिखोpages()
		 * someबार bales out without करोing anything.
		 */
		अगर (wbc->nr_to_ग_लिखो <= 0) अणु
			/* Slice used up. Queue क्रम next turn. */
			requeue_io(inode, wb);
		पूर्ण अन्यथा अणु
			/*
			 * Writeback blocked by something other than
			 * congestion. Delay the inode क्रम some समय to
			 * aव्योम spinning on the CPU (100% ioरुको)
			 * retrying ग_लिखोback of the dirty page/inode
			 * that cannot be perक्रमmed immediately.
			 */
			redirty_tail_locked(inode, wb);
		पूर्ण
	पूर्ण अन्यथा अगर (inode->i_state & I_सूचीTY) अणु
		/*
		 * Fileप्रणालीs can dirty the inode during ग_लिखोback operations,
		 * such as delayed allocation during submission or metadata
		 * updates after data IO completion.
		 */
		redirty_tail_locked(inode, wb);
	पूर्ण अन्यथा अगर (inode->i_state & I_सूचीTY_TIME) अणु
		inode->dirtied_when = jअगरfies;
		inode_io_list_move_locked(inode, wb, &wb->b_dirty_समय);
		inode->i_state &= ~I_SYNC_QUEUED;
	पूर्ण अन्यथा अणु
		/* The inode is clean. Remove from ग_लिखोback lists. */
		inode_io_list_del_locked(inode, wb);
	पूर्ण
पूर्ण

/*
 * Write out an inode and its dirty pages (or some of its dirty pages, depending
 * on @wbc->nr_to_ग_लिखो), and clear the relevant dirty flags from i_state.
 *
 * This करोesn't हटाओ the inode from the ग_लिखोback list it is on, except
 * potentially to move it from b_dirty_समय to b_dirty due to बारtamp
 * expiration.  The caller is otherwise responsible क्रम ग_लिखोback list handling.
 *
 * The caller is also responsible क्रम setting the I_SYNC flag beक्रमehand and
 * calling inode_sync_complete() to clear it afterwards.
 */
अटल पूर्णांक
__ग_लिखोback_single_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा address_space *mapping = inode->i_mapping;
	दीर्घ nr_to_ग_लिखो = wbc->nr_to_ग_लिखो;
	अचिन्हित dirty;
	पूर्णांक ret;

	WARN_ON(!(inode->i_state & I_SYNC));

	trace_ग_लिखोback_single_inode_start(inode, wbc, nr_to_ग_लिखो);

	ret = करो_ग_लिखोpages(mapping, wbc);

	/*
	 * Make sure to रुको on the data beक्रमe writing out the metadata.
	 * This is important क्रम fileप्रणालीs that modअगरy metadata on data
	 * I/O completion. We करोn't करो it क्रम sync(2) ग_लिखोback because it has a
	 * separate, बाह्यal IO completion path and ->sync_fs क्रम guaranteeing
	 * inode metadata is written back correctly.
	 */
	अगर (wbc->sync_mode == WB_SYNC_ALL && !wbc->क्रम_sync) अणु
		पूर्णांक err = filemap_fdataरुको(mapping);
		अगर (ret == 0)
			ret = err;
	पूर्ण

	/*
	 * If the inode has dirty बारtamps and we need to ग_लिखो them, call
	 * mark_inode_dirty_sync() to notअगरy the fileप्रणाली about it and to
	 * change I_सूचीTY_TIME पूर्णांकo I_सूचीTY_SYNC.
	 */
	अगर ((inode->i_state & I_सूचीTY_TIME) &&
	    (wbc->sync_mode == WB_SYNC_ALL ||
	     समय_after(jअगरfies, inode->dirtied_समय_when +
			dirtyसमय_expire_पूर्णांकerval * HZ))) अणु
		trace_ग_लिखोback_lazyसमय(inode);
		mark_inode_dirty_sync(inode);
	पूर्ण

	/*
	 * Get and clear the dirty flags from i_state.  This needs to be करोne
	 * after calling ग_लिखोpages because some fileप्रणालीs may redirty the
	 * inode during ग_लिखोpages due to delalloc.  It also needs to be करोne
	 * after handling बारtamp expiration, as that may dirty the inode too.
	 */
	spin_lock(&inode->i_lock);
	dirty = inode->i_state & I_सूचीTY;
	inode->i_state &= ~dirty;

	/*
	 * Paired with smp_mb() in __mark_inode_dirty().  This allows
	 * __mark_inode_dirty() to test i_state without grabbing i_lock -
	 * either they see the I_सूचीTY bits cleared or we see the dirtied
	 * inode.
	 *
	 * I_सूचीTY_PAGES is always cleared together above even अगर @mapping
	 * still has dirty pages.  The flag is reinstated after smp_mb() अगर
	 * necessary.  This guarantees that either __mark_inode_dirty()
	 * sees clear I_सूचीTY_PAGES or we see PAGECACHE_TAG_सूचीTY.
	 */
	smp_mb();

	अगर (mapping_tagged(mapping, PAGECACHE_TAG_सूचीTY))
		inode->i_state |= I_सूचीTY_PAGES;

	spin_unlock(&inode->i_lock);

	/* Don't ग_लिखो the inode अगर only I_सूचीTY_PAGES was set */
	अगर (dirty & ~I_सूचीTY_PAGES) अणु
		पूर्णांक err = ग_लिखो_inode(inode, wbc);
		अगर (ret == 0)
			ret = err;
	पूर्ण
	trace_ग_लिखोback_single_inode(inode, wbc, nr_to_ग_लिखो);
	वापस ret;
पूर्ण

/*
 * Write out an inode's dirty data and metadata on-demand, i.e. separately from
 * the regular batched ग_लिखोback करोne by the flusher thपढ़ोs in
 * ग_लिखोback_sb_inodes().  @wbc controls various aspects of the ग_लिखो, such as
 * whether it is a data-पूर्णांकegrity sync (%WB_SYNC_ALL) or not (%WB_SYNC_NONE).
 *
 * To prevent the inode from going away, either the caller must have a reference
 * to the inode, or the inode must have I_WILL_FREE or I_FREEING set.
 */
अटल पूर्णांक ग_लिखोback_single_inode(काष्ठा inode *inode,
				  काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा bdi_ग_लिखोback *wb;
	पूर्णांक ret = 0;

	spin_lock(&inode->i_lock);
	अगर (!atomic_पढ़ो(&inode->i_count))
		WARN_ON(!(inode->i_state & (I_WILL_FREE|I_FREEING)));
	अन्यथा
		WARN_ON(inode->i_state & I_WILL_FREE);

	अगर (inode->i_state & I_SYNC) अणु
		/*
		 * Writeback is alपढ़ोy running on the inode.  For WB_SYNC_NONE,
		 * that's enough and we can just वापस.  For WB_SYNC_ALL, we
		 * must रुको क्रम the existing ग_लिखोback to complete, then करो
		 * ग_लिखोback again अगर there's anything left.
		 */
		अगर (wbc->sync_mode != WB_SYNC_ALL)
			जाओ out;
		__inode_रुको_क्रम_ग_लिखोback(inode);
	पूर्ण
	WARN_ON(inode->i_state & I_SYNC);
	/*
	 * If the inode is alपढ़ोy fully clean, then there's nothing to करो.
	 *
	 * For data-पूर्णांकegrity syncs we also need to check whether any pages are
	 * still under ग_लिखोback, e.g. due to prior WB_SYNC_NONE ग_लिखोback.  If
	 * there are any such pages, we'll need to रुको क्रम them.
	 */
	अगर (!(inode->i_state & I_सूचीTY_ALL) &&
	    (wbc->sync_mode != WB_SYNC_ALL ||
	     !mapping_tagged(inode->i_mapping, PAGECACHE_TAG_WRITEBACK)))
		जाओ out;
	inode->i_state |= I_SYNC;
	wbc_attach_and_unlock_inode(wbc, inode);

	ret = __ग_लिखोback_single_inode(inode, wbc);

	wbc_detach_inode(wbc);

	wb = inode_to_wb_and_lock_list(inode);
	spin_lock(&inode->i_lock);
	/*
	 * If the inode is now fully clean, then it can be safely हटाओd from
	 * its ग_लिखोback list (अगर any).  Otherwise the flusher thपढ़ोs are
	 * responsible क्रम the ग_लिखोback lists.
	 */
	अगर (!(inode->i_state & I_सूचीTY_ALL))
		inode_io_list_del_locked(inode, wb);
	spin_unlock(&wb->list_lock);
	inode_sync_complete(inode);
out:
	spin_unlock(&inode->i_lock);
	वापस ret;
पूर्ण

अटल दीर्घ ग_लिखोback_chunk_size(काष्ठा bdi_ग_लिखोback *wb,
				 काष्ठा wb_ग_लिखोback_work *work)
अणु
	दीर्घ pages;

	/*
	 * WB_SYNC_ALL mode करोes livelock aव्योमance by syncing dirty
	 * inodes/pages in one big loop. Setting wbc.nr_to_ग_लिखो=दीर्घ_उच्च
	 * here aव्योमs calling पूर्णांकo ग_लिखोback_inodes_wb() more than once.
	 *
	 * The पूर्णांकended call sequence क्रम WB_SYNC_ALL ग_लिखोback is:
	 *
	 *      wb_ग_लिखोback()
	 *          ग_लिखोback_sb_inodes()       <== called only once
	 *              ग_लिखो_cache_pages()     <== called once क्रम each inode
	 *                   (quickly) tag currently dirty pages
	 *                   (maybe slowly) sync all tagged pages
	 */
	अगर (work->sync_mode == WB_SYNC_ALL || work->tagged_ग_लिखोpages)
		pages = दीर्घ_उच्च;
	अन्यथा अणु
		pages = min(wb->avg_ग_लिखो_bandwidth / 2,
			    global_wb_करोमुख्य.dirty_limit / सूचीTY_SCOPE);
		pages = min(pages, work->nr_pages);
		pages = round_करोwn(pages + MIN_WRITEBACK_PAGES,
				   MIN_WRITEBACK_PAGES);
	पूर्ण

	वापस pages;
पूर्ण

/*
 * Write a portion of b_io inodes which beदीर्घ to @sb.
 *
 * Return the number of pages and/or inodes written.
 *
 * NOTE! This is called with wb->list_lock held, and will
 * unlock and relock that क्रम each inode it ends up करोing
 * IO क्रम.
 */
अटल दीर्घ ग_लिखोback_sb_inodes(काष्ठा super_block *sb,
				काष्ठा bdi_ग_लिखोback *wb,
				काष्ठा wb_ग_लिखोback_work *work)
अणु
	काष्ठा ग_लिखोback_control wbc = अणु
		.sync_mode		= work->sync_mode,
		.tagged_ग_लिखोpages	= work->tagged_ग_लिखोpages,
		.क्रम_kupdate		= work->क्रम_kupdate,
		.क्रम_background		= work->क्रम_background,
		.क्रम_sync		= work->क्रम_sync,
		.range_cyclic		= work->range_cyclic,
		.range_start		= 0,
		.range_end		= Lदीर्घ_उच्च,
	पूर्ण;
	अचिन्हित दीर्घ start_समय = jअगरfies;
	दीर्घ ग_लिखो_chunk;
	दीर्घ wrote = 0;  /* count both pages and inodes */

	जबतक (!list_empty(&wb->b_io)) अणु
		काष्ठा inode *inode = wb_inode(wb->b_io.prev);
		काष्ठा bdi_ग_लिखोback *पंचांगp_wb;

		अगर (inode->i_sb != sb) अणु
			अगर (work->sb) अणु
				/*
				 * We only want to ग_लिखो back data क्रम this
				 * superblock, move all inodes not beदीर्घing
				 * to it back onto the dirty list.
				 */
				redirty_tail(inode, wb);
				जारी;
			पूर्ण

			/*
			 * The inode beदीर्घs to a dअगरferent superblock.
			 * Bounce back to the caller to unpin this and
			 * pin the next superblock.
			 */
			अवरोध;
		पूर्ण

		/*
		 * Don't bother with new inodes or inodes being मुक्तd, first
		 * kind करोes not need periodic ग_लिखोout yet, and क्रम the latter
		 * kind ग_लिखोout is handled by the मुक्तr.
		 */
		spin_lock(&inode->i_lock);
		अगर (inode->i_state & (I_NEW | I_FREEING | I_WILL_FREE)) अणु
			redirty_tail_locked(inode, wb);
			spin_unlock(&inode->i_lock);
			जारी;
		पूर्ण
		अगर ((inode->i_state & I_SYNC) && wbc.sync_mode != WB_SYNC_ALL) अणु
			/*
			 * If this inode is locked क्रम ग_लिखोback and we are not
			 * करोing ग_लिखोback-क्रम-data-पूर्णांकegrity, move it to
			 * b_more_io so that ग_लिखोback can proceed with the
			 * other inodes on s_io.
			 *
			 * We'll have another go at writing back this inode
			 * when we completed a full scan of b_io.
			 */
			spin_unlock(&inode->i_lock);
			requeue_io(inode, wb);
			trace_ग_लिखोback_sb_inodes_requeue(inode);
			जारी;
		पूर्ण
		spin_unlock(&wb->list_lock);

		/*
		 * We alपढ़ोy requeued the inode अगर it had I_SYNC set and we
		 * are करोing WB_SYNC_NONE ग_लिखोback. So this catches only the
		 * WB_SYNC_ALL हाल.
		 */
		अगर (inode->i_state & I_SYNC) अणु
			/* Wait क्रम I_SYNC. This function drops i_lock... */
			inode_sleep_on_ग_लिखोback(inode);
			/* Inode may be gone, start again */
			spin_lock(&wb->list_lock);
			जारी;
		पूर्ण
		inode->i_state |= I_SYNC;
		wbc_attach_and_unlock_inode(&wbc, inode);

		ग_लिखो_chunk = ग_लिखोback_chunk_size(wb, work);
		wbc.nr_to_ग_लिखो = ग_लिखो_chunk;
		wbc.pages_skipped = 0;

		/*
		 * We use I_SYNC to pin the inode in memory. While it is set
		 * evict_inode() will रुको so the inode cannot be मुक्तd.
		 */
		__ग_लिखोback_single_inode(inode, &wbc);

		wbc_detach_inode(&wbc);
		work->nr_pages -= ग_लिखो_chunk - wbc.nr_to_ग_लिखो;
		wrote += ग_लिखो_chunk - wbc.nr_to_ग_लिखो;

		अगर (need_resched()) अणु
			/*
			 * We're trying to balance between building up a nice
			 * दीर्घ list of IOs to improve our merge rate, and
			 * getting those IOs out quickly क्रम anyone throttling
			 * in balance_dirty_pages().  cond_resched() करोesn't
			 * unplug, so get our IOs out the करोor beक्रमe we
			 * give up the CPU.
			 */
			blk_flush_plug(current);
			cond_resched();
		पूर्ण

		/*
		 * Requeue @inode अगर still dirty.  Be careful as @inode may
		 * have been चयनed to another wb in the meanसमय.
		 */
		पंचांगp_wb = inode_to_wb_and_lock_list(inode);
		spin_lock(&inode->i_lock);
		अगर (!(inode->i_state & I_सूचीTY_ALL))
			wrote++;
		requeue_inode(inode, पंचांगp_wb, &wbc);
		inode_sync_complete(inode);
		spin_unlock(&inode->i_lock);

		अगर (unlikely(पंचांगp_wb != wb)) अणु
			spin_unlock(&पंचांगp_wb->list_lock);
			spin_lock(&wb->list_lock);
		पूर्ण

		/*
		 * bail out to wb_ग_लिखोback() often enough to check
		 * background threshold and other termination conditions.
		 */
		अगर (wrote) अणु
			अगर (समय_is_beक्रमe_jअगरfies(start_समय + HZ / 10UL))
				अवरोध;
			अगर (work->nr_pages <= 0)
				अवरोध;
		पूर्ण
	पूर्ण
	वापस wrote;
पूर्ण

अटल दीर्घ __ग_लिखोback_inodes_wb(काष्ठा bdi_ग_लिखोback *wb,
				  काष्ठा wb_ग_लिखोback_work *work)
अणु
	अचिन्हित दीर्घ start_समय = jअगरfies;
	दीर्घ wrote = 0;

	जबतक (!list_empty(&wb->b_io)) अणु
		काष्ठा inode *inode = wb_inode(wb->b_io.prev);
		काष्ठा super_block *sb = inode->i_sb;

		अगर (!trylock_super(sb)) अणु
			/*
			 * trylock_super() may fail consistently due to
			 * s_umount being grabbed by someone अन्यथा. Don't use
			 * requeue_io() to aव्योम busy retrying the inode/sb.
			 */
			redirty_tail(inode, wb);
			जारी;
		पूर्ण
		wrote += ग_लिखोback_sb_inodes(sb, wb, work);
		up_पढ़ो(&sb->s_umount);

		/* refer to the same tests at the end of ग_लिखोback_sb_inodes */
		अगर (wrote) अणु
			अगर (समय_is_beक्रमe_jअगरfies(start_समय + HZ / 10UL))
				अवरोध;
			अगर (work->nr_pages <= 0)
				अवरोध;
		पूर्ण
	पूर्ण
	/* Leave any unwritten inodes on b_io */
	वापस wrote;
पूर्ण

अटल दीर्घ ग_लिखोback_inodes_wb(काष्ठा bdi_ग_लिखोback *wb, दीर्घ nr_pages,
				क्रमागत wb_reason reason)
अणु
	काष्ठा wb_ग_लिखोback_work work = अणु
		.nr_pages	= nr_pages,
		.sync_mode	= WB_SYNC_NONE,
		.range_cyclic	= 1,
		.reason		= reason,
	पूर्ण;
	काष्ठा blk_plug plug;

	blk_start_plug(&plug);
	spin_lock(&wb->list_lock);
	अगर (list_empty(&wb->b_io))
		queue_io(wb, &work, jअगरfies);
	__ग_लिखोback_inodes_wb(wb, &work);
	spin_unlock(&wb->list_lock);
	blk_finish_plug(&plug);

	वापस nr_pages - work.nr_pages;
पूर्ण

/*
 * Explicit flushing or periodic ग_लिखोback of "old" data.
 *
 * Define "old": the first समय one of an inode's pages is dirtied, we mark the
 * dirtying-समय in the inode's address_space.  So this periodic ग_लिखोback code
 * just walks the superblock inode list, writing back any inodes which are
 * older than a specअगरic poपूर्णांक in समय.
 *
 * Try to run once per dirty_ग_लिखोback_पूर्णांकerval.  But अगर a ग_लिखोback event
 * takes दीर्घer than a dirty_ग_लिखोback_पूर्णांकerval पूर्णांकerval, then leave a
 * one-second gap.
 *
 * dirtied_beक्रमe takes precedence over nr_to_ग_लिखो.  So we'll only ग_लिखो back
 * all dirty pages अगर they are all attached to "old" mappings.
 */
अटल दीर्घ wb_ग_लिखोback(काष्ठा bdi_ग_लिखोback *wb,
			 काष्ठा wb_ग_लिखोback_work *work)
अणु
	अचिन्हित दीर्घ wb_start = jअगरfies;
	दीर्घ nr_pages = work->nr_pages;
	अचिन्हित दीर्घ dirtied_beक्रमe = jअगरfies;
	काष्ठा inode *inode;
	दीर्घ progress;
	काष्ठा blk_plug plug;

	blk_start_plug(&plug);
	spin_lock(&wb->list_lock);
	क्रम (;;) अणु
		/*
		 * Stop ग_लिखोback when nr_pages has been consumed
		 */
		अगर (work->nr_pages <= 0)
			अवरोध;

		/*
		 * Background ग_लिखोout and kupdate-style ग_लिखोback may
		 * run क्रमever. Stop them अगर there is other work to करो
		 * so that e.g. sync can proceed. They'll be restarted
		 * after the other works are all करोne.
		 */
		अगर ((work->क्रम_background || work->क्रम_kupdate) &&
		    !list_empty(&wb->work_list))
			अवरोध;

		/*
		 * For background ग_लिखोout, stop when we are below the
		 * background dirty threshold
		 */
		अगर (work->क्रम_background && !wb_over_bg_thresh(wb))
			अवरोध;

		/*
		 * Kupdate and background works are special and we want to
		 * include all inodes that need writing. Livelock aव्योमance is
		 * handled by these works yielding to any other work so we are
		 * safe.
		 */
		अगर (work->क्रम_kupdate) अणु
			dirtied_beक्रमe = jअगरfies -
				msecs_to_jअगरfies(dirty_expire_पूर्णांकerval * 10);
		पूर्ण अन्यथा अगर (work->क्रम_background)
			dirtied_beक्रमe = jअगरfies;

		trace_ग_लिखोback_start(wb, work);
		अगर (list_empty(&wb->b_io))
			queue_io(wb, work, dirtied_beक्रमe);
		अगर (work->sb)
			progress = ग_लिखोback_sb_inodes(work->sb, wb, work);
		अन्यथा
			progress = __ग_लिखोback_inodes_wb(wb, work);
		trace_ग_लिखोback_written(wb, work);

		wb_update_bandwidth(wb, wb_start);

		/*
		 * Did we ग_लिखो something? Try क्रम more
		 *
		 * Dirty inodes are moved to b_io क्रम ग_लिखोback in batches.
		 * The completion of the current batch करोes not necessarily
		 * mean the overall work is करोne. So we keep looping as दीर्घ
		 * as made some progress on cleaning pages or inodes.
		 */
		अगर (progress)
			जारी;
		/*
		 * No more inodes क्रम IO, bail
		 */
		अगर (list_empty(&wb->b_more_io))
			अवरोध;
		/*
		 * Nothing written. Wait क्रम some inode to
		 * become available क्रम ग_लिखोback. Otherwise
		 * we'll just busyloop.
		 */
		trace_ग_लिखोback_रुको(wb, work);
		inode = wb_inode(wb->b_more_io.prev);
		spin_lock(&inode->i_lock);
		spin_unlock(&wb->list_lock);
		/* This function drops i_lock... */
		inode_sleep_on_ग_लिखोback(inode);
		spin_lock(&wb->list_lock);
	पूर्ण
	spin_unlock(&wb->list_lock);
	blk_finish_plug(&plug);

	वापस nr_pages - work->nr_pages;
पूर्ण

/*
 * Return the next wb_ग_लिखोback_work काष्ठा that hasn't been processed yet.
 */
अटल काष्ठा wb_ग_लिखोback_work *get_next_work_item(काष्ठा bdi_ग_लिखोback *wb)
अणु
	काष्ठा wb_ग_लिखोback_work *work = शून्य;

	spin_lock_bh(&wb->work_lock);
	अगर (!list_empty(&wb->work_list)) अणु
		work = list_entry(wb->work_list.next,
				  काष्ठा wb_ग_लिखोback_work, list);
		list_del_init(&work->list);
	पूर्ण
	spin_unlock_bh(&wb->work_lock);
	वापस work;
पूर्ण

अटल दीर्घ wb_check_background_flush(काष्ठा bdi_ग_लिखोback *wb)
अणु
	अगर (wb_over_bg_thresh(wb)) अणु

		काष्ठा wb_ग_लिखोback_work work = अणु
			.nr_pages	= दीर्घ_उच्च,
			.sync_mode	= WB_SYNC_NONE,
			.क्रम_background	= 1,
			.range_cyclic	= 1,
			.reason		= WB_REASON_BACKGROUND,
		पूर्ण;

		वापस wb_ग_लिखोback(wb, &work);
	पूर्ण

	वापस 0;
पूर्ण

अटल दीर्घ wb_check_old_data_flush(काष्ठा bdi_ग_लिखोback *wb)
अणु
	अचिन्हित दीर्घ expired;
	दीर्घ nr_pages;

	/*
	 * When set to zero, disable periodic ग_लिखोback
	 */
	अगर (!dirty_ग_लिखोback_पूर्णांकerval)
		वापस 0;

	expired = wb->last_old_flush +
			msecs_to_jअगरfies(dirty_ग_लिखोback_पूर्णांकerval * 10);
	अगर (समय_beक्रमe(jअगरfies, expired))
		वापस 0;

	wb->last_old_flush = jअगरfies;
	nr_pages = get_nr_dirty_pages();

	अगर (nr_pages) अणु
		काष्ठा wb_ग_लिखोback_work work = अणु
			.nr_pages	= nr_pages,
			.sync_mode	= WB_SYNC_NONE,
			.क्रम_kupdate	= 1,
			.range_cyclic	= 1,
			.reason		= WB_REASON_PERIODIC,
		पूर्ण;

		वापस wb_ग_लिखोback(wb, &work);
	पूर्ण

	वापस 0;
पूर्ण

अटल दीर्घ wb_check_start_all(काष्ठा bdi_ग_लिखोback *wb)
अणु
	दीर्घ nr_pages;

	अगर (!test_bit(WB_start_all, &wb->state))
		वापस 0;

	nr_pages = get_nr_dirty_pages();
	अगर (nr_pages) अणु
		काष्ठा wb_ग_लिखोback_work work = अणु
			.nr_pages	= wb_split_bdi_pages(wb, nr_pages),
			.sync_mode	= WB_SYNC_NONE,
			.range_cyclic	= 1,
			.reason		= wb->start_all_reason,
		पूर्ण;

		nr_pages = wb_ग_लिखोback(wb, &work);
	पूर्ण

	clear_bit(WB_start_all, &wb->state);
	वापस nr_pages;
पूर्ण


/*
 * Retrieve work items and करो the ग_लिखोback they describe
 */
अटल दीर्घ wb_करो_ग_लिखोback(काष्ठा bdi_ग_लिखोback *wb)
अणु
	काष्ठा wb_ग_लिखोback_work *work;
	दीर्घ wrote = 0;

	set_bit(WB_ग_लिखोback_running, &wb->state);
	जबतक ((work = get_next_work_item(wb)) != शून्य) अणु
		trace_ग_लिखोback_exec(wb, work);
		wrote += wb_ग_लिखोback(wb, work);
		finish_ग_लिखोback_work(wb, work);
	पूर्ण

	/*
	 * Check क्रम a flush-everything request
	 */
	wrote += wb_check_start_all(wb);

	/*
	 * Check क्रम periodic ग_लिखोback, kupdated() style
	 */
	wrote += wb_check_old_data_flush(wb);
	wrote += wb_check_background_flush(wb);
	clear_bit(WB_ग_लिखोback_running, &wb->state);

	वापस wrote;
पूर्ण

/*
 * Handle ग_लिखोback of dirty data क्रम the device backed by this bdi. Also
 * reschedules periodically and करोes kupdated style flushing.
 */
व्योम wb_workfn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bdi_ग_लिखोback *wb = container_of(to_delayed_work(work),
						काष्ठा bdi_ग_लिखोback, dwork);
	दीर्घ pages_written;

	set_worker_desc("flush-%s", bdi_dev_name(wb->bdi));
	current->flags |= PF_SWAPWRITE;

	अगर (likely(!current_is_workqueue_rescuer() ||
		   !test_bit(WB_रेजिस्टरed, &wb->state))) अणु
		/*
		 * The normal path.  Keep writing back @wb until its
		 * work_list is empty.  Note that this path is also taken
		 * अगर @wb is shutting करोwn even when we're running off the
		 * rescuer as work_list needs to be drained.
		 */
		करो अणु
			pages_written = wb_करो_ग_लिखोback(wb);
			trace_ग_लिखोback_pages_written(pages_written);
		पूर्ण जबतक (!list_empty(&wb->work_list));
	पूर्ण अन्यथा अणु
		/*
		 * bdi_wq can't get enough workers and we're running off
		 * the emergency worker.  Don't hog it.  Hopefully, 1024 is
		 * enough क्रम efficient IO.
		 */
		pages_written = ग_लिखोback_inodes_wb(wb, 1024,
						    WB_REASON_FORKER_THREAD);
		trace_ग_लिखोback_pages_written(pages_written);
	पूर्ण

	अगर (!list_empty(&wb->work_list))
		wb_wakeup(wb);
	अन्यथा अगर (wb_has_dirty_io(wb) && dirty_ग_लिखोback_पूर्णांकerval)
		wb_wakeup_delayed(wb);

	current->flags &= ~PF_SWAPWRITE;
पूर्ण

/*
 * Start ग_लिखोback of `nr_pages' pages on this bdi. If `nr_pages' is zero,
 * ग_लिखो back the whole world.
 */
अटल व्योम __wakeup_flusher_thपढ़ोs_bdi(काष्ठा backing_dev_info *bdi,
					 क्रमागत wb_reason reason)
अणु
	काष्ठा bdi_ग_लिखोback *wb;

	अगर (!bdi_has_dirty_io(bdi))
		वापस;

	list_क्रम_each_entry_rcu(wb, &bdi->wb_list, bdi_node)
		wb_start_ग_लिखोback(wb, reason);
पूर्ण

व्योम wakeup_flusher_thपढ़ोs_bdi(काष्ठा backing_dev_info *bdi,
				क्रमागत wb_reason reason)
अणु
	rcu_पढ़ो_lock();
	__wakeup_flusher_thपढ़ोs_bdi(bdi, reason);
	rcu_पढ़ो_unlock();
पूर्ण

/*
 * Wakeup the flusher thपढ़ोs to start ग_लिखोback of all currently dirty pages
 */
व्योम wakeup_flusher_thपढ़ोs(क्रमागत wb_reason reason)
अणु
	काष्ठा backing_dev_info *bdi;

	/*
	 * If we are expecting ग_लिखोback progress we must submit plugged IO.
	 */
	अगर (blk_needs_flush_plug(current))
		blk_schedule_flush_plug(current);

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(bdi, &bdi_list, bdi_list)
		__wakeup_flusher_thपढ़ोs_bdi(bdi, reason);
	rcu_पढ़ो_unlock();
पूर्ण

/*
 * Wake up bdi's periodically to make sure dirtyसमय inodes माला_लो
 * written back periodically.  We deliberately करो *not* check the
 * b_dirtyसमय list in wb_has_dirty_io(), since this would cause the
 * kernel to be स्थिरantly waking up once there are any dirtyसमय
 * inodes on the प्रणाली.  So instead we define a separate delayed work
 * function which माला_लो called much more rarely.  (By शेष, only
 * once every 12 hours.)
 *
 * If there is any other ग_लिखो activity going on in the file प्रणाली,
 * this function won't be necessary.  But अगर the only thing that has
 * happened on the file प्रणाली is a dirtyसमय inode caused by an aसमय
 * update, we need this infraकाष्ठाure below to make sure that inode
 * eventually माला_लो pushed out to disk.
 */
अटल व्योम wakeup_dirtyसमय_ग_लिखोback(काष्ठा work_काष्ठा *w);
अटल DECLARE_DELAYED_WORK(dirtyसमय_work, wakeup_dirtyसमय_ग_लिखोback);

अटल व्योम wakeup_dirtyसमय_ग_लिखोback(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा backing_dev_info *bdi;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(bdi, &bdi_list, bdi_list) अणु
		काष्ठा bdi_ग_लिखोback *wb;

		list_क्रम_each_entry_rcu(wb, &bdi->wb_list, bdi_node)
			अगर (!list_empty(&wb->b_dirty_समय))
				wb_wakeup(wb);
	पूर्ण
	rcu_पढ़ो_unlock();
	schedule_delayed_work(&dirtyसमय_work, dirtyसमय_expire_पूर्णांकerval * HZ);
पूर्ण

अटल पूर्णांक __init start_dirtyसमय_ग_लिखोback(व्योम)
अणु
	schedule_delayed_work(&dirtyसमय_work, dirtyसमय_expire_पूर्णांकerval * HZ);
	वापस 0;
पूर्ण
__initcall(start_dirtyसमय_ग_लिखोback);

पूर्णांक dirtyसमय_पूर्णांकerval_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			       व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक ret;

	ret = proc_करोपूर्णांकvec_minmax(table, ग_लिखो, buffer, lenp, ppos);
	अगर (ret == 0 && ग_लिखो)
		mod_delayed_work(प्रणाली_wq, &dirtyसमय_work, 0);
	वापस ret;
पूर्ण

अटल noअंतरभूत व्योम block_dump___mark_inode_dirty(काष्ठा inode *inode)
अणु
	अगर (inode->i_ino || म_भेद(inode->i_sb->s_id, "bdev")) अणु
		काष्ठा dentry *dentry;
		स्थिर अक्षर *name = "?";

		dentry = d_find_alias(inode);
		अगर (dentry) अणु
			spin_lock(&dentry->d_lock);
			name = (स्थिर अक्षर *) dentry->d_name.name;
		पूर्ण
		prपूर्णांकk(KERN_DEBUG
		       "%s(%d): dirtied inode %lu (%s) on %s\n",
		       current->comm, task_pid_nr(current), inode->i_ino,
		       name, inode->i_sb->s_id);
		अगर (dentry) अणु
			spin_unlock(&dentry->d_lock);
			dput(dentry);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * __mark_inode_dirty -	पूर्णांकernal function to mark an inode dirty
 *
 * @inode: inode to mark
 * @flags: what kind of dirty, e.g. I_सूचीTY_SYNC.  This can be a combination of
 *	   multiple I_सूचीTY_* flags, except that I_सूचीTY_TIME can't be combined
 *	   with I_सूचीTY_PAGES.
 *
 * Mark an inode as dirty.  We notअगरy the fileप्रणाली, then update the inode's
 * dirty flags.  Then, अगर needed we add the inode to the appropriate dirty list.
 *
 * Most callers should use mark_inode_dirty() or mark_inode_dirty_sync()
 * instead of calling this directly.
 *
 * CAREFUL!  We only add the inode to the dirty list अगर it is hashed or अगर it
 * refers to a blockdev.  Unhashed inodes will never be added to the dirty list
 * even अगर they are later hashed, as they will have been marked dirty alपढ़ोy.
 *
 * In लघु, ensure you hash any inodes _beक्रमe_ you start marking them dirty.
 *
 * Note that क्रम blockdevs, inode->dirtied_when represents the dirtying समय of
 * the block-special inode (/dev/hda1) itself.  And the ->dirtied_when field of
 * the kernel-पूर्णांकernal blockdev inode represents the dirtying समय of the
 * blockdev's pages.  This is why क्रम I_सूचीTY_PAGES we always use
 * page->mapping->host, so the page-dirtying समय is recorded in the पूर्णांकernal
 * blockdev inode.
 */
व्योम __mark_inode_dirty(काष्ठा inode *inode, पूर्णांक flags)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	पूर्णांक dirtyसमय = 0;

	trace_ग_लिखोback_mark_inode_dirty(inode, flags);

	अगर (flags & I_सूचीTY_INODE) अणु
		/*
		 * Notअगरy the fileप्रणाली about the inode being dirtied, so that
		 * (अगर needed) it can update on-disk fields and journal the
		 * inode.  This is only needed when the inode itself is being
		 * dirtied now.  I.e. it's only needed क्रम I_सूचीTY_INODE, not
		 * क्रम just I_सूचीTY_PAGES or I_सूचीTY_TIME.
		 */
		trace_ग_लिखोback_dirty_inode_start(inode, flags);
		अगर (sb->s_op->dirty_inode)
			sb->s_op->dirty_inode(inode, flags & I_सूचीTY_INODE);
		trace_ग_लिखोback_dirty_inode(inode, flags);

		/* I_सूचीTY_INODE supersedes I_सूचीTY_TIME. */
		flags &= ~I_सूचीTY_TIME;
	पूर्ण अन्यथा अणु
		/*
		 * Else it's either I_सूचीTY_PAGES, I_सूचीTY_TIME, or nothing.
		 * (We करोn't support setting both I_सूचीTY_PAGES and I_सूचीTY_TIME
		 * in one call to __mark_inode_dirty().)
		 */
		dirtyसमय = flags & I_सूचीTY_TIME;
		WARN_ON_ONCE(dirtyसमय && flags != I_सूचीTY_TIME);
	पूर्ण

	/*
	 * Paired with smp_mb() in __ग_लिखोback_single_inode() क्रम the
	 * following lockless i_state test.  See there क्रम details.
	 */
	smp_mb();

	अगर (((inode->i_state & flags) == flags) ||
	    (dirtyसमय && (inode->i_state & I_सूचीTY_INODE)))
		वापस;

	अगर (unlikely(block_dump))
		block_dump___mark_inode_dirty(inode);

	spin_lock(&inode->i_lock);
	अगर (dirtyसमय && (inode->i_state & I_सूचीTY_INODE))
		जाओ out_unlock_inode;
	अगर ((inode->i_state & flags) != flags) अणु
		स्थिर पूर्णांक was_dirty = inode->i_state & I_सूचीTY;

		inode_attach_wb(inode, शून्य);

		/* I_सूचीTY_INODE supersedes I_सूचीTY_TIME. */
		अगर (flags & I_सूचीTY_INODE)
			inode->i_state &= ~I_सूचीTY_TIME;
		inode->i_state |= flags;

		/*
		 * If the inode is queued क्रम ग_लिखोback by flush worker, just
		 * update its dirty state. Once the flush worker is करोne with
		 * the inode it will place it on the appropriate superblock
		 * list, based upon its state.
		 */
		अगर (inode->i_state & I_SYNC_QUEUED)
			जाओ out_unlock_inode;

		/*
		 * Only add valid (hashed) inodes to the superblock's
		 * dirty list.  Add blockdev inodes as well.
		 */
		अगर (!S_ISBLK(inode->i_mode)) अणु
			अगर (inode_unhashed(inode))
				जाओ out_unlock_inode;
		पूर्ण
		अगर (inode->i_state & I_FREEING)
			जाओ out_unlock_inode;

		/*
		 * If the inode was alपढ़ोy on b_dirty/b_io/b_more_io, करोn't
		 * reposition it (that would अवरोध b_dirty समय-ordering).
		 */
		अगर (!was_dirty) अणु
			काष्ठा bdi_ग_लिखोback *wb;
			काष्ठा list_head *dirty_list;
			bool wakeup_bdi = false;

			wb = locked_inode_to_wb_and_lock_list(inode);

			inode->dirtied_when = jअगरfies;
			अगर (dirtyसमय)
				inode->dirtied_समय_when = jअगरfies;

			अगर (inode->i_state & I_सूचीTY)
				dirty_list = &wb->b_dirty;
			अन्यथा
				dirty_list = &wb->b_dirty_समय;

			wakeup_bdi = inode_io_list_move_locked(inode, wb,
							       dirty_list);

			spin_unlock(&wb->list_lock);
			trace_ग_लिखोback_dirty_inode_enqueue(inode);

			/*
			 * If this is the first dirty inode क्रम this bdi,
			 * we have to wake-up the corresponding bdi thपढ़ो
			 * to make sure background ग_लिखो-back happens
			 * later.
			 */
			अगर (wakeup_bdi &&
			    (wb->bdi->capabilities & BDI_CAP_WRITEBACK))
				wb_wakeup_delayed(wb);
			वापस;
		पूर्ण
	पूर्ण
out_unlock_inode:
	spin_unlock(&inode->i_lock);
पूर्ण
EXPORT_SYMBOL(__mark_inode_dirty);

/*
 * The @s_sync_lock is used to serialise concurrent sync operations
 * to aव्योम lock contention problems with concurrent रुको_sb_inodes() calls.
 * Concurrent callers will block on the s_sync_lock rather than करोing contending
 * walks. The queueing मुख्यtains sync(2) required behaviour as all the IO that
 * has been issued up to the समय this function is enter is guaranteed to be
 * completed by the समय we have gained the lock and रुकोed क्रम all IO that is
 * in progress regardless of the order callers are granted the lock.
 */
अटल व्योम रुको_sb_inodes(काष्ठा super_block *sb)
अणु
	LIST_HEAD(sync_list);

	/*
	 * We need to be रक्षित against the fileप्रणाली going from
	 * r/o to r/w or vice versa.
	 */
	WARN_ON(!rwsem_is_locked(&sb->s_umount));

	mutex_lock(&sb->s_sync_lock);

	/*
	 * Splice the ग_लिखोback list onto a temporary list to aव्योम रुकोing on
	 * inodes that have started ग_लिखोback after this poपूर्णांक.
	 *
	 * Use rcu_पढ़ो_lock() to keep the inodes around until we have a
	 * reference. s_inode_wblist_lock protects sb->s_inodes_wb as well as
	 * the local list because inodes can be dropped from either by ग_लिखोback
	 * completion.
	 */
	rcu_पढ़ो_lock();
	spin_lock_irq(&sb->s_inode_wblist_lock);
	list_splice_init(&sb->s_inodes_wb, &sync_list);

	/*
	 * Data पूर्णांकegrity sync. Must रुको क्रम all pages under ग_लिखोback, because
	 * there may have been pages dirtied beक्रमe our sync call, but which had
	 * ग_लिखोout started beक्रमe we ग_लिखो it out.  In which हाल, the inode
	 * may not be on the dirty list, but we still have to रुको क्रम that
	 * ग_लिखोout.
	 */
	जबतक (!list_empty(&sync_list)) अणु
		काष्ठा inode *inode = list_first_entry(&sync_list, काष्ठा inode,
						       i_wb_list);
		काष्ठा address_space *mapping = inode->i_mapping;

		/*
		 * Move each inode back to the wb list beक्रमe we drop the lock
		 * to preserve consistency between i_wb_list and the mapping
		 * ग_लिखोback tag. Writeback completion is responsible to हटाओ
		 * the inode from either list once the ग_लिखोback tag is cleared.
		 */
		list_move_tail(&inode->i_wb_list, &sb->s_inodes_wb);

		/*
		 * The mapping can appear untagged जबतक still on-list since we
		 * करो not have the mapping lock. Skip it here, wb completion
		 * will हटाओ it.
		 */
		अगर (!mapping_tagged(mapping, PAGECACHE_TAG_WRITEBACK))
			जारी;

		spin_unlock_irq(&sb->s_inode_wblist_lock);

		spin_lock(&inode->i_lock);
		अगर (inode->i_state & (I_FREEING|I_WILL_FREE|I_NEW)) अणु
			spin_unlock(&inode->i_lock);

			spin_lock_irq(&sb->s_inode_wblist_lock);
			जारी;
		पूर्ण
		__iget(inode);
		spin_unlock(&inode->i_lock);
		rcu_पढ़ो_unlock();

		/*
		 * We keep the error status of inभागidual mapping so that
		 * applications can catch the ग_लिखोback error using fsync(2).
		 * See filemap_fdataरुको_keep_errors() क्रम details.
		 */
		filemap_fdataरुको_keep_errors(mapping);

		cond_resched();

		iput(inode);

		rcu_पढ़ो_lock();
		spin_lock_irq(&sb->s_inode_wblist_lock);
	पूर्ण
	spin_unlock_irq(&sb->s_inode_wblist_lock);
	rcu_पढ़ो_unlock();
	mutex_unlock(&sb->s_sync_lock);
पूर्ण

अटल व्योम __ग_लिखोback_inodes_sb_nr(काष्ठा super_block *sb, अचिन्हित दीर्घ nr,
				     क्रमागत wb_reason reason, bool skip_अगर_busy)
अणु
	काष्ठा backing_dev_info *bdi = sb->s_bdi;
	DEFINE_WB_COMPLETION(करोne, bdi);
	काष्ठा wb_ग_लिखोback_work work = अणु
		.sb			= sb,
		.sync_mode		= WB_SYNC_NONE,
		.tagged_ग_लिखोpages	= 1,
		.करोne			= &करोne,
		.nr_pages		= nr,
		.reason			= reason,
	पूर्ण;

	अगर (!bdi_has_dirty_io(bdi) || bdi == &noop_backing_dev_info)
		वापस;
	WARN_ON(!rwsem_is_locked(&sb->s_umount));

	bdi_split_work_to_wbs(sb->s_bdi, &work, skip_अगर_busy);
	wb_रुको_क्रम_completion(&करोne);
पूर्ण

/**
 * ग_लिखोback_inodes_sb_nr -	ग_लिखोback dirty inodes from given super_block
 * @sb: the superblock
 * @nr: the number of pages to ग_लिखो
 * @reason: reason why some ग_लिखोback work initiated
 *
 * Start ग_लिखोback on some inodes on this super_block. No guarantees are made
 * on how many (अगर any) will be written, and this function करोes not रुको
 * क्रम IO completion of submitted IO.
 */
व्योम ग_लिखोback_inodes_sb_nr(काष्ठा super_block *sb,
			    अचिन्हित दीर्घ nr,
			    क्रमागत wb_reason reason)
अणु
	__ग_लिखोback_inodes_sb_nr(sb, nr, reason, false);
पूर्ण
EXPORT_SYMBOL(ग_लिखोback_inodes_sb_nr);

/**
 * ग_लिखोback_inodes_sb	-	ग_लिखोback dirty inodes from given super_block
 * @sb: the superblock
 * @reason: reason why some ग_लिखोback work was initiated
 *
 * Start ग_लिखोback on some inodes on this super_block. No guarantees are made
 * on how many (अगर any) will be written, and this function करोes not रुको
 * क्रम IO completion of submitted IO.
 */
व्योम ग_लिखोback_inodes_sb(काष्ठा super_block *sb, क्रमागत wb_reason reason)
अणु
	वापस ग_लिखोback_inodes_sb_nr(sb, get_nr_dirty_pages(), reason);
पूर्ण
EXPORT_SYMBOL(ग_लिखोback_inodes_sb);

/**
 * try_to_ग_लिखोback_inodes_sb - try to start ग_लिखोback अगर none underway
 * @sb: the superblock
 * @reason: reason why some ग_लिखोback work was initiated
 *
 * Invoke __ग_लिखोback_inodes_sb_nr अगर no ग_लिखोback is currently underway.
 */
व्योम try_to_ग_लिखोback_inodes_sb(काष्ठा super_block *sb, क्रमागत wb_reason reason)
अणु
	अगर (!करोwn_पढ़ो_trylock(&sb->s_umount))
		वापस;

	__ग_लिखोback_inodes_sb_nr(sb, get_nr_dirty_pages(), reason, true);
	up_पढ़ो(&sb->s_umount);
पूर्ण
EXPORT_SYMBOL(try_to_ग_लिखोback_inodes_sb);

/**
 * sync_inodes_sb	-	sync sb inode pages
 * @sb: the superblock
 *
 * This function ग_लिखोs and रुकोs on any dirty inode beदीर्घing to this
 * super_block.
 */
व्योम sync_inodes_sb(काष्ठा super_block *sb)
अणु
	काष्ठा backing_dev_info *bdi = sb->s_bdi;
	DEFINE_WB_COMPLETION(करोne, bdi);
	काष्ठा wb_ग_लिखोback_work work = अणु
		.sb		= sb,
		.sync_mode	= WB_SYNC_ALL,
		.nr_pages	= दीर्घ_उच्च,
		.range_cyclic	= 0,
		.करोne		= &करोne,
		.reason		= WB_REASON_SYNC,
		.क्रम_sync	= 1,
	पूर्ण;

	/*
	 * Can't skip on !bdi_has_dirty() because we should रुको क्रम !dirty
	 * inodes under ग_लिखोback and I_सूचीTY_TIME inodes ignored by
	 * bdi_has_dirty() need to be written out too.
	 */
	अगर (bdi == &noop_backing_dev_info)
		वापस;
	WARN_ON(!rwsem_is_locked(&sb->s_umount));

	/* protect against inode wb चयन, see inode_चयन_wbs_work_fn() */
	bdi_करोwn_ग_लिखो_wb_चयन_rwsem(bdi);
	bdi_split_work_to_wbs(bdi, &work, false);
	wb_रुको_क्रम_completion(&करोne);
	bdi_up_ग_लिखो_wb_चयन_rwsem(bdi);

	रुको_sb_inodes(sb);
पूर्ण
EXPORT_SYMBOL(sync_inodes_sb);

/**
 * ग_लिखो_inode_now	-	ग_लिखो an inode to disk
 * @inode: inode to ग_लिखो to disk
 * @sync: whether the ग_लिखो should be synchronous or not
 *
 * This function commits an inode to disk immediately अगर it is dirty. This is
 * primarily needed by knfsd.
 *
 * The caller must either have a ref on the inode or must have set I_WILL_FREE.
 */
पूर्णांक ग_लिखो_inode_now(काष्ठा inode *inode, पूर्णांक sync)
अणु
	काष्ठा ग_लिखोback_control wbc = अणु
		.nr_to_ग_लिखो = दीर्घ_उच्च,
		.sync_mode = sync ? WB_SYNC_ALL : WB_SYNC_NONE,
		.range_start = 0,
		.range_end = Lदीर्घ_उच्च,
	पूर्ण;

	अगर (!mapping_can_ग_लिखोback(inode->i_mapping))
		wbc.nr_to_ग_लिखो = 0;

	might_sleep();
	वापस ग_लिखोback_single_inode(inode, &wbc);
पूर्ण
EXPORT_SYMBOL(ग_लिखो_inode_now);

/**
 * sync_inode - ग_लिखो an inode and its pages to disk.
 * @inode: the inode to sync
 * @wbc: controls the ग_लिखोback mode
 *
 * sync_inode() will ग_लिखो an inode and its pages to disk.  It will also
 * correctly update the inode on its superblock's dirty inode lists and will
 * update inode->i_state.
 *
 * The caller must have a ref on the inode.
 */
पूर्णांक sync_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस ग_लिखोback_single_inode(inode, wbc);
पूर्ण
EXPORT_SYMBOL(sync_inode);

/**
 * sync_inode_metadata - ग_लिखो an inode to disk
 * @inode: the inode to sync
 * @रुको: रुको क्रम I/O to complete.
 *
 * Write an inode to disk and adjust its dirty state after completion.
 *
 * Note: only ग_लिखोs the actual inode, no associated data or other metadata.
 */
पूर्णांक sync_inode_metadata(काष्ठा inode *inode, पूर्णांक रुको)
अणु
	काष्ठा ग_लिखोback_control wbc = अणु
		.sync_mode = रुको ? WB_SYNC_ALL : WB_SYNC_NONE,
		.nr_to_ग_लिखो = 0, /* metadata-only */
	पूर्ण;

	वापस sync_inode(inode, &wbc);
पूर्ण
EXPORT_SYMBOL(sync_inode_metadata);
