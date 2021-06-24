<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/cgroup-defs.h - basic definitions क्रम cgroup
 *
 * This file provides basic type and पूर्णांकerface.  Include this file directly
 * only अगर necessary to aव्योम cyclic dependencies.
 */
#अगर_अघोषित _LINUX_CGROUP_DEFS_H
#घोषणा _LINUX_CGROUP_DEFS_H

#समावेश <linux/सीमा.स>
#समावेश <linux/list.h>
#समावेश <linux/idr.h>
#समावेश <linux/रुको.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/refcount.h>
#समावेश <linux/percpu-refcount.h>
#समावेश <linux/percpu-rwsem.h>
#समावेश <linux/u64_stats_sync.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/bpf-cgroup.h>
#समावेश <linux/psi_types.h>

#अगर_घोषित CONFIG_CGROUPS

काष्ठा cgroup;
काष्ठा cgroup_root;
काष्ठा cgroup_subsys;
काष्ठा cgroup_taskset;
काष्ठा kernfs_node;
काष्ठा kernfs_ops;
काष्ठा kernfs_खोलो_file;
काष्ठा seq_file;
काष्ठा poll_table_काष्ठा;

#घोषणा MAX_CGROUP_TYPE_NAMELEN 32
#घोषणा MAX_CGROUP_ROOT_NAMELEN 64
#घोषणा MAX_CFTYPE_NAME		64

/* define the क्रमागतeration of all cgroup subप्रणालीs */
#घोषणा SUBSYS(_x) _x ## _cgrp_id,
क्रमागत cgroup_subsys_id अणु
#समावेश <linux/cgroup_subsys.h>
	CGROUP_SUBSYS_COUNT,
पूर्ण;
#अघोषित SUBSYS

/* bits in काष्ठा cgroup_subsys_state flags field */
क्रमागत अणु
	CSS_NO_REF	= (1 << 0), /* no reference counting क्रम this css */
	CSS_ONLINE	= (1 << 1), /* between ->css_online() and ->css_offline() */
	CSS_RELEASED	= (1 << 2), /* refcnt reached zero, released */
	CSS_VISIBLE	= (1 << 3), /* css is visible to userland */
	CSS_DYING	= (1 << 4), /* css is dying */
पूर्ण;

/* bits in काष्ठा cgroup flags field */
क्रमागत अणु
	/* Control Group requires release notअगरications to userspace */
	CGRP_NOTIFY_ON_RELEASE,
	/*
	 * Clone the parent's configuration when creating a new child
	 * cpuset cgroup.  For historical reasons, this option can be
	 * specअगरied at mount समय and thus is implemented here.
	 */
	CGRP_CPUSET_CLONE_CHILDREN,

	/* Control group has to be frozen. */
	CGRP_FREEZE,

	/* Cgroup is frozen. */
	CGRP_FROZEN,
पूर्ण;

/* cgroup_root->flags */
क्रमागत अणु
	CGRP_ROOT_NOPREFIX	= (1 << 1), /* mounted subप्रणालीs have no named prefix */
	CGRP_ROOT_XATTR		= (1 << 2), /* supports extended attributes */

	/*
	 * Consider namespaces as delegation boundaries.  If this flag is
	 * set, controller specअगरic पूर्णांकerface files in a namespace root
	 * aren't ग_लिखोable from inside the namespace.
	 */
	CGRP_ROOT_NS_DELEGATE	= (1 << 3),

	/*
	 * Enable cpuset controller in v1 cgroup to use v2 behavior.
	 */
	CGRP_ROOT_CPUSET_V2_MODE = (1 << 4),

	/*
	 * Enable legacy local memory.events.
	 */
	CGRP_ROOT_MEMORY_LOCAL_EVENTS = (1 << 5),

	/*
	 * Enable recursive subtree protection
	 */
	CGRP_ROOT_MEMORY_RECURSIVE_PROT = (1 << 6),
पूर्ण;

/* cftype->flags */
क्रमागत अणु
	CFTYPE_ONLY_ON_ROOT	= (1 << 0),	/* only create on root cgrp */
	CFTYPE_NOT_ON_ROOT	= (1 << 1),	/* करोn't create on root cgrp */
	CFTYPE_NS_DELEGATABLE	= (1 << 2),	/* ग_लिखोable beyond delegation boundaries */

	CFTYPE_NO_PREFIX	= (1 << 3),	/* (DON'T USE FOR NEW खाताS) no subsys prefix */
	CFTYPE_WORLD_WRITABLE	= (1 << 4),	/* (DON'T USE FOR NEW खाताS) S_IWUGO */
	CFTYPE_DEBUG		= (1 << 5),	/* create when cgroup_debug */

	/* पूर्णांकernal flags, करो not use outside cgroup core proper */
	__CFTYPE_ONLY_ON_DFL	= (1 << 16),	/* only on शेष hierarchy */
	__CFTYPE_NOT_ON_DFL	= (1 << 17),	/* not on शेष hierarchy */
