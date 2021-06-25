<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/रुको.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/module.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/device.h>
#समावेश <trace/events/ग_लिखोback.h>

काष्ठा backing_dev_info noop_backing_dev_info;
EXPORT_SYMBOL_GPL(noop_backing_dev_info);

अटल काष्ठा class *bdi_class;
अटल स्थिर अक्षर *bdi_unknown_name = "(unknown)";

/*
 * bdi_lock protects bdi_tree and updates to bdi_list. bdi_list has RCU
 * पढ़ोer side locking.
 */
DEFINE_SPINLOCK(bdi_lock);
अटल u64 bdi_id_cursor;
अटल काष्ठा rb_root bdi_tree = RB_ROOT;
LIST_HEAD(bdi_list);

/* bdi_wq serves all asynchronous ग_लिखोback tasks */
काष्ठा workqueue_काष्ठा *bdi_wq;

#घोषणा K(x) ((x) << (PAGE_SHIFT - 10))

#अगर_घोषित CONFIG_DEBUG_FS
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>

अटल काष्ठा dentry *bdi_debug_root;

अटल व्योम bdi_debug_init(व्योम)
अणु
	bdi_debug_root = debugfs_create_dir("bdi", शून्य);
पूर्ण

अटल पूर्णांक bdi_debug_stats_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा backing_dev_info *bdi = m->निजी;
	काष्ठा bdi_ग_लिखोback *wb = &bdi->wb;
	अचिन्हित दीर्घ background_thresh;
	अचिन्हित दीर्घ dirty_thresh;
	अचिन्हित दीर्घ wb_thresh;
	अचिन्हित दीर्घ nr_dirty, nr_io, nr_more_io, nr_dirty_समय;
	काष्ठा inode *inode;

	nr_dirty = nr_io = nr_more_io = nr_dirty_समय = 0;
	spin_lock(&wb->list_lock);
	list_क्रम_each_entry(inode, &wb->b_dirty, i_io_list)
		nr_dirty++;
	list_क्रम_each_entry(inode, &wb->b_io, i_io_list)
		nr_io++;
	list_क्रम_each_entry(inode, &wb->b_more_io, i_io_list)
		nr_more_io++;
	list_क्रम_each_entry(inode, &wb->b_dirty_समय, i_io_list)
		अगर (inode->i_state & I_सूचीTY_TIME)
			nr_dirty_समय++;
	spin_unlock(&wb->list_lock);

	global_dirty_limits(&background_thresh, &dirty_thresh);
	wb_thresh = wb_calc_thresh(wb, dirty_thresh);

	seq_म_लिखो(m,
		   "BdiWriteback:       %10lu kB\n"
		   "BdiReclaimable:     %10lu kB\n"
		   "BdiDirtyThresh:     %10lu kB\n"
		   "DirtyThresh:        %10lu kB\n"
		   "BackgroundThresh:   %10lu kB\n"
		   "BdiDirtied:         %10lu kB\n"
		   "BdiWritten:         %10lu kB\n"
		   "BdiWriteBandwidth:  %10lu kBps\n"
		   "b_dirty:            %10lu\n"
		   "b_io:               %10lu\n"
		   "b_more_io:          %10lu\n"
		   "b_dirty_time:       %10lu\n"
		   "bdi_list:           %10u\n"
		   "state:              %10lx\n",
		   (अचिन्हित दीर्घ) K(wb_stat(wb, WB_WRITEBACK)),
		   (अचिन्हित दीर्घ) K(wb_stat(wb, WB_RECLAIMABLE)),
		   K(wb_thresh),
		   K(dirty_thresh),
		   K(background_thresh),
		   (अचिन्हित दीर्घ) K(wb_stat(wb, WB_सूचीTIED)),
		   (अचिन्हित दीर्घ) K(wb_stat(wb, WB_WRITTEN)),
		   (अचिन्हित दीर्घ) K(wb->ग_लिखो_bandwidth),
		   nr_dirty,
		   nr_io,
		   nr_more_io,
		   nr_dirty_समय,
		   !list_empty(&bdi->bdi_list), bdi->wb.state);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(bdi_debug_stats);

अटल व्योम bdi_debug_रेजिस्टर(काष्ठा backing_dev_info *bdi, स्थिर अक्षर *name)
अणु
	bdi->debug_dir = debugfs_create_dir(name, bdi_debug_root);

	debugfs_create_file("stats", 0444, bdi->debug_dir, bdi,
			    &bdi_debug_stats_fops);
पूर्ण

