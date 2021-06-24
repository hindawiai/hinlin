<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_BACKING_DEV_DEFS_H
#घोषणा __LINUX_BACKING_DEV_DEFS_H

#समावेश <linux/list.h>
#समावेश <linux/radix-tree.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/percpu_counter.h>
#समावेश <linux/percpu-refcount.h>
#समावेश <linux/flex_proportions.h>
#समावेश <linux/समयr.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/kref.h>
#समावेश <linux/refcount.h>

काष्ठा page;
काष्ठा device;
काष्ठा dentry;

/*
 * Bits in bdi_ग_लिखोback.state
 */
क्रमागत wb_state अणु
	WB_रेजिस्टरed,		/* bdi_रेजिस्टर() was करोne */
	WB_ग_लिखोback_running,	/* Writeback is in progress */
	WB_has_dirty_io,	/* Dirty inodes on ->b_अणुdirty|io|more_ioपूर्ण */
	WB_start_all,		/* nr_pages == 0 (all) work pending */
पूर्ण;

क्रमागत wb_congested_state अणु
	WB_async_congested,	/* The async (ग_लिखो) queue is getting full */
	WB_sync_congested,	/* The sync queue is getting full */
पूर्ण;

क्रमागत wb_stat_item अणु
	WB_RECLAIMABLE,
	WB_WRITEBACK,
	WB_सूचीTIED,
	WB_WRITTEN,
	NR_WB_STAT_ITEMS
पूर्ण;

#घोषणा WB_STAT_BATCH (8*(1+ilog2(nr_cpu_ids)))

/*
 * why some ग_लिखोback work was initiated
 */
क्रमागत wb_reason अणु
	WB_REASON_BACKGROUND,
	WB_REASON_VMSCAN,
	WB_REASON_SYNC,
	WB_REASON_PERIODIC,
	WB_REASON_LAPTOP_TIMER,
	WB_REASON_FS_FREE_SPACE,
	/*
	 * There is no bdi विभाजनer thपढ़ो any more and works are करोne
	 * by emergency worker, however, this is TPs userland visible
	 * and we'll be exposing exactly the same inक्रमmation,
	 * so it has a mismatch name.
	 */
	WB_REASON_FORKER_THREAD,
	WB_REASON_FOREIGN_FLUSH,

	WB_REASON_MAX,
पूर्ण;

काष्ठा wb_completion अणु
	atomic_t		cnt;
	रुको_queue_head_t	*रुकोq;
पूर्ण;

#घोषणा __WB_COMPLETION_INIT(_रुकोq)	\
	(काष्ठा wb_completion)अणु .cnt = ATOMIC_INIT(1), .रुकोq = (_रुकोq) पूर्ण

/*
 * If one wants to रुको क्रम one or more wb_ग_लिखोback_works, each work's
 * ->करोne should be set to a wb_completion defined using the following
 * macro.  Once all work items are issued with wb_queue_work(), the caller
 * can रुको क्रम the completion of all using wb_रुको_क्रम_completion().  Work
 * items which are रुकोed upon aren't मुक्तd स्वतःmatically on completion.
 */
#घोषणा WB_COMPLETION_INIT(bdi)		__WB_COMPLETION_INIT(&(bdi)->wb_रुकोq)

#घोषणा DEFINE_WB_COMPLETION(cmpl, bdi)	\
	काष्ठा wb_completion cmpl = WB_COMPLETION_INIT(bdi)

/*
 * Each wb (bdi_ग_लिखोback) can perक्रमm ग_लिखोback operations, is measured
 * and throttled, independently.  Without cgroup ग_लिखोback, each bdi
 * (bdi_ग_लिखोback) is served by its embedded bdi->wb.
 *
 * On the शेष hierarchy, blkcg implicitly enables memcg.  This allows
 * using memcg's page ownership क्रम attributing ग_लिखोback IOs, and every
 * memcg - blkcg combination can be served by its own wb by assigning a
 * dedicated wb to each memcg, which enables isolation across dअगरferent
 * cgroups and propagation of IO back pressure करोwn from the IO layer upto
 * the tasks which are generating the dirty pages to be written back.
 *
 * A cgroup wb is indexed on its bdi by the ID of the associated memcg,
 * refcounted with the number of inodes attached to it, and pins the memcg
 * and the corresponding blkcg.  As the corresponding blkcg क्रम a memcg may
 * change as blkcg is disabled and enabled higher up in the hierarchy, a wb
 * is tested क्रम blkcg after lookup and हटाओd from index on mismatch so
 * that a new wb क्रम the combination can be created.
 */