पूर्ण;

/*
 * cgroup_file is the handle क्रम a file instance created in a cgroup which
 * is used, क्रम example, to generate file changed notअगरications.  This can
 * be obtained by setting cftype->file_offset.
 */
काष्ठा cgroup_file अणु
	/* करो not access any fields from outside cgroup core */
	काष्ठा kernfs_node *kn;
	अचिन्हित दीर्घ notअगरied_at;
	काष्ठा समयr_list notअगरy_समयr;
पूर्ण;

/*
 * Per-subप्रणाली/per-cgroup state मुख्यtained by the प्रणाली.  This is the
 * fundamental काष्ठाural building block that controllers deal with.
 *
 * Fields marked with "PI:" are खुला and immutable and may be accessed
 * directly without synchronization.
 */
काष्ठा cgroup_subsys_state अणु
	/* PI: the cgroup that this css is attached to */
	काष्ठा cgroup *cgroup;

	/* PI: the cgroup subप्रणाली that this css is attached to */
	काष्ठा cgroup_subsys *ss;

	/* reference count - access via css_[try]get() and css_put() */
	काष्ठा percpu_ref refcnt;

	/* siblings list anchored at the parent's ->children */
	काष्ठा list_head sibling;
	काष्ठा list_head children;

	/* flush target list anchored at cgrp->rstat_css_list */
	काष्ठा list_head rstat_css_node;

	/*
	 * PI: Subsys-unique ID.  0 is unused and root is always 1.  The
	 * matching css can be looked up using css_from_id().
	 */
	पूर्णांक id;

	अचिन्हित पूर्णांक flags;

	/*
	 * Monotonically increasing unique serial number which defines a
	 * unअगरorm order among all csses.  It's guaranteed that all
	 * ->children lists are in the ascending order of ->serial_nr and
	 * used to allow पूर्णांकerrupting and resuming iterations.
	 */
	u64 serial_nr;

	/*
	 * Incremented by online self and children.  Used to guarantee that
	 * parents are not offlined beक्रमe their children.
	 */
	atomic_t online_cnt;

	/* percpu_ref समाप्तing and RCU release */
	काष्ठा work_काष्ठा destroy_work;
	काष्ठा rcu_work destroy_rwork;

	/*
	 * PI: the parent css.	Placed here क्रम cache proximity to following
	 * fields of the containing काष्ठाure.
	 */
	काष्ठा cgroup_subsys_state *parent;
पूर्ण;

/*
 * A css_set is a काष्ठाure holding poपूर्णांकers to a set of
 * cgroup_subsys_state objects. This saves space in the task काष्ठा
 * object and speeds up विभाजन()/निकास(), since a single inc/dec and a
 * list_add()/del() can bump the reference count on the entire cgroup
 * set क्रम a task.
 */
