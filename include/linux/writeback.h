<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/linux/ग_लिखोback.h
 */
#अगर_अघोषित WRITEBACK_H
#घोषणा WRITEBACK_H

#समावेश <linux/sched.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/fs.h>
#समावेश <linux/flex_proportions.h>
#समावेश <linux/backing-dev-defs.h>
#समावेश <linux/blk_types.h>
#समावेश <linux/blk-cgroup.h>

काष्ठा bio;

DECLARE_PER_CPU(पूर्णांक, dirty_throttle_leaks);

/*
 * The 1/4 region under the global dirty thresh is क्रम smooth dirty throttling:
 *
 *	(thresh - thresh/सूचीTY_FULL_SCOPE, thresh)
 *
 * Further beyond, all dirtier tasks will enter a loop रुकोing (possibly दीर्घ
 * समय) क्रम the dirty pages to drop, unless written enough pages.
 *
 * The global dirty threshold is normally equal to the global dirty limit,
 * except when the प्रणाली suddenly allocates a lot of anonymous memory and
 * knocks करोwn the global dirty threshold quickly, in which हाल the global
 * dirty limit will follow करोwn slowly to prevent livelocking all dirtier tasks.
 */
#घोषणा सूचीTY_SCOPE		8
#घोषणा सूचीTY_FULL_SCOPE	(सूचीTY_SCOPE / 2)

काष्ठा backing_dev_info;

/*
 * fs/fs-ग_लिखोback.c
 */
क्रमागत ग_लिखोback_sync_modes अणु
	WB_SYNC_NONE,	/* Don't रुको on anything */
	WB_SYNC_ALL,	/* Wait on every mapping */
पूर्ण;

/*
 * A control काष्ठाure which tells the ग_लिखोback code what to करो.  These are
 * always on the stack, and hence need no locking.  They are always initialised
 * in a manner such that unspecअगरied fields are set to zero.
 */
काष्ठा ग_लिखोback_control अणु
	दीर्घ nr_to_ग_लिखो;		/* Write this many pages, and decrement
					   this क्रम each page written */
	दीर्घ pages_skipped;		/* Pages which were not written */

	/*
	 * For a_ops->ग_लिखोpages(): अगर start or end are non-zero then this is
	 * a hपूर्णांक that the fileप्रणाली need only ग_लिखो out the pages inside that
	 * byterange.  The byte at `end' is included in the ग_लिखोout request.
	 */
	loff_t range_start;
	loff_t range_end;

	क्रमागत ग_लिखोback_sync_modes sync_mode;

	अचिन्हित क्रम_kupdate:1;		/* A kupdate ग_लिखोback */
	अचिन्हित क्रम_background:1;	/* A background ग_लिखोback */
	अचिन्हित tagged_ग_लिखोpages:1;	/* tag-and-ग_लिखो to aव्योम livelock */
	अचिन्हित क्रम_reclaim:1;		/* Invoked from the page allocator */
	अचिन्हित range_cyclic:1;	/* range_start is cyclic */
	अचिन्हित क्रम_sync:1;		/* sync(2) WB_SYNC_ALL ग_लिखोback */

	/*
	 * When ग_लिखोback IOs are bounced through async layers, only the
	 * initial synchronous phase should be accounted towards inode
	 * cgroup ownership arbitration to aव्योम confusion.  Later stages
	 * can set the following flag to disable the accounting.
	 */
	अचिन्हित no_cgroup_owner:1;

	अचिन्हित punt_to_cgroup:1;	/* cgrp punting, see __REQ_CGROUP_PUNT */

#अगर_घोषित CONFIG_CGROUP_WRITEBACK
	काष्ठा bdi_ग_लिखोback *wb;	/* wb this ग_लिखोback is issued under */
	काष्ठा inode *inode;		/* inode being written out */

	/* क्रमeign inode detection, see wbc_detach_inode() */
	पूर्णांक wb_id;			/* current wb id */
	पूर्णांक wb_lcand_id;		/* last क्रमeign candidate wb id */
	पूर्णांक wb_tcand_id;		/* this क्रमeign candidate wb id */
	माप_प्रकार wb_bytes;		/* bytes written by current wb */
	माप_प्रकार wb_lcand_bytes;		/* bytes written by last candidate */
	माप_प्रकार wb_tcand_bytes;		/* bytes written by this candidate */
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत पूर्णांक wbc_to_ग_लिखो_flags(काष्ठा ग_लिखोback_control *wbc)
अणु
	पूर्णांक flags = 0;

	अगर (wbc->punt_to_cgroup)
		flags = REQ_CGROUP_PUNT;

	अगर (wbc->sync_mode == WB_SYNC_ALL)
		flags |= REQ_SYNC;
	अन्यथा अगर (wbc->क्रम_kupdate || wbc->क्रम_background)
		flags |= REQ_BACKGROUND;

	वापस flags;