अटल व्योम bdi_debug_unरेजिस्टर(काष्ठा backing_dev_info *bdi)
अणु
	debugfs_हटाओ_recursive(bdi->debug_dir);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम bdi_debug_init(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम bdi_debug_रेजिस्टर(काष्ठा backing_dev_info *bdi,
				      स्थिर अक्षर *name)
अणु
पूर्ण
अटल अंतरभूत व्योम bdi_debug_unरेजिस्टर(काष्ठा backing_dev_info *bdi)
अणु
पूर्ण
#पूर्ण_अगर

अटल sमाप_प्रकार पढ़ो_ahead_kb_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा backing_dev_info *bdi = dev_get_drvdata(dev);
	अचिन्हित दीर्घ पढ़ो_ahead_kb;
	sमाप_प्रकार ret;

	ret = kम_से_अदीर्घ(buf, 10, &पढ़ो_ahead_kb);
	अगर (ret < 0)
		वापस ret;

	bdi->ra_pages = पढ़ो_ahead_kb >> (PAGE_SHIFT - 10);

	वापस count;
पूर्ण

#घोषणा BDI_SHOW(name, expr)						\
अटल sमाप_प्रकार name##_show(काष्ठा device *dev,				\
			   काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	काष्ठा backing_dev_info *bdi = dev_get_drvdata(dev);		\
									\
	वापस sysfs_emit(buf, "%lld\n", (दीर्घ दीर्घ)expr);		\
पूर्ण									\
अटल DEVICE_ATTR_RW(name);

BDI_SHOW(पढ़ो_ahead_kb, K(bdi->ra_pages))

अटल sमाप_प्रकार min_ratio_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा backing_dev_info *bdi = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक ratio;
	sमाप_प्रकार ret;

	ret = kstrtouपूर्णांक(buf, 10, &ratio);
	अगर (ret < 0)
		वापस ret;

	ret = bdi_set_min_ratio(bdi, ratio);
	अगर (!ret)
		ret = count;

	वापस ret;
पूर्ण
BDI_SHOW(min_ratio, bdi->min_ratio)

अटल sमाप_प्रकार max_ratio_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा backing_dev_info *bdi = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक ratio;
	sमाप_प्रकार ret;

	ret = kstrtouपूर्णांक(buf, 10, &ratio);
	अगर (ret < 0)
		वापस ret;

	ret = bdi_set_max_ratio(bdi, ratio);
	अगर (!ret)
		ret = count;

	वापस ret;
पूर्ण
BDI_SHOW(max_ratio, bdi->max_ratio)

अटल sमाप_प्रकार stable_pages_required_show(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	dev_warn_once(dev,
		"the stable_pages_required attribute has been removed. Use the stable_writes queue attribute instead.\n");
	वापस sysfs_emit(buf, "%d\n", 0);
पूर्ण
अटल DEVICE_ATTR_RO(stable_pages_required);

अटल काष्ठा attribute *bdi_dev_attrs[] = अणु
	&dev_attr_पढ़ो_ahead_kb.attr,
	&dev_attr_min_ratio.attr,
	&dev_attr_max_ratio.attr,
	&dev_attr_stable_pages_required.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(bdi_dev);

अटल __init पूर्णांक bdi_class_init(व्योम)
अणु
	bdi_class = class_create(THIS_MODULE, "bdi");
	अगर (IS_ERR(bdi_class))
		वापस PTR_ERR(bdi_class);

	bdi_class->dev_groups = bdi_dev_groups;
	bdi_debug_init();

	वापस 0;
पूर्ण
postcore_initcall(bdi_class_init);

अटल पूर्णांक bdi_init(काष्ठा backing_dev_info *bdi);

अटल पूर्णांक __init शेष_bdi_init(व्योम)
अणु
	पूर्णांक err;

	bdi_wq = alloc_workqueue("writeback", WQ_MEM_RECLAIM | WQ_UNBOUND |
				 WQ_SYSFS, 0);
	अगर (!bdi_wq)
		वापस -ENOMEM;

	err = bdi_init(&noop_backing_dev_info);

	वापस err;
पूर्ण
subsys_initcall(शेष_bdi_init);

/*
 * This function is used when the first inode क्रम this wb is marked dirty. It
 * wakes-up the corresponding bdi thपढ़ो which should then take care of the
 * periodic background ग_लिखो-out of dirty inodes. Since the ग_लिखो-out would
 * starts only 'dirty_writeback_interval' centisecs from now anyway, we just
 * set up a समयr which wakes the bdi thपढ़ो up later.
 *
 * Note, we wouldn't bother setting up the समयr, but this function is on the
 * fast-path (used by '__mark_inode_dirty()'), so we save few context चयनes
 * by delaying the wake-up.
 *
 * We have to be careful not to postpone flush work अगर it is scheduled क्रम
 * earlier. Thus we use queue_delayed_work().
 */
व्योम wb_wakeup_delayed(काष्ठा bdi_ग_लिखोback *wb)
अणु
	अचिन्हित दीर्घ समयout;

	समयout = msecs_to_jअगरfies(dirty_ग_लिखोback_पूर्णांकerval * 10);
	spin_lock_bh(&wb->work_lock);
	अगर (test_bit(WB_रेजिस्टरed, &wb->state))
		queue_delayed_work(bdi_wq, &wb->dwork, समयout);
	spin_unlock_bh(&wb->work_lock);
पूर्ण

/*
 * Initial ग_लिखो bandwidth: 100 MB/s
 */
#घोषणा INIT_BW		(100 << (20 - PAGE_SHIFT))

अटल पूर्णांक wb_init(काष्ठा bdi_ग_लिखोback *wb, काष्ठा backing_dev_info *bdi,
		   gfp_t gfp)
अणु
	पूर्णांक i, err;

	स_रखो(wb, 0, माप(*wb));

	अगर (wb != &bdi->wb)
		bdi_get(bdi);
	wb->bdi = bdi;
	wb->last_old_flush = jअगरfies;
	INIT_LIST_HEAD(&wb->b_dirty);
	INIT_LIST_HEAD(&wb->b_io);
	INIT_LIST_HEAD(&wb->b_more_io);
	INIT_LIST_HEAD(&wb->b_dirty_समय);
	spin_lock_init(&wb->list_lock);

	wb->bw_समय_stamp = jअगरfies;
	wb->balanced_dirty_ratelimit = INIT_BW;
	wb->dirty_ratelimit = INIT_BW;
	wb->ग_लिखो_bandwidth = INIT_BW;
	wb->avg_ग_लिखो_bandwidth = INIT_BW;

	spin_lock_init(&wb->work_lock);
	INIT_LIST_HEAD(&wb->work_list);
	INIT_DELAYED_WORK(&wb->dwork, wb_workfn);
	wb->dirty_sleep = jअगरfies;

	err = fprop_local_init_percpu(&wb->completions, gfp);
	अगर (err)
		जाओ out_put_bdi;

	क्रम (i = 0; i < NR_WB_STAT_ITEMS; i++) अणु
		err = percpu_counter_init(&wb->stat[i], 0, gfp);
		अगर (err)
			जाओ out_destroy_stat;
	पूर्ण

	वापस 0;

out_destroy_stat:
	जबतक (i--)
		percpu_counter_destroy(&wb->stat[i]);
	fprop_local_destroy_percpu(&wb->completions);
out_put_bdi:
	अगर (wb != &bdi->wb)
		bdi_put(bdi);
	वापस err;
पूर्ण

अटल व्योम cgwb_हटाओ_from_bdi_list(काष्ठा bdi_ग_लिखोback *wb);

/*
 * Remove bdi from the global list and shutकरोwn any thपढ़ोs we have running
 */
अटल व्योम wb_shutकरोwn(काष्ठा bdi_ग_लिखोback *wb)
अणु
	/* Make sure nobody queues further work */
	spin_lock_bh(&wb->work_lock);
	अगर (!test_and_clear_bit(WB_रेजिस्टरed, &wb->state)) अणु
		spin_unlock_bh(&wb->work_lock);
		वापस;
	पूर्ण
	spin_unlock_bh(&wb->work_lock);

	cgwb_हटाओ_from_bdi_list(wb);
	/*
	 * Drain work list and shutकरोwn the delayed_work.  !WB_रेजिस्टरed
	 * tells wb_workfn() that @wb is dying and its work_list needs to
	 * be drained no matter what.
	 */
	mod_delayed_work(bdi_wq, &wb->dwork, 0);
	flush_delayed_work(&wb->dwork);
	WARN_ON(!list_empty(&wb->work_list));
पूर्ण

अटल व्योम wb_निकास(काष्ठा bdi_ग_लिखोback *wb)
अणु
	पूर्णांक i;

	WARN_ON(delayed_work_pending(&wb->dwork));

	क्रम (i = 0; i < NR_WB_STAT_ITEMS; i++)
		percpu_counter_destroy(&wb->stat[i]);

	fprop_local_destroy_percpu(&wb->completions);
	अगर (wb != &wb->bdi->wb)
		bdi_put(wb->bdi);
पूर्ण

#अगर_घोषित CONFIG_CGROUP_WRITEBACK

#समावेश <linux/memcontrol.h>

/*
 * cgwb_lock protects bdi->cgwb_tree, blkcg->cgwb_list, and memcg->cgwb_list.
 * bdi->cgwb_tree is also RCU रक्षित.
 */
अटल DEFINE_SPINLOCK(cgwb_lock);
अटल काष्ठा workqueue_काष्ठा *cgwb_release_wq;

अटल व्योम cgwb_release_workfn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bdi_ग_लिखोback *wb = container_of(work, काष्ठा bdi_ग_लिखोback,
						release_work);
	काष्ठा blkcg *blkcg = css_to_blkcg(wb->blkcg_css);

	mutex_lock(&wb->bdi->cgwb_release_mutex);
	wb_shutकरोwn(wb);

	css_put(wb->memcg_css);
	css_put(wb->blkcg_css);
	mutex_unlock(&wb->bdi->cgwb_release_mutex);

	/* triggers blkg deकाष्ठाion अगर no online users left */
	blkcg_unpin_online(blkcg);

	fprop_local_destroy_percpu(&wb->memcg_completions);
	percpu_ref_निकास(&wb->refcnt);
	wb_निकास(wb);
	kमुक्त_rcu(wb, rcu);
पूर्ण

अटल व्योम cgwb_release(काष्ठा percpu_ref *refcnt)
अणु
	काष्ठा bdi_ग_लिखोback *wb = container_of(refcnt, काष्ठा bdi_ग_लिखोback,
						refcnt);
	queue_work(cgwb_release_wq, &wb->release_work);
पूर्ण

अटल व्योम cgwb_समाप्त(काष्ठा bdi_ग_लिखोback *wb)
अणु
	lockdep_निश्चित_held(&cgwb_lock);

	WARN_ON(!radix_tree_delete(&wb->bdi->cgwb_tree, wb->memcg_css->id));
	list_del(&wb->memcg_node);
	list_del(&wb->blkcg_node);
	percpu_ref_समाप्त(&wb->refcnt);
पूर्ण

अटल व्योम cgwb_हटाओ_from_bdi_list(काष्ठा bdi_ग_लिखोback *wb)
अणु
	spin_lock_irq(&cgwb_lock);
	list_del_rcu(&wb->bdi_node);
	spin_unlock_irq(&cgwb_lock);
पूर्ण

अटल पूर्णांक cgwb_create(काष्ठा backing_dev_info *bdi,
		       काष्ठा cgroup_subsys_state *memcg_css, gfp_t gfp)
अणु
	काष्ठा mem_cgroup *memcg;
	काष्ठा cgroup_subsys_state *blkcg_css;
	काष्ठा blkcg *blkcg;
	काष्ठा list_head *memcg_cgwb_list, *blkcg_cgwb_list;
	काष्ठा bdi_ग_लिखोback *wb;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	memcg = mem_cgroup_from_css(memcg_css);
	blkcg_css = cgroup_get_e_css(memcg_css->cgroup, &io_cgrp_subsys);
	blkcg = css_to_blkcg(blkcg_css);
	memcg_cgwb_list = &memcg->cgwb_list;
	blkcg_cgwb_list = &blkcg->cgwb_list;

	/* look up again under lock and discard on blkcg mismatch */
	spin_lock_irqsave(&cgwb_lock, flags);
	wb = radix_tree_lookup(&bdi->cgwb_tree, memcg_css->id);
	अगर (wb && wb->blkcg_css != blkcg_css) अणु
		cgwb_समाप्त(wb);
		wb = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&cgwb_lock, flags);
	अगर (wb)
		जाओ out_put;

	/* need to create a new one */
	wb = kदो_स्मृति(माप(*wb), gfp);
	अगर (!wb) अणु
		ret = -ENOMEM;
		जाओ out_put;
	पूर्ण

	ret = wb_init(wb, bdi, gfp);
	अगर (ret)
		जाओ err_मुक्त;

	ret = percpu_ref_init(&wb->refcnt, cgwb_release, 0, gfp);
	अगर (ret)
		जाओ err_wb_निकास;

	ret = fprop_local_init_percpu(&wb->memcg_completions, gfp);
	अगर (ret)
		जाओ err_ref_निकास;

	wb->memcg_css = memcg_css;
	wb->blkcg_css = blkcg_css;
	INIT_WORK(&wb->release_work, cgwb_release_workfn);
	set_bit(WB_रेजिस्टरed, &wb->state);

	/*
	 * The root wb determines the रेजिस्टरed state of the whole bdi and
	 * memcg_cgwb_list and blkcg_cgwb_list's next poपूर्णांकers indicate
	 * whether they're still online.  Don't link @wb अगर any is dead.
	 * See wb_memcg_offline() and wb_blkcg_offline().
	 */
	ret = -ENODEV;
	spin_lock_irqsave(&cgwb_lock, flags);
	अगर (test_bit(WB_रेजिस्टरed, &bdi->wb.state) &&
	    blkcg_cgwb_list->next && memcg_cgwb_list->next) अणु
		/* we might have raced another instance of this function */
		ret = radix_tree_insert(&bdi->cgwb_tree, memcg_css->id, wb);
		अगर (!ret) अणु
			list_add_tail_rcu(&wb->bdi_node, &bdi->wb_list);
			list_add(&wb->memcg_node, memcg_cgwb_list);
			list_add(&wb->blkcg_node, blkcg_cgwb_list);
			blkcg_pin_online(blkcg);
			css_get(memcg_css);
			css_get(blkcg_css);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&cgwb_lock, flags);
	अगर (ret) अणु
		अगर (ret == -EEXIST)
			ret = 0;
		जाओ err_fprop_निकास;
	पूर्ण
	जाओ out_put;