काष्ठा css_set अणु
	/*
	 * Set of subप्रणाली states, one क्रम each subप्रणाली. This array is
	 * immutable after creation apart from the init_css_set during
	 * subप्रणाली registration (at boot समय).
	 */
	काष्ठा cgroup_subsys_state *subsys[CGROUP_SUBSYS_COUNT];

	/* reference count */
	refcount_t refcount;

	/*
	 * For a करोमुख्य cgroup, the following poपूर्णांकs to self.  If thपढ़ोed,
	 * to the matching cset of the nearest करोमुख्य ancestor.  The
	 * करोm_cset provides access to the करोमुख्य cgroup and its csses to
	 * which करोमुख्य level resource consumptions should be अक्षरged.
	 */
	काष्ठा css_set *करोm_cset;

	/* the शेष cgroup associated with this css_set */
	काष्ठा cgroup *dfl_cgrp;

	/* पूर्णांकernal task count, रक्षित by css_set_lock */
	पूर्णांक nr_tasks;

	/*
	 * Lists running through all tasks using this cgroup group.
	 * mg_tasks lists tasks which beदीर्घ to this cset but are in the
	 * process of being migrated out or in.  Protected by
	 * css_set_rwsem, but, during migration, once tasks are moved to
	 * mg_tasks, it can be पढ़ो safely जबतक holding cgroup_mutex.
	 */
	काष्ठा list_head tasks;
	काष्ठा list_head mg_tasks;
	काष्ठा list_head dying_tasks;

	/* all css_task_iters currently walking this cset */
	काष्ठा list_head task_iters;

	/*
	 * On the शेष hierarchy, ->subsys[ssid] may poपूर्णांक to a css
	 * attached to an ancestor instead of the cgroup this css_set is
	 * associated with.  The following node is anchored at
	 * ->subsys[ssid]->cgroup->e_csets[ssid] and provides a way to
	 * iterate through all css's attached to a given cgroup.
	 */
	काष्ठा list_head e_cset_node[CGROUP_SUBSYS_COUNT];

	/* all thपढ़ोed csets whose ->करोm_cset poपूर्णांकs to this cset */
	काष्ठा list_head thपढ़ोed_csets;
	काष्ठा list_head thपढ़ोed_csets_node;

	/*
	 * List running through all cgroup groups in the same hash
	 * slot. Protected by css_set_lock
	 */
	काष्ठा hlist_node hlist;

	/*
	 * List of cgrp_cset_links poपूर्णांकing at cgroups referenced from this
	 * css_set.  Protected by css_set_lock.
	 */
	काष्ठा list_head cgrp_links;

	/*
	 * List of csets participating in the on-going migration either as
	 * source or destination.  Protected by cgroup_mutex.
	 */
	काष्ठा list_head mg_preload_node;
	काष्ठा list_head mg_node;

	/*
	 * If this cset is acting as the source of migration the following
	 * two fields are set.  mg_src_cgrp and mg_dst_cgrp are
	 * respectively the source and destination cgroups of the on-going
	 * migration.  mg_dst_cset is the destination cset the target tasks
	 * on this cset should be migrated to.  Protected by cgroup_mutex.
	 */
	काष्ठा cgroup *mg_src_cgrp;
	काष्ठा cgroup *mg_dst_cgrp;
	काष्ठा css_set *mg_dst_cset;

	/* dead and being drained, ignore क्रम migration */
	bool dead;

	/* For RCU-रक्षित deletion */
	काष्ठा rcu_head rcu_head;
पूर्ण;

काष्ठा cgroup_base_stat अणु
	काष्ठा task_cpuसमय cpuसमय;
पूर्ण;

/*
 * rstat - cgroup scalable recursive statistics.  Accounting is करोne
 * per-cpu in cgroup_rstat_cpu which is then lazily propagated up the
 * hierarchy on पढ़ोs.
 *
 * When a stat माला_लो updated, the cgroup_rstat_cpu and its ancestors are
 * linked पूर्णांकo the updated tree.  On the following पढ़ो, propagation only
 * considers and consumes the updated tree.  This makes पढ़ोing O(the
 * number of descendants which have been active since last पढ़ो) instead of
 * O(the total number of descendants).
 *
 * This is important because there can be a lot of (draining) cgroups which
 * aren't active and stat may be पढ़ो frequently.  The combination can
 * become very expensive.  By propagating selectively, increasing पढ़ोing
 * frequency decreases the cost of each पढ़ो.
 *
 * This काष्ठा hosts both the fields which implement the above -
 * updated_children and updated_next - and the fields which track basic
 * resource statistics on top of it - bsync, bstat and last_bstat.
 */
काष्ठा cgroup_rstat_cpu अणु
	/*
	 * ->bsync protects ->bstat.  These are the only fields which get
	 * updated in the hot path.
	 */
	काष्ठा u64_stats_sync bsync;
	काष्ठा cgroup_base_stat bstat;

	/*
	 * Snapshots at the last पढ़ोing.  These are used to calculate the
	 * deltas to propagate to the global counters.
	 */
	काष्ठा cgroup_base_stat last_bstat;

	/*
	 * Child cgroups with stat updates on this cpu since the last पढ़ो
	 * are linked on the parent's ->updated_children through
	 * ->updated_next.
	 *
	 * In addition to being more compact, singly-linked list poपूर्णांकing
	 * to the cgroup makes it unnecessary क्रम each per-cpu काष्ठा to
	 * poपूर्णांक back to the associated cgroup.
	 *
	 * Protected by per-cpu cgroup_rstat_cpu_lock.
	 */
	काष्ठा cgroup *updated_children;	/* terminated by self cgroup */
	काष्ठा cgroup *updated_next;		/* शून्य अगरf not on the list */
पूर्ण;