पूर्ण

अटल अंतरभूत काष्ठा cgroup_subsys_state *
wbc_blkcg_css(काष्ठा ग_लिखोback_control *wbc)
अणु
#अगर_घोषित CONFIG_CGROUP_WRITEBACK
	अगर (wbc->wb)
		वापस wbc->wb->blkcg_css;
#पूर्ण_अगर
	वापस blkcg_root_css;
पूर्ण

/*
 * A wb_करोमुख्य represents a करोमुख्य that wb's (bdi_writeback's) beदीर्घ to
 * and are measured against each other in.  There always is one global
 * करोमुख्य, global_wb_करोमुख्य, that every wb in the प्रणाली is a member of.
 * This allows measuring the relative bandwidth of each wb to distribute
 * dirtyable memory accordingly.
 */
काष्ठा wb_करोमुख्य अणु
	spinlock_t lock;

	/*
	 * Scale the ग_लिखोback cache size proportional to the relative
	 * ग_लिखोout speed.
	 *
	 * We करो this by keeping a भग्नing proportion between BDIs, based
	 * on page ग_लिखोback completions [end_page_ग_लिखोback()]. Those
	 * devices that ग_लिखो out pages fastest will get the larger share,
	 * जबतक the slower will get a smaller share.
	 *
	 * We use page ग_लिखोout completions because we are पूर्णांकerested in
	 * getting rid of dirty pages. Having them written out is the
	 * primary goal.
	 *
	 * We पूर्णांकroduce a concept of समय, a period over which we measure
	 * these events, because demand can/will vary over समय. The length
	 * of this period itself is measured in page ग_लिखोback completions.
	 */
	काष्ठा fprop_global completions;
	काष्ठा समयr_list period_समयr;	/* समयr क्रम aging of completions */
	अचिन्हित दीर्घ period_समय;

	/*
	 * The dirtyable memory and dirty threshold could be suddenly
	 * knocked करोwn by a large amount (eg. on the startup of KVM in a
	 * swapless प्रणाली). This may throw the प्रणाली पूर्णांकo deep dirty
	 * exceeded state and throttle heavy/light dirtiers alike. To
	 * retain good responsiveness, मुख्यtain global_dirty_limit क्रम
	 * tracking slowly करोwn to the knocked करोwn dirty threshold.
	 *
	 * Both fields are रक्षित by ->lock.
	 */
	अचिन्हित दीर्घ dirty_limit_tstamp;
	अचिन्हित दीर्घ dirty_limit;
पूर्ण;

/**
 * wb_करोमुख्य_size_changed - memory available to a wb_करोमुख्य has changed
 * @करोm: wb_करोमुख्य of पूर्णांकerest
 *
 * This function should be called when the amount of memory available to
 * @करोm has changed.  It resets @करोm's dirty limit parameters to prevent
 * the past values which करोn't match the current configuration from skewing
 * dirty throttling.  Without this, when memory size of a wb_करोमुख्य is
 * greatly reduced, the dirty throttling logic may allow too many pages to
 * be dirtied leading to consecutive unnecessary OOMs and may get stuck in
 * that situation.
 */
अटल अंतरभूत व्योम wb_करोमुख्य_size_changed(काष्ठा wb_करोमुख्य *करोm)
अणु
	spin_lock(&करोm->lock);
	करोm->dirty_limit_tstamp = jअगरfies;
	करोm->dirty_limit = 0;
	spin_unlock(&करोm->lock);
पूर्ण

/*
 * fs/fs-ग_लिखोback.c
 */	
काष्ठा bdi_ग_लिखोback;
व्योम ग_लिखोback_inodes_sb(काष्ठा super_block *, क्रमागत wb_reason reason);
व्योम ग_लिखोback_inodes_sb_nr(काष्ठा super_block *, अचिन्हित दीर्घ nr,
							क्रमागत wb_reason reason);
व्योम try_to_ग_लिखोback_inodes_sb(काष्ठा super_block *sb, क्रमागत wb_reason reason);
व्योम sync_inodes_sb(काष्ठा super_block *);
व्योम wakeup_flusher_thपढ़ोs(क्रमागत wb_reason reason);
व्योम wakeup_flusher_thपढ़ोs_bdi(काष्ठा backing_dev_info *bdi,
				क्रमागत wb_reason reason);
व्योम inode_रुको_क्रम_ग_लिखोback(काष्ठा inode *inode);
व्योम inode_io_list_del(काष्ठा inode *inode);

/* ग_लिखोback.h requires fs.h; it, too, is not included from here. */
अटल अंतरभूत व्योम रुको_on_inode(काष्ठा inode *inode)
अणु
	might_sleep();
	रुको_on_bit(&inode->i_state, __I_NEW, TASK_UNINTERRUPTIBLE);
पूर्ण