err_fprop_निकास:
	fprop_local_destroy_percpu(&wb->memcg_completions);
err_ref_निकास:
	percpu_ref_निकास(&wb->refcnt);
err_wb_निकास:
	wb_निकास(wb);
err_मुक्त:
	kमुक्त(wb);
out_put:
	css_put(blkcg_css);
	वापस ret;
पूर्ण

/**
 * wb_get_lookup - get wb क्रम a given memcg
 * @bdi: target bdi
 * @memcg_css: cgroup_subsys_state of the target memcg (must have positive ref)
 *
 * Try to get the wb क्रम @memcg_css on @bdi.  The वापसed wb has its
 * refcount incremented.
 *
 * This function uses css_get() on @memcg_css and thus expects its refcnt
 * to be positive on invocation.  IOW, rcu_पढ़ो_lock() protection on
 * @memcg_css isn't enough.  try_get it beक्रमe calling this function.
 *
 * A wb is keyed by its associated memcg.  As blkcg implicitly enables
 * memcg on the शेष hierarchy, memcg association is guaranteed to be
 * more specअगरic (equal or descendant to the associated blkcg) and thus can
 * identअगरy both the memcg and blkcg associations.
 *
 * Because the blkcg associated with a memcg may change as blkcg is enabled
 * and disabled बंदr to root in the hierarchy, each wb keeps track of
 * both the memcg and blkcg associated with it and verअगरies the blkcg on
 * each lookup.  On mismatch, the existing wb is discarded and a new one is
 * created.
 */