काष्ठा cgroup_मुक्तzer_state अणु
	/* Should the cgroup and its descendants be frozen. */
	bool मुक्तze;

	/* Should the cgroup actually be frozen? */
	पूर्णांक e_मुक्तze;

	/* Fields below are रक्षित by css_set_lock */

	/* Number of frozen descendant cgroups */
	पूर्णांक nr_frozen_descendants;

	/*
	 * Number of tasks, which are counted as frozen:
	 * frozen, SIGSTOPped, and PTRACEd.
	 */
	पूर्णांक nr_frozen_tasks;
पूर्ण;

काष्ठा cgroup अणु
	/* self css with शून्य ->ss, poपूर्णांकs back to this cgroup */
	काष्ठा cgroup_subsys_state self;

	अचिन्हित दीर्घ flags;		/* "unsigned long" so bitops work */

	/*
	 * The depth this cgroup is at.  The root is at depth zero and each
	 * step करोwn the hierarchy increments the level.  This aदीर्घ with
	 * ancestor_ids[] can determine whether a given cgroup is a
	 * descendant of another without traversing the hierarchy.
	 */
	पूर्णांक level;

	/* Maximum allowed descent tree depth */
	पूर्णांक max_depth;

	/*
	 * Keep track of total numbers of visible and dying descent cgroups.
	 * Dying cgroups are cgroups which were deleted by a user,
	 * but are still existing because someone अन्यथा is holding a reference.
	 * max_descendants is a maximum allowed number of descent cgroups.
	 *
	 * nr_descendants and nr_dying_descendants are रक्षित
	 * by cgroup_mutex and css_set_lock. It's fine to पढ़ो them holding
	 * any of cgroup_mutex and css_set_lock; क्रम writing both locks
	 * should be held.
	 */
	पूर्णांक nr_descendants;
	पूर्णांक nr_dying_descendants;
	पूर्णांक max_descendants;

	/*
	 * Each non-empty css_set associated with this cgroup contributes
	 * one to nr_populated_csets.  The counter is zero अगरf this cgroup
	 * करोesn't have any tasks.
	 *
	 * All children which have non-zero nr_populated_csets and/or
	 * nr_populated_children of their own contribute one to either
	 * nr_populated_करोमुख्य_children or nr_populated_thपढ़ोed_children
	 * depending on their type.  Each counter is zero अगरf all cgroups
	 * of the type in the subtree proper करोn't have any tasks.
	 */
	पूर्णांक nr_populated_csets;
	पूर्णांक nr_populated_करोमुख्य_children;
	पूर्णांक nr_populated_thपढ़ोed_children;

	पूर्णांक nr_thपढ़ोed_children;	/* # of live thपढ़ोed child cgroups */

	काष्ठा kernfs_node *kn;		/* cgroup kernfs entry */
	काष्ठा cgroup_file procs_file;	/* handle क्रम "cgroup.procs" */
	काष्ठा cgroup_file events_file;	/* handle क्रम "cgroup.events" */

	/*
	 * The biपंचांगask of subप्रणालीs enabled on the child cgroups.
	 * ->subtree_control is the one configured through
	 * "cgroup.subtree_control" जबतक ->child_ss_mask is the effective
	 * one which may have more subप्रणालीs enabled.  Controller knobs
	 * are made available अगरf it's enabled in ->subtree_control.
	 */
	u16 subtree_control;
	u16 subtree_ss_mask;
	u16 old_subtree_control;
	u16 old_subtree_ss_mask;

	/* Private poपूर्णांकers क्रम each रेजिस्टरed subप्रणाली */
	काष्ठा cgroup_subsys_state __rcu *subsys[CGROUP_SUBSYS_COUNT];

	काष्ठा cgroup_root *root;

	/*
	 * List of cgrp_cset_links poपूर्णांकing at css_sets with tasks in this
	 * cgroup.  Protected by css_set_lock.
	 */
	काष्ठा list_head cset_links;

	/*
	 * On the शेष hierarchy, a css_set क्रम a cgroup with some
	 * susbsys disabled will poपूर्णांक to css's which are associated with
	 * the बंदst ancestor which has the subsys enabled.  The
	 * following lists all css_sets which poपूर्णांक to this cgroup's css
	 * क्रम the given subप्रणाली.
	 */
	काष्ठा list_head e_csets[CGROUP_SUBSYS_COUNT];

	/*
	 * If !thपढ़ोed, self.  If thपढ़ोed, it poपूर्णांकs to the nearest
	 * करोमुख्य ancestor.  Inside a thपढ़ोed subtree, cgroups are exempt
	 * from process granularity and no-पूर्णांकernal-task स्थिरraपूर्णांक.
	 * Doमुख्य level resource consumptions which aren't tied to a
	 * specअगरic task are अक्षरged to the करोm_cgrp.
	 */
	काष्ठा cgroup *करोm_cgrp;
	काष्ठा cgroup *old_करोm_cgrp;		/* used जबतक enabling thपढ़ोed */

	/* per-cpu recursive resource statistics */
	काष्ठा cgroup_rstat_cpu __percpu *rstat_cpu;
	काष्ठा list_head rstat_css_list;

	/* cgroup basic resource statistics */
	काष्ठा cgroup_base_stat last_bstat;
	काष्ठा cgroup_base_stat bstat;
	काष्ठा prev_cpuसमय prev_cpuसमय;	/* क्रम prपूर्णांकing out cpuसमय */

	/*
	 * list of pidlists, up to two क्रम each namespace (one क्रम procs, one
	 * क्रम tasks); created on demand.
	 */
	काष्ठा list_head pidlists;
	काष्ठा mutex pidlist_mutex;

	/* used to रुको क्रम offlining of csses */
	रुको_queue_head_t offline_रुकोq;

	/* used to schedule release agent */
	काष्ठा work_काष्ठा release_agent_work;

	/* used to track pressure stalls */
	काष्ठा psi_group psi;

	/* used to store eBPF programs */
	काष्ठा cgroup_bpf bpf;

	/* If there is block congestion on this cgroup. */
	atomic_t congestion_count;

	/* Used to store पूर्णांकernal मुक्तzer state */
	काष्ठा cgroup_मुक्तzer_state मुक्तzer;

	/* ids of the ancestors at each level including self */
	u64 ancestor_ids[];
