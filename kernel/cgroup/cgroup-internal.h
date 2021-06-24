<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __CGROUP_INTERNAL_H
#घोषणा __CGROUP_INTERNAL_H

#समावेश <linux/cgroup.h>
#समावेश <linux/kernfs.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/list.h>
#समावेश <linux/refcount.h>
#समावेश <linux/fs_parser.h>

#घोषणा TRACE_CGROUP_PATH_LEN 1024
बाह्य spinlock_t trace_cgroup_path_lock;
बाह्य अक्षर trace_cgroup_path[TRACE_CGROUP_PATH_LEN];
बाह्य bool cgroup_debug;
बाह्य व्योम __init enable_debug_cgroup(व्योम);

/*
 * cgroup_path() takes a spin lock. It is good practice not to take
 * spin locks within trace poपूर्णांक handlers, as they are mostly hidden
 * from normal view. As cgroup_path() can take the kernfs_नाम_lock
 * spin lock, it is best to not call that function from the trace event
 * handler.
 *
 * Note: trace_cgroup_##type##_enabled() is a अटल branch that will only
 *       be set when the trace event is enabled.
 */
#घोषणा TRACE_CGROUP_PATH(type, cgrp, ...)				\
	करो अणु								\
		अगर (trace_cgroup_##type##_enabled()) अणु			\
			अचिन्हित दीर्घ flags;				\
			spin_lock_irqsave(&trace_cgroup_path_lock,	\
					  flags);			\
			cgroup_path(cgrp, trace_cgroup_path,		\
				    TRACE_CGROUP_PATH_LEN);		\
			trace_cgroup_##type(cgrp, trace_cgroup_path,	\
					    ##__VA_ARGS__);		\
			spin_unlock_irqrestore(&trace_cgroup_path_lock, \
					       flags);			\
		पूर्ण							\
	पूर्ण जबतक (0)

/*
 * The cgroup fileप्रणाली superblock creation/mount context.
 */
काष्ठा cgroup_fs_context अणु
	काष्ठा kernfs_fs_context kfc;
	काष्ठा cgroup_root	*root;
	काष्ठा cgroup_namespace	*ns;
	अचिन्हित पूर्णांक	flags;			/* CGRP_ROOT_* flags */

	/* cgroup1 bits */
	bool		cpuset_clone_children;
	bool		none;			/* User explicitly requested empty subप्रणाली */
	bool		all_ss;			/* Seen 'all' option */
	u16		subsys_mask;		/* Selected subप्रणालीs */
	अक्षर		*name;			/* Hierarchy name */
	अक्षर		*release_agent;		/* Path क्रम release notअगरications */
पूर्ण;

अटल अंतरभूत काष्ठा cgroup_fs_context *cgroup_fc2context(काष्ठा fs_context *fc)
अणु
	काष्ठा kernfs_fs_context *kfc = fc->fs_निजी;

	वापस container_of(kfc, काष्ठा cgroup_fs_context, kfc);
पूर्ण

/*
 * A cgroup can be associated with multiple css_sets as dअगरferent tasks may
 * beदीर्घ to dअगरferent cgroups on dअगरferent hierarchies.  In the other
 * direction, a css_set is naturally associated with multiple cgroups.
 * This M:N relationship is represented by the following link काष्ठाure
 * which exists क्रम each association and allows traversing the associations
 * from both sides.
 */
काष्ठा cgrp_cset_link अणु
	/* the cgroup and css_set this link associates */
	काष्ठा cgroup		*cgrp;
	काष्ठा css_set		*cset;

	/* list of cgrp_cset_links anchored at cgrp->cset_links */
	काष्ठा list_head	cset_link;

	/* list of cgrp_cset_links anchored at css_set->cgrp_links */
	काष्ठा list_head	cgrp_link;
पूर्ण;

/* used to track tasks and csets during migration */
काष्ठा cgroup_taskset अणु
	/* the src and dst cset list running through cset->mg_node */
	काष्ठा list_head	src_csets;
	काष्ठा list_head	dst_csets;

	/* the number of tasks in the set */
	पूर्णांक			nr_tasks;

	/* the subsys currently being processed */
	पूर्णांक			ssid;

	/*
	 * Fields क्रम cgroup_taskset_*() iteration.
	 *
	 * Beक्रमe migration is committed, the target migration tasks are on
	 * ->mg_tasks of the csets on ->src_csets.  After, on ->mg_tasks of
	 * the csets on ->dst_csets.  ->csets poपूर्णांक to either ->src_csets
	 * or ->dst_csets depending on whether migration is committed.
	 *
	 * ->cur_csets and ->cur_task poपूर्णांक to the current task position
	 * during iteration.
	 */
	काष्ठा list_head	*csets;
	काष्ठा css_set		*cur_cset;
	काष्ठा task_काष्ठा	*cur_task;
पूर्ण;

/* migration context also tracks preloading */
काष्ठा cgroup_mgctx अणु
	/*
	 * Preloaded source and destination csets.  Used to guarantee
	 * atomic success or failure on actual migration.
	 */
	काष्ठा list_head	preloaded_src_csets;
	काष्ठा list_head	preloaded_dst_csets;

	/* tasks and csets to migrate */
	काष्ठा cgroup_taskset	tset;

	/* subप्रणालीs affected by migration */
	u16			ss_mask;
पूर्ण;

#घोषणा CGROUP_TASKSET_INIT(tset)						\
अणु										\
	.src_csets		= LIST_HEAD_INIT(tset.src_csets),		\
	.dst_csets		= LIST_HEAD_INIT(tset.dst_csets),		\
	.csets			= &tset.src_csets,				\
पूर्ण

#घोषणा CGROUP_MGCTX_INIT(name)							\
अणु										\
	LIST_HEAD_INIT(name.preloaded_src_csets),				\
	LIST_HEAD_INIT(name.preloaded_dst_csets),				\
	CGROUP_TASKSET_INIT(name.tset),						\
पूर्ण

#घोषणा DEFINE_CGROUP_MGCTX(name)						\
	काष्ठा cgroup_mgctx name = CGROUP_MGCTX_INIT(name)

बाह्य काष्ठा mutex cgroup_mutex;
बाह्य spinlock_t css_set_lock;
बाह्य काष्ठा cgroup_subsys *cgroup_subsys[];
बाह्य काष्ठा list_head cgroup_roots;
बाह्य काष्ठा file_प्रणाली_type cgroup_fs_type;

/* iterate across the hierarchies */
#घोषणा क्रम_each_root(root)						\
	list_क्रम_each_entry((root), &cgroup_roots, root_list)

/**
 * क्रम_each_subsys - iterate all enabled cgroup subप्रणालीs
 * @ss: the iteration cursor
 * @ssid: the index of @ss, CGROUP_SUBSYS_COUNT after reaching the end
 */
#घोषणा क्रम_each_subsys(ss, ssid)					\
	क्रम ((ssid) = 0; (ssid) < CGROUP_SUBSYS_COUNT &&		\
	     (((ss) = cgroup_subsys[ssid]) || true); (ssid)++)

अटल अंतरभूत bool cgroup_is_dead(स्थिर काष्ठा cgroup *cgrp)
अणु
	वापस !(cgrp->self.flags & CSS_ONLINE);
पूर्ण

अटल अंतरभूत bool notअगरy_on_release(स्थिर काष्ठा cgroup *cgrp)
अणु
	वापस test_bit(CGRP_NOTIFY_ON_RELEASE, &cgrp->flags);
पूर्ण

व्योम put_css_set_locked(काष्ठा css_set *cset);

अटल अंतरभूत व्योम put_css_set(काष्ठा css_set *cset)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * Ensure that the refcount करोesn't hit zero जबतक any पढ़ोers
	 * can see it. Similar to atomic_dec_and_lock(), but क्रम an
	 * rwlock
	 */
	अगर (refcount_dec_not_one(&cset->refcount))
		वापस;

	spin_lock_irqsave(&css_set_lock, flags);
	put_css_set_locked(cset);
	spin_unlock_irqrestore(&css_set_lock, flags);
पूर्ण

/*
 * refcounted get/put क्रम css_set objects
 */
अटल अंतरभूत व्योम get_css_set(काष्ठा css_set *cset)
अणु
	refcount_inc(&cset->refcount);
पूर्ण

bool cgroup_ssid_enabled(पूर्णांक ssid);
bool cgroup_on_dfl(स्थिर काष्ठा cgroup *cgrp);
bool cgroup_is_thपढ़ो_root(काष्ठा cgroup *cgrp);
bool cgroup_is_thपढ़ोed(काष्ठा cgroup *cgrp);

काष्ठा cgroup_root *cgroup_root_from_kf(काष्ठा kernfs_root *kf_root);
काष्ठा cgroup *task_cgroup_from_root(काष्ठा task_काष्ठा *task,
				     काष्ठा cgroup_root *root);
काष्ठा cgroup *cgroup_kn_lock_live(काष्ठा kernfs_node *kn, bool drain_offline);
व्योम cgroup_kn_unlock(काष्ठा kernfs_node *kn);
पूर्णांक cgroup_path_ns_locked(काष्ठा cgroup *cgrp, अक्षर *buf, माप_प्रकार buflen,
			  काष्ठा cgroup_namespace *ns);

व्योम cgroup_मुक्त_root(काष्ठा cgroup_root *root);
व्योम init_cgroup_root(काष्ठा cgroup_fs_context *ctx);
पूर्णांक cgroup_setup_root(काष्ठा cgroup_root *root, u16 ss_mask);
पूर्णांक rebind_subप्रणालीs(काष्ठा cgroup_root *dst_root, u16 ss_mask);
पूर्णांक cgroup_करो_get_tree(काष्ठा fs_context *fc);

पूर्णांक cgroup_migrate_vet_dst(काष्ठा cgroup *dst_cgrp);
व्योम cgroup_migrate_finish(काष्ठा cgroup_mgctx *mgctx);
व्योम cgroup_migrate_add_src(काष्ठा css_set *src_cset, काष्ठा cgroup *dst_cgrp,
			    काष्ठा cgroup_mgctx *mgctx);
पूर्णांक cgroup_migrate_prepare_dst(काष्ठा cgroup_mgctx *mgctx);
पूर्णांक cgroup_migrate(काष्ठा task_काष्ठा *leader, bool thपढ़ोgroup,
		   काष्ठा cgroup_mgctx *mgctx);

पूर्णांक cgroup_attach_task(काष्ठा cgroup *dst_cgrp, काष्ठा task_काष्ठा *leader,
		       bool thपढ़ोgroup);
काष्ठा task_काष्ठा *cgroup_procs_ग_लिखो_start(अक्षर *buf, bool thपढ़ोgroup,
					     bool *locked)
	__acquires(&cgroup_thपढ़ोgroup_rwsem);
व्योम cgroup_procs_ग_लिखो_finish(काष्ठा task_काष्ठा *task, bool locked)
	__releases(&cgroup_thपढ़ोgroup_rwsem);

व्योम cgroup_lock_and_drain_offline(काष्ठा cgroup *cgrp);

पूर्णांक cgroup_सूची_गढ़ो(काष्ठा kernfs_node *parent_kn, स्थिर अक्षर *name, umode_t mode);
पूर्णांक cgroup_सूची_हटाओ(काष्ठा kernfs_node *kn);
पूर्णांक cgroup_show_path(काष्ठा seq_file *sf, काष्ठा kernfs_node *kf_node,
		     काष्ठा kernfs_root *kf_root);

पूर्णांक __cgroup_task_count(स्थिर काष्ठा cgroup *cgrp);
पूर्णांक cgroup_task_count(स्थिर काष्ठा cgroup *cgrp);

/*
 * rstat.c
 */
पूर्णांक cgroup_rstat_init(काष्ठा cgroup *cgrp);
व्योम cgroup_rstat_निकास(काष्ठा cgroup *cgrp);
व्योम cgroup_rstat_boot(व्योम);
व्योम cgroup_base_stat_cpuसमय_show(काष्ठा seq_file *seq);

/*
 * namespace.c
 */
बाह्य स्थिर काष्ठा proc_ns_operations cgroupns_operations;

/*
 * cgroup-v1.c
 */
बाह्य काष्ठा cftype cgroup1_base_files[];
बाह्य काष्ठा kernfs_syscall_ops cgroup1_kf_syscall_ops;
बाह्य स्थिर काष्ठा fs_parameter_spec cgroup1_fs_parameters[];

पूर्णांक proc_cgroupstats_show(काष्ठा seq_file *m, व्योम *v);
bool cgroup1_ssid_disabled(पूर्णांक ssid);
व्योम cgroup1_pidlist_destroy_all(काष्ठा cgroup *cgrp);
व्योम cgroup1_release_agent(काष्ठा work_काष्ठा *work);
व्योम cgroup1_check_क्रम_release(काष्ठा cgroup *cgrp);
पूर्णांक cgroup1_parse_param(काष्ठा fs_context *fc, काष्ठा fs_parameter *param);
पूर्णांक cgroup1_get_tree(काष्ठा fs_context *fc);
पूर्णांक cgroup1_reconfigure(काष्ठा fs_context *ctx);

#पूर्ण_अगर /* __CGROUP_INTERNAL_H */