काष्ठा bdi_ग_लिखोback *wb_get_lookup(काष्ठा backing_dev_info *bdi,
				    काष्ठा cgroup_subsys_state *memcg_css)
अणु
	काष्ठा bdi_ग_लिखोback *wb;

	अगर (!memcg_css->parent)
		वापस &bdi->wb;

	rcu_पढ़ो_lock();
	wb = radix_tree_lookup(&bdi->cgwb_tree, memcg_css->id);
	अगर (wb) अणु
		काष्ठा cgroup_subsys_state *blkcg_css;

		/* see whether the blkcg association has changed */
		blkcg_css = cgroup_get_e_css(memcg_css->cgroup, &io_cgrp_subsys);
		अगर (unlikely(wb->blkcg_css != blkcg_css || !wb_tryget(wb)))
			wb = शून्य;
		css_put(blkcg_css);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस wb;
पूर्ण

/**
 * wb_get_create - get wb क्रम a given memcg, create अगर necessary
 * @bdi: target bdi
 * @memcg_css: cgroup_subsys_state of the target memcg (must have positive ref)
 * @gfp: allocation mask to use
 *
 * Try to get the wb क्रम @memcg_css on @bdi.  If it करोesn't exist, try to
 * create one.  See wb_get_lookup() क्रम more details.
 */