पूर्ण;

/*
 * A cgroup_root represents the root of a cgroup hierarchy, and may be
 * associated with a kernfs_root to क्रमm an active hierarchy.  This is
 * पूर्णांकernal to cgroup core.  Don't access directly from controllers.
 */
काष्ठा cgroup_root अणु
	काष्ठा kernfs_root *kf_root;

	/* The biपंचांगask of subप्रणालीs attached to this hierarchy */
	अचिन्हित पूर्णांक subsys_mask;

	/* Unique id क्रम this hierarchy. */
	पूर्णांक hierarchy_id;

	/* The root cgroup.  Root is destroyed on its release. */
	काष्ठा cgroup cgrp;

	/* क्रम cgrp->ancestor_ids[0] */
	u64 cgrp_ancestor_id_storage;

	/* Number of cgroups in the hierarchy, used only क्रम /proc/cgroups */
	atomic_t nr_cgrps;

	/* A list running through the active hierarchies */
	काष्ठा list_head root_list;

	/* Hierarchy-specअगरic flags */
	अचिन्हित पूर्णांक flags;

	/* The path to use क्रम release notअगरications. */
	अक्षर release_agent_path[PATH_MAX];

	/* The name क्रम this hierarchy - may be empty */
	अक्षर name[MAX_CGROUP_ROOT_NAMELEN];
पूर्ण;

/*
 * काष्ठा cftype: handler definitions क्रम cgroup control files
 *
 * When पढ़ोing/writing to a file:
 *	- the cgroup to use is file->f_path.dentry->d_parent->d_fsdata
 *	- the 'cftype' of the file is file->f_path.dentry->d_fsdata
 */