काष्ठा bdi_ग_लिखोback अणु
	काष्ठा backing_dev_info *bdi;	/* our parent bdi */

	अचिन्हित दीर्घ state;		/* Always use atomic bitops on this */
	अचिन्हित दीर्घ last_old_flush;	/* last old data flush */

	काष्ठा list_head b_dirty;	/* dirty inodes */
	काष्ठा list_head b_io;		/* parked क्रम ग_लिखोback */
	काष्ठा list_head b_more_io;	/* parked क्रम more ग_लिखोback */
	काष्ठा list_head b_dirty_समय;	/* समय stamps are dirty */
	spinlock_t list_lock;		/* protects the b_* lists */

	काष्ठा percpu_counter stat[NR_WB_STAT_ITEMS];

	अचिन्हित दीर्घ congested;	/* WB_[a]sync_congested flags */

	अचिन्हित दीर्घ bw_समय_stamp;	/* last समय ग_लिखो bw is updated */
	अचिन्हित दीर्घ dirtied_stamp;
	अचिन्हित दीर्घ written_stamp;	/* pages written at bw_समय_stamp */
	अचिन्हित दीर्घ ग_लिखो_bandwidth;	/* the estimated ग_लिखो bandwidth */
	अचिन्हित दीर्घ avg_ग_लिखो_bandwidth; /* further smoothed ग_लिखो bw, > 0 */

	/*
	 * The base dirty throttle rate, re-calculated on every 200ms.
	 * All the bdi tasks' dirty rate will be curbed under it.
	 * @dirty_ratelimit tracks the estimated @balanced_dirty_ratelimit
	 * in small steps and is much more smooth/stable than the latter.
	 */
	अचिन्हित दीर्घ dirty_ratelimit;
	अचिन्हित दीर्घ balanced_dirty_ratelimit;

	काष्ठा fprop_local_percpu completions;
	पूर्णांक dirty_exceeded;
	क्रमागत wb_reason start_all_reason;

	spinlock_t work_lock;		/* protects work_list & dwork scheduling */
	काष्ठा list_head work_list;
	काष्ठा delayed_work dwork;	/* work item used क्रम ग_लिखोback */

	अचिन्हित दीर्घ dirty_sleep;	/* last रुको */

	काष्ठा list_head bdi_node;	/* anchored at bdi->wb_list */

#अगर_घोषित CONFIG_CGROUP_WRITEBACK
	काष्ठा percpu_ref refcnt;	/* used only क्रम !root wb's */
	काष्ठा fprop_local_percpu memcg_completions;
	काष्ठा cgroup_subsys_state *memcg_css; /* the associated memcg */
	काष्ठा cgroup_subsys_state *blkcg_css; /* and blkcg */
	काष्ठा list_head memcg_node;	/* anchored at memcg->cgwb_list */
	काष्ठा list_head blkcg_node;	/* anchored at blkcg->cgwb_list */

	जोड़ अणु
		काष्ठा work_काष्ठा release_work;
		काष्ठा rcu_head rcu;
	पूर्ण;
#पूर्ण_अगर
पूर्ण;

काष्ठा backing_dev_info अणु
	u64 id;
	काष्ठा rb_node rb_node; /* keyed by ->id */
	काष्ठा list_head bdi_list;
	अचिन्हित दीर्घ ra_pages;	/* max पढ़ोahead in PAGE_SIZE units */
	अचिन्हित दीर्घ io_pages;	/* max allowed IO size */

	काष्ठा kref refcnt;	/* Reference counter क्रम the काष्ठाure */
	अचिन्हित पूर्णांक capabilities; /* Device capabilities */
	अचिन्हित पूर्णांक min_ratio;
	अचिन्हित पूर्णांक max_ratio, max_prop_frac;

	/*
	 * Sum of avg_ग_लिखो_bw of wbs with dirty inodes.  > 0 अगर there are
	 * any dirty wbs, which is depended upon by bdi_has_dirty().
	 */
	atomic_दीर्घ_t tot_ग_लिखो_bandwidth;

	काष्ठा bdi_ग_लिखोback wb;  /* the root ग_लिखोback info क्रम this bdi */
	काष्ठा list_head wb_list; /* list of all wbs */