काष्ठा bdi_ग_लिखोback *wb_get_create(काष्ठा backing_dev_info *bdi,
				    काष्ठा cgroup_subsys_state *memcg_css,
				    gfp_t gfp)
अणु
	काष्ठा bdi_ग_लिखोback *wb;

	might_alloc(gfp);

	अगर (!memcg_css->parent)
		वापस &bdi->wb;

	करो अणु
		wb = wb_get_lookup(bdi, memcg_css);
	पूर्ण जबतक (!wb && !cgwb_create(bdi, memcg_css, gfp));

	वापस wb;
पूर्ण

अटल पूर्णांक cgwb_bdi_init(काष्ठा backing_dev_info *bdi)
अणु
	पूर्णांक ret;

	INIT_RADIX_TREE(&bdi->cgwb_tree, GFP_ATOMIC);
	mutex_init(&bdi->cgwb_release_mutex);
	init_rwsem(&bdi->wb_चयन_rwsem);

	ret = wb_init(&bdi->wb, bdi, GFP_KERNEL);
	अगर (!ret) अणु
		bdi->wb.memcg_css = &root_mem_cgroup->css;
		bdi->wb.blkcg_css = blkcg_root_css;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम cgwb_bdi_unरेजिस्टर(काष्ठा backing_dev_info *bdi)
अणु
	काष्ठा radix_tree_iter iter;
	व्योम **slot;
	काष्ठा bdi_ग_लिखोback *wb;

	WARN_ON(test_bit(WB_रेजिस्टरed, &bdi->wb.state));

	spin_lock_irq(&cgwb_lock);
	radix_tree_क्रम_each_slot(slot, &bdi->cgwb_tree, &iter, 0)
		cgwb_समाप्त(*slot);
	spin_unlock_irq(&cgwb_lock);

	mutex_lock(&bdi->cgwb_release_mutex);
	spin_lock_irq(&cgwb_lock);
	जबतक (!list_empty(&bdi->wb_list)) अणु
		wb = list_first_entry(&bdi->wb_list, काष्ठा bdi_ग_लिखोback,
				      bdi_node);
		spin_unlock_irq(&cgwb_lock);
		wb_shutकरोwn(wb);
		spin_lock_irq(&cgwb_lock);
	पूर्ण
	spin_unlock_irq(&cgwb_lock);
	mutex_unlock(&bdi->cgwb_release_mutex);
पूर्ण