काष्ठा cftype अणु
	/*
	 * By convention, the name should begin with the name of the
	 * subप्रणाली, followed by a period.  Zero length string indicates
	 * end of cftype array.
	 */
	अक्षर name[MAX_CFTYPE_NAME];
	अचिन्हित दीर्घ निजी;

	/*
	 * The maximum length of string, excluding trailing nul, that can
	 * be passed to ग_लिखो.  If < PAGE_SIZE-1, PAGE_SIZE-1 is assumed.
	 */
	माप_प्रकार max_ग_लिखो_len;

	/* CFTYPE_* flags */
	अचिन्हित पूर्णांक flags;

	/*
	 * If non-zero, should contain the offset from the start of css to
	 * a काष्ठा cgroup_file field.  cgroup will record the handle of
	 * the created file पूर्णांकo it.  The recorded handle can be used as
	 * दीर्घ as the containing css reमुख्यs accessible.
	 */
	अचिन्हित पूर्णांक file_offset;

	/*
	 * Fields used क्रम पूर्णांकernal bookkeeping.  Initialized स्वतःmatically
	 * during registration.
	 */
	काष्ठा cgroup_subsys *ss;	/* शून्य क्रम cgroup core files */
	काष्ठा list_head node;		/* anchored at ss->cfts */
	काष्ठा kernfs_ops *kf_ops;

	पूर्णांक (*खोलो)(काष्ठा kernfs_खोलो_file *of);
	व्योम (*release)(काष्ठा kernfs_खोलो_file *of);

	/*
	 * पढ़ो_u64() is a लघुcut क्रम the common हाल of वापसing a
	 * single पूर्णांकeger. Use it in place of पढ़ो()
	 */
	u64 (*पढ़ो_u64)(काष्ठा cgroup_subsys_state *css, काष्ठा cftype *cft);
	/*
	 * पढ़ो_s64() is a चिन्हित version of पढ़ो_u64()
	 */
	s64 (*पढ़ो_s64)(काष्ठा cgroup_subsys_state *css, काष्ठा cftype *cft);

	/* generic seq_file पढ़ो पूर्णांकerface */
	पूर्णांक (*seq_show)(काष्ठा seq_file *sf, व्योम *v);

	/* optional ops, implement all or none */
	व्योम *(*seq_start)(काष्ठा seq_file *sf, loff_t *ppos);
	व्योम *(*seq_next)(काष्ठा seq_file *sf, व्योम *v, loff_t *ppos);
	व्योम (*seq_stop)(काष्ठा seq_file *sf, व्योम *v);

	/*
	 * ग_लिखो_u64() is a लघुcut क्रम the common हाल of accepting
	 * a single पूर्णांकeger (as parsed by simple_म_से_अदीर्घl) from
	 * userspace. Use in place of ग_लिखो(); वापस 0 or error.
	 */
	पूर्णांक (*ग_लिखो_u64)(काष्ठा cgroup_subsys_state *css, काष्ठा cftype *cft,
			 u64 val);
	/*
	 * ग_लिखो_s64() is a चिन्हित version of ग_लिखो_u64()
	 */
	पूर्णांक (*ग_लिखो_s64)(काष्ठा cgroup_subsys_state *css, काष्ठा cftype *cft,
			 s64 val);

	/*
	 * ग_लिखो() is the generic ग_लिखो callback which maps directly to
	 * kernfs ग_लिखो operation and overrides all other operations.
	 * Maximum ग_लिखो size is determined by ->max_ग_लिखो_len.  Use
	 * of_css/cft() to access the associated css and cft.
	 */
	sमाप_प्रकार (*ग_लिखो)(काष्ठा kernfs_खोलो_file *of,
			 अक्षर *buf, माप_प्रकार nbytes, loff_t off);

	__poll_t (*poll)(काष्ठा kernfs_खोलो_file *of,
			 काष्ठा poll_table_काष्ठा *pt);

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	काष्ठा lock_class_key	lockdep_key;
#पूर्ण_अगर
पूर्ण;

/*
 * Control Group subप्रणाली type.
 * See Documentation/admin-guide/cgroup-v1/cgroups.rst क्रम details
 */