#अगर_घोषित CONFIG_CGROUP_WRITEBACK

#समावेश <linux/cgroup.h>
#समावेश <linux/bपन.स>

व्योम __inode_attach_wb(काष्ठा inode *inode, काष्ठा page *page);
व्योम wbc_attach_and_unlock_inode(काष्ठा ग_लिखोback_control *wbc,
				 काष्ठा inode *inode)
	__releases(&inode->i_lock);
व्योम wbc_detach_inode(काष्ठा ग_लिखोback_control *wbc);
व्योम wbc_account_cgroup_owner(काष्ठा ग_लिखोback_control *wbc, काष्ठा page *page,
			      माप_प्रकार bytes);
पूर्णांक cgroup_ग_लिखोback_by_id(u64 bdi_id, पूर्णांक memcg_id, अचिन्हित दीर्घ nr_pages,
			   क्रमागत wb_reason reason, काष्ठा wb_completion *करोne);
व्योम cgroup_ग_लिखोback_umount(व्योम);

/**
 * inode_attach_wb - associate an inode with its wb
 * @inode: inode of पूर्णांकerest
 * @page: page being dirtied (may be शून्य)
 *
 * If @inode करोesn't have its wb, associate it with the wb matching the
 * memcg of @page or, अगर @page is शून्य, %current.  May be called w/ or w/o
 * @inode->i_lock.
 */
अटल अंतरभूत व्योम inode_attach_wb(काष्ठा inode *inode, काष्ठा page *page)
अणु
	अगर (!inode->i_wb)
		__inode_attach_wb(inode, page);
पूर्ण

/**
 * inode_detach_wb - disassociate an inode from its wb
 * @inode: inode of पूर्णांकerest
 *
 * @inode is being मुक्तd.  Detach from its wb.
 */
अटल अंतरभूत व्योम inode_detach_wb(काष्ठा inode *inode)
अणु
	अगर (inode->i_wb) अणु
		WARN_ON_ONCE(!(inode->i_state & I_CLEAR));
		wb_put(inode->i_wb);
		inode->i_wb = शून्य;
	पूर्ण
पूर्ण

/**
 * wbc_attach_fdataग_लिखो_inode - associate wbc and inode क्रम fdataग_लिखो
 * @wbc: ग_लिखोback_control of पूर्णांकerest
 * @inode: target inode
 *
 * This function is to be used by __filemap_fdataग_लिखो_range(), which is an
 * alternative entry poपूर्णांक पूर्णांकo ग_लिखोback code, and first ensures @inode is
 * associated with a bdi_ग_लिखोback and attaches it to @wbc.
 */
अटल अंतरभूत व्योम wbc_attach_fdataग_लिखो_inode(काष्ठा ग_लिखोback_control *wbc,
					       काष्ठा inode *inode)
अणु
	spin_lock(&inode->i_lock);
	inode_attach_wb(inode, शून्य);
	wbc_attach_and_unlock_inode(wbc, inode);
पूर्ण

/**
 * wbc_init_bio - ग_लिखोback specअगरic initializtion of bio
 * @wbc: ग_लिखोback_control क्रम the ग_लिखोback in progress
 * @bio: bio to be initialized
 *
 * @bio is a part of the ग_लिखोback in progress controlled by @wbc.  Perक्रमm
 * ग_लिखोback specअगरic initialization.  This is used to apply the cgroup
 * ग_लिखोback context.  Must be called after the bio has been associated with
 * a device.
 */
अटल अंतरभूत व्योम wbc_init_bio(काष्ठा ग_लिखोback_control *wbc, काष्ठा bio *bio)
अणु
	/*
	 * pageout() path करोesn't attach @wbc to the inode being written
	 * out.  This is पूर्णांकentional as we करोn't want the function to block
	 * behind a slow cgroup.  Ultimately, we want pageout() to kick off
	 * regular ग_लिखोback instead of writing things out itself.
	 */
	अगर (wbc->wb)
		bio_associate_blkg_from_css(bio, wbc->wb->blkcg_css);
पूर्ण

#अन्यथा	/* CONFIG_CGROUP_WRITEBACK */

अटल अंतरभूत व्योम inode_attach_wb(काष्ठा inode *inode, काष्ठा page *page)
अणु
पूर्ण

अटल अंतरभूत व्योम inode_detach_wb(काष्ठा inode *inode)
अणु
पूर्ण

अटल अंतरभूत व्योम wbc_attach_and_unlock_inode(काष्ठा ग_लिखोback_control *wbc,
					       काष्ठा inode *inode)
	__releases(&inode->i_lock)
अणु
	spin_unlock(&inode->i_lock);
पूर्ण

अटल अंतरभूत व्योम wbc_attach_fdataग_लिखो_inode(काष्ठा ग_लिखोback_control *wbc,
					       काष्ठा inode *inode)