/**
 * wb_memcg_offline - समाप्त all wb's associated with a memcg being offlined
 * @memcg: memcg being offlined
 *
 * Also prevents creation of any new wb's associated with @memcg.
 */
व्योम wb_memcg_offline(काष्ठा mem_cgroup *memcg)
अणु
	काष्ठा list_head *memcg_cgwb_list = &memcg->cgwb_list;
	काष्ठा bdi_ग_लिखोback *wb, *next;

	spin_lock_irq(&cgwb_lock);
	list_क्रम_each_entry_safe(wb, next, memcg_cgwb_list, memcg_node)
		cgwb_समाप्त(wb);
	memcg_cgwb_list->next = शून्य;	/* prevent new wb's */
	spin_unlock_irq(&cgwb_lock);
पूर्ण

/**
 * wb_blkcg_offline - समाप्त all wb's associated with a blkcg being offlined
 * @blkcg: blkcg being offlined
 *
 * Also prevents creation of any new wb's associated with @blkcg.
 */
व्योम wb_blkcg_offline(काष्ठा blkcg *blkcg)
अणु
	काष्ठा bdi_ग_लिखोback *wb, *next;

	spin_lock_irq(&cgwb_lock);
	list_क्रम_each_entry_safe(wb, next, &blkcg->cgwb_list, blkcg_node)
		cgwb_समाप्त(wb);
	blkcg->cgwb_list.next = शून्य;	/* prevent new wb's */
	spin_unlock_irq(&cgwb_lock);
पूर्ण

अटल व्योम cgwb_bdi_रेजिस्टर(काष्ठा backing_dev_info *bdi)
अणु
	spin_lock_irq(&cgwb_lock);
	list_add_tail_rcu(&bdi->wb.bdi_node, &bdi->wb_list);
	spin_unlock_irq(&cgwb_lock);
पूर्ण

अटल पूर्णांक __init cgwb_init(व्योम)
अणु
	/*
	 * There can be many concurrent release work items overwhelming
	 * प्रणाली_wq.  Put them in a separate wq and limit concurrency.
	 * There's no poपूर्णांक in executing many of these in parallel.
	 */
	cgwb_release_wq = alloc_workqueue("cgwb_release", 0, 1);
	अगर (!cgwb_release_wq)
		वापस -ENOMEM;

	वापस 0;
पूर्ण
subsys_initcall(cgwb_init);

#अन्यथा	/* CONFIG_CGROUP_WRITEBACK */

अटल पूर्णांक cgwb_bdi_init(काष्ठा backing_dev_info *bdi)
अणु
	वापस wb_init(&bdi->wb, bdi, GFP_KERNEL);
पूर्ण

अटल व्योम cgwb_bdi_unरेजिस्टर(काष्ठा backing_dev_info *bdi) अणु पूर्ण

अटल व्योम cgwb_bdi_रेजिस्टर(काष्ठा backing_dev_info *bdi)
अणु
	list_add_tail_rcu(&bdi->wb.bdi_node, &bdi->wb_list);
पूर्ण

अटल व्योम cgwb_हटाओ_from_bdi_list(काष्ठा bdi_ग_लिखोback *wb)
अणु
	list_del_rcu(&wb->bdi_node);
पूर्ण

#पूर्ण_अगर	/* CONFIG_CGROUP_WRITEBACK */

अटल पूर्णांक bdi_init(काष्ठा backing_dev_info *bdi)
अणु
	पूर्णांक ret;

	bdi->dev = शून्य;

	kref_init(&bdi->refcnt);
	bdi->min_ratio = 0;
	bdi->max_ratio = 100;
	bdi->max_prop_frac = FPROP_FRAC_BASE;
	INIT_LIST_HEAD(&bdi->bdi_list);
	INIT_LIST_HEAD(&bdi->wb_list);
	init_रुकोqueue_head(&bdi->wb_रुकोq);

	ret = cgwb_bdi_init(bdi);

	वापस ret;
पूर्ण

काष्ठा backing_dev_info *bdi_alloc(पूर्णांक node_id)
अणु
	काष्ठा backing_dev_info *bdi;

	bdi = kzalloc_node(माप(*bdi), GFP_KERNEL, node_id);
	अगर (!bdi)
		वापस शून्य;

	अगर (bdi_init(bdi)) अणु
		kमुक्त(bdi);
		वापस शून्य;
	पूर्ण
	bdi->capabilities = BDI_CAP_WRITEBACK | BDI_CAP_WRITEBACK_ACCT;
	bdi->ra_pages = VM_READAHEAD_PAGES;
	bdi->io_pages = VM_READAHEAD_PAGES;
	वापस bdi;
पूर्ण
EXPORT_SYMBOL(bdi_alloc);