काष्ठा cgroup_subsys अणु
	काष्ठा cgroup_subsys_state *(*css_alloc)(काष्ठा cgroup_subsys_state *parent_css);
	पूर्णांक (*css_online)(काष्ठा cgroup_subsys_state *css);
	व्योम (*css_offline)(काष्ठा cgroup_subsys_state *css);
	व्योम (*css_released)(काष्ठा cgroup_subsys_state *css);
	व्योम (*css_मुक्त)(काष्ठा cgroup_subsys_state *css);
	व्योम (*css_reset)(काष्ठा cgroup_subsys_state *css);
	व्योम (*css_rstat_flush)(काष्ठा cgroup_subsys_state *css, पूर्णांक cpu);
	पूर्णांक (*css_extra_stat_show)(काष्ठा seq_file *seq,
				   काष्ठा cgroup_subsys_state *css);

	पूर्णांक (*can_attach)(काष्ठा cgroup_taskset *tset);
	व्योम (*cancel_attach)(काष्ठा cgroup_taskset *tset);
	व्योम (*attach)(काष्ठा cgroup_taskset *tset);
	व्योम (*post_attach)(व्योम);
	पूर्णांक (*can_विभाजन)(काष्ठा task_काष्ठा *task,
			काष्ठा css_set *cset);
	व्योम (*cancel_विभाजन)(काष्ठा task_काष्ठा *task, काष्ठा css_set *cset);
	व्योम (*विभाजन)(काष्ठा task_काष्ठा *task);
	व्योम (*निकास)(काष्ठा task_काष्ठा *task);
	व्योम (*release)(काष्ठा task_काष्ठा *task);
	व्योम (*bind)(काष्ठा cgroup_subsys_state *root_css);

	bool early_init:1;

	/*
	 * If %true, the controller, on the शेष hierarchy, करोesn't show
	 * up in "cgroup.controllers" or "cgroup.subtree_control", is
	 * implicitly enabled on all cgroups on the शेष hierarchy, and
	 * bypasses the "no internal process" स्थिरraपूर्णांक.  This is क्रम
	 * utility type controllers which is transparent to userland.
	 *
	 * An implicit controller can be stolen from the शेष hierarchy
	 * anyसमय and thus must be okay with offline csses from previous
	 * hierarchies coexisting with csses क्रम the current one.
	 */
	bool implicit_on_dfl:1;

	/*
	 * If %true, the controller, supports thपढ़ोed mode on the शेष
	 * hierarchy.  In a thपढ़ोed subtree, both process granularity and
	 * no-पूर्णांकernal-process स्थिरraपूर्णांक are ignored and a thपढ़ोed
	 * controllers should be able to handle that.
	 *
	 * Note that as an implicit controller is स्वतःmatically enabled on
	 * all cgroups on the शेष hierarchy, it should also be
	 * thपढ़ोed.  implicit && !thपढ़ोed is not supported.
	 */
	bool thपढ़ोed:1;

	/* the following two fields are initialized स्वतःmatically during boot */
	पूर्णांक id;
	स्थिर अक्षर *name;

	/* optional, initialized स्वतःmatically during boot अगर not set */
	स्थिर अक्षर *legacy_name;

	/* link to parent, रक्षित by cgroup_lock() */
	काष्ठा cgroup_root *root;

	/* idr क्रम css->id */
	काष्ठा idr css_idr;

	/*
	 * List of cftypes.  Each entry is the first entry of an array
	 * terminated by zero length name.
	 */
	काष्ठा list_head cfts;

	/*
	 * Base cftypes which are स्वतःmatically रेजिस्टरed.  The two can
	 * poपूर्णांक to the same array.
	 */
	काष्ठा cftype *dfl_cftypes;	/* क्रम the शेष hierarchy */
	काष्ठा cftype *legacy_cftypes;	/* क्रम the legacy hierarchies */

	/*
	 * A subप्रणाली may depend on other subप्रणालीs.  When such subप्रणाली
	 * is enabled on a cgroup, the depended-upon subप्रणालीs are enabled
	 * together अगर available.  Subप्रणालीs enabled due to dependency are
	 * not visible to userland until explicitly enabled.  The following
	 * specअगरies the mask of subप्रणालीs that this one depends on.
	 */
	अचिन्हित पूर्णांक depends_on;
पूर्ण;

बाह्य काष्ठा percpu_rw_semaphore cgroup_thपढ़ोgroup_rwsem;

/**
 * cgroup_thपढ़ोgroup_change_begin - thपढ़ोgroup exclusion क्रम cgroups
 * @tsk: target task
 *
 * Allows cgroup operations to synchronize against thपढ़ोgroup changes
 * using a percpu_rw_semaphore.
 */
अटल अंतरभूत व्योम cgroup_thपढ़ोgroup_change_begin(काष्ठा task_काष्ठा *tsk)
अणु
	percpu_करोwn_पढ़ो(&cgroup_thपढ़ोgroup_rwsem);
पूर्ण

/**
 * cgroup_thपढ़ोgroup_change_end - thपढ़ोgroup exclusion क्रम cgroups
 * @tsk: target task
 *
 * Counterpart of cgroup_thपढ़ोcgroup_change_begin().
 */
अटल अंतरभूत व्योम cgroup_thपढ़ोgroup_change_end(काष्ठा task_काष्ठा *tsk)
अणु
	percpu_up_पढ़ो(&cgroup_thपढ़ोgroup_rwsem);
पूर्ण

#अन्यथा	/* CONFIG_CGROUPS */

#घोषणा CGROUP_SUBSYS_COUNT 0

अटल अंतरभूत व्योम cgroup_thपढ़ोgroup_change_begin(काष्ठा task_काष्ठा *tsk)
अणु
	might_sleep();
पूर्ण

अटल अंतरभूत व्योम cgroup_thपढ़ोgroup_change_end(काष्ठा task_काष्ठा *tsk) अणुपूर्ण

#पूर्ण_अगर	/* CONFIG_CGROUPS */

#अगर_घोषित CONFIG_SOCK_CGROUP_DATA