अणु
पूर्ण

अटल अंतरभूत व्योम wbc_detach_inode(काष्ठा ग_लिखोback_control *wbc)
अणु
पूर्ण

अटल अंतरभूत व्योम wbc_init_bio(काष्ठा ग_लिखोback_control *wbc, काष्ठा bio *bio)
अणु
पूर्ण

अटल अंतरभूत व्योम wbc_account_cgroup_owner(काष्ठा ग_लिखोback_control *wbc,
					    काष्ठा page *page, माप_प्रकार bytes)
अणु
पूर्ण

अटल अंतरभूत व्योम cgroup_ग_लिखोback_umount(व्योम)
अणु
पूर्ण

#पूर्ण_अगर	/* CONFIG_CGROUP_WRITEBACK */

/*
 * mm/page-ग_लिखोback.c
 */
#अगर_घोषित CONFIG_BLOCK
व्योम laptop_io_completion(काष्ठा backing_dev_info *info);
व्योम laptop_sync_completion(व्योम);
व्योम laptop_mode_sync(काष्ठा work_काष्ठा *work);
व्योम laptop_mode_समयr_fn(काष्ठा समयr_list *t);
#अन्यथा
अटल अंतरभूत व्योम laptop_sync_completion(व्योम) अणु पूर्ण
#पूर्ण_अगर
bool node_dirty_ok(काष्ठा pglist_data *pgdat);
पूर्णांक wb_करोमुख्य_init(काष्ठा wb_करोमुख्य *करोm, gfp_t gfp);
#अगर_घोषित CONFIG_CGROUP_WRITEBACK
व्योम wb_करोमुख्य_निकास(काष्ठा wb_करोमुख्य *करोm);
#पूर्ण_अगर

बाह्य काष्ठा wb_करोमुख्य global_wb_करोमुख्य;

/* These are exported to sysctl. */
बाह्य पूर्णांक dirty_background_ratio;
बाह्य अचिन्हित दीर्घ dirty_background_bytes;
बाह्य पूर्णांक vm_dirty_ratio;
बाह्य अचिन्हित दीर्घ vm_dirty_bytes;
बाह्य अचिन्हित पूर्णांक dirty_ग_लिखोback_पूर्णांकerval;
बाह्य अचिन्हित पूर्णांक dirty_expire_पूर्णांकerval;
बाह्य अचिन्हित पूर्णांक dirtyसमय_expire_पूर्णांकerval;
बाह्य पूर्णांक vm_highmem_is_dirtyable;
बाह्य पूर्णांक block_dump;
बाह्य पूर्णांक laptop_mode;

पूर्णांक dirty_background_ratio_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos);
पूर्णांक dirty_background_bytes_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos);
पूर्णांक dirty_ratio_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos);
पूर्णांक dirty_bytes_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos);
पूर्णांक dirtyसमय_पूर्णांकerval_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos);
पूर्णांक dirty_ग_लिखोback_centisecs_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos);

व्योम global_dirty_limits(अचिन्हित दीर्घ *pbackground, अचिन्हित दीर्घ *pdirty);
अचिन्हित दीर्घ wb_calc_thresh(काष्ठा bdi_ग_लिखोback *wb, अचिन्हित दीर्घ thresh);

व्योम wb_update_bandwidth(काष्ठा bdi_ग_लिखोback *wb, अचिन्हित दीर्घ start_समय);
व्योम balance_dirty_pages_ratelimited(काष्ठा address_space *mapping);
bool wb_over_bg_thresh(काष्ठा bdi_ग_लिखोback *wb);

प्रकार पूर्णांक (*ग_लिखोpage_t)(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc,
				व्योम *data);

पूर्णांक generic_ग_लिखोpages(काष्ठा address_space *mapping,
		       काष्ठा ग_लिखोback_control *wbc);
व्योम tag_pages_क्रम_ग_लिखोback(काष्ठा address_space *mapping,
			     pgoff_t start, pgoff_t end);
पूर्णांक ग_लिखो_cache_pages(काष्ठा address_space *mapping,
		      काष्ठा ग_लिखोback_control *wbc, ग_लिखोpage_t ग_लिखोpage,
		      व्योम *data);
पूर्णांक करो_ग_लिखोpages(काष्ठा address_space *mapping, काष्ठा ग_लिखोback_control *wbc);
व्योम ग_लिखोback_set_ratelimit(व्योम);
व्योम tag_pages_क्रम_ग_लिखोback(काष्ठा address_space *mapping,
			     pgoff_t start, pgoff_t end);

व्योम account_page_redirty(काष्ठा page *page);

व्योम sb_mark_inode_ग_लिखोback(काष्ठा inode *inode);
व्योम sb_clear_inode_ग_लिखोback(काष्ठा inode *inode);

#पूर्ण_अगर		/* WRITEBACK_H */