अटल काष्ठा rb_node **bdi_lookup_rb_node(u64 id, काष्ठा rb_node **parentp)
अणु
	काष्ठा rb_node **p = &bdi_tree.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा backing_dev_info *bdi;

	lockdep_निश्चित_held(&bdi_lock);

	जबतक (*p) अणु
		parent = *p;
		bdi = rb_entry(parent, काष्ठा backing_dev_info, rb_node);

		अगर (bdi->id > id)
			p = &(*p)->rb_left;
		अन्यथा अगर (bdi->id < id)
			p = &(*p)->rb_right;
		अन्यथा
			अवरोध;
	पूर्ण

	अगर (parentp)
		*parentp = parent;
	वापस p;
पूर्ण

/**
 * bdi_get_by_id - lookup and get bdi from its id
 * @id: bdi id to lookup
 *
 * Find bdi matching @id and get it.  Returns शून्य अगर the matching bdi
 * करोesn't exist or is alपढ़ोy unरेजिस्टरed.
 */
काष्ठा backing_dev_info *bdi_get_by_id(u64 id)
अणु
	काष्ठा backing_dev_info *bdi = शून्य;
	काष्ठा rb_node **p;

	spin_lock_bh(&bdi_lock);
	p = bdi_lookup_rb_node(id, शून्य);
	अगर (*p) अणु
		bdi = rb_entry(*p, काष्ठा backing_dev_info, rb_node);
		bdi_get(bdi);
	पूर्ण
	spin_unlock_bh(&bdi_lock);

	वापस bdi;
पूर्ण