/*
 * sock_cgroup_data is embedded at sock->sk_cgrp_data and contains
 * per-socket cgroup inक्रमmation except क्रम memcg association.
 *
 * On legacy hierarchies, net_prio and net_cls controllers directly set
 * attributes on each sock which can then be tested by the network layer.
 * On the शेष hierarchy, each sock is associated with the cgroup it was
 * created in and the networking layer can match the cgroup directly.
 *
 * To aव्योम carrying all three cgroup related fields separately in sock,
 * sock_cgroup_data overloads (prioidx, classid) and the cgroup poपूर्णांकer.
 * On boot, sock_cgroup_data records the cgroup that the sock was created
 * in so that cgroup2 matches can be made; however, once either net_prio or
 * net_cls starts being used, the area is overridden to carry prioidx and/or
 * classid.  The two modes are distinguished by whether the lowest bit is
 * set.  Clear bit indicates cgroup poपूर्णांकer जबतक set bit prioidx and
 * classid.
 *
 * While userland may start using net_prio or net_cls at any समय, once
 * either is used, cgroup2 matching no दीर्घer works.  There is no reason to
 * mix the two and this is in line with how legacy and v2 compatibility is
 * handled.  On mode चयन, cgroup references which are alपढ़ोy being
 * poपूर्णांकed to by socks may be leaked.  While this can be remedied by adding
 * synchronization around sock_cgroup_data, given that the number of leaked
 * cgroups is bound and highly unlikely to be high, this seems to be the
 * better trade-off.
 */
काष्ठा sock_cgroup_data अणु
	जोड़ अणु
#अगर_घोषित __LITTLE_ENDIAN
		काष्ठा अणु
			u8	is_data : 1;
			u8	no_refcnt : 1;
			u8	unused : 6;
			u8	padding;
			u16	prioidx;
			u32	classid;
		पूर्ण __packed;
#अन्यथा
		काष्ठा अणु
			u32	classid;
			u16	prioidx;
			u8	padding;
			u8	unused : 6;
			u8	no_refcnt : 1;
			u8	is_data : 1;
		पूर्ण __packed;
#पूर्ण_अगर
		u64		val;
	पूर्ण;
पूर्ण;

/*
 * There's a theoretical winकरोw where the following accessors race with
 * updaters and वापस part of the previous poपूर्णांकer as the prioidx or
 * classid.  Such races are लघु-lived and the result isn't critical.
 */
अटल अंतरभूत u16 sock_cgroup_prioidx(स्थिर काष्ठा sock_cgroup_data *skcd)
अणु
	/* fallback to 1 which is always the ID of the root cgroup */
	वापस (skcd->is_data & 1) ? skcd->prioidx : 1;
पूर्ण

अटल अंतरभूत u32 sock_cgroup_classid(स्थिर काष्ठा sock_cgroup_data *skcd)
अणु
	/* fallback to 0 which is the unconfigured शेष classid */
	वापस (skcd->is_data & 1) ? skcd->classid : 0;
पूर्ण

/*
 * If invoked concurrently, the updaters may clobber each other.  The
 * caller is responsible क्रम synchronization.
 */
अटल अंतरभूत व्योम sock_cgroup_set_prioidx(काष्ठा sock_cgroup_data *skcd,
					   u16 prioidx)
अणु
	काष्ठा sock_cgroup_data skcd_buf = अणुअणु .val = READ_ONCE(skcd->val) पूर्णपूर्ण;

	अगर (sock_cgroup_prioidx(&skcd_buf) == prioidx)
		वापस;

	अगर (!(skcd_buf.is_data & 1)) अणु
		skcd_buf.val = 0;
		skcd_buf.is_data = 1;
	पूर्ण

	skcd_buf.prioidx = prioidx;
	WRITE_ONCE(skcd->val, skcd_buf.val);	/* see sock_cgroup_ptr() */
पूर्ण

अटल अंतरभूत व्योम sock_cgroup_set_classid(काष्ठा sock_cgroup_data *skcd,
					   u32 classid)
अणु
	काष्ठा sock_cgroup_data skcd_buf = अणुअणु .val = READ_ONCE(skcd->val) पूर्णपूर्ण;

	अगर (sock_cgroup_classid(&skcd_buf) == classid)
		वापस;

	अगर (!(skcd_buf.is_data & 1)) अणु
		skcd_buf.val = 0;
		skcd_buf.is_data = 1;
	पूर्ण

	skcd_buf.classid = classid;
	WRITE_ONCE(skcd->val, skcd_buf.val);	/* see sock_cgroup_ptr() */
पूर्ण

#अन्यथा	/* CONFIG_SOCK_CGROUP_DATA */

काष्ठा sock_cgroup_data अणु
पूर्ण;

#पूर्ण_अगर	/* CONFIG_SOCK_CGROUP_DATA */

#पूर्ण_अगर	/* _LINUX_CGROUP_DEFS_H */