#अगर_घोषित CONFIG_CGROUP_WRITEBACK
	काष्ठा radix_tree_root cgwb_tree; /* radix tree of active cgroup wbs */
	काष्ठा mutex cgwb_release_mutex;  /* protect shutकरोwn of wb काष्ठाs */
	काष्ठा rw_semaphore wb_चयन_rwsem; /* no cgwb चयन जबतक syncing */
#पूर्ण_अगर
	रुको_queue_head_t wb_रुकोq;

	काष्ठा device *dev;
	अक्षर dev_name[64];
	काष्ठा device *owner;

	काष्ठा समयr_list laptop_mode_wb_समयr;

#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *debug_dir;
#पूर्ण_अगर
पूर्ण;

क्रमागत अणु
	BLK_RW_ASYNC	= 0,
	BLK_RW_SYNC	= 1,
पूर्ण;

व्योम clear_bdi_congested(काष्ठा backing_dev_info *bdi, पूर्णांक sync);
व्योम set_bdi_congested(काष्ठा backing_dev_info *bdi, पूर्णांक sync);

काष्ठा wb_lock_cookie अणु
	bool locked;
	अचिन्हित दीर्घ flags;
पूर्ण;

#अगर_घोषित CONFIG_CGROUP_WRITEBACK

/**
 * wb_tryget - try to increment a wb's refcount
 * @wb: bdi_ग_लिखोback to get
 */
अटल अंतरभूत bool wb_tryget(काष्ठा bdi_ग_लिखोback *wb)
अणु
	अगर (wb != &wb->bdi->wb)
		वापस percpu_ref_tryget(&wb->refcnt);
	वापस true;
पूर्ण

/**
 * wb_get - increment a wb's refcount
 * @wb: bdi_ग_लिखोback to get
 */
अटल अंतरभूत व्योम wb_get(काष्ठा bdi_ग_लिखोback *wb)
अणु
	अगर (wb != &wb->bdi->wb)
		percpu_ref_get(&wb->refcnt);
पूर्ण

/**
 * wb_put - decrement a wb's refcount
 * @wb: bdi_ग_लिखोback to put
 */
अटल अंतरभूत व्योम wb_put(काष्ठा bdi_ग_लिखोback *wb)
अणु
	अगर (WARN_ON_ONCE(!wb->bdi)) अणु
		/*
		 * A driver bug might cause a file to be हटाओd beक्रमe bdi was
		 * initialized.
		 */
		वापस;
	पूर्ण

	अगर (wb != &wb->bdi->wb)
		percpu_ref_put(&wb->refcnt);
पूर्ण

/**
 * wb_dying - is a wb dying?
 * @wb: bdi_ग_लिखोback of पूर्णांकerest
 *
 * Returns whether @wb is unlinked and being drained.
 */
अटल अंतरभूत bool wb_dying(काष्ठा bdi_ग_लिखोback *wb)
अणु
	वापस percpu_ref_is_dying(&wb->refcnt);
पूर्ण

#अन्यथा	/* CONFIG_CGROUP_WRITEBACK */

अटल अंतरभूत bool wb_tryget(काष्ठा bdi_ग_लिखोback *wb)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत व्योम wb_get(काष्ठा bdi_ग_लिखोback *wb)
अणु
पूर्ण

अटल अंतरभूत व्योम wb_put(काष्ठा bdi_ग_लिखोback *wb)
अणु
पूर्ण

अटल अंतरभूत bool wb_dying(काष्ठा bdi_ग_लिखोback *wb)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर	/* CONFIG_CGROUP_WRITEBACK */

#पूर्ण_अगर	/* __LINUX_BACKING_DEV_DEFS_H */