पूर्णांक bdi_रेजिस्टर_va(काष्ठा backing_dev_info *bdi, स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	काष्ठा device *dev;
	काष्ठा rb_node *parent, **p;

	अगर (bdi->dev)	/* The driver needs to use separate queues per device */
		वापस 0;

	vsnम_लिखो(bdi->dev_name, माप(bdi->dev_name), fmt, args);
	dev = device_create(bdi_class, शून्य, MKDEV(0, 0), bdi, bdi->dev_name);
	अगर (IS_ERR(dev))
		वापस PTR_ERR(dev);

	cgwb_bdi_रेजिस्टर(bdi);
	bdi->dev = dev;

	bdi_debug_रेजिस्टर(bdi, dev_name(dev));
	set_bit(WB_रेजिस्टरed, &bdi->wb.state);

	spin_lock_bh(&bdi_lock);

	bdi->id = ++bdi_id_cursor;

	p = bdi_lookup_rb_node(bdi->id, &parent);
	rb_link_node(&bdi->rb_node, parent, p);
	rb_insert_color(&bdi->rb_node, &bdi_tree);

	list_add_tail_rcu(&bdi->bdi_list, &bdi_list);

	spin_unlock_bh(&bdi_lock);

	trace_ग_लिखोback_bdi_रेजिस्टर(bdi);
	वापस 0;
पूर्ण

पूर्णांक bdi_रेजिस्टर(काष्ठा backing_dev_info *bdi, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक ret;

	बहु_शुरू(args, fmt);
	ret = bdi_रेजिस्टर_va(bdi, fmt, args);
	बहु_पूर्ण(args);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(bdi_रेजिस्टर);

व्योम bdi_set_owner(काष्ठा backing_dev_info *bdi, काष्ठा device *owner)
अणु
	WARN_ON_ONCE(bdi->owner);
	bdi->owner = owner;
	get_device(owner);
पूर्ण

/*
 * Remove bdi from bdi_list, and ensure that it is no दीर्घer visible
 */
अटल व्योम bdi_हटाओ_from_list(काष्ठा backing_dev_info *bdi)
अणु
	spin_lock_bh(&bdi_lock);
	rb_erase(&bdi->rb_node, &bdi_tree);
	list_del_rcu(&bdi->bdi_list);
	spin_unlock_bh(&bdi_lock);

	synchronize_rcu_expedited();
पूर्ण

व्योम bdi_unरेजिस्टर(काष्ठा backing_dev_info *bdi)
अणु
	/* make sure nobody finds us on the bdi_list anymore */
	bdi_हटाओ_from_list(bdi);
	wb_shutकरोwn(&bdi->wb);
	cgwb_bdi_unरेजिस्टर(bdi);

	अगर (bdi->dev) अणु
		bdi_debug_unरेजिस्टर(bdi);
		device_unरेजिस्टर(bdi->dev);
		bdi->dev = शून्य;
	पूर्ण

	अगर (bdi->owner) अणु
		put_device(bdi->owner);
		bdi->owner = शून्य;
	पूर्ण
पूर्ण

अटल व्योम release_bdi(काष्ठा kref *ref)
अणु
	काष्ठा backing_dev_info *bdi =
			container_of(ref, काष्ठा backing_dev_info, refcnt);

	अगर (test_bit(WB_रेजिस्टरed, &bdi->wb.state))
		bdi_unरेजिस्टर(bdi);
	WARN_ON_ONCE(bdi->dev);
	wb_निकास(&bdi->wb);
	kमुक्त(bdi);
पूर्ण

व्योम bdi_put(काष्ठा backing_dev_info *bdi)
अणु
	kref_put(&bdi->refcnt, release_bdi);
पूर्ण
EXPORT_SYMBOL(bdi_put);

स्थिर अक्षर *bdi_dev_name(काष्ठा backing_dev_info *bdi)
अणु
	अगर (!bdi || !bdi->dev)
		वापस bdi_unknown_name;
	वापस bdi->dev_name;
पूर्ण
EXPORT_SYMBOL_GPL(bdi_dev_name);

अटल रुको_queue_head_t congestion_wqh[2] = अणु
		__WAIT_QUEUE_HEAD_INITIALIZER(congestion_wqh[0]),
		__WAIT_QUEUE_HEAD_INITIALIZER(congestion_wqh[1])
	पूर्ण;
अटल atomic_t nr_wb_congested[2];

व्योम clear_bdi_congested(काष्ठा backing_dev_info *bdi, पूर्णांक sync)
अणु
	रुको_queue_head_t *wqh = &congestion_wqh[sync];
	क्रमागत wb_congested_state bit;

	bit = sync ? WB_sync_congested : WB_async_congested;
	अगर (test_and_clear_bit(bit, &bdi->wb.congested))
		atomic_dec(&nr_wb_congested[sync]);
	smp_mb__after_atomic();
	अगर (रुकोqueue_active(wqh))
		wake_up(wqh);
पूर्ण
EXPORT_SYMBOL(clear_bdi_congested);

व्योम set_bdi_congested(काष्ठा backing_dev_info *bdi, पूर्णांक sync)
अणु
	क्रमागत wb_congested_state bit;

	bit = sync ? WB_sync_congested : WB_async_congested;
	अगर (!test_and_set_bit(bit, &bdi->wb.congested))
		atomic_inc(&nr_wb_congested[sync]);
पूर्ण
EXPORT_SYMBOL(set_bdi_congested);

/**
 * congestion_रुको - रुको क्रम a backing_dev to become uncongested
 * @sync: SYNC or ASYNC IO
 * @समयout: समयout in jअगरfies
 *
 * Waits क्रम up to @समयout jअगरfies क्रम a backing_dev (any backing_dev) to निकास
 * ग_लिखो congestion.  If no backing_devs are congested then just रुको क्रम the
 * next ग_लिखो to be completed.
 */
दीर्घ congestion_रुको(पूर्णांक sync, दीर्घ समयout)
अणु
	दीर्घ ret;
	अचिन्हित दीर्घ start = jअगरfies;
	DEFINE_WAIT(रुको);
	रुको_queue_head_t *wqh = &congestion_wqh[sync];

	prepare_to_रुको(wqh, &रुको, TASK_UNINTERRUPTIBLE);
	ret = io_schedule_समयout(समयout);
	finish_रुको(wqh, &रुको);

	trace_ग_लिखोback_congestion_रुको(jअगरfies_to_usecs(समयout),
					jअगरfies_to_usecs(jअगरfies - start));

	वापस ret;
पूर्ण
EXPORT_SYMBOL(congestion_रुको);

/**
 * रुको_अगरf_congested - Conditionally रुको क्रम a backing_dev to become uncongested or a pgdat to complete ग_लिखोs
 * @sync: SYNC or ASYNC IO
 * @समयout: समयout in jअगरfies
 *
 * In the event of a congested backing_dev (any backing_dev) this रुकोs
 * क्रम up to @समयout jअगरfies क्रम either a BDI to निकास congestion of the
 * given @sync queue or a ग_लिखो to complete.
 *
 * The वापस value is 0 अगर the sleep is क्रम the full समयout. Otherwise,
 * it is the number of jअगरfies that were still reमुख्यing when the function
 * वापसed. वापस_value == समयout implies the function did not sleep.
 */
दीर्घ रुको_अगरf_congested(पूर्णांक sync, दीर्घ समयout)
अणु
	दीर्घ ret;
	अचिन्हित दीर्घ start = jअगरfies;
	DEFINE_WAIT(रुको);
	रुको_queue_head_t *wqh = &congestion_wqh[sync];

	/*
	 * If there is no congestion, yield अगर necessary instead
	 * of sleeping on the congestion queue
	 */
	अगर (atomic_पढ़ो(&nr_wb_congested[sync]) == 0) अणु
		cond_resched();

		/* In हाल we scheduled, work out समय reमुख्यing */
		ret = समयout - (jअगरfies - start);
		अगर (ret < 0)
			ret = 0;

		जाओ out;
	पूर्ण

	/* Sleep until uncongested or a ग_लिखो happens */
	prepare_to_रुको(wqh, &रुको, TASK_UNINTERRUPTIBLE);
	ret = io_schedule_समयout(समयout);
	finish_रुको(wqh, &रुको);

out:
	trace_ग_लिखोback_रुको_अगरf_congested(jअगरfies_to_usecs(समयout),
					jअगरfies_to_usecs(jअगरfies - start));

	वापस ret;
पूर्ण
EXPORT_SYMBOL(रुको_अगरf_congested);
