<शैली गुरु>
/*
 *  Generic process-grouping प्रणाली.
 *
 *  Based originally on the cpuset प्रणाली, extracted by Paul Menage
 *  Copyright (C) 2006 Google, Inc
 *
 *  Notअगरications support
 *  Copyright (C) 2009 Nokia Corporation
 *  Author: Kirill A. Shutemov
 *
 *  Copyright notices from the original cpuset code:
 *  --------------------------------------------------
 *  Copyright (C) 2003 BULL SA.
 *  Copyright (C) 2004-2006 Silicon Graphics, Inc.
 *
 *  Portions derived from Patrick Mochel's sysfs code.
 *  sysfs is Copyright (c) 2001-3 Patrick Mochel
 *
 *  2003-10-10 Written by Simon Derr.
 *  2003-10-22 Updates by Stephen Hemminger.
 *  2004 May-July Rework by Paul Jackson.
 *  ---------------------------------------------------
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of the Linux
 *  distribution क्रम more details.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "cgroup-internal.h"

#समावेश <linux/cred.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init_task.h>
#समावेश <linux/kernel.h>
#समावेश <linux/magic.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mount.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/percpu-rwsem.h>
#समावेश <linux/माला.स>
#समावेश <linux/hashtable.h>
#समावेश <linux/idr.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/atomic.h>
#समावेश <linux/cpuset.h>
#समावेश <linux/proc_ns.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/file.h>
#समावेश <linux/fs_parser.h>
#समावेश <linux/sched/cpuसमय.स>
#समावेश <linux/psi.h>
#समावेश <net/sock.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/cgroup.h>

#घोषणा CGROUP_खाता_NAME_MAX		(MAX_CGROUP_TYPE_NAMELEN +	\
					 MAX_CFTYPE_NAME + 2)
/* let's not notअगरy more than 100 बार per second */
#घोषणा CGROUP_खाता_NOTIFY_MIN_INTV	DIV_ROUND_UP(HZ, 100)

/*
 * cgroup_mutex is the master lock.  Any modअगरication to cgroup or its
 * hierarchy must be perक्रमmed जबतक holding it.
 *
 * css_set_lock protects task->cgroups poपूर्णांकer, the list of css_set
 * objects, and the chain of tasks off each css_set.
 *
 * These locks are exported अगर CONFIG_PROVE_RCU so that accessors in
 * cgroup.h can use them क्रम lockdep annotations.
 */
DEFINE_MUTEX(cgroup_mutex);
DEFINE_SPINLOCK(css_set_lock);

#अगर_घोषित CONFIG_PROVE_RCU
EXPORT_SYMBOL_GPL(cgroup_mutex);
EXPORT_SYMBOL_GPL(css_set_lock);
#पूर्ण_अगर

DEFINE_SPINLOCK(trace_cgroup_path_lock);
अक्षर trace_cgroup_path[TRACE_CGROUP_PATH_LEN];
bool cgroup_debug __पढ़ो_mostly;

/*
 * Protects cgroup_idr and css_idr so that IDs can be released without
 * grabbing cgroup_mutex.
 */
अटल DEFINE_SPINLOCK(cgroup_idr_lock);

/*
 * Protects cgroup_file->kn क्रम !self csses.  It synchronizes notअगरications
 * against file removal/re-creation across css hiding.
 */
अटल DEFINE_SPINLOCK(cgroup_file_kn_lock);

DEFINE_PERCPU_RWSEM(cgroup_thपढ़ोgroup_rwsem);

#घोषणा cgroup_निश्चित_mutex_or_rcu_locked()				\
	RCU_LOCKDEP_WARN(!rcu_पढ़ो_lock_held() &&			\
			   !lockdep_is_held(&cgroup_mutex),		\
			   "cgroup_mutex or RCU read lock required");

/*
 * cgroup deकाष्ठाion makes heavy use of work items and there can be a lot
 * of concurrent deकाष्ठाions.  Use a separate workqueue so that cgroup
 * deकाष्ठाion work items करोn't end up filling up max_active of प्रणाली_wq
 * which may lead to deadlock.
 */
अटल काष्ठा workqueue_काष्ठा *cgroup_destroy_wq;

/* generate an array of cgroup subप्रणाली poपूर्णांकers */
#घोषणा SUBSYS(_x) [_x ## _cgrp_id] = &_x ## _cgrp_subsys,
काष्ठा cgroup_subsys *cgroup_subsys[] = अणु
#समावेश <linux/cgroup_subsys.h>
पूर्ण;
#अघोषित SUBSYS

/* array of cgroup subप्रणाली names */
#घोषणा SUBSYS(_x) [_x ## _cgrp_id] = #_x,
अटल स्थिर अक्षर *cgroup_subsys_name[] = अणु
#समावेश <linux/cgroup_subsys.h>
पूर्ण;
#अघोषित SUBSYS

/* array of अटल_keys क्रम cgroup_subsys_enabled() and cgroup_subsys_on_dfl() */
#घोषणा SUBSYS(_x)								\
	DEFINE_STATIC_KEY_TRUE(_x ## _cgrp_subsys_enabled_key);			\
	DEFINE_STATIC_KEY_TRUE(_x ## _cgrp_subsys_on_dfl_key);			\
	EXPORT_SYMBOL_GPL(_x ## _cgrp_subsys_enabled_key);			\
	EXPORT_SYMBOL_GPL(_x ## _cgrp_subsys_on_dfl_key);
#समावेश <linux/cgroup_subsys.h>
#अघोषित SUBSYS

#घोषणा SUBSYS(_x) [_x ## _cgrp_id] = &_x ## _cgrp_subsys_enabled_key,
अटल काष्ठा अटल_key_true *cgroup_subsys_enabled_key[] = अणु
#समावेश <linux/cgroup_subsys.h>
पूर्ण;
#अघोषित SUBSYS

#घोषणा SUBSYS(_x) [_x ## _cgrp_id] = &_x ## _cgrp_subsys_on_dfl_key,
अटल काष्ठा अटल_key_true *cgroup_subsys_on_dfl_key[] = अणु
#समावेश <linux/cgroup_subsys.h>
पूर्ण;
#अघोषित SUBSYS

अटल DEFINE_PER_CPU(काष्ठा cgroup_rstat_cpu, cgrp_dfl_root_rstat_cpu);

/* the शेष hierarchy */
काष्ठा cgroup_root cgrp_dfl_root = अणु .cgrp.rstat_cpu = &cgrp_dfl_root_rstat_cpu पूर्ण;
EXPORT_SYMBOL_GPL(cgrp_dfl_root);

/*
 * The शेष hierarchy always exists but is hidden until mounted क्रम the
 * first समय.  This is क्रम backward compatibility.
 */
अटल bool cgrp_dfl_visible;

/* some controllers are not supported in the शेष hierarchy */
अटल u16 cgrp_dfl_inhibit_ss_mask;

/* some controllers are implicitly enabled on the शेष hierarchy */
अटल u16 cgrp_dfl_implicit_ss_mask;

/* some controllers can be thपढ़ोed on the शेष hierarchy */
अटल u16 cgrp_dfl_thपढ़ोed_ss_mask;

/* The list of hierarchy roots */
LIST_HEAD(cgroup_roots);
अटल पूर्णांक cgroup_root_count;

/* hierarchy ID allocation and mapping, रक्षित by cgroup_mutex */
अटल DEFINE_IDR(cgroup_hierarchy_idr);

/*
 * Assign a monotonically increasing serial number to csses.  It guarantees
 * cgroups with bigger numbers are newer than those with smaller numbers.
 * Also, as csses are always appended to the parent's ->children list, it
 * guarantees that sibling csses are always sorted in the ascending serial
 * number order on the list.  Protected by cgroup_mutex.
 */
अटल u64 css_serial_nr_next = 1;

/*
 * These biपंचांगasks identअगरy subप्रणालीs with specअगरic features to aव्योम
 * having to करो iterative checks repeatedly.
 */
अटल u16 have_विभाजन_callback __पढ़ो_mostly;
अटल u16 have_निकास_callback __पढ़ो_mostly;
अटल u16 have_release_callback __पढ़ो_mostly;
अटल u16 have_canविभाजन_callback __पढ़ो_mostly;

/* cgroup namespace क्रम init task */
काष्ठा cgroup_namespace init_cgroup_ns = अणु
	.ns.count	= REFCOUNT_INIT(2),
	.user_ns	= &init_user_ns,
	.ns.ops		= &cgroupns_operations,
	.ns.inum	= PROC_CGROUP_INIT_INO,
	.root_cset	= &init_css_set,
पूर्ण;

अटल काष्ठा file_प्रणाली_type cgroup2_fs_type;
अटल काष्ठा cftype cgroup_base_files[];

अटल पूर्णांक cgroup_apply_control(काष्ठा cgroup *cgrp);
अटल व्योम cgroup_finalize_control(काष्ठा cgroup *cgrp, पूर्णांक ret);
अटल व्योम css_task_iter_skip(काष्ठा css_task_iter *it,
			       काष्ठा task_काष्ठा *task);
अटल पूर्णांक cgroup_destroy_locked(काष्ठा cgroup *cgrp);
अटल काष्ठा cgroup_subsys_state *css_create(काष्ठा cgroup *cgrp,
					      काष्ठा cgroup_subsys *ss);
अटल व्योम css_release(काष्ठा percpu_ref *ref);
अटल व्योम समाप्त_css(काष्ठा cgroup_subsys_state *css);
अटल पूर्णांक cgroup_addrm_files(काष्ठा cgroup_subsys_state *css,
			      काष्ठा cgroup *cgrp, काष्ठा cftype cfts[],
			      bool is_add);

/**
 * cgroup_ssid_enabled - cgroup subsys enabled test by subsys ID
 * @ssid: subsys ID of पूर्णांकerest
 *
 * cgroup_subsys_enabled() can only be used with literal subsys names which
 * is fine क्रम inभागidual subप्रणालीs but unsuitable क्रम cgroup core.  This
 * is slower अटल_key_enabled() based test indexed by @ssid.
 */
bool cgroup_ssid_enabled(पूर्णांक ssid)
अणु
	अगर (CGROUP_SUBSYS_COUNT == 0)
		वापस false;

	वापस अटल_key_enabled(cgroup_subsys_enabled_key[ssid]);
पूर्ण

/**
 * cgroup_on_dfl - test whether a cgroup is on the शेष hierarchy
 * @cgrp: the cgroup of पूर्णांकerest
 *
 * The शेष hierarchy is the v2 पूर्णांकerface of cgroup and this function
 * can be used to test whether a cgroup is on the शेष hierarchy क्रम
 * हालs where a subप्रणाली should behave dअगरferently depending on the
 * पूर्णांकerface version.
 *
 * List of changed behaviors:
 *
 * - Mount options "noprefix", "xattr", "clone_children", "release_agent"
 *   and "name" are disallowed.
 *
 * - When mounting an existing superblock, mount options should match.
 *
 * - Remount is disallowed.
 *
 * - नाम(2) is disallowed.
 *
 * - "tasks" is हटाओd.  Everything should be at process granularity.  Use
 *   "cgroup.procs" instead.
 *
 * - "cgroup.procs" is not sorted.  pids will be unique unless they got
 *   recycled in-between पढ़ोs.
 *
 * - "release_agent" and "notify_on_release" are हटाओd.  Replacement
 *   notअगरication mechanism will be implemented.
 *
 * - "cgroup.clone_children" is हटाओd.
 *
 * - "cgroup.subtree_populated" is available.  Its value is 0 अगर the cgroup
 *   and its descendants contain no task; otherwise, 1.  The file also
 *   generates kernfs notअगरication which can be monitored through poll and
 *   [di]notअगरy when the value of the file changes.
 *
 * - cpuset: tasks will be kept in empty cpusets when hotplug happens and
 *   take masks of ancestors with non-empty cpus/mems, instead of being
 *   moved to an ancestor.
 *
 * - cpuset: a task can be moved पूर्णांकo an empty cpuset, and again it takes
 *   masks of ancestors.
 *
 * - blkcg: blk-throttle becomes properly hierarchical.
 *
 * - debug: disallowed on the शेष hierarchy.
 */
bool cgroup_on_dfl(स्थिर काष्ठा cgroup *cgrp)
अणु
	वापस cgrp->root == &cgrp_dfl_root;
पूर्ण

/* IDR wrappers which synchronize using cgroup_idr_lock */
अटल पूर्णांक cgroup_idr_alloc(काष्ठा idr *idr, व्योम *ptr, पूर्णांक start, पूर्णांक end,
			    gfp_t gfp_mask)
अणु
	पूर्णांक ret;

	idr_preload(gfp_mask);
	spin_lock_bh(&cgroup_idr_lock);
	ret = idr_alloc(idr, ptr, start, end, gfp_mask & ~__GFP_सूचीECT_RECLAIM);
	spin_unlock_bh(&cgroup_idr_lock);
	idr_preload_end();
	वापस ret;
पूर्ण

अटल व्योम *cgroup_idr_replace(काष्ठा idr *idr, व्योम *ptr, पूर्णांक id)
अणु
	व्योम *ret;

	spin_lock_bh(&cgroup_idr_lock);
	ret = idr_replace(idr, ptr, id);
	spin_unlock_bh(&cgroup_idr_lock);
	वापस ret;
पूर्ण

अटल व्योम cgroup_idr_हटाओ(काष्ठा idr *idr, पूर्णांक id)
अणु
	spin_lock_bh(&cgroup_idr_lock);
	idr_हटाओ(idr, id);
	spin_unlock_bh(&cgroup_idr_lock);
पूर्ण

अटल bool cgroup_has_tasks(काष्ठा cgroup *cgrp)
अणु
	वापस cgrp->nr_populated_csets;
पूर्ण

bool cgroup_is_thपढ़ोed(काष्ठा cgroup *cgrp)
अणु
	वापस cgrp->करोm_cgrp != cgrp;
पूर्ण

/* can @cgrp host both करोमुख्य and thपढ़ोed children? */
अटल bool cgroup_is_mixable(काष्ठा cgroup *cgrp)
अणु
	/*
	 * Root isn't under करोमुख्य level resource control exempting it from
	 * the no-पूर्णांकernal-process स्थिरraपूर्णांक, so it can serve as a thपढ़ो
	 * root and a parent of resource करोमुख्यs at the same समय.
	 */
	वापस !cgroup_parent(cgrp);
पूर्ण

/* can @cgrp become a thपढ़ो root? Should always be true क्रम a thपढ़ो root */
अटल bool cgroup_can_be_thपढ़ो_root(काष्ठा cgroup *cgrp)
अणु
	/* mixables करोn't care */
	अगर (cgroup_is_mixable(cgrp))
		वापस true;

	/* करोमुख्य roots can't be nested under thपढ़ोed */
	अगर (cgroup_is_thपढ़ोed(cgrp))
		वापस false;

	/* can only have either करोमुख्य or thपढ़ोed children */
	अगर (cgrp->nr_populated_करोमुख्य_children)
		वापस false;

	/* and no करोमुख्य controllers can be enabled */
	अगर (cgrp->subtree_control & ~cgrp_dfl_thपढ़ोed_ss_mask)
		वापस false;

	वापस true;
पूर्ण

/* is @cgrp root of a thपढ़ोed subtree? */
bool cgroup_is_thपढ़ो_root(काष्ठा cgroup *cgrp)
अणु
	/* thपढ़ो root should be a करोमुख्य */
	अगर (cgroup_is_thपढ़ोed(cgrp))
		वापस false;

	/* a करोमुख्य w/ thपढ़ोed children is a thपढ़ो root */
	अगर (cgrp->nr_thपढ़ोed_children)
		वापस true;

	/*
	 * A करोमुख्य which has tasks and explicit thपढ़ोed controllers
	 * enabled is a thपढ़ो root.
	 */
	अगर (cgroup_has_tasks(cgrp) &&
	    (cgrp->subtree_control & cgrp_dfl_thपढ़ोed_ss_mask))
		वापस true;

	वापस false;
पूर्ण

/* a करोमुख्य which isn't connected to the root w/o brekage can't be used */
अटल bool cgroup_is_valid_करोमुख्य(काष्ठा cgroup *cgrp)
अणु
	/* the cgroup itself can be a thपढ़ो root */
	अगर (cgroup_is_thपढ़ोed(cgrp))
		वापस false;

	/* but the ancestors can't be unless mixable */
	जबतक ((cgrp = cgroup_parent(cgrp))) अणु
		अगर (!cgroup_is_mixable(cgrp) && cgroup_is_thपढ़ो_root(cgrp))
			वापस false;
		अगर (cgroup_is_thपढ़ोed(cgrp))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* subप्रणालीs visibly enabled on a cgroup */
अटल u16 cgroup_control(काष्ठा cgroup *cgrp)
अणु
	काष्ठा cgroup *parent = cgroup_parent(cgrp);
	u16 root_ss_mask = cgrp->root->subsys_mask;

	अगर (parent) अणु
		u16 ss_mask = parent->subtree_control;

		/* thपढ़ोed cgroups can only have thपढ़ोed controllers */
		अगर (cgroup_is_thपढ़ोed(cgrp))
			ss_mask &= cgrp_dfl_thपढ़ोed_ss_mask;
		वापस ss_mask;
	पूर्ण

	अगर (cgroup_on_dfl(cgrp))
		root_ss_mask &= ~(cgrp_dfl_inhibit_ss_mask |
				  cgrp_dfl_implicit_ss_mask);
	वापस root_ss_mask;
पूर्ण

/* subप्रणालीs enabled on a cgroup */
अटल u16 cgroup_ss_mask(काष्ठा cgroup *cgrp)
अणु
	काष्ठा cgroup *parent = cgroup_parent(cgrp);

	अगर (parent) अणु
		u16 ss_mask = parent->subtree_ss_mask;

		/* thपढ़ोed cgroups can only have thपढ़ोed controllers */
		अगर (cgroup_is_thपढ़ोed(cgrp))
			ss_mask &= cgrp_dfl_thपढ़ोed_ss_mask;
		वापस ss_mask;
	पूर्ण

	वापस cgrp->root->subsys_mask;
पूर्ण

/**
 * cgroup_css - obtain a cgroup's css क्रम the specअगरied subप्रणाली
 * @cgrp: the cgroup of पूर्णांकerest
 * @ss: the subप्रणाली of पूर्णांकerest (%शून्य वापसs @cgrp->self)
 *
 * Return @cgrp's css (cgroup_subsys_state) associated with @ss.  This
 * function must be called either under cgroup_mutex or rcu_पढ़ो_lock() and
 * the caller is responsible क्रम pinning the वापसed css अगर it wants to
 * keep accessing it outside the said locks.  This function may वापस
 * %शून्य अगर @cgrp करोesn't have @subsys_id enabled.
 */
अटल काष्ठा cgroup_subsys_state *cgroup_css(काष्ठा cgroup *cgrp,
					      काष्ठा cgroup_subsys *ss)
अणु
	अगर (ss)
		वापस rcu_dereference_check(cgrp->subsys[ss->id],
					lockdep_is_held(&cgroup_mutex));
	अन्यथा
		वापस &cgrp->self;
पूर्ण

/**
 * cgroup_tryget_css - try to get a cgroup's css क्रम the specअगरied subप्रणाली
 * @cgrp: the cgroup of पूर्णांकerest
 * @ss: the subप्रणाली of पूर्णांकerest
 *
 * Find and get @cgrp's css associated with @ss.  If the css doesn't exist
 * or is offline, %शून्य is वापसed.
 */
अटल काष्ठा cgroup_subsys_state *cgroup_tryget_css(काष्ठा cgroup *cgrp,
						     काष्ठा cgroup_subsys *ss)
अणु
	काष्ठा cgroup_subsys_state *css;

	rcu_पढ़ो_lock();
	css = cgroup_css(cgrp, ss);
	अगर (css && !css_tryget_online(css))
		css = शून्य;
	rcu_पढ़ो_unlock();

	वापस css;
पूर्ण

/**
 * cgroup_e_css_by_mask - obtain a cgroup's effective css क्रम the specअगरied ss
 * @cgrp: the cgroup of पूर्णांकerest
 * @ss: the subप्रणाली of पूर्णांकerest (%शून्य वापसs @cgrp->self)
 *
 * Similar to cgroup_css() but वापसs the effective css, which is defined
 * as the matching css of the nearest ancestor including self which has @ss
 * enabled.  If @ss is associated with the hierarchy @cgrp is on, this
 * function is guaranteed to वापस non-शून्य css.
 */
अटल काष्ठा cgroup_subsys_state *cgroup_e_css_by_mask(काष्ठा cgroup *cgrp,
							काष्ठा cgroup_subsys *ss)
अणु
	lockdep_निश्चित_held(&cgroup_mutex);

	अगर (!ss)
		वापस &cgrp->self;

	/*
	 * This function is used जबतक updating css associations and thus
	 * can't test the csses directly.  Test ss_mask.
	 */
	जबतक (!(cgroup_ss_mask(cgrp) & (1 << ss->id))) अणु
		cgrp = cgroup_parent(cgrp);
		अगर (!cgrp)
			वापस शून्य;
	पूर्ण

	वापस cgroup_css(cgrp, ss);
पूर्ण

/**
 * cgroup_e_css - obtain a cgroup's effective css क्रम the specअगरied subप्रणाली
 * @cgrp: the cgroup of पूर्णांकerest
 * @ss: the subप्रणाली of पूर्णांकerest
 *
 * Find and get the effective css of @cgrp क्रम @ss.  The effective css is
 * defined as the matching css of the nearest ancestor including self which
 * has @ss enabled.  If @ss is not mounted on the hierarchy @cgrp is on,
 * the root css is वापसed, so this function always वापसs a valid css.
 *
 * The वापसed css is not guaranteed to be online, and thereक्रमe it is the
 * callers responsibility to try get a reference क्रम it.
 */
काष्ठा cgroup_subsys_state *cgroup_e_css(काष्ठा cgroup *cgrp,
					 काष्ठा cgroup_subsys *ss)
अणु
	काष्ठा cgroup_subsys_state *css;

	करो अणु
		css = cgroup_css(cgrp, ss);

		अगर (css)
			वापस css;
		cgrp = cgroup_parent(cgrp);
	पूर्ण जबतक (cgrp);

	वापस init_css_set.subsys[ss->id];
पूर्ण

/**
 * cgroup_get_e_css - get a cgroup's effective css क्रम the specअगरied subप्रणाली
 * @cgrp: the cgroup of पूर्णांकerest
 * @ss: the subप्रणाली of पूर्णांकerest
 *
 * Find and get the effective css of @cgrp क्रम @ss.  The effective css is
 * defined as the matching css of the nearest ancestor including self which
 * has @ss enabled.  If @ss is not mounted on the hierarchy @cgrp is on,
 * the root css is वापसed, so this function always वापसs a valid css.
 * The वापसed css must be put using css_put().
 */
काष्ठा cgroup_subsys_state *cgroup_get_e_css(काष्ठा cgroup *cgrp,
					     काष्ठा cgroup_subsys *ss)
अणु
	काष्ठा cgroup_subsys_state *css;

	rcu_पढ़ो_lock();

	करो अणु
		css = cgroup_css(cgrp, ss);

		अगर (css && css_tryget_online(css))
			जाओ out_unlock;
		cgrp = cgroup_parent(cgrp);
	पूर्ण जबतक (cgrp);

	css = init_css_set.subsys[ss->id];
	css_get(css);
out_unlock:
	rcu_पढ़ो_unlock();
	वापस css;
पूर्ण

अटल व्योम cgroup_get_live(काष्ठा cgroup *cgrp)
अणु
	WARN_ON_ONCE(cgroup_is_dead(cgrp));
	css_get(&cgrp->self);
पूर्ण

/**
 * __cgroup_task_count - count the number of tasks in a cgroup. The caller
 * is responsible क्रम taking the css_set_lock.
 * @cgrp: the cgroup in question
 */
पूर्णांक __cgroup_task_count(स्थिर काष्ठा cgroup *cgrp)
अणु
	पूर्णांक count = 0;
	काष्ठा cgrp_cset_link *link;

	lockdep_निश्चित_held(&css_set_lock);

	list_क्रम_each_entry(link, &cgrp->cset_links, cset_link)
		count += link->cset->nr_tasks;

	वापस count;
पूर्ण

/**
 * cgroup_task_count - count the number of tasks in a cgroup.
 * @cgrp: the cgroup in question
 */
पूर्णांक cgroup_task_count(स्थिर काष्ठा cgroup *cgrp)
अणु
	पूर्णांक count;

	spin_lock_irq(&css_set_lock);
	count = __cgroup_task_count(cgrp);
	spin_unlock_irq(&css_set_lock);

	वापस count;
पूर्ण

काष्ठा cgroup_subsys_state *of_css(काष्ठा kernfs_खोलो_file *of)
अणु
	काष्ठा cgroup *cgrp = of->kn->parent->priv;
	काष्ठा cftype *cft = of_cft(of);

	/*
	 * This is खोलो and unरक्षित implementation of cgroup_css().
	 * seq_css() is only called from a kernfs file operation which has
	 * an active reference on the file.  Because all the subप्रणाली
	 * files are drained beक्रमe a css is disassociated with a cgroup,
	 * the matching css from the cgroup's subsys table is guaranteed to
	 * be and stay valid until the enclosing operation is complete.
	 */
	अगर (cft->ss)
		वापस rcu_dereference_raw(cgrp->subsys[cft->ss->id]);
	अन्यथा
		वापस &cgrp->self;
पूर्ण
EXPORT_SYMBOL_GPL(of_css);

/**
 * क्रम_each_css - iterate all css's of a cgroup
 * @css: the iteration cursor
 * @ssid: the index of the subप्रणाली, CGROUP_SUBSYS_COUNT after reaching the end
 * @cgrp: the target cgroup to iterate css's of
 *
 * Should be called under cgroup_[tree_]mutex.
 */
#घोषणा क्रम_each_css(css, ssid, cgrp)					\
	क्रम ((ssid) = 0; (ssid) < CGROUP_SUBSYS_COUNT; (ssid)++)	\
		अगर (!((css) = rcu_dereference_check(			\
				(cgrp)->subsys[(ssid)],			\
				lockdep_is_held(&cgroup_mutex)))) अणु पूर्ण	\
		अन्यथा

/**
 * क्रम_each_e_css - iterate all effective css's of a cgroup
 * @css: the iteration cursor
 * @ssid: the index of the subप्रणाली, CGROUP_SUBSYS_COUNT after reaching the end
 * @cgrp: the target cgroup to iterate css's of
 *
 * Should be called under cgroup_[tree_]mutex.
 */
#घोषणा क्रम_each_e_css(css, ssid, cgrp)					    \
	क्रम ((ssid) = 0; (ssid) < CGROUP_SUBSYS_COUNT; (ssid)++)	    \
		अगर (!((css) = cgroup_e_css_by_mask(cgrp,		    \
						   cgroup_subsys[(ssid)]))) \
			;						    \
		अन्यथा

/**
 * करो_each_subsys_mask - filter क्रम_each_subsys with a biपंचांगask
 * @ss: the iteration cursor
 * @ssid: the index of @ss, CGROUP_SUBSYS_COUNT after reaching the end
 * @ss_mask: the biपंचांगask
 *
 * The block will only run क्रम हालs where the ssid-th bit (1 << ssid) of
 * @ss_mask is set.
 */
#घोषणा करो_each_subsys_mask(ss, ssid, ss_mask) करो अणु			\
	अचिन्हित दीर्घ __ss_mask = (ss_mask);				\
	अगर (!CGROUP_SUBSYS_COUNT) अणु /* to aव्योम spurious gcc warning */	\
		(ssid) = 0;						\
		अवरोध;							\
	पूर्ण								\
	क्रम_each_set_bit(ssid, &__ss_mask, CGROUP_SUBSYS_COUNT) अणु	\
		(ss) = cgroup_subsys[ssid];				\
		अणु

#घोषणा जबतक_each_subsys_mask()					\
		पूर्ण							\
	पूर्ण								\
पूर्ण जबतक (false)

/* iterate over child cgrps, lock should be held throughout iteration */
#घोषणा cgroup_क्रम_each_live_child(child, cgrp)				\
	list_क्रम_each_entry((child), &(cgrp)->self.children, self.sibling) \
		अगर ((अणु lockdep_निश्चित_held(&cgroup_mutex);		\
		       cgroup_is_dead(child); पूर्ण))			\
			;						\
		अन्यथा

/* walk live descendants in pre order */
#घोषणा cgroup_क्रम_each_live_descendant_pre(dsct, d_css, cgrp)		\
	css_क्रम_each_descendant_pre((d_css), cgroup_css((cgrp), शून्य))	\
		अगर ((अणु lockdep_निश्चित_held(&cgroup_mutex);		\
		       (dsct) = (d_css)->cgroup;			\
		       cgroup_is_dead(dsct); पूर्ण))			\
			;						\
		अन्यथा

/* walk live descendants in postorder */
#घोषणा cgroup_क्रम_each_live_descendant_post(dsct, d_css, cgrp)		\
	css_क्रम_each_descendant_post((d_css), cgroup_css((cgrp), शून्य))	\
		अगर ((अणु lockdep_निश्चित_held(&cgroup_mutex);		\
		       (dsct) = (d_css)->cgroup;			\
		       cgroup_is_dead(dsct); पूर्ण))			\
			;						\
		अन्यथा

/*
 * The शेष css_set - used by init and its children prior to any
 * hierarchies being mounted. It contains a poपूर्णांकer to the root state
 * क्रम each subप्रणाली. Also used to anchor the list of css_sets. Not
 * reference-counted, to improve perक्रमmance when child cgroups
 * haven't been created.
 */
काष्ठा css_set init_css_set = अणु
	.refcount		= REFCOUNT_INIT(1),
	.करोm_cset		= &init_css_set,
	.tasks			= LIST_HEAD_INIT(init_css_set.tasks),
	.mg_tasks		= LIST_HEAD_INIT(init_css_set.mg_tasks),
	.dying_tasks		= LIST_HEAD_INIT(init_css_set.dying_tasks),
	.task_iters		= LIST_HEAD_INIT(init_css_set.task_iters),
	.thपढ़ोed_csets		= LIST_HEAD_INIT(init_css_set.thपढ़ोed_csets),
	.cgrp_links		= LIST_HEAD_INIT(init_css_set.cgrp_links),
	.mg_preload_node	= LIST_HEAD_INIT(init_css_set.mg_preload_node),
	.mg_node		= LIST_HEAD_INIT(init_css_set.mg_node),

	/*
	 * The following field is re-initialized when this cset माला_लो linked
	 * in cgroup_init().  However, let's initialize the field
	 * अटलally too so that the शेष cgroup can be accessed safely
	 * early during boot.
	 */
	.dfl_cgrp		= &cgrp_dfl_root.cgrp,
पूर्ण;

अटल पूर्णांक css_set_count	= 1;	/* 1 क्रम init_css_set */

अटल bool css_set_thपढ़ोed(काष्ठा css_set *cset)
अणु
	वापस cset->करोm_cset != cset;
पूर्ण

/**
 * css_set_populated - करोes a css_set contain any tasks?
 * @cset: target css_set
 *
 * css_set_populated() should be the same as !!cset->nr_tasks at steady
 * state. However, css_set_populated() can be called जबतक a task is being
 * added to or हटाओd from the linked list beक्रमe the nr_tasks is
 * properly updated. Hence, we can't just look at ->nr_tasks here.
 */
अटल bool css_set_populated(काष्ठा css_set *cset)
अणु
	lockdep_निश्चित_held(&css_set_lock);

	वापस !list_empty(&cset->tasks) || !list_empty(&cset->mg_tasks);
पूर्ण

/**
 * cgroup_update_populated - update the populated count of a cgroup
 * @cgrp: the target cgroup
 * @populated: inc or dec populated count
 *
 * One of the css_sets associated with @cgrp is either getting its first
 * task or losing the last.  Update @cgrp->nr_populated_* accordingly.  The
 * count is propagated towards root so that a given cgroup's
 * nr_populated_children is zero अगरf none of its descendants contain any
 * tasks.
 *
 * @cgrp's पूर्णांकerface file "cgroup.populated" is zero अगर both
 * @cgrp->nr_populated_csets and @cgrp->nr_populated_children are zero and
 * 1 otherwise.  When the sum changes from or to zero, userland is notअगरied
 * that the content of the पूर्णांकerface file has changed.  This can be used to
 * detect when @cgrp and its descendants become populated or empty.
 */
अटल व्योम cgroup_update_populated(काष्ठा cgroup *cgrp, bool populated)
अणु
	काष्ठा cgroup *child = शून्य;
	पूर्णांक adj = populated ? 1 : -1;

	lockdep_निश्चित_held(&css_set_lock);

	करो अणु
		bool was_populated = cgroup_is_populated(cgrp);

		अगर (!child) अणु
			cgrp->nr_populated_csets += adj;
		पूर्ण अन्यथा अणु
			अगर (cgroup_is_thपढ़ोed(child))
				cgrp->nr_populated_thपढ़ोed_children += adj;
			अन्यथा
				cgrp->nr_populated_करोमुख्य_children += adj;
		पूर्ण

		अगर (was_populated == cgroup_is_populated(cgrp))
			अवरोध;

		cgroup1_check_क्रम_release(cgrp);
		TRACE_CGROUP_PATH(notअगरy_populated, cgrp,
				  cgroup_is_populated(cgrp));
		cgroup_file_notअगरy(&cgrp->events_file);

		child = cgrp;
		cgrp = cgroup_parent(cgrp);
	पूर्ण जबतक (cgrp);
पूर्ण

/**
 * css_set_update_populated - update populated state of a css_set
 * @cset: target css_set
 * @populated: whether @cset is populated or depopulated
 *
 * @cset is either getting the first task or losing the last.  Update the
 * populated counters of all associated cgroups accordingly.
 */
अटल व्योम css_set_update_populated(काष्ठा css_set *cset, bool populated)
अणु
	काष्ठा cgrp_cset_link *link;

	lockdep_निश्चित_held(&css_set_lock);

	list_क्रम_each_entry(link, &cset->cgrp_links, cgrp_link)
		cgroup_update_populated(link->cgrp, populated);
पूर्ण

/*
 * @task is leaving, advance task iterators which are poपूर्णांकing to it so
 * that they can resume at the next position.  Advancing an iterator might
 * हटाओ it from the list, use safe walk.  See css_task_iter_skip() क्रम
 * details.
 */
अटल व्योम css_set_skip_task_iters(काष्ठा css_set *cset,
				    काष्ठा task_काष्ठा *task)
अणु
	काष्ठा css_task_iter *it, *pos;

	list_क्रम_each_entry_safe(it, pos, &cset->task_iters, iters_node)
		css_task_iter_skip(it, task);
पूर्ण

/**
 * css_set_move_task - move a task from one css_set to another
 * @task: task being moved
 * @from_cset: css_set @task currently beदीर्घs to (may be शून्य)
 * @to_cset: new css_set @task is being moved to (may be शून्य)
 * @use_mg_tasks: move to @to_cset->mg_tasks instead of ->tasks
 *
 * Move @task from @from_cset to @to_cset.  If @task didn't beदीर्घ to any
 * css_set, @from_cset can be शून्य.  If @task is being disassociated
 * instead of moved, @to_cset can be शून्य.
 *
 * This function स्वतःmatically handles populated counter updates and
 * css_task_iter adjusपंचांगents but the caller is responsible क्रम managing
 * @from_cset and @to_cset's reference counts.
 */
अटल व्योम css_set_move_task(काष्ठा task_काष्ठा *task,
			      काष्ठा css_set *from_cset, काष्ठा css_set *to_cset,
			      bool use_mg_tasks)
अणु
	lockdep_निश्चित_held(&css_set_lock);

	अगर (to_cset && !css_set_populated(to_cset))
		css_set_update_populated(to_cset, true);

	अगर (from_cset) अणु
		WARN_ON_ONCE(list_empty(&task->cg_list));

		css_set_skip_task_iters(from_cset, task);
		list_del_init(&task->cg_list);
		अगर (!css_set_populated(from_cset))
			css_set_update_populated(from_cset, false);
	पूर्ण अन्यथा अणु
		WARN_ON_ONCE(!list_empty(&task->cg_list));
	पूर्ण

	अगर (to_cset) अणु
		/*
		 * We are synchronized through cgroup_thपढ़ोgroup_rwsem
		 * against PF_EXITING setting such that we can't race
		 * against cgroup_निकास()/cgroup_मुक्त() dropping the css_set.
		 */
		WARN_ON_ONCE(task->flags & PF_EXITING);

		cgroup_move_task(task, to_cset);
		list_add_tail(&task->cg_list, use_mg_tasks ? &to_cset->mg_tasks :
							     &to_cset->tasks);
	पूर्ण
पूर्ण

/*
 * hash table क्रम cgroup groups. This improves the perक्रमmance to find
 * an existing css_set. This hash करोesn't (currently) take पूर्णांकo
 * account cgroups in empty hierarchies.
 */
#घोषणा CSS_SET_HASH_BITS	7
अटल DEFINE_HASHTABLE(css_set_table, CSS_SET_HASH_BITS);

अटल अचिन्हित दीर्घ css_set_hash(काष्ठा cgroup_subsys_state *css[])
अणु
	अचिन्हित दीर्घ key = 0UL;
	काष्ठा cgroup_subsys *ss;
	पूर्णांक i;

	क्रम_each_subsys(ss, i)
		key += (अचिन्हित दीर्घ)css[i];
	key = (key >> 16) ^ key;

	वापस key;
पूर्ण

व्योम put_css_set_locked(काष्ठा css_set *cset)
अणु
	काष्ठा cgrp_cset_link *link, *पंचांगp_link;
	काष्ठा cgroup_subsys *ss;
	पूर्णांक ssid;

	lockdep_निश्चित_held(&css_set_lock);

	अगर (!refcount_dec_and_test(&cset->refcount))
		वापस;

	WARN_ON_ONCE(!list_empty(&cset->thपढ़ोed_csets));

	/* This css_set is dead. Unlink it and release cgroup and css refs */
	क्रम_each_subsys(ss, ssid) अणु
		list_del(&cset->e_cset_node[ssid]);
		css_put(cset->subsys[ssid]);
	पूर्ण
	hash_del(&cset->hlist);
	css_set_count--;

	list_क्रम_each_entry_safe(link, पंचांगp_link, &cset->cgrp_links, cgrp_link) अणु
		list_del(&link->cset_link);
		list_del(&link->cgrp_link);
		अगर (cgroup_parent(link->cgrp))
			cgroup_put(link->cgrp);
		kमुक्त(link);
	पूर्ण

	अगर (css_set_thपढ़ोed(cset)) अणु
		list_del(&cset->thपढ़ोed_csets_node);
		put_css_set_locked(cset->करोm_cset);
	पूर्ण

	kमुक्त_rcu(cset, rcu_head);
पूर्ण

/**
 * compare_css_sets - helper function क्रम find_existing_css_set().
 * @cset: candidate css_set being tested
 * @old_cset: existing css_set क्रम a task
 * @new_cgrp: cgroup that's being entered by the task
 * @ढाँचा: desired set of css poपूर्णांकers in css_set (pre-calculated)
 *
 * Returns true अगर "cset" matches "old_cset" except क्रम the hierarchy
 * which "new_cgrp" beदीर्घs to, क्रम which it should match "new_cgrp".
 */
अटल bool compare_css_sets(काष्ठा css_set *cset,
			     काष्ठा css_set *old_cset,
			     काष्ठा cgroup *new_cgrp,
			     काष्ठा cgroup_subsys_state *ढाँचा[])
अणु
	काष्ठा cgroup *new_dfl_cgrp;
	काष्ठा list_head *l1, *l2;

	/*
	 * On the शेष hierarchy, there can be csets which are
	 * associated with the same set of cgroups but dअगरferent csses.
	 * Let's first ensure that csses match.
	 */
	अगर (स_भेद(ढाँचा, cset->subsys, माप(cset->subsys)))
		वापस false;


	/* @cset's domain should match the default cgroup's */
	अगर (cgroup_on_dfl(new_cgrp))
		new_dfl_cgrp = new_cgrp;
	अन्यथा
		new_dfl_cgrp = old_cset->dfl_cgrp;

	अगर (new_dfl_cgrp->करोm_cgrp != cset->करोm_cset->dfl_cgrp)
		वापस false;

	/*
	 * Compare cgroup poपूर्णांकers in order to distinguish between
	 * dअगरferent cgroups in hierarchies.  As dअगरferent cgroups may
	 * share the same effective css, this comparison is always
	 * necessary.
	 */
	l1 = &cset->cgrp_links;
	l2 = &old_cset->cgrp_links;
	जबतक (1) अणु
		काष्ठा cgrp_cset_link *link1, *link2;
		काष्ठा cgroup *cgrp1, *cgrp2;

		l1 = l1->next;
		l2 = l2->next;
		/* See अगर we reached the end - both lists are equal length. */
		अगर (l1 == &cset->cgrp_links) अणु
			BUG_ON(l2 != &old_cset->cgrp_links);
			अवरोध;
		पूर्ण अन्यथा अणु
			BUG_ON(l2 == &old_cset->cgrp_links);
		पूर्ण
		/* Locate the cgroups associated with these links. */
		link1 = list_entry(l1, काष्ठा cgrp_cset_link, cgrp_link);
		link2 = list_entry(l2, काष्ठा cgrp_cset_link, cgrp_link);
		cgrp1 = link1->cgrp;
		cgrp2 = link2->cgrp;
		/* Hierarchies should be linked in the same order. */
		BUG_ON(cgrp1->root != cgrp2->root);

		/*
		 * If this hierarchy is the hierarchy of the cgroup
		 * that's changing, then we need to check that this
		 * css_set poपूर्णांकs to the new cgroup; अगर it's any other
		 * hierarchy, then this css_set should poपूर्णांक to the
		 * same cgroup as the old css_set.
		 */
		अगर (cgrp1->root == new_cgrp->root) अणु
			अगर (cgrp1 != new_cgrp)
				वापस false;
		पूर्ण अन्यथा अणु
			अगर (cgrp1 != cgrp2)
				वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

/**
 * find_existing_css_set - init css array and find the matching css_set
 * @old_cset: the css_set that we're using beक्रमe the cgroup transition
 * @cgrp: the cgroup that we're moving पूर्णांकo
 * @ढाँचा: out param क्रम the new set of csses, should be clear on entry
 */
अटल काष्ठा css_set *find_existing_css_set(काष्ठा css_set *old_cset,
					काष्ठा cgroup *cgrp,
					काष्ठा cgroup_subsys_state *ढाँचा[])
अणु
	काष्ठा cgroup_root *root = cgrp->root;
	काष्ठा cgroup_subsys *ss;
	काष्ठा css_set *cset;
	अचिन्हित दीर्घ key;
	पूर्णांक i;

	/*
	 * Build the set of subप्रणाली state objects that we want to see in the
	 * new css_set. While subप्रणालीs can change globally, the entries here
	 * won't change, so no need क्रम locking.
	 */
	क्रम_each_subsys(ss, i) अणु
		अगर (root->subsys_mask & (1UL << i)) अणु
			/*
			 * @ss is in this hierarchy, so we want the
			 * effective css from @cgrp.
			 */
			ढाँचा[i] = cgroup_e_css_by_mask(cgrp, ss);
		पूर्ण अन्यथा अणु
			/*
			 * @ss is not in this hierarchy, so we करोn't want
			 * to change the css.
			 */
			ढाँचा[i] = old_cset->subsys[i];
		पूर्ण
	पूर्ण

	key = css_set_hash(ढाँचा);
	hash_क्रम_each_possible(css_set_table, cset, hlist, key) अणु
		अगर (!compare_css_sets(cset, old_cset, cgrp, ढाँचा))
			जारी;

		/* This css_set matches what we need */
		वापस cset;
	पूर्ण

	/* No existing cgroup group matched */
	वापस शून्य;
पूर्ण

अटल व्योम मुक्त_cgrp_cset_links(काष्ठा list_head *links_to_मुक्त)
अणु
	काष्ठा cgrp_cset_link *link, *पंचांगp_link;

	list_क्रम_each_entry_safe(link, पंचांगp_link, links_to_मुक्त, cset_link) अणु
		list_del(&link->cset_link);
		kमुक्त(link);
	पूर्ण
पूर्ण

/**
 * allocate_cgrp_cset_links - allocate cgrp_cset_links
 * @count: the number of links to allocate
 * @पंचांगp_links: list_head the allocated links are put on
 *
 * Allocate @count cgrp_cset_link काष्ठाures and chain them on @पंचांगp_links
 * through ->cset_link.  Returns 0 on success or -त्रुटि_सं.
 */
अटल पूर्णांक allocate_cgrp_cset_links(पूर्णांक count, काष्ठा list_head *पंचांगp_links)
अणु
	काष्ठा cgrp_cset_link *link;
	पूर्णांक i;

	INIT_LIST_HEAD(पंचांगp_links);

	क्रम (i = 0; i < count; i++) अणु
		link = kzalloc(माप(*link), GFP_KERNEL);
		अगर (!link) अणु
			मुक्त_cgrp_cset_links(पंचांगp_links);
			वापस -ENOMEM;
		पूर्ण
		list_add(&link->cset_link, पंचांगp_links);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * link_css_set - a helper function to link a css_set to a cgroup
 * @पंचांगp_links: cgrp_cset_link objects allocated by allocate_cgrp_cset_links()
 * @cset: the css_set to be linked
 * @cgrp: the destination cgroup
 */
अटल व्योम link_css_set(काष्ठा list_head *पंचांगp_links, काष्ठा css_set *cset,
			 काष्ठा cgroup *cgrp)
अणु
	काष्ठा cgrp_cset_link *link;

	BUG_ON(list_empty(पंचांगp_links));

	अगर (cgroup_on_dfl(cgrp))
		cset->dfl_cgrp = cgrp;

	link = list_first_entry(पंचांगp_links, काष्ठा cgrp_cset_link, cset_link);
	link->cset = cset;
	link->cgrp = cgrp;

	/*
	 * Always add links to the tail of the lists so that the lists are
	 * in chronological order.
	 */
	list_move_tail(&link->cset_link, &cgrp->cset_links);
	list_add_tail(&link->cgrp_link, &cset->cgrp_links);

	अगर (cgroup_parent(cgrp))
		cgroup_get_live(cgrp);
पूर्ण

/**
 * find_css_set - वापस a new css_set with one cgroup updated
 * @old_cset: the baseline css_set
 * @cgrp: the cgroup to be updated
 *
 * Return a new css_set that's equivalent to @old_cset, but with @cgrp
 * substituted पूर्णांकo the appropriate hierarchy.
 */
अटल काष्ठा css_set *find_css_set(काष्ठा css_set *old_cset,
				    काष्ठा cgroup *cgrp)
अणु
	काष्ठा cgroup_subsys_state *ढाँचा[CGROUP_SUBSYS_COUNT] = अणु पूर्ण;
	काष्ठा css_set *cset;
	काष्ठा list_head पंचांगp_links;
	काष्ठा cgrp_cset_link *link;
	काष्ठा cgroup_subsys *ss;
	अचिन्हित दीर्घ key;
	पूर्णांक ssid;

	lockdep_निश्चित_held(&cgroup_mutex);

	/* First see अगर we alपढ़ोy have a cgroup group that matches
	 * the desired set */
	spin_lock_irq(&css_set_lock);
	cset = find_existing_css_set(old_cset, cgrp, ढाँचा);
	अगर (cset)
		get_css_set(cset);
	spin_unlock_irq(&css_set_lock);

	अगर (cset)
		वापस cset;

	cset = kzalloc(माप(*cset), GFP_KERNEL);
	अगर (!cset)
		वापस शून्य;

	/* Allocate all the cgrp_cset_link objects that we'll need */
	अगर (allocate_cgrp_cset_links(cgroup_root_count, &पंचांगp_links) < 0) अणु
		kमुक्त(cset);
		वापस शून्य;
	पूर्ण

	refcount_set(&cset->refcount, 1);
	cset->करोm_cset = cset;
	INIT_LIST_HEAD(&cset->tasks);
	INIT_LIST_HEAD(&cset->mg_tasks);
	INIT_LIST_HEAD(&cset->dying_tasks);
	INIT_LIST_HEAD(&cset->task_iters);
	INIT_LIST_HEAD(&cset->thपढ़ोed_csets);
	INIT_HLIST_NODE(&cset->hlist);
	INIT_LIST_HEAD(&cset->cgrp_links);
	INIT_LIST_HEAD(&cset->mg_preload_node);
	INIT_LIST_HEAD(&cset->mg_node);

	/* Copy the set of subप्रणाली state objects generated in
	 * find_existing_css_set() */
	स_नकल(cset->subsys, ढाँचा, माप(cset->subsys));

	spin_lock_irq(&css_set_lock);
	/* Add reference counts and links from the new css_set. */
	list_क्रम_each_entry(link, &old_cset->cgrp_links, cgrp_link) अणु
		काष्ठा cgroup *c = link->cgrp;

		अगर (c->root == cgrp->root)
			c = cgrp;
		link_css_set(&पंचांगp_links, cset, c);
	पूर्ण

	BUG_ON(!list_empty(&पंचांगp_links));

	css_set_count++;

	/* Add @cset to the hash table */
	key = css_set_hash(cset->subsys);
	hash_add(css_set_table, &cset->hlist, key);

	क्रम_each_subsys(ss, ssid) अणु
		काष्ठा cgroup_subsys_state *css = cset->subsys[ssid];

		list_add_tail(&cset->e_cset_node[ssid],
			      &css->cgroup->e_csets[ssid]);
		css_get(css);
	पूर्ण

	spin_unlock_irq(&css_set_lock);

	/*
	 * If @cset should be thपढ़ोed, look up the matching करोm_cset and
	 * link them up.  We first fully initialize @cset then look क्रम the
	 * करोm_cset.  It's simpler this way and safe as @cset is guaranteed
	 * to stay empty until we वापस.
	 */
	अगर (cgroup_is_thपढ़ोed(cset->dfl_cgrp)) अणु
		काष्ठा css_set *dcset;

		dcset = find_css_set(cset, cset->dfl_cgrp->करोm_cgrp);
		अगर (!dcset) अणु
			put_css_set(cset);
			वापस शून्य;
		पूर्ण

		spin_lock_irq(&css_set_lock);
		cset->करोm_cset = dcset;
		list_add_tail(&cset->thपढ़ोed_csets_node,
			      &dcset->thपढ़ोed_csets);
		spin_unlock_irq(&css_set_lock);
	पूर्ण

	वापस cset;
पूर्ण

काष्ठा cgroup_root *cgroup_root_from_kf(काष्ठा kernfs_root *kf_root)
अणु
	काष्ठा cgroup *root_cgrp = kf_root->kn->priv;

	वापस root_cgrp->root;
पूर्ण

अटल पूर्णांक cgroup_init_root_id(काष्ठा cgroup_root *root)
अणु
	पूर्णांक id;

	lockdep_निश्चित_held(&cgroup_mutex);

	id = idr_alloc_cyclic(&cgroup_hierarchy_idr, root, 0, 0, GFP_KERNEL);
	अगर (id < 0)
		वापस id;

	root->hierarchy_id = id;
	वापस 0;
पूर्ण

अटल व्योम cgroup_निकास_root_id(काष्ठा cgroup_root *root)
अणु
	lockdep_निश्चित_held(&cgroup_mutex);

	idr_हटाओ(&cgroup_hierarchy_idr, root->hierarchy_id);
पूर्ण

व्योम cgroup_मुक्त_root(काष्ठा cgroup_root *root)
अणु
	kमुक्त(root);
पूर्ण

अटल व्योम cgroup_destroy_root(काष्ठा cgroup_root *root)
अणु
	काष्ठा cgroup *cgrp = &root->cgrp;
	काष्ठा cgrp_cset_link *link, *पंचांगp_link;

	trace_cgroup_destroy_root(root);

	cgroup_lock_and_drain_offline(&cgrp_dfl_root.cgrp);

	BUG_ON(atomic_पढ़ो(&root->nr_cgrps));
	BUG_ON(!list_empty(&cgrp->self.children));

	/* Rebind all subप्रणालीs back to the शेष hierarchy */
	WARN_ON(rebind_subप्रणालीs(&cgrp_dfl_root, root->subsys_mask));

	/*
	 * Release all the links from cset_links to this hierarchy's
	 * root cgroup
	 */
	spin_lock_irq(&css_set_lock);

	list_क्रम_each_entry_safe(link, पंचांगp_link, &cgrp->cset_links, cset_link) अणु
		list_del(&link->cset_link);
		list_del(&link->cgrp_link);
		kमुक्त(link);
	पूर्ण

	spin_unlock_irq(&css_set_lock);

	अगर (!list_empty(&root->root_list)) अणु
		list_del(&root->root_list);
		cgroup_root_count--;
	पूर्ण

	cgroup_निकास_root_id(root);

	mutex_unlock(&cgroup_mutex);

	cgroup_rstat_निकास(cgrp);
	kernfs_destroy_root(root->kf_root);
	cgroup_मुक्त_root(root);
पूर्ण

/*
 * look up cgroup associated with current task's cgroup namespace on the
 * specअगरied hierarchy
 */
अटल काष्ठा cgroup *
current_cgns_cgroup_from_root(काष्ठा cgroup_root *root)
अणु
	काष्ठा cgroup *res = शून्य;
	काष्ठा css_set *cset;

	lockdep_निश्चित_held(&css_set_lock);

	rcu_पढ़ो_lock();

	cset = current->nsproxy->cgroup_ns->root_cset;
	अगर (cset == &init_css_set) अणु
		res = &root->cgrp;
	पूर्ण अन्यथा अगर (root == &cgrp_dfl_root) अणु
		res = cset->dfl_cgrp;
	पूर्ण अन्यथा अणु
		काष्ठा cgrp_cset_link *link;

		list_क्रम_each_entry(link, &cset->cgrp_links, cgrp_link) अणु
			काष्ठा cgroup *c = link->cgrp;

			अगर (c->root == root) अणु
				res = c;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	BUG_ON(!res);
	वापस res;
पूर्ण

/* look up cgroup associated with given css_set on the specअगरied hierarchy */
अटल काष्ठा cgroup *cset_cgroup_from_root(काष्ठा css_set *cset,
					    काष्ठा cgroup_root *root)
अणु
	काष्ठा cgroup *res = शून्य;

	lockdep_निश्चित_held(&cgroup_mutex);
	lockdep_निश्चित_held(&css_set_lock);

	अगर (cset == &init_css_set) अणु
		res = &root->cgrp;
	पूर्ण अन्यथा अगर (root == &cgrp_dfl_root) अणु
		res = cset->dfl_cgrp;
	पूर्ण अन्यथा अणु
		काष्ठा cgrp_cset_link *link;

		list_क्रम_each_entry(link, &cset->cgrp_links, cgrp_link) अणु
			काष्ठा cgroup *c = link->cgrp;

			अगर (c->root == root) अणु
				res = c;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	BUG_ON(!res);
	वापस res;
पूर्ण

/*
 * Return the cgroup क्रम "task" from the given hierarchy. Must be
 * called with cgroup_mutex and css_set_lock held.
 */
काष्ठा cgroup *task_cgroup_from_root(काष्ठा task_काष्ठा *task,
				     काष्ठा cgroup_root *root)
अणु
	/*
	 * No need to lock the task - since we hold css_set_lock the
	 * task can't change groups.
	 */
	वापस cset_cgroup_from_root(task_css_set(task), root);
पूर्ण

/*
 * A task must hold cgroup_mutex to modअगरy cgroups.
 *
 * Any task can increment and decrement the count field without lock.
 * So in general, code holding cgroup_mutex can't rely on the count
 * field not changing.  However, अगर the count goes to zero, then only
 * cgroup_attach_task() can increment it again.  Because a count of zero
 * means that no tasks are currently attached, thereक्रमe there is no
 * way a task attached to that cgroup can विभाजन (the other way to
 * increment the count).  So code holding cgroup_mutex can safely
 * assume that अगर the count is zero, it will stay zero. Similarly, अगर
 * a task holds cgroup_mutex on a cgroup with zero count, it
 * knows that the cgroup won't be हटाओd, as cgroup_सूची_हटाओ()
 * needs that mutex.
 *
 * A cgroup can only be deleted अगर both its 'count' of using tasks
 * is zero, and its list of 'children' cgroups is empty.  Since all
 * tasks in the प्रणाली use _some_ cgroup, and since there is always at
 * least one task in the प्रणाली (init, pid == 1), thereक्रमe, root cgroup
 * always has either children cgroups and/or using tasks.  So we करोn't
 * need a special hack to ensure that root cgroup cannot be deleted.
 *
 * P.S.  One more locking exception.  RCU is used to guard the
 * update of a tasks cgroup poपूर्णांकer by cgroup_attach_task()
 */

अटल काष्ठा kernfs_syscall_ops cgroup_kf_syscall_ops;

अटल अक्षर *cgroup_file_name(काष्ठा cgroup *cgrp, स्थिर काष्ठा cftype *cft,
			      अक्षर *buf)
अणु
	काष्ठा cgroup_subsys *ss = cft->ss;

	अगर (cft->ss && !(cft->flags & CFTYPE_NO_PREFIX) &&
	    !(cgrp->root->flags & CGRP_ROOT_NOPREFIX)) अणु
		स्थिर अक्षर *dbg = (cft->flags & CFTYPE_DEBUG) ? ".__DEBUG__." : "";

		snम_लिखो(buf, CGROUP_खाता_NAME_MAX, "%s%s.%s",
			 dbg, cgroup_on_dfl(cgrp) ? ss->name : ss->legacy_name,
			 cft->name);
	पूर्ण अन्यथा अणु
		strscpy(buf, cft->name, CGROUP_खाता_NAME_MAX);
	पूर्ण
	वापस buf;
पूर्ण

/**
 * cgroup_file_mode - deduce file mode of a control file
 * @cft: the control file in question
 *
 * S_IRUGO क्रम पढ़ो, S_IWUSR क्रम ग_लिखो.
 */
अटल umode_t cgroup_file_mode(स्थिर काष्ठा cftype *cft)
अणु
	umode_t mode = 0;

	अगर (cft->पढ़ो_u64 || cft->पढ़ो_s64 || cft->seq_show)
		mode |= S_IRUGO;

	अगर (cft->ग_लिखो_u64 || cft->ग_लिखो_s64 || cft->ग_लिखो) अणु
		अगर (cft->flags & CFTYPE_WORLD_WRITABLE)
			mode |= S_IWUGO;
		अन्यथा
			mode |= S_IWUSR;
	पूर्ण

	वापस mode;
पूर्ण

/**
 * cgroup_calc_subtree_ss_mask - calculate subtree_ss_mask
 * @subtree_control: the new subtree_control mask to consider
 * @this_ss_mask: available subप्रणालीs
 *
 * On the शेष hierarchy, a subप्रणाली may request other subप्रणालीs to be
 * enabled together through its ->depends_on mask.  In such हालs, more
 * subप्रणालीs than specअगरied in "cgroup.subtree_control" may be enabled.
 *
 * This function calculates which subप्रणालीs need to be enabled अगर
 * @subtree_control is to be applied जबतक restricted to @this_ss_mask.
 */
अटल u16 cgroup_calc_subtree_ss_mask(u16 subtree_control, u16 this_ss_mask)
अणु
	u16 cur_ss_mask = subtree_control;
	काष्ठा cgroup_subsys *ss;
	पूर्णांक ssid;

	lockdep_निश्चित_held(&cgroup_mutex);

	cur_ss_mask |= cgrp_dfl_implicit_ss_mask;

	जबतक (true) अणु
		u16 new_ss_mask = cur_ss_mask;

		करो_each_subsys_mask(ss, ssid, cur_ss_mask) अणु
			new_ss_mask |= ss->depends_on;
		पूर्ण जबतक_each_subsys_mask();

		/*
		 * Mask out subप्रणालीs which aren't available.  This can
		 * happen only अगर some depended-upon subप्रणालीs were bound
		 * to non-शेष hierarchies.
		 */
		new_ss_mask &= this_ss_mask;

		अगर (new_ss_mask == cur_ss_mask)
			अवरोध;
		cur_ss_mask = new_ss_mask;
	पूर्ण

	वापस cur_ss_mask;
पूर्ण

/**
 * cgroup_kn_unlock - unlocking helper क्रम cgroup kernfs methods
 * @kn: the kernfs_node being serviced
 *
 * This helper unकरोes cgroup_kn_lock_live() and should be invoked beक्रमe
 * the method finishes अगर locking succeeded.  Note that once this function
 * वापसs the cgroup वापसed by cgroup_kn_lock_live() may become
 * inaccessible any समय.  If the caller पूर्णांकends to जारी to access the
 * cgroup, it should pin it beक्रमe invoking this function.
 */
व्योम cgroup_kn_unlock(काष्ठा kernfs_node *kn)
अणु
	काष्ठा cgroup *cgrp;

	अगर (kernfs_type(kn) == KERNFS_सूची)
		cgrp = kn->priv;
	अन्यथा
		cgrp = kn->parent->priv;

	mutex_unlock(&cgroup_mutex);

	kernfs_unअवरोध_active_protection(kn);
	cgroup_put(cgrp);
पूर्ण

/**
 * cgroup_kn_lock_live - locking helper क्रम cgroup kernfs methods
 * @kn: the kernfs_node being serviced
 * @drain_offline: perक्रमm offline draining on the cgroup
 *
 * This helper is to be used by a cgroup kernfs method currently servicing
 * @kn.  It अवरोधs the active protection, perक्रमms cgroup locking and
 * verअगरies that the associated cgroup is alive.  Returns the cgroup अगर
 * alive; otherwise, %शून्य.  A successful वापस should be unकरोne by a
 * matching cgroup_kn_unlock() invocation.  If @drain_offline is %true, the
 * cgroup is drained of offlining csses beक्रमe वापस.
 *
 * Any cgroup kernfs method implementation which requires locking the
 * associated cgroup should use this helper.  It aव्योमs nesting cgroup
 * locking under kernfs active protection and allows all kernfs operations
 * including self-removal.
 */
काष्ठा cgroup *cgroup_kn_lock_live(काष्ठा kernfs_node *kn, bool drain_offline)
अणु
	काष्ठा cgroup *cgrp;

	अगर (kernfs_type(kn) == KERNFS_सूची)
		cgrp = kn->priv;
	अन्यथा
		cgrp = kn->parent->priv;

	/*
	 * We're gonna grab cgroup_mutex which nests outside kernfs
	 * active_ref.  cgroup liveliness check alone provides enough
	 * protection against removal.  Ensure @cgrp stays accessible and
	 * अवरोध the active_ref protection.
	 */
	अगर (!cgroup_tryget(cgrp))
		वापस शून्य;
	kernfs_अवरोध_active_protection(kn);

	अगर (drain_offline)
		cgroup_lock_and_drain_offline(cgrp);
	अन्यथा
		mutex_lock(&cgroup_mutex);

	अगर (!cgroup_is_dead(cgrp))
		वापस cgrp;

	cgroup_kn_unlock(kn);
	वापस शून्य;
पूर्ण

अटल व्योम cgroup_rm_file(काष्ठा cgroup *cgrp, स्थिर काष्ठा cftype *cft)
अणु
	अक्षर name[CGROUP_खाता_NAME_MAX];

	lockdep_निश्चित_held(&cgroup_mutex);

	अगर (cft->file_offset) अणु
		काष्ठा cgroup_subsys_state *css = cgroup_css(cgrp, cft->ss);
		काष्ठा cgroup_file *cfile = (व्योम *)css + cft->file_offset;

		spin_lock_irq(&cgroup_file_kn_lock);
		cfile->kn = शून्य;
		spin_unlock_irq(&cgroup_file_kn_lock);

		del_समयr_sync(&cfile->notअगरy_समयr);
	पूर्ण

	kernfs_हटाओ_by_name(cgrp->kn, cgroup_file_name(cgrp, cft, name));
पूर्ण

/**
 * css_clear_dir - हटाओ subsys files in a cgroup directory
 * @css: target css
 */
अटल व्योम css_clear_dir(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा cgroup *cgrp = css->cgroup;
	काष्ठा cftype *cfts;

	अगर (!(css->flags & CSS_VISIBLE))
		वापस;

	css->flags &= ~CSS_VISIBLE;

	अगर (!css->ss) अणु
		अगर (cgroup_on_dfl(cgrp))
			cfts = cgroup_base_files;
		अन्यथा
			cfts = cgroup1_base_files;

		cgroup_addrm_files(css, cgrp, cfts, false);
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry(cfts, &css->ss->cfts, node)
			cgroup_addrm_files(css, cgrp, cfts, false);
	पूर्ण
पूर्ण

/**
 * css_populate_dir - create subsys files in a cgroup directory
 * @css: target css
 *
 * On failure, no file is added.
 */
अटल पूर्णांक css_populate_dir(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा cgroup *cgrp = css->cgroup;
	काष्ठा cftype *cfts, *failed_cfts;
	पूर्णांक ret;

	अगर ((css->flags & CSS_VISIBLE) || !cgrp->kn)
		वापस 0;

	अगर (!css->ss) अणु
		अगर (cgroup_on_dfl(cgrp))
			cfts = cgroup_base_files;
		अन्यथा
			cfts = cgroup1_base_files;

		ret = cgroup_addrm_files(&cgrp->self, cgrp, cfts, true);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry(cfts, &css->ss->cfts, node) अणु
			ret = cgroup_addrm_files(css, cgrp, cfts, true);
			अगर (ret < 0) अणु
				failed_cfts = cfts;
				जाओ err;
			पूर्ण
		पूर्ण
	पूर्ण

	css->flags |= CSS_VISIBLE;

	वापस 0;
err:
	list_क्रम_each_entry(cfts, &css->ss->cfts, node) अणु
		अगर (cfts == failed_cfts)
			अवरोध;
		cgroup_addrm_files(css, cgrp, cfts, false);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक rebind_subप्रणालीs(काष्ठा cgroup_root *dst_root, u16 ss_mask)
अणु
	काष्ठा cgroup *dcgrp = &dst_root->cgrp;
	काष्ठा cgroup_subsys *ss;
	पूर्णांक ssid, i, ret;

	lockdep_निश्चित_held(&cgroup_mutex);

	करो_each_subsys_mask(ss, ssid, ss_mask) अणु
		/*
		 * If @ss has non-root csses attached to it, can't move.
		 * If @ss is an implicit controller, it is exempt from this
		 * rule and can be stolen.
		 */
		अगर (css_next_child(शून्य, cgroup_css(&ss->root->cgrp, ss)) &&
		    !ss->implicit_on_dfl)
			वापस -EBUSY;

		/* can't move between two non-dummy roots either */
		अगर (ss->root != &cgrp_dfl_root && dst_root != &cgrp_dfl_root)
			वापस -EBUSY;
	पूर्ण जबतक_each_subsys_mask();

	करो_each_subsys_mask(ss, ssid, ss_mask) अणु
		काष्ठा cgroup_root *src_root = ss->root;
		काष्ठा cgroup *scgrp = &src_root->cgrp;
		काष्ठा cgroup_subsys_state *css = cgroup_css(scgrp, ss);
		काष्ठा css_set *cset;

		WARN_ON(!css || cgroup_css(dcgrp, ss));

		/* disable from the source */
		src_root->subsys_mask &= ~(1 << ssid);
		WARN_ON(cgroup_apply_control(scgrp));
		cgroup_finalize_control(scgrp, 0);

		/* rebind */
		RCU_INIT_POINTER(scgrp->subsys[ssid], शून्य);
		rcu_assign_poपूर्णांकer(dcgrp->subsys[ssid], css);
		ss->root = dst_root;
		css->cgroup = dcgrp;

		spin_lock_irq(&css_set_lock);
		hash_क्रम_each(css_set_table, i, cset, hlist)
			list_move_tail(&cset->e_cset_node[ss->id],
				       &dcgrp->e_csets[ss->id]);
		spin_unlock_irq(&css_set_lock);

		अगर (ss->css_rstat_flush) अणु
			list_del_rcu(&css->rstat_css_node);
			list_add_rcu(&css->rstat_css_node,
				     &dcgrp->rstat_css_list);
		पूर्ण

		/* शेष hierarchy करोesn't enable controllers by शेष */
		dst_root->subsys_mask |= 1 << ssid;
		अगर (dst_root == &cgrp_dfl_root) अणु
			अटल_branch_enable(cgroup_subsys_on_dfl_key[ssid]);
		पूर्ण अन्यथा अणु
			dcgrp->subtree_control |= 1 << ssid;
			अटल_branch_disable(cgroup_subsys_on_dfl_key[ssid]);
		पूर्ण

		ret = cgroup_apply_control(dcgrp);
		अगर (ret)
			pr_warn("partial failure to rebind %s controller (err=%d)\n",
				ss->name, ret);

		अगर (ss->bind)
			ss->bind(css);
	पूर्ण जबतक_each_subsys_mask();

	kernfs_activate(dcgrp->kn);
	वापस 0;
पूर्ण

पूर्णांक cgroup_show_path(काष्ठा seq_file *sf, काष्ठा kernfs_node *kf_node,
		     काष्ठा kernfs_root *kf_root)
अणु
	पूर्णांक len = 0;
	अक्षर *buf = शून्य;
	काष्ठा cgroup_root *kf_cgroot = cgroup_root_from_kf(kf_root);
	काष्ठा cgroup *ns_cgroup;

	buf = kदो_स्मृति(PATH_MAX, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	spin_lock_irq(&css_set_lock);
	ns_cgroup = current_cgns_cgroup_from_root(kf_cgroot);
	len = kernfs_path_from_node(kf_node, ns_cgroup->kn, buf, PATH_MAX);
	spin_unlock_irq(&css_set_lock);

	अगर (len >= PATH_MAX)
		len = -दुस्फल;
	अन्यथा अगर (len > 0) अणु
		seq_escape(sf, buf, " \t\n\\");
		len = 0;
	पूर्ण
	kमुक्त(buf);
	वापस len;
पूर्ण

क्रमागत cgroup2_param अणु
	Opt_nsdelegate,
	Opt_memory_localevents,
	Opt_memory_recursiveprot,
	nr__cgroup2_params
पूर्ण;

अटल स्थिर काष्ठा fs_parameter_spec cgroup2_fs_parameters[] = अणु
	fsparam_flag("nsdelegate",		Opt_nsdelegate),
	fsparam_flag("memory_localevents",	Opt_memory_localevents),
	fsparam_flag("memory_recursiveprot",	Opt_memory_recursiveprot),
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक cgroup2_parse_param(काष्ठा fs_context *fc, काष्ठा fs_parameter *param)
अणु
	काष्ठा cgroup_fs_context *ctx = cgroup_fc2context(fc);
	काष्ठा fs_parse_result result;
	पूर्णांक opt;

	opt = fs_parse(fc, cgroup2_fs_parameters, param, &result);
	अगर (opt < 0)
		वापस opt;

	चयन (opt) अणु
	हाल Opt_nsdelegate:
		ctx->flags |= CGRP_ROOT_NS_DELEGATE;
		वापस 0;
	हाल Opt_memory_localevents:
		ctx->flags |= CGRP_ROOT_MEMORY_LOCAL_EVENTS;
		वापस 0;
	हाल Opt_memory_recursiveprot:
		ctx->flags |= CGRP_ROOT_MEMORY_RECURSIVE_PROT;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल व्योम apply_cgroup_root_flags(अचिन्हित पूर्णांक root_flags)
अणु
	अगर (current->nsproxy->cgroup_ns == &init_cgroup_ns) अणु
		अगर (root_flags & CGRP_ROOT_NS_DELEGATE)
			cgrp_dfl_root.flags |= CGRP_ROOT_NS_DELEGATE;
		अन्यथा
			cgrp_dfl_root.flags &= ~CGRP_ROOT_NS_DELEGATE;

		अगर (root_flags & CGRP_ROOT_MEMORY_LOCAL_EVENTS)
			cgrp_dfl_root.flags |= CGRP_ROOT_MEMORY_LOCAL_EVENTS;
		अन्यथा
			cgrp_dfl_root.flags &= ~CGRP_ROOT_MEMORY_LOCAL_EVENTS;

		अगर (root_flags & CGRP_ROOT_MEMORY_RECURSIVE_PROT)
			cgrp_dfl_root.flags |= CGRP_ROOT_MEMORY_RECURSIVE_PROT;
		अन्यथा
			cgrp_dfl_root.flags &= ~CGRP_ROOT_MEMORY_RECURSIVE_PROT;
	पूर्ण
पूर्ण

अटल पूर्णांक cgroup_show_options(काष्ठा seq_file *seq, काष्ठा kernfs_root *kf_root)
अणु
	अगर (cgrp_dfl_root.flags & CGRP_ROOT_NS_DELEGATE)
		seq_माला_दो(seq, ",nsdelegate");
	अगर (cgrp_dfl_root.flags & CGRP_ROOT_MEMORY_LOCAL_EVENTS)
		seq_माला_दो(seq, ",memory_localevents");
	अगर (cgrp_dfl_root.flags & CGRP_ROOT_MEMORY_RECURSIVE_PROT)
		seq_माला_दो(seq, ",memory_recursiveprot");
	वापस 0;
पूर्ण

अटल पूर्णांक cgroup_reconfigure(काष्ठा fs_context *fc)
अणु
	काष्ठा cgroup_fs_context *ctx = cgroup_fc2context(fc);

	apply_cgroup_root_flags(ctx->flags);
	वापस 0;
पूर्ण

अटल व्योम init_cgroup_housekeeping(काष्ठा cgroup *cgrp)
अणु
	काष्ठा cgroup_subsys *ss;
	पूर्णांक ssid;

	INIT_LIST_HEAD(&cgrp->self.sibling);
	INIT_LIST_HEAD(&cgrp->self.children);
	INIT_LIST_HEAD(&cgrp->cset_links);
	INIT_LIST_HEAD(&cgrp->pidlists);
	mutex_init(&cgrp->pidlist_mutex);
	cgrp->self.cgroup = cgrp;
	cgrp->self.flags |= CSS_ONLINE;
	cgrp->करोm_cgrp = cgrp;
	cgrp->max_descendants = पूर्णांक_उच्च;
	cgrp->max_depth = पूर्णांक_उच्च;
	INIT_LIST_HEAD(&cgrp->rstat_css_list);
	prev_cpuसमय_init(&cgrp->prev_cpuसमय);

	क्रम_each_subsys(ss, ssid)
		INIT_LIST_HEAD(&cgrp->e_csets[ssid]);

	init_रुकोqueue_head(&cgrp->offline_रुकोq);
	INIT_WORK(&cgrp->release_agent_work, cgroup1_release_agent);
पूर्ण

व्योम init_cgroup_root(काष्ठा cgroup_fs_context *ctx)
अणु
	काष्ठा cgroup_root *root = ctx->root;
	काष्ठा cgroup *cgrp = &root->cgrp;

	INIT_LIST_HEAD(&root->root_list);
	atomic_set(&root->nr_cgrps, 1);
	cgrp->root = root;
	init_cgroup_housekeeping(cgrp);

	root->flags = ctx->flags;
	अगर (ctx->release_agent)
		strscpy(root->release_agent_path, ctx->release_agent, PATH_MAX);
	अगर (ctx->name)
		strscpy(root->name, ctx->name, MAX_CGROUP_ROOT_NAMELEN);
	अगर (ctx->cpuset_clone_children)
		set_bit(CGRP_CPUSET_CLONE_CHILDREN, &root->cgrp.flags);
पूर्ण

पूर्णांक cgroup_setup_root(काष्ठा cgroup_root *root, u16 ss_mask)
अणु
	LIST_HEAD(पंचांगp_links);
	काष्ठा cgroup *root_cgrp = &root->cgrp;
	काष्ठा kernfs_syscall_ops *kf_sops;
	काष्ठा css_set *cset;
	पूर्णांक i, ret;

	lockdep_निश्चित_held(&cgroup_mutex);

	ret = percpu_ref_init(&root_cgrp->self.refcnt, css_release,
			      0, GFP_KERNEL);
	अगर (ret)
		जाओ out;

	/*
	 * We're accessing css_set_count without locking css_set_lock here,
	 * but that's OK - it can only be increased by someone holding
	 * cgroup_lock, and that's us.  Later rebinding may disable
	 * controllers on the शेष hierarchy and thus create new csets,
	 * which can't be more than the existing ones.  Allocate 2x.
	 */
	ret = allocate_cgrp_cset_links(2 * css_set_count, &पंचांगp_links);
	अगर (ret)
		जाओ cancel_ref;

	ret = cgroup_init_root_id(root);
	अगर (ret)
		जाओ cancel_ref;

	kf_sops = root == &cgrp_dfl_root ?
		&cgroup_kf_syscall_ops : &cgroup1_kf_syscall_ops;

	root->kf_root = kernfs_create_root(kf_sops,
					   KERNFS_ROOT_CREATE_DEACTIVATED |
					   KERNFS_ROOT_SUPPORT_EXPORTOP |
					   KERNFS_ROOT_SUPPORT_USER_XATTR,
					   root_cgrp);
	अगर (IS_ERR(root->kf_root)) अणु
		ret = PTR_ERR(root->kf_root);
		जाओ निकास_root_id;
	पूर्ण
	root_cgrp->kn = root->kf_root->kn;
	WARN_ON_ONCE(cgroup_ino(root_cgrp) != 1);
	root_cgrp->ancestor_ids[0] = cgroup_id(root_cgrp);

	ret = css_populate_dir(&root_cgrp->self);
	अगर (ret)
		जाओ destroy_root;

	ret = cgroup_rstat_init(root_cgrp);
	अगर (ret)
		जाओ destroy_root;

	ret = rebind_subप्रणालीs(root, ss_mask);
	अगर (ret)
		जाओ निकास_stats;

	ret = cgroup_bpf_inherit(root_cgrp);
	WARN_ON_ONCE(ret);

	trace_cgroup_setup_root(root);

	/*
	 * There must be no failure हाल after here, since rebinding takes
	 * care of subप्रणालीs' refcounts, which are explicitly dropped in
	 * the failure निकास path.
	 */
	list_add(&root->root_list, &cgroup_roots);
	cgroup_root_count++;

	/*
	 * Link the root cgroup in this hierarchy पूर्णांकo all the css_set
	 * objects.
	 */
	spin_lock_irq(&css_set_lock);
	hash_क्रम_each(css_set_table, i, cset, hlist) अणु
		link_css_set(&पंचांगp_links, cset, root_cgrp);
		अगर (css_set_populated(cset))
			cgroup_update_populated(root_cgrp, true);
	पूर्ण
	spin_unlock_irq(&css_set_lock);

	BUG_ON(!list_empty(&root_cgrp->self.children));
	BUG_ON(atomic_पढ़ो(&root->nr_cgrps) != 1);

	ret = 0;
	जाओ out;

निकास_stats:
	cgroup_rstat_निकास(root_cgrp);
destroy_root:
	kernfs_destroy_root(root->kf_root);
	root->kf_root = शून्य;
निकास_root_id:
	cgroup_निकास_root_id(root);
cancel_ref:
	percpu_ref_निकास(&root_cgrp->self.refcnt);
out:
	मुक्त_cgrp_cset_links(&पंचांगp_links);
	वापस ret;
पूर्ण

पूर्णांक cgroup_करो_get_tree(काष्ठा fs_context *fc)
अणु
	काष्ठा cgroup_fs_context *ctx = cgroup_fc2context(fc);
	पूर्णांक ret;

	ctx->kfc.root = ctx->root->kf_root;
	अगर (fc->fs_type == &cgroup2_fs_type)
		ctx->kfc.magic = CGROUP2_SUPER_MAGIC;
	अन्यथा
		ctx->kfc.magic = CGROUP_SUPER_MAGIC;
	ret = kernfs_get_tree(fc);

	/*
	 * In non-init cgroup namespace, instead of root cgroup's dentry,
	 * we वापस the dentry corresponding to the cgroupns->root_cgrp.
	 */
	अगर (!ret && ctx->ns != &init_cgroup_ns) अणु
		काष्ठा dentry *nsdentry;
		काष्ठा super_block *sb = fc->root->d_sb;
		काष्ठा cgroup *cgrp;

		mutex_lock(&cgroup_mutex);
		spin_lock_irq(&css_set_lock);

		cgrp = cset_cgroup_from_root(ctx->ns->root_cset, ctx->root);

		spin_unlock_irq(&css_set_lock);
		mutex_unlock(&cgroup_mutex);

		nsdentry = kernfs_node_dentry(cgrp->kn, sb);
		dput(fc->root);
		अगर (IS_ERR(nsdentry)) अणु
			deactivate_locked_super(sb);
			ret = PTR_ERR(nsdentry);
			nsdentry = शून्य;
		पूर्ण
		fc->root = nsdentry;
	पूर्ण

	अगर (!ctx->kfc.new_sb_created)
		cgroup_put(&ctx->root->cgrp);

	वापस ret;
पूर्ण

/*
 * Destroy a cgroup fileप्रणाली context.
 */
अटल व्योम cgroup_fs_context_मुक्त(काष्ठा fs_context *fc)
अणु
	काष्ठा cgroup_fs_context *ctx = cgroup_fc2context(fc);

	kमुक्त(ctx->name);
	kमुक्त(ctx->release_agent);
	put_cgroup_ns(ctx->ns);
	kernfs_मुक्त_fs_context(fc);
	kमुक्त(ctx);
पूर्ण

अटल पूर्णांक cgroup_get_tree(काष्ठा fs_context *fc)
अणु
	काष्ठा cgroup_fs_context *ctx = cgroup_fc2context(fc);
	पूर्णांक ret;

	cgrp_dfl_visible = true;
	cgroup_get_live(&cgrp_dfl_root.cgrp);
	ctx->root = &cgrp_dfl_root;

	ret = cgroup_करो_get_tree(fc);
	अगर (!ret)
		apply_cgroup_root_flags(ctx->flags);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा fs_context_operations cgroup_fs_context_ops = अणु
	.मुक्त		= cgroup_fs_context_मुक्त,
	.parse_param	= cgroup2_parse_param,
	.get_tree	= cgroup_get_tree,
	.reconfigure	= cgroup_reconfigure,
पूर्ण;

अटल स्थिर काष्ठा fs_context_operations cgroup1_fs_context_ops = अणु
	.मुक्त		= cgroup_fs_context_मुक्त,
	.parse_param	= cgroup1_parse_param,
	.get_tree	= cgroup1_get_tree,
	.reconfigure	= cgroup1_reconfigure,
पूर्ण;

/*
 * Initialise the cgroup fileप्रणाली creation/reconfiguration context.  Notably,
 * we select the namespace we're going to use.
 */
अटल पूर्णांक cgroup_init_fs_context(काष्ठा fs_context *fc)
अणु
	काष्ठा cgroup_fs_context *ctx;

	ctx = kzalloc(माप(काष्ठा cgroup_fs_context), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->ns = current->nsproxy->cgroup_ns;
	get_cgroup_ns(ctx->ns);
	fc->fs_निजी = &ctx->kfc;
	अगर (fc->fs_type == &cgroup2_fs_type)
		fc->ops = &cgroup_fs_context_ops;
	अन्यथा
		fc->ops = &cgroup1_fs_context_ops;
	put_user_ns(fc->user_ns);
	fc->user_ns = get_user_ns(ctx->ns->user_ns);
	fc->global = true;
	वापस 0;
पूर्ण

अटल व्योम cgroup_समाप्त_sb(काष्ठा super_block *sb)
अणु
	काष्ठा kernfs_root *kf_root = kernfs_root_from_sb(sb);
	काष्ठा cgroup_root *root = cgroup_root_from_kf(kf_root);

	/*
	 * If @root करोesn't have any children, start समाप्तing it.
	 * This prevents new mounts by disabling percpu_ref_tryget_live().
	 * cgroup_mount() may रुको क्रम @root's release.
	 *
	 * And करोn't समाप्त the शेष root.
	 */
	अगर (list_empty(&root->cgrp.self.children) && root != &cgrp_dfl_root &&
	    !percpu_ref_is_dying(&root->cgrp.self.refcnt))
		percpu_ref_समाप्त(&root->cgrp.self.refcnt);
	cgroup_put(&root->cgrp);
	kernfs_समाप्त_sb(sb);
पूर्ण

काष्ठा file_प्रणाली_type cgroup_fs_type = अणु
	.name			= "cgroup",
	.init_fs_context	= cgroup_init_fs_context,
	.parameters		= cgroup1_fs_parameters,
	.समाप्त_sb		= cgroup_समाप्त_sb,
	.fs_flags		= FS_USERNS_MOUNT,
पूर्ण;

अटल काष्ठा file_प्रणाली_type cgroup2_fs_type = अणु
	.name			= "cgroup2",
	.init_fs_context	= cgroup_init_fs_context,
	.parameters		= cgroup2_fs_parameters,
	.समाप्त_sb		= cgroup_समाप्त_sb,
	.fs_flags		= FS_USERNS_MOUNT,
पूर्ण;

#अगर_घोषित CONFIG_CPUSETS
अटल स्थिर काष्ठा fs_context_operations cpuset_fs_context_ops = अणु
	.get_tree	= cgroup1_get_tree,
	.मुक्त		= cgroup_fs_context_मुक्त,
पूर्ण;

/*
 * This is ugly, but preserves the userspace API क्रम existing cpuset
 * users. If someone tries to mount the "cpuset" fileप्रणाली, we
 * silently चयन it to mount "cgroup" instead
 */
अटल पूर्णांक cpuset_init_fs_context(काष्ठा fs_context *fc)
अणु
	अक्षर *agent = kstrdup("/sbin/cpuset_release_agent", GFP_USER);
	काष्ठा cgroup_fs_context *ctx;
	पूर्णांक err;

	err = cgroup_init_fs_context(fc);
	अगर (err) अणु
		kमुक्त(agent);
		वापस err;
	पूर्ण

	fc->ops = &cpuset_fs_context_ops;

	ctx = cgroup_fc2context(fc);
	ctx->subsys_mask = 1 << cpuset_cgrp_id;
	ctx->flags |= CGRP_ROOT_NOPREFIX;
	ctx->release_agent = agent;

	get_fileप्रणाली(&cgroup_fs_type);
	put_fileप्रणाली(fc->fs_type);
	fc->fs_type = &cgroup_fs_type;

	वापस 0;
पूर्ण

अटल काष्ठा file_प्रणाली_type cpuset_fs_type = अणु
	.name			= "cpuset",
	.init_fs_context	= cpuset_init_fs_context,
	.fs_flags		= FS_USERNS_MOUNT,
पूर्ण;
#पूर्ण_अगर

पूर्णांक cgroup_path_ns_locked(काष्ठा cgroup *cgrp, अक्षर *buf, माप_प्रकार buflen,
			  काष्ठा cgroup_namespace *ns)
अणु
	काष्ठा cgroup *root = cset_cgroup_from_root(ns->root_cset, cgrp->root);

	वापस kernfs_path_from_node(cgrp->kn, root->kn, buf, buflen);
पूर्ण

पूर्णांक cgroup_path_ns(काष्ठा cgroup *cgrp, अक्षर *buf, माप_प्रकार buflen,
		   काष्ठा cgroup_namespace *ns)
अणु
	पूर्णांक ret;

	mutex_lock(&cgroup_mutex);
	spin_lock_irq(&css_set_lock);

	ret = cgroup_path_ns_locked(cgrp, buf, buflen, ns);

	spin_unlock_irq(&css_set_lock);
	mutex_unlock(&cgroup_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(cgroup_path_ns);

/**
 * task_cgroup_path - cgroup path of a task in the first cgroup hierarchy
 * @task: target task
 * @buf: the buffer to ग_लिखो the path पूर्णांकo
 * @buflen: the length of the buffer
 *
 * Determine @task's cgroup on the first (the one with the lowest non-zero
 * hierarchy_id) cgroup hierarchy and copy its path पूर्णांकo @buf.  This
 * function grअसल cgroup_mutex and shouldn't be used inside locks used by
 * cgroup controller callbacks.
 *
 * Return value is the same as kernfs_path().
 */
पूर्णांक task_cgroup_path(काष्ठा task_काष्ठा *task, अक्षर *buf, माप_प्रकार buflen)
अणु
	काष्ठा cgroup_root *root;
	काष्ठा cgroup *cgrp;
	पूर्णांक hierarchy_id = 1;
	पूर्णांक ret;

	mutex_lock(&cgroup_mutex);
	spin_lock_irq(&css_set_lock);

	root = idr_get_next(&cgroup_hierarchy_idr, &hierarchy_id);

	अगर (root) अणु
		cgrp = task_cgroup_from_root(task, root);
		ret = cgroup_path_ns_locked(cgrp, buf, buflen, &init_cgroup_ns);
	पूर्ण अन्यथा अणु
		/* अगर no hierarchy exists, everyone is in "/" */
		ret = strlcpy(buf, "/", buflen);
	पूर्ण

	spin_unlock_irq(&css_set_lock);
	mutex_unlock(&cgroup_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(task_cgroup_path);

/**
 * cgroup_migrate_add_task - add a migration target task to a migration context
 * @task: target task
 * @mgctx: target migration context
 *
 * Add @task, which is a migration target, to @mgctx->tset.  This function
 * becomes noop अगर @task करोesn't need to be migrated.  @task's css_set
 * should have been added as a migration source and @task->cg_list will be
 * moved from the css_set's tasks list to mg_tasks one.
 */
अटल व्योम cgroup_migrate_add_task(काष्ठा task_काष्ठा *task,
				    काष्ठा cgroup_mgctx *mgctx)
अणु
	काष्ठा css_set *cset;

	lockdep_निश्चित_held(&css_set_lock);

	/* @task either alपढ़ोy निकासed or can't निकास until the end */
	अगर (task->flags & PF_EXITING)
		वापस;

	/* cgroup_thपढ़ोgroup_rwsem protects racing against विभाजनs */
	WARN_ON_ONCE(list_empty(&task->cg_list));

	cset = task_css_set(task);
	अगर (!cset->mg_src_cgrp)
		वापस;

	mgctx->tset.nr_tasks++;

	list_move_tail(&task->cg_list, &cset->mg_tasks);
	अगर (list_empty(&cset->mg_node))
		list_add_tail(&cset->mg_node,
			      &mgctx->tset.src_csets);
	अगर (list_empty(&cset->mg_dst_cset->mg_node))
		list_add_tail(&cset->mg_dst_cset->mg_node,
			      &mgctx->tset.dst_csets);
पूर्ण

/**
 * cgroup_taskset_first - reset taskset and वापस the first task
 * @tset: taskset of पूर्णांकerest
 * @dst_cssp: output variable क्रम the destination css
 *
 * @tset iteration is initialized and the first task is वापसed.
 */
काष्ठा task_काष्ठा *cgroup_taskset_first(काष्ठा cgroup_taskset *tset,
					 काष्ठा cgroup_subsys_state **dst_cssp)
अणु
	tset->cur_cset = list_first_entry(tset->csets, काष्ठा css_set, mg_node);
	tset->cur_task = शून्य;

	वापस cgroup_taskset_next(tset, dst_cssp);
पूर्ण

/**
 * cgroup_taskset_next - iterate to the next task in taskset
 * @tset: taskset of पूर्णांकerest
 * @dst_cssp: output variable क्रम the destination css
 *
 * Return the next task in @tset.  Iteration must have been initialized
 * with cgroup_taskset_first().
 */
काष्ठा task_काष्ठा *cgroup_taskset_next(काष्ठा cgroup_taskset *tset,
					काष्ठा cgroup_subsys_state **dst_cssp)
अणु
	काष्ठा css_set *cset = tset->cur_cset;
	काष्ठा task_काष्ठा *task = tset->cur_task;

	जबतक (&cset->mg_node != tset->csets) अणु
		अगर (!task)
			task = list_first_entry(&cset->mg_tasks,
						काष्ठा task_काष्ठा, cg_list);
		अन्यथा
			task = list_next_entry(task, cg_list);

		अगर (&task->cg_list != &cset->mg_tasks) अणु
			tset->cur_cset = cset;
			tset->cur_task = task;

			/*
			 * This function may be called both beक्रमe and
			 * after cgroup_taskset_migrate().  The two हालs
			 * can be distinguished by looking at whether @cset
			 * has its ->mg_dst_cset set.
			 */
			अगर (cset->mg_dst_cset)
				*dst_cssp = cset->mg_dst_cset->subsys[tset->ssid];
			अन्यथा
				*dst_cssp = cset->subsys[tset->ssid];

			वापस task;
		पूर्ण

		cset = list_next_entry(cset, mg_node);
		task = शून्य;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * cgroup_taskset_migrate - migrate a taskset
 * @mgctx: migration context
 *
 * Migrate tasks in @mgctx as setup by migration preparation functions.
 * This function fails अगरf one of the ->can_attach callbacks fails and
 * guarantees that either all or none of the tasks in @mgctx are migrated.
 * @mgctx is consumed regardless of success.
 */
अटल पूर्णांक cgroup_migrate_execute(काष्ठा cgroup_mgctx *mgctx)
अणु
	काष्ठा cgroup_taskset *tset = &mgctx->tset;
	काष्ठा cgroup_subsys *ss;
	काष्ठा task_काष्ठा *task, *पंचांगp_task;
	काष्ठा css_set *cset, *पंचांगp_cset;
	पूर्णांक ssid, failed_ssid, ret;

	/* check that we can legitimately attach to the cgroup */
	अगर (tset->nr_tasks) अणु
		करो_each_subsys_mask(ss, ssid, mgctx->ss_mask) अणु
			अगर (ss->can_attach) अणु
				tset->ssid = ssid;
				ret = ss->can_attach(tset);
				अगर (ret) अणु
					failed_ssid = ssid;
					जाओ out_cancel_attach;
				पूर्ण
			पूर्ण
		पूर्ण जबतक_each_subsys_mask();
	पूर्ण

	/*
	 * Now that we're guaranteed success, proceed to move all tasks to
	 * the new cgroup.  There are no failure हालs after here, so this
	 * is the commit poपूर्णांक.
	 */
	spin_lock_irq(&css_set_lock);
	list_क्रम_each_entry(cset, &tset->src_csets, mg_node) अणु
		list_क्रम_each_entry_safe(task, पंचांगp_task, &cset->mg_tasks, cg_list) अणु
			काष्ठा css_set *from_cset = task_css_set(task);
			काष्ठा css_set *to_cset = cset->mg_dst_cset;

			get_css_set(to_cset);
			to_cset->nr_tasks++;
			css_set_move_task(task, from_cset, to_cset, true);
			from_cset->nr_tasks--;
			/*
			 * If the source or destination cgroup is frozen,
			 * the task might require to change its state.
			 */
			cgroup_मुक्तzer_migrate_task(task, from_cset->dfl_cgrp,
						    to_cset->dfl_cgrp);
			put_css_set_locked(from_cset);

		पूर्ण
	पूर्ण
	spin_unlock_irq(&css_set_lock);

	/*
	 * Migration is committed, all target tasks are now on dst_csets.
	 * Nothing is sensitive to विभाजन() after this poपूर्णांक.  Notअगरy
	 * controllers that migration is complete.
	 */
	tset->csets = &tset->dst_csets;

	अगर (tset->nr_tasks) अणु
		करो_each_subsys_mask(ss, ssid, mgctx->ss_mask) अणु
			अगर (ss->attach) अणु
				tset->ssid = ssid;
				ss->attach(tset);
			पूर्ण
		पूर्ण जबतक_each_subsys_mask();
	पूर्ण

	ret = 0;
	जाओ out_release_tset;

out_cancel_attach:
	अगर (tset->nr_tasks) अणु
		करो_each_subsys_mask(ss, ssid, mgctx->ss_mask) अणु
			अगर (ssid == failed_ssid)
				अवरोध;
			अगर (ss->cancel_attach) अणु
				tset->ssid = ssid;
				ss->cancel_attach(tset);
			पूर्ण
		पूर्ण जबतक_each_subsys_mask();
	पूर्ण
out_release_tset:
	spin_lock_irq(&css_set_lock);
	list_splice_init(&tset->dst_csets, &tset->src_csets);
	list_क्रम_each_entry_safe(cset, पंचांगp_cset, &tset->src_csets, mg_node) अणु
		list_splice_tail_init(&cset->mg_tasks, &cset->tasks);
		list_del_init(&cset->mg_node);
	पूर्ण
	spin_unlock_irq(&css_set_lock);

	/*
	 * Re-initialize the cgroup_taskset काष्ठाure in हाल it is reused
	 * again in another cgroup_migrate_add_task()/cgroup_migrate_execute()
	 * iteration.
	 */
	tset->nr_tasks = 0;
	tset->csets    = &tset->src_csets;
	वापस ret;
पूर्ण

/**
 * cgroup_migrate_vet_dst - verअगरy whether a cgroup can be migration destination
 * @dst_cgrp: destination cgroup to test
 *
 * On the शेष hierarchy, except क्रम the mixable, (possible) thपढ़ो root
 * and thपढ़ोed cgroups, subtree_control must be zero क्रम migration
 * destination cgroups with tasks so that child cgroups करोn't compete
 * against tasks.
 */
पूर्णांक cgroup_migrate_vet_dst(काष्ठा cgroup *dst_cgrp)
अणु
	/* v1 करोesn't have any restriction */
	अगर (!cgroup_on_dfl(dst_cgrp))
		वापस 0;

	/* verअगरy @dst_cgrp can host resources */
	अगर (!cgroup_is_valid_करोमुख्य(dst_cgrp->करोm_cgrp))
		वापस -EOPNOTSUPP;

	/* mixables करोn't care */
	अगर (cgroup_is_mixable(dst_cgrp))
		वापस 0;

	/*
	 * If @dst_cgrp is alपढ़ोy or can become a thपढ़ो root or is
	 * thपढ़ोed, it करोesn't matter.
	 */
	अगर (cgroup_can_be_thपढ़ो_root(dst_cgrp) || cgroup_is_thपढ़ोed(dst_cgrp))
		वापस 0;

	/* apply no-पूर्णांकernal-process स्थिरraपूर्णांक */
	अगर (dst_cgrp->subtree_control)
		वापस -EBUSY;

	वापस 0;
पूर्ण

/**
 * cgroup_migrate_finish - cleanup after attach
 * @mgctx: migration context
 *
 * Unकरो cgroup_migrate_add_src() and cgroup_migrate_prepare_dst().  See
 * those functions क्रम details.
 */
व्योम cgroup_migrate_finish(काष्ठा cgroup_mgctx *mgctx)
अणु
	LIST_HEAD(preloaded);
	काष्ठा css_set *cset, *पंचांगp_cset;

	lockdep_निश्चित_held(&cgroup_mutex);

	spin_lock_irq(&css_set_lock);

	list_splice_tail_init(&mgctx->preloaded_src_csets, &preloaded);
	list_splice_tail_init(&mgctx->preloaded_dst_csets, &preloaded);

	list_क्रम_each_entry_safe(cset, पंचांगp_cset, &preloaded, mg_preload_node) अणु
		cset->mg_src_cgrp = शून्य;
		cset->mg_dst_cgrp = शून्य;
		cset->mg_dst_cset = शून्य;
		list_del_init(&cset->mg_preload_node);
		put_css_set_locked(cset);
	पूर्ण

	spin_unlock_irq(&css_set_lock);
पूर्ण

/**
 * cgroup_migrate_add_src - add a migration source css_set
 * @src_cset: the source css_set to add
 * @dst_cgrp: the destination cgroup
 * @mgctx: migration context
 *
 * Tasks beदीर्घing to @src_cset are about to be migrated to @dst_cgrp.  Pin
 * @src_cset and add it to @mgctx->src_csets, which should later be cleaned
 * up by cgroup_migrate_finish().
 *
 * This function may be called without holding cgroup_thपढ़ोgroup_rwsem
 * even अगर the target is a process.  Thपढ़ोs may be created and destroyed
 * but as दीर्घ as cgroup_mutex is not dropped, no new css_set can be put
 * पूर्णांकo play and the preloaded css_sets are guaranteed to cover all
 * migrations.
 */
व्योम cgroup_migrate_add_src(काष्ठा css_set *src_cset,
			    काष्ठा cgroup *dst_cgrp,
			    काष्ठा cgroup_mgctx *mgctx)
अणु
	काष्ठा cgroup *src_cgrp;

	lockdep_निश्चित_held(&cgroup_mutex);
	lockdep_निश्चित_held(&css_set_lock);

	/*
	 * If ->dead, @src_set is associated with one or more dead cgroups
	 * and करोesn't contain any migratable tasks.  Ignore it early so
	 * that the rest of migration path करोesn't get confused by it.
	 */
	अगर (src_cset->dead)
		वापस;

	src_cgrp = cset_cgroup_from_root(src_cset, dst_cgrp->root);

	अगर (!list_empty(&src_cset->mg_preload_node))
		वापस;

	WARN_ON(src_cset->mg_src_cgrp);
	WARN_ON(src_cset->mg_dst_cgrp);
	WARN_ON(!list_empty(&src_cset->mg_tasks));
	WARN_ON(!list_empty(&src_cset->mg_node));

	src_cset->mg_src_cgrp = src_cgrp;
	src_cset->mg_dst_cgrp = dst_cgrp;
	get_css_set(src_cset);
	list_add_tail(&src_cset->mg_preload_node, &mgctx->preloaded_src_csets);
पूर्ण

/**
 * cgroup_migrate_prepare_dst - prepare destination css_sets क्रम migration
 * @mgctx: migration context
 *
 * Tasks are about to be moved and all the source css_sets have been
 * preloaded to @mgctx->preloaded_src_csets.  This function looks up and
 * pins all destination css_sets, links each to its source, and append them
 * to @mgctx->preloaded_dst_csets.
 *
 * This function must be called after cgroup_migrate_add_src() has been
 * called on each migration source css_set.  After migration is perक्रमmed
 * using cgroup_migrate(), cgroup_migrate_finish() must be called on
 * @mgctx.
 */
पूर्णांक cgroup_migrate_prepare_dst(काष्ठा cgroup_mgctx *mgctx)
अणु
	काष्ठा css_set *src_cset, *पंचांगp_cset;

	lockdep_निश्चित_held(&cgroup_mutex);

	/* look up the dst cset क्रम each src cset and link it to src */
	list_क्रम_each_entry_safe(src_cset, पंचांगp_cset, &mgctx->preloaded_src_csets,
				 mg_preload_node) अणु
		काष्ठा css_set *dst_cset;
		काष्ठा cgroup_subsys *ss;
		पूर्णांक ssid;

		dst_cset = find_css_set(src_cset, src_cset->mg_dst_cgrp);
		अगर (!dst_cset)
			वापस -ENOMEM;

		WARN_ON_ONCE(src_cset->mg_dst_cset || dst_cset->mg_dst_cset);

		/*
		 * If src cset equals dst, it's noop.  Drop the src.
		 * cgroup_migrate() will skip the cset too.  Note that we
		 * can't handle src == dst as some nodes are used by both.
		 */
		अगर (src_cset == dst_cset) अणु
			src_cset->mg_src_cgrp = शून्य;
			src_cset->mg_dst_cgrp = शून्य;
			list_del_init(&src_cset->mg_preload_node);
			put_css_set(src_cset);
			put_css_set(dst_cset);
			जारी;
		पूर्ण

		src_cset->mg_dst_cset = dst_cset;

		अगर (list_empty(&dst_cset->mg_preload_node))
			list_add_tail(&dst_cset->mg_preload_node,
				      &mgctx->preloaded_dst_csets);
		अन्यथा
			put_css_set(dst_cset);

		क्रम_each_subsys(ss, ssid)
			अगर (src_cset->subsys[ssid] != dst_cset->subsys[ssid])
				mgctx->ss_mask |= 1 << ssid;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * cgroup_migrate - migrate a process or task to a cgroup
 * @leader: the leader of the process or the task to migrate
 * @thपढ़ोgroup: whether @leader poपूर्णांकs to the whole process or a single task
 * @mgctx: migration context
 *
 * Migrate a process or task denoted by @leader.  If migrating a process,
 * the caller must be holding cgroup_thपढ़ोgroup_rwsem.  The caller is also
 * responsible क्रम invoking cgroup_migrate_add_src() and
 * cgroup_migrate_prepare_dst() on the tarमाला_लो beक्रमe invoking this
 * function and following up with cgroup_migrate_finish().
 *
 * As दीर्घ as a controller's ->can_attach() doesn't fail, this function is
 * guaranteed to succeed.  This means that, excluding ->can_attach()
 * failure, when migrating multiple tarमाला_लो, the success or failure can be
 * decided क्रम all tarमाला_लो by invoking group_migrate_prepare_dst() beक्रमe
 * actually starting migrating.
 */
पूर्णांक cgroup_migrate(काष्ठा task_काष्ठा *leader, bool thपढ़ोgroup,
		   काष्ठा cgroup_mgctx *mgctx)
अणु
	काष्ठा task_काष्ठा *task;

	/*
	 * Prevent मुक्तing of tasks जबतक we take a snapshot. Tasks that are
	 * alपढ़ोy PF_EXITING could be मुक्तd from underneath us unless we
	 * take an rcu_पढ़ो_lock.
	 */
	spin_lock_irq(&css_set_lock);
	rcu_पढ़ो_lock();
	task = leader;
	करो अणु
		cgroup_migrate_add_task(task, mgctx);
		अगर (!thपढ़ोgroup)
			अवरोध;
	पूर्ण जबतक_each_thपढ़ो(leader, task);
	rcu_पढ़ो_unlock();
	spin_unlock_irq(&css_set_lock);

	वापस cgroup_migrate_execute(mgctx);
पूर्ण

/**
 * cgroup_attach_task - attach a task or a whole thपढ़ोgroup to a cgroup
 * @dst_cgrp: the cgroup to attach to
 * @leader: the task or the leader of the thपढ़ोgroup to be attached
 * @thपढ़ोgroup: attach the whole thपढ़ोgroup?
 *
 * Call holding cgroup_mutex and cgroup_thपढ़ोgroup_rwsem.
 */
पूर्णांक cgroup_attach_task(काष्ठा cgroup *dst_cgrp, काष्ठा task_काष्ठा *leader,
		       bool thपढ़ोgroup)
अणु
	DEFINE_CGROUP_MGCTX(mgctx);
	काष्ठा task_काष्ठा *task;
	पूर्णांक ret = 0;

	/* look up all src csets */
	spin_lock_irq(&css_set_lock);
	rcu_पढ़ो_lock();
	task = leader;
	करो अणु
		cgroup_migrate_add_src(task_css_set(task), dst_cgrp, &mgctx);
		अगर (!thपढ़ोgroup)
			अवरोध;
	पूर्ण जबतक_each_thपढ़ो(leader, task);
	rcu_पढ़ो_unlock();
	spin_unlock_irq(&css_set_lock);

	/* prepare dst csets and commit */
	ret = cgroup_migrate_prepare_dst(&mgctx);
	अगर (!ret)
		ret = cgroup_migrate(leader, thपढ़ोgroup, &mgctx);

	cgroup_migrate_finish(&mgctx);

	अगर (!ret)
		TRACE_CGROUP_PATH(attach_task, dst_cgrp, leader, thपढ़ोgroup);

	वापस ret;
पूर्ण

काष्ठा task_काष्ठा *cgroup_procs_ग_लिखो_start(अक्षर *buf, bool thपढ़ोgroup,
					     bool *locked)
	__acquires(&cgroup_thपढ़ोgroup_rwsem)
अणु
	काष्ठा task_काष्ठा *tsk;
	pid_t pid;

	अगर (kstrtoपूर्णांक(म_मालाip(buf), 0, &pid) || pid < 0)
		वापस ERR_PTR(-EINVAL);

	/*
	 * If we migrate a single thपढ़ो, we करोn't care about thपढ़ोgroup
	 * stability. If the thपढ़ो is `current`, it won't निकास(2) under our
	 * hands or change PID through exec(2). We exclude
	 * cgroup_update_dfl_csses and other cgroup_अणुproc,thपढ़ोपूर्णs_ग_लिखो
	 * callers by cgroup_mutex.
	 * Thereक्रमe, we can skip the global lock.
	 */
	lockdep_निश्चित_held(&cgroup_mutex);
	अगर (pid || thपढ़ोgroup) अणु
		percpu_करोwn_ग_लिखो(&cgroup_thपढ़ोgroup_rwsem);
		*locked = true;
	पूर्ण अन्यथा अणु
		*locked = false;
	पूर्ण

	rcu_पढ़ो_lock();
	अगर (pid) अणु
		tsk = find_task_by_vpid(pid);
		अगर (!tsk) अणु
			tsk = ERR_PTR(-ESRCH);
			जाओ out_unlock_thपढ़ोgroup;
		पूर्ण
	पूर्ण अन्यथा अणु
		tsk = current;
	पूर्ण

	अगर (thपढ़ोgroup)
		tsk = tsk->group_leader;

	/*
	 * kthपढ़ोs may acquire PF_NO_SETAFFINITY during initialization.
	 * If userland migrates such a kthपढ़ो to a non-root cgroup, it can
	 * become trapped in a cpuset, or RT kthपढ़ो may be born in a
	 * cgroup with no rt_runसमय allocated.  Just say no.
	 */
	अगर (tsk->no_cgroup_migration || (tsk->flags & PF_NO_SETAFFINITY)) अणु
		tsk = ERR_PTR(-EINVAL);
		जाओ out_unlock_thपढ़ोgroup;
	पूर्ण

	get_task_काष्ठा(tsk);
	जाओ out_unlock_rcu;

out_unlock_thपढ़ोgroup:
	अगर (*locked) अणु
		percpu_up_ग_लिखो(&cgroup_thपढ़ोgroup_rwsem);
		*locked = false;
	पूर्ण
out_unlock_rcu:
	rcu_पढ़ो_unlock();
	वापस tsk;
पूर्ण

व्योम cgroup_procs_ग_लिखो_finish(काष्ठा task_काष्ठा *task, bool locked)
	__releases(&cgroup_thपढ़ोgroup_rwsem)
अणु
	काष्ठा cgroup_subsys *ss;
	पूर्णांक ssid;

	/* release reference from cgroup_procs_ग_लिखो_start() */
	put_task_काष्ठा(task);

	अगर (locked)
		percpu_up_ग_लिखो(&cgroup_thपढ़ोgroup_rwsem);
	क्रम_each_subsys(ss, ssid)
		अगर (ss->post_attach)
			ss->post_attach();
पूर्ण

अटल व्योम cgroup_prपूर्णांक_ss_mask(काष्ठा seq_file *seq, u16 ss_mask)
अणु
	काष्ठा cgroup_subsys *ss;
	bool prपूर्णांकed = false;
	पूर्णांक ssid;

	करो_each_subsys_mask(ss, ssid, ss_mask) अणु
		अगर (prपूर्णांकed)
			seq_अ_दो(seq, ' ');
		seq_माला_दो(seq, ss->name);
		prपूर्णांकed = true;
	पूर्ण जबतक_each_subsys_mask();
	अगर (prपूर्णांकed)
		seq_अ_दो(seq, '\n');
पूर्ण

/* show controllers which are enabled from the parent */
अटल पूर्णांक cgroup_controllers_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा cgroup *cgrp = seq_css(seq)->cgroup;

	cgroup_prपूर्णांक_ss_mask(seq, cgroup_control(cgrp));
	वापस 0;
पूर्ण

/* show controllers which are enabled क्रम a given cgroup's children */
अटल पूर्णांक cgroup_subtree_control_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा cgroup *cgrp = seq_css(seq)->cgroup;

	cgroup_prपूर्णांक_ss_mask(seq, cgrp->subtree_control);
	वापस 0;
पूर्ण

/**
 * cgroup_update_dfl_csses - update css assoc of a subtree in शेष hierarchy
 * @cgrp: root of the subtree to update csses क्रम
 *
 * @cgrp's control masks have changed and its subtree's css associations
 * need to be updated accordingly.  This function looks up all css_sets
 * which are attached to the subtree, creates the matching updated css_sets
 * and migrates the tasks to the new ones.
 */
अटल पूर्णांक cgroup_update_dfl_csses(काष्ठा cgroup *cgrp)
अणु
	DEFINE_CGROUP_MGCTX(mgctx);
	काष्ठा cgroup_subsys_state *d_css;
	काष्ठा cgroup *dsct;
	काष्ठा css_set *src_cset;
	पूर्णांक ret;

	lockdep_निश्चित_held(&cgroup_mutex);

	percpu_करोwn_ग_लिखो(&cgroup_thपढ़ोgroup_rwsem);

	/* look up all csses currently attached to @cgrp's subtree */
	spin_lock_irq(&css_set_lock);
	cgroup_क्रम_each_live_descendant_pre(dsct, d_css, cgrp) अणु
		काष्ठा cgrp_cset_link *link;

		list_क्रम_each_entry(link, &dsct->cset_links, cset_link)
			cgroup_migrate_add_src(link->cset, dsct, &mgctx);
	पूर्ण
	spin_unlock_irq(&css_set_lock);

	/* शून्य dst indicates self on शेष hierarchy */
	ret = cgroup_migrate_prepare_dst(&mgctx);
	अगर (ret)
		जाओ out_finish;

	spin_lock_irq(&css_set_lock);
	list_क्रम_each_entry(src_cset, &mgctx.preloaded_src_csets, mg_preload_node) अणु
		काष्ठा task_काष्ठा *task, *ntask;

		/* all tasks in src_csets need to be migrated */
		list_क्रम_each_entry_safe(task, ntask, &src_cset->tasks, cg_list)
			cgroup_migrate_add_task(task, &mgctx);
	पूर्ण
	spin_unlock_irq(&css_set_lock);

	ret = cgroup_migrate_execute(&mgctx);
out_finish:
	cgroup_migrate_finish(&mgctx);
	percpu_up_ग_लिखो(&cgroup_thपढ़ोgroup_rwsem);
	वापस ret;
पूर्ण

/**
 * cgroup_lock_and_drain_offline - lock cgroup_mutex and drain offlined csses
 * @cgrp: root of the target subtree
 *
 * Because css offlining is asynchronous, userland may try to re-enable a
 * controller जबतक the previous css is still around.  This function grअसल
 * cgroup_mutex and drains the previous css instances of @cgrp's subtree.
 */
व्योम cgroup_lock_and_drain_offline(काष्ठा cgroup *cgrp)
	__acquires(&cgroup_mutex)
अणु
	काष्ठा cgroup *dsct;
	काष्ठा cgroup_subsys_state *d_css;
	काष्ठा cgroup_subsys *ss;
	पूर्णांक ssid;

restart:
	mutex_lock(&cgroup_mutex);

	cgroup_क्रम_each_live_descendant_post(dsct, d_css, cgrp) अणु
		क्रम_each_subsys(ss, ssid) अणु
			काष्ठा cgroup_subsys_state *css = cgroup_css(dsct, ss);
			DEFINE_WAIT(रुको);

			अगर (!css || !percpu_ref_is_dying(&css->refcnt))
				जारी;

			cgroup_get_live(dsct);
			prepare_to_रुको(&dsct->offline_रुकोq, &रुको,
					TASK_UNINTERRUPTIBLE);

			mutex_unlock(&cgroup_mutex);
			schedule();
			finish_रुको(&dsct->offline_रुकोq, &रुको);

			cgroup_put(dsct);
			जाओ restart;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * cgroup_save_control - save control masks and करोm_cgrp of a subtree
 * @cgrp: root of the target subtree
 *
 * Save ->subtree_control, ->subtree_ss_mask and ->करोm_cgrp to the
 * respective old_ prefixed fields क्रम @cgrp's subtree including @cgrp
 * itself.
 */
अटल व्योम cgroup_save_control(काष्ठा cgroup *cgrp)
अणु
	काष्ठा cgroup *dsct;
	काष्ठा cgroup_subsys_state *d_css;

	cgroup_क्रम_each_live_descendant_pre(dsct, d_css, cgrp) अणु
		dsct->old_subtree_control = dsct->subtree_control;
		dsct->old_subtree_ss_mask = dsct->subtree_ss_mask;
		dsct->old_करोm_cgrp = dsct->करोm_cgrp;
	पूर्ण
पूर्ण

/**
 * cgroup_propagate_control - refresh control masks of a subtree
 * @cgrp: root of the target subtree
 *
 * For @cgrp and its subtree, ensure ->subtree_ss_mask matches
 * ->subtree_control and propagate controller availability through the
 * subtree so that descendants करोn't have unavailable controllers enabled.
 */
अटल व्योम cgroup_propagate_control(काष्ठा cgroup *cgrp)
अणु
	काष्ठा cgroup *dsct;
	काष्ठा cgroup_subsys_state *d_css;

	cgroup_क्रम_each_live_descendant_pre(dsct, d_css, cgrp) अणु
		dsct->subtree_control &= cgroup_control(dsct);
		dsct->subtree_ss_mask =
			cgroup_calc_subtree_ss_mask(dsct->subtree_control,
						    cgroup_ss_mask(dsct));
	पूर्ण
पूर्ण

/**
 * cgroup_restore_control - restore control masks and करोm_cgrp of a subtree
 * @cgrp: root of the target subtree
 *
 * Restore ->subtree_control, ->subtree_ss_mask and ->करोm_cgrp from the
 * respective old_ prefixed fields क्रम @cgrp's subtree including @cgrp
 * itself.
 */
अटल व्योम cgroup_restore_control(काष्ठा cgroup *cgrp)
अणु
	काष्ठा cgroup *dsct;
	काष्ठा cgroup_subsys_state *d_css;

	cgroup_क्रम_each_live_descendant_post(dsct, d_css, cgrp) अणु
		dsct->subtree_control = dsct->old_subtree_control;
		dsct->subtree_ss_mask = dsct->old_subtree_ss_mask;
		dsct->करोm_cgrp = dsct->old_करोm_cgrp;
	पूर्ण
पूर्ण

अटल bool css_visible(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा cgroup_subsys *ss = css->ss;
	काष्ठा cgroup *cgrp = css->cgroup;

	अगर (cgroup_control(cgrp) & (1 << ss->id))
		वापस true;
	अगर (!(cgroup_ss_mask(cgrp) & (1 << ss->id)))
		वापस false;
	वापस cgroup_on_dfl(cgrp) && ss->implicit_on_dfl;
पूर्ण

/**
 * cgroup_apply_control_enable - enable or show csses according to control
 * @cgrp: root of the target subtree
 *
 * Walk @cgrp's subtree and create new csses or make the existing ones
 * visible.  A css is created invisible अगर it's being implicitly enabled
 * through dependency.  An invisible css is made visible when the userland
 * explicitly enables it.
 *
 * Returns 0 on success, -त्रुटि_सं on failure.  On failure, csses which have
 * been processed alपढ़ोy aren't cleaned up.  The caller is responsible क्रम
 * cleaning up with cgroup_apply_control_disable().
 */
अटल पूर्णांक cgroup_apply_control_enable(काष्ठा cgroup *cgrp)
अणु
	काष्ठा cgroup *dsct;
	काष्ठा cgroup_subsys_state *d_css;
	काष्ठा cgroup_subsys *ss;
	पूर्णांक ssid, ret;

	cgroup_क्रम_each_live_descendant_pre(dsct, d_css, cgrp) अणु
		क्रम_each_subsys(ss, ssid) अणु
			काष्ठा cgroup_subsys_state *css = cgroup_css(dsct, ss);

			अगर (!(cgroup_ss_mask(dsct) & (1 << ss->id)))
				जारी;

			अगर (!css) अणु
				css = css_create(dsct, ss);
				अगर (IS_ERR(css))
					वापस PTR_ERR(css);
			पूर्ण

			WARN_ON_ONCE(percpu_ref_is_dying(&css->refcnt));

			अगर (css_visible(css)) अणु
				ret = css_populate_dir(css);
				अगर (ret)
					वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * cgroup_apply_control_disable - समाप्त or hide csses according to control
 * @cgrp: root of the target subtree
 *
 * Walk @cgrp's subtree and समाप्त and hide csses so that they match
 * cgroup_ss_mask() and cgroup_visible_mask().
 *
 * A css is hidden when the userland requests it to be disabled जबतक other
 * subप्रणालीs are still depending on it.  The css must not actively control
 * resources and be in the vanilla state अगर it's made visible again later.
 * Controllers which may be depended upon should provide ->css_reset() क्रम
 * this purpose.
 */
अटल व्योम cgroup_apply_control_disable(काष्ठा cgroup *cgrp)
अणु
	काष्ठा cgroup *dsct;
	काष्ठा cgroup_subsys_state *d_css;
	काष्ठा cgroup_subsys *ss;
	पूर्णांक ssid;

	cgroup_क्रम_each_live_descendant_post(dsct, d_css, cgrp) अणु
		क्रम_each_subsys(ss, ssid) अणु
			काष्ठा cgroup_subsys_state *css = cgroup_css(dsct, ss);

			अगर (!css)
				जारी;

			WARN_ON_ONCE(percpu_ref_is_dying(&css->refcnt));

			अगर (css->parent &&
			    !(cgroup_ss_mask(dsct) & (1 << ss->id))) अणु
				समाप्त_css(css);
			पूर्ण अन्यथा अगर (!css_visible(css)) अणु
				css_clear_dir(css);
				अगर (ss->css_reset)
					ss->css_reset(css);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * cgroup_apply_control - apply control mask updates to the subtree
 * @cgrp: root of the target subtree
 *
 * subप्रणालीs can be enabled and disabled in a subtree using the following
 * steps.
 *
 * 1. Call cgroup_save_control() to stash the current state.
 * 2. Update ->subtree_control masks in the subtree as desired.
 * 3. Call cgroup_apply_control() to apply the changes.
 * 4. Optionally perक्रमm other related operations.
 * 5. Call cgroup_finalize_control() to finish up.
 *
 * This function implements step 3 and propagates the mask changes
 * throughout @cgrp's subtree, updates csses accordingly and perक्रमm
 * process migrations.
 */
अटल पूर्णांक cgroup_apply_control(काष्ठा cgroup *cgrp)
अणु
	पूर्णांक ret;

	cgroup_propagate_control(cgrp);

	ret = cgroup_apply_control_enable(cgrp);
	अगर (ret)
		वापस ret;

	/*
	 * At this poपूर्णांक, cgroup_e_css_by_mask() results reflect the new csses
	 * making the following cgroup_update_dfl_csses() properly update
	 * css associations of all tasks in the subtree.
	 */
	ret = cgroup_update_dfl_csses(cgrp);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

/**
 * cgroup_finalize_control - finalize control mask update
 * @cgrp: root of the target subtree
 * @ret: the result of the update
 *
 * Finalize control mask update.  See cgroup_apply_control() क्रम more info.
 */
अटल व्योम cgroup_finalize_control(काष्ठा cgroup *cgrp, पूर्णांक ret)
अणु
	अगर (ret) अणु
		cgroup_restore_control(cgrp);
		cgroup_propagate_control(cgrp);
	पूर्ण

	cgroup_apply_control_disable(cgrp);
पूर्ण

अटल पूर्णांक cgroup_vet_subtree_control_enable(काष्ठा cgroup *cgrp, u16 enable)
अणु
	u16 करोमुख्य_enable = enable & ~cgrp_dfl_thपढ़ोed_ss_mask;

	/* अगर nothing is getting enabled, nothing to worry about */
	अगर (!enable)
		वापस 0;

	/* can @cgrp host any resources? */
	अगर (!cgroup_is_valid_करोमुख्य(cgrp->करोm_cgrp))
		वापस -EOPNOTSUPP;

	/* mixables करोn't care */
	अगर (cgroup_is_mixable(cgrp))
		वापस 0;

	अगर (करोमुख्य_enable) अणु
		/* can't enable करोमुख्य controllers inside a thपढ़ो subtree */
		अगर (cgroup_is_thपढ़ो_root(cgrp) || cgroup_is_thपढ़ोed(cgrp))
			वापस -EOPNOTSUPP;
	पूर्ण अन्यथा अणु
		/*
		 * Thपढ़ोed controllers can handle पूर्णांकernal competitions
		 * and are always allowed inside a (prospective) thपढ़ो
		 * subtree.
		 */
		अगर (cgroup_can_be_thपढ़ो_root(cgrp) || cgroup_is_thपढ़ोed(cgrp))
			वापस 0;
	पूर्ण

	/*
	 * Controllers can't be enabled क्रम a cgroup with tasks to aव्योम
	 * child cgroups competing against tasks.
	 */
	अगर (cgroup_has_tasks(cgrp))
		वापस -EBUSY;

	वापस 0;
पूर्ण

/* change the enabled child controllers क्रम a cgroup in the शेष hierarchy */
अटल sमाप_प्रकार cgroup_subtree_control_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
					    अक्षर *buf, माप_प्रकार nbytes,
					    loff_t off)
अणु
	u16 enable = 0, disable = 0;
	काष्ठा cgroup *cgrp, *child;
	काष्ठा cgroup_subsys *ss;
	अक्षर *tok;
	पूर्णांक ssid, ret;

	/*
	 * Parse input - space separated list of subप्रणाली names prefixed
	 * with either + or -.
	 */
	buf = म_मालाip(buf);
	जबतक ((tok = strsep(&buf, " "))) अणु
		अगर (tok[0] == '\0')
			जारी;
		करो_each_subsys_mask(ss, ssid, ~cgrp_dfl_inhibit_ss_mask) अणु
			अगर (!cgroup_ssid_enabled(ssid) ||
			    म_भेद(tok + 1, ss->name))
				जारी;

			अगर (*tok == '+') अणु
				enable |= 1 << ssid;
				disable &= ~(1 << ssid);
			पूर्ण अन्यथा अगर (*tok == '-') अणु
				disable |= 1 << ssid;
				enable &= ~(1 << ssid);
			पूर्ण अन्यथा अणु
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		पूर्ण जबतक_each_subsys_mask();
		अगर (ssid == CGROUP_SUBSYS_COUNT)
			वापस -EINVAL;
	पूर्ण

	cgrp = cgroup_kn_lock_live(of->kn, true);
	अगर (!cgrp)
		वापस -ENODEV;

	क्रम_each_subsys(ss, ssid) अणु
		अगर (enable & (1 << ssid)) अणु
			अगर (cgrp->subtree_control & (1 << ssid)) अणु
				enable &= ~(1 << ssid);
				जारी;
			पूर्ण

			अगर (!(cgroup_control(cgrp) & (1 << ssid))) अणु
				ret = -ENOENT;
				जाओ out_unlock;
			पूर्ण
		पूर्ण अन्यथा अगर (disable & (1 << ssid)) अणु
			अगर (!(cgrp->subtree_control & (1 << ssid))) अणु
				disable &= ~(1 << ssid);
				जारी;
			पूर्ण

			/* a child has it enabled? */
			cgroup_क्रम_each_live_child(child, cgrp) अणु
				अगर (child->subtree_control & (1 << ssid)) अणु
					ret = -EBUSY;
					जाओ out_unlock;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!enable && !disable) अणु
		ret = 0;
		जाओ out_unlock;
	पूर्ण

	ret = cgroup_vet_subtree_control_enable(cgrp, enable);
	अगर (ret)
		जाओ out_unlock;

	/* save and update control masks and prepare csses */
	cgroup_save_control(cgrp);

	cgrp->subtree_control |= enable;
	cgrp->subtree_control &= ~disable;

	ret = cgroup_apply_control(cgrp);
	cgroup_finalize_control(cgrp, ret);
	अगर (ret)
		जाओ out_unlock;

	kernfs_activate(cgrp->kn);
out_unlock:
	cgroup_kn_unlock(of->kn);
	वापस ret ?: nbytes;
पूर्ण

/**
 * cgroup_enable_thपढ़ोed - make @cgrp thपढ़ोed
 * @cgrp: the target cgroup
 *
 * Called when "threaded" is written to the cgroup.type पूर्णांकerface file and
 * tries to make @cgrp thपढ़ोed and join the parent's resource करोमुख्य.
 * This function is never called on the root cgroup as cgroup.type करोesn't
 * exist on it.
 */
अटल पूर्णांक cgroup_enable_thपढ़ोed(काष्ठा cgroup *cgrp)
अणु
	काष्ठा cgroup *parent = cgroup_parent(cgrp);
	काष्ठा cgroup *करोm_cgrp = parent->करोm_cgrp;
	काष्ठा cgroup *dsct;
	काष्ठा cgroup_subsys_state *d_css;
	पूर्णांक ret;

	lockdep_निश्चित_held(&cgroup_mutex);

	/* noop अगर alपढ़ोy thपढ़ोed */
	अगर (cgroup_is_thपढ़ोed(cgrp))
		वापस 0;

	/*
	 * If @cgroup is populated or has करोमुख्य controllers enabled, it
	 * can't be चयनed.  While the below cgroup_can_be_thपढ़ो_root()
	 * test can catch the same conditions, that's only when @parent is
	 * not mixable, so let's check it explicitly.
	 */
	अगर (cgroup_is_populated(cgrp) ||
	    cgrp->subtree_control & ~cgrp_dfl_thपढ़ोed_ss_mask)
		वापस -EOPNOTSUPP;

	/* we're joining the parent's करोमुख्य, ensure its validity */
	अगर (!cgroup_is_valid_करोमुख्य(करोm_cgrp) ||
	    !cgroup_can_be_thपढ़ो_root(करोm_cgrp))
		वापस -EOPNOTSUPP;

	/*
	 * The following shouldn't cause actual migrations and should
	 * always succeed.
	 */
	cgroup_save_control(cgrp);

	cgroup_क्रम_each_live_descendant_pre(dsct, d_css, cgrp)
		अगर (dsct == cgrp || cgroup_is_thपढ़ोed(dsct))
			dsct->करोm_cgrp = करोm_cgrp;

	ret = cgroup_apply_control(cgrp);
	अगर (!ret)
		parent->nr_thपढ़ोed_children++;

	cgroup_finalize_control(cgrp, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक cgroup_type_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा cgroup *cgrp = seq_css(seq)->cgroup;

	अगर (cgroup_is_thपढ़ोed(cgrp))
		seq_माला_दो(seq, "threaded\n");
	अन्यथा अगर (!cgroup_is_valid_करोमुख्य(cgrp))
		seq_माला_दो(seq, "domain invalid\n");
	अन्यथा अगर (cgroup_is_thपढ़ो_root(cgrp))
		seq_माला_दो(seq, "domain threaded\n");
	अन्यथा
		seq_माला_दो(seq, "domain\n");

	वापस 0;
पूर्ण

अटल sमाप_प्रकार cgroup_type_ग_लिखो(काष्ठा kernfs_खोलो_file *of, अक्षर *buf,
				 माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा cgroup *cgrp;
	पूर्णांक ret;

	/* only चयनing to thपढ़ोed mode is supported */
	अगर (म_भेद(म_मालाip(buf), "threaded"))
		वापस -EINVAL;

	/* drain dying csses beक्रमe we re-apply (thपढ़ोed) subtree control */
	cgrp = cgroup_kn_lock_live(of->kn, true);
	अगर (!cgrp)
		वापस -ENOENT;

	/* thपढ़ोed can only be enabled */
	ret = cgroup_enable_thपढ़ोed(cgrp);

	cgroup_kn_unlock(of->kn);
	वापस ret ?: nbytes;
पूर्ण

अटल पूर्णांक cgroup_max_descendants_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा cgroup *cgrp = seq_css(seq)->cgroup;
	पूर्णांक descendants = READ_ONCE(cgrp->max_descendants);

	अगर (descendants == पूर्णांक_उच्च)
		seq_माला_दो(seq, "max\n");
	अन्यथा
		seq_म_लिखो(seq, "%d\n", descendants);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार cgroup_max_descendants_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
					   अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा cgroup *cgrp;
	पूर्णांक descendants;
	sमाप_प्रकार ret;

	buf = म_मालाip(buf);
	अगर (!म_भेद(buf, "max")) अणु
		descendants = पूर्णांक_उच्च;
	पूर्ण अन्यथा अणु
		ret = kstrtoपूर्णांक(buf, 0, &descendants);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (descendants < 0)
		वापस -दुस्फल;

	cgrp = cgroup_kn_lock_live(of->kn, false);
	अगर (!cgrp)
		वापस -ENOENT;

	cgrp->max_descendants = descendants;

	cgroup_kn_unlock(of->kn);

	वापस nbytes;
पूर्ण

अटल पूर्णांक cgroup_max_depth_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा cgroup *cgrp = seq_css(seq)->cgroup;
	पूर्णांक depth = READ_ONCE(cgrp->max_depth);

	अगर (depth == पूर्णांक_उच्च)
		seq_माला_दो(seq, "max\n");
	अन्यथा
		seq_म_लिखो(seq, "%d\n", depth);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार cgroup_max_depth_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
				      अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा cgroup *cgrp;
	sमाप_प्रकार ret;
	पूर्णांक depth;

	buf = म_मालाip(buf);
	अगर (!म_भेद(buf, "max")) अणु
		depth = पूर्णांक_उच्च;
	पूर्ण अन्यथा अणु
		ret = kstrtoपूर्णांक(buf, 0, &depth);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (depth < 0)
		वापस -दुस्फल;

	cgrp = cgroup_kn_lock_live(of->kn, false);
	अगर (!cgrp)
		वापस -ENOENT;

	cgrp->max_depth = depth;

	cgroup_kn_unlock(of->kn);

	वापस nbytes;
पूर्ण

अटल पूर्णांक cgroup_events_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा cgroup *cgrp = seq_css(seq)->cgroup;

	seq_म_लिखो(seq, "populated %d\n", cgroup_is_populated(cgrp));
	seq_म_लिखो(seq, "frozen %d\n", test_bit(CGRP_FROZEN, &cgrp->flags));

	वापस 0;
पूर्ण

अटल पूर्णांक cgroup_stat_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा cgroup *cgroup = seq_css(seq)->cgroup;

	seq_म_लिखो(seq, "nr_descendants %d\n",
		   cgroup->nr_descendants);
	seq_म_लिखो(seq, "nr_dying_descendants %d\n",
		   cgroup->nr_dying_descendants);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cgroup_extra_stat_show(काष्ठा seq_file *seq,
						 काष्ठा cgroup *cgrp, पूर्णांक ssid)
अणु
	काष्ठा cgroup_subsys *ss = cgroup_subsys[ssid];
	काष्ठा cgroup_subsys_state *css;
	पूर्णांक ret;

	अगर (!ss->css_extra_stat_show)
		वापस 0;

	css = cgroup_tryget_css(cgrp, ss);
	अगर (!css)
		वापस 0;

	ret = ss->css_extra_stat_show(seq, css);
	css_put(css);
	वापस ret;
पूर्ण

अटल पूर्णांक cpu_stat_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा cgroup __maybe_unused *cgrp = seq_css(seq)->cgroup;
	पूर्णांक ret = 0;

	cgroup_base_stat_cpuसमय_show(seq);
#अगर_घोषित CONFIG_CGROUP_SCHED
	ret = cgroup_extra_stat_show(seq, cgrp, cpu_cgrp_id);
#पूर्ण_अगर
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PSI
अटल पूर्णांक cgroup_io_pressure_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा cgroup *cgrp = seq_css(seq)->cgroup;
	काष्ठा psi_group *psi = cgroup_ino(cgrp) == 1 ? &psi_प्रणाली : &cgrp->psi;

	वापस psi_show(seq, psi, PSI_IO);
पूर्ण
अटल पूर्णांक cgroup_memory_pressure_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा cgroup *cgrp = seq_css(seq)->cgroup;
	काष्ठा psi_group *psi = cgroup_ino(cgrp) == 1 ? &psi_प्रणाली : &cgrp->psi;

	वापस psi_show(seq, psi, PSI_MEM);
पूर्ण
अटल पूर्णांक cgroup_cpu_pressure_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा cgroup *cgrp = seq_css(seq)->cgroup;
	काष्ठा psi_group *psi = cgroup_ino(cgrp) == 1 ? &psi_प्रणाली : &cgrp->psi;

	वापस psi_show(seq, psi, PSI_CPU);
पूर्ण

अटल sमाप_प्रकार cgroup_pressure_ग_लिखो(काष्ठा kernfs_खोलो_file *of, अक्षर *buf,
					  माप_प्रकार nbytes, क्रमागत psi_res res)
अणु
	काष्ठा psi_trigger *new;
	काष्ठा cgroup *cgrp;
	काष्ठा psi_group *psi;

	cgrp = cgroup_kn_lock_live(of->kn, false);
	अगर (!cgrp)
		वापस -ENODEV;

	cgroup_get(cgrp);
	cgroup_kn_unlock(of->kn);

	psi = cgroup_ino(cgrp) == 1 ? &psi_प्रणाली : &cgrp->psi;
	new = psi_trigger_create(psi, buf, nbytes, res);
	अगर (IS_ERR(new)) अणु
		cgroup_put(cgrp);
		वापस PTR_ERR(new);
	पूर्ण

	psi_trigger_replace(&of->priv, new);

	cgroup_put(cgrp);

	वापस nbytes;
पूर्ण

अटल sमाप_प्रकार cgroup_io_pressure_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
					  अक्षर *buf, माप_प्रकार nbytes,
					  loff_t off)
अणु
	वापस cgroup_pressure_ग_लिखो(of, buf, nbytes, PSI_IO);
पूर्ण

अटल sमाप_प्रकार cgroup_memory_pressure_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
					  अक्षर *buf, माप_प्रकार nbytes,
					  loff_t off)
अणु
	वापस cgroup_pressure_ग_लिखो(of, buf, nbytes, PSI_MEM);
पूर्ण

अटल sमाप_प्रकार cgroup_cpu_pressure_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
					  अक्षर *buf, माप_प्रकार nbytes,
					  loff_t off)
अणु
	वापस cgroup_pressure_ग_लिखो(of, buf, nbytes, PSI_CPU);
पूर्ण

अटल __poll_t cgroup_pressure_poll(काष्ठा kernfs_खोलो_file *of,
					  poll_table *pt)
अणु
	वापस psi_trigger_poll(&of->priv, of->file, pt);
पूर्ण

अटल व्योम cgroup_pressure_release(काष्ठा kernfs_खोलो_file *of)
अणु
	psi_trigger_replace(&of->priv, शून्य);
पूर्ण
#पूर्ण_अगर /* CONFIG_PSI */

अटल पूर्णांक cgroup_मुक्तze_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा cgroup *cgrp = seq_css(seq)->cgroup;

	seq_म_लिखो(seq, "%d\n", cgrp->मुक्तzer.मुक्तze);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार cgroup_मुक्तze_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
				   अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा cgroup *cgrp;
	sमाप_प्रकार ret;
	पूर्णांक मुक्तze;

	ret = kstrtoपूर्णांक(म_मालाip(buf), 0, &मुक्तze);
	अगर (ret)
		वापस ret;

	अगर (मुक्तze < 0 || मुक्तze > 1)
		वापस -दुस्फल;

	cgrp = cgroup_kn_lock_live(of->kn, false);
	अगर (!cgrp)
		वापस -ENOENT;

	cgroup_मुक्तze(cgrp, मुक्तze);

	cgroup_kn_unlock(of->kn);

	वापस nbytes;
पूर्ण

अटल पूर्णांक cgroup_file_खोलो(काष्ठा kernfs_खोलो_file *of)
अणु
	काष्ठा cftype *cft = of_cft(of);

	अगर (cft->खोलो)
		वापस cft->खोलो(of);
	वापस 0;
पूर्ण

अटल व्योम cgroup_file_release(काष्ठा kernfs_खोलो_file *of)
अणु
	काष्ठा cftype *cft = of_cft(of);

	अगर (cft->release)
		cft->release(of);
पूर्ण

अटल sमाप_प्रकार cgroup_file_ग_लिखो(काष्ठा kernfs_खोलो_file *of, अक्षर *buf,
				 माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा cgroup_namespace *ns = current->nsproxy->cgroup_ns;
	काष्ठा cgroup *cgrp = of->kn->parent->priv;
	काष्ठा cftype *cft = of_cft(of);
	काष्ठा cgroup_subsys_state *css;
	पूर्णांक ret;

	अगर (!nbytes)
		वापस 0;

	/*
	 * If namespaces are delegation boundaries, disallow ग_लिखोs to
	 * files in an non-init namespace root from inside the namespace
	 * except क्रम the files explicitly marked delegatable -
	 * cgroup.procs and cgroup.subtree_control.
	 */
	अगर ((cgrp->root->flags & CGRP_ROOT_NS_DELEGATE) &&
	    !(cft->flags & CFTYPE_NS_DELEGATABLE) &&
	    ns != &init_cgroup_ns && ns->root_cset->dfl_cgrp == cgrp)
		वापस -EPERM;

	अगर (cft->ग_लिखो)
		वापस cft->ग_लिखो(of, buf, nbytes, off);

	/*
	 * kernfs guarantees that a file isn't deleted with operations in
	 * flight, which means that the matching css is and stays alive and
	 * करोesn't need to be pinned.  The RCU locking is not necessary
	 * either.  It's just क्रम the convenience of using cgroup_css().
	 */
	rcu_पढ़ो_lock();
	css = cgroup_css(cgrp, cft->ss);
	rcu_पढ़ो_unlock();

	अगर (cft->ग_लिखो_u64) अणु
		अचिन्हित दीर्घ दीर्घ v;
		ret = kम_से_अदीर्घl(buf, 0, &v);
		अगर (!ret)
			ret = cft->ग_लिखो_u64(css, cft, v);
	पूर्ण अन्यथा अगर (cft->ग_लिखो_s64) अणु
		दीर्घ दीर्घ v;
		ret = kम_से_दीर्घl(buf, 0, &v);
		अगर (!ret)
			ret = cft->ग_लिखो_s64(css, cft, v);
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	वापस ret ?: nbytes;
पूर्ण

अटल __poll_t cgroup_file_poll(काष्ठा kernfs_खोलो_file *of, poll_table *pt)
अणु
	काष्ठा cftype *cft = of_cft(of);

	अगर (cft->poll)
		वापस cft->poll(of, pt);

	वापस kernfs_generic_poll(of, pt);
पूर्ण

अटल व्योम *cgroup_seqfile_start(काष्ठा seq_file *seq, loff_t *ppos)
अणु
	वापस seq_cft(seq)->seq_start(seq, ppos);
पूर्ण

अटल व्योम *cgroup_seqfile_next(काष्ठा seq_file *seq, व्योम *v, loff_t *ppos)
अणु
	वापस seq_cft(seq)->seq_next(seq, v, ppos);
पूर्ण

अटल व्योम cgroup_seqfile_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (seq_cft(seq)->seq_stop)
		seq_cft(seq)->seq_stop(seq, v);
पूर्ण

अटल पूर्णांक cgroup_seqfile_show(काष्ठा seq_file *m, व्योम *arg)
अणु
	काष्ठा cftype *cft = seq_cft(m);
	काष्ठा cgroup_subsys_state *css = seq_css(m);

	अगर (cft->seq_show)
		वापस cft->seq_show(m, arg);

	अगर (cft->पढ़ो_u64)
		seq_म_लिखो(m, "%llu\n", cft->पढ़ो_u64(css, cft));
	अन्यथा अगर (cft->पढ़ो_s64)
		seq_म_लिखो(m, "%lld\n", cft->पढ़ो_s64(css, cft));
	अन्यथा
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल काष्ठा kernfs_ops cgroup_kf_single_ops = अणु
	.atomic_ग_लिखो_len	= PAGE_SIZE,
	.खोलो			= cgroup_file_खोलो,
	.release		= cgroup_file_release,
	.ग_लिखो			= cgroup_file_ग_लिखो,
	.poll			= cgroup_file_poll,
	.seq_show		= cgroup_seqfile_show,
पूर्ण;

अटल काष्ठा kernfs_ops cgroup_kf_ops = अणु
	.atomic_ग_लिखो_len	= PAGE_SIZE,
	.खोलो			= cgroup_file_खोलो,
	.release		= cgroup_file_release,
	.ग_लिखो			= cgroup_file_ग_लिखो,
	.poll			= cgroup_file_poll,
	.seq_start		= cgroup_seqfile_start,
	.seq_next		= cgroup_seqfile_next,
	.seq_stop		= cgroup_seqfile_stop,
	.seq_show		= cgroup_seqfile_show,
पूर्ण;

/* set uid and gid of cgroup dirs and files to that of the creator */
अटल पूर्णांक cgroup_kn_set_ugid(काष्ठा kernfs_node *kn)
अणु
	काष्ठा iattr iattr = अणु .ia_valid = ATTR_UID | ATTR_GID,
			       .ia_uid = current_fsuid(),
			       .ia_gid = current_fsgid(), पूर्ण;

	अगर (uid_eq(iattr.ia_uid, GLOBAL_ROOT_UID) &&
	    gid_eq(iattr.ia_gid, GLOBAL_ROOT_GID))
		वापस 0;

	वापस kernfs_setattr(kn, &iattr);
पूर्ण

अटल व्योम cgroup_file_notअगरy_समयr(काष्ठा समयr_list *समयr)
अणु
	cgroup_file_notअगरy(container_of(समयr, काष्ठा cgroup_file,
					notअगरy_समयr));
पूर्ण

अटल पूर्णांक cgroup_add_file(काष्ठा cgroup_subsys_state *css, काष्ठा cgroup *cgrp,
			   काष्ठा cftype *cft)
अणु
	अक्षर name[CGROUP_खाता_NAME_MAX];
	काष्ठा kernfs_node *kn;
	काष्ठा lock_class_key *key = शून्य;
	पूर्णांक ret;

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	key = &cft->lockdep_key;
#पूर्ण_अगर
	kn = __kernfs_create_file(cgrp->kn, cgroup_file_name(cgrp, cft, name),
				  cgroup_file_mode(cft),
				  GLOBAL_ROOT_UID, GLOBAL_ROOT_GID,
				  0, cft->kf_ops, cft,
				  शून्य, key);
	अगर (IS_ERR(kn))
		वापस PTR_ERR(kn);

	ret = cgroup_kn_set_ugid(kn);
	अगर (ret) अणु
		kernfs_हटाओ(kn);
		वापस ret;
	पूर्ण

	अगर (cft->file_offset) अणु
		काष्ठा cgroup_file *cfile = (व्योम *)css + cft->file_offset;

		समयr_setup(&cfile->notअगरy_समयr, cgroup_file_notअगरy_समयr, 0);

		spin_lock_irq(&cgroup_file_kn_lock);
		cfile->kn = kn;
		spin_unlock_irq(&cgroup_file_kn_lock);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * cgroup_addrm_files - add or हटाओ files to a cgroup directory
 * @css: the target css
 * @cgrp: the target cgroup (usually css->cgroup)
 * @cfts: array of cftypes to be added
 * @is_add: whether to add or हटाओ
 *
 * Depending on @is_add, add or हटाओ files defined by @cfts on @cgrp.
 * For removals, this function never fails.
 */
अटल पूर्णांक cgroup_addrm_files(काष्ठा cgroup_subsys_state *css,
			      काष्ठा cgroup *cgrp, काष्ठा cftype cfts[],
			      bool is_add)
अणु
	काष्ठा cftype *cft, *cft_end = शून्य;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&cgroup_mutex);

restart:
	क्रम (cft = cfts; cft != cft_end && cft->name[0] != '\0'; cft++) अणु
		/* करोes cft->flags tell us to skip this file on @cgrp? */
		अगर ((cft->flags & __CFTYPE_ONLY_ON_DFL) && !cgroup_on_dfl(cgrp))
			जारी;
		अगर ((cft->flags & __CFTYPE_NOT_ON_DFL) && cgroup_on_dfl(cgrp))
			जारी;
		अगर ((cft->flags & CFTYPE_NOT_ON_ROOT) && !cgroup_parent(cgrp))
			जारी;
		अगर ((cft->flags & CFTYPE_ONLY_ON_ROOT) && cgroup_parent(cgrp))
			जारी;
		अगर ((cft->flags & CFTYPE_DEBUG) && !cgroup_debug)
			जारी;
		अगर (is_add) अणु
			ret = cgroup_add_file(css, cgrp, cft);
			अगर (ret) अणु
				pr_warn("%s: failed to add %s, err=%d\n",
					__func__, cft->name, ret);
				cft_end = cft;
				is_add = false;
				जाओ restart;
			पूर्ण
		पूर्ण अन्यथा अणु
			cgroup_rm_file(cgrp, cft);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक cgroup_apply_cftypes(काष्ठा cftype *cfts, bool is_add)
अणु
	काष्ठा cgroup_subsys *ss = cfts[0].ss;
	काष्ठा cgroup *root = &ss->root->cgrp;
	काष्ठा cgroup_subsys_state *css;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&cgroup_mutex);

	/* add/rm files क्रम all cgroups created beक्रमe */
	css_क्रम_each_descendant_pre(css, cgroup_css(root, ss)) अणु
		काष्ठा cgroup *cgrp = css->cgroup;

		अगर (!(css->flags & CSS_VISIBLE))
			जारी;

		ret = cgroup_addrm_files(css, cgrp, cfts, is_add);
		अगर (ret)
			अवरोध;
	पूर्ण

	अगर (is_add && !ret)
		kernfs_activate(root->kn);
	वापस ret;
पूर्ण

अटल व्योम cgroup_निकास_cftypes(काष्ठा cftype *cfts)
अणु
	काष्ठा cftype *cft;

	क्रम (cft = cfts; cft->name[0] != '\0'; cft++) अणु
		/* मुक्त copy क्रम custom atomic_ग_लिखो_len, see init_cftypes() */
		अगर (cft->max_ग_लिखो_len && cft->max_ग_लिखो_len != PAGE_SIZE)
			kमुक्त(cft->kf_ops);
		cft->kf_ops = शून्य;
		cft->ss = शून्य;

		/* revert flags set by cgroup core जबतक adding @cfts */
		cft->flags &= ~(__CFTYPE_ONLY_ON_DFL | __CFTYPE_NOT_ON_DFL);
	पूर्ण
पूर्ण

अटल पूर्णांक cgroup_init_cftypes(काष्ठा cgroup_subsys *ss, काष्ठा cftype *cfts)
अणु
	काष्ठा cftype *cft;

	क्रम (cft = cfts; cft->name[0] != '\0'; cft++) अणु
		काष्ठा kernfs_ops *kf_ops;

		WARN_ON(cft->ss || cft->kf_ops);

		अगर (cft->seq_start)
			kf_ops = &cgroup_kf_ops;
		अन्यथा
			kf_ops = &cgroup_kf_single_ops;

		/*
		 * Ugh... अगर @cft wants a custom max_ग_लिखो_len, we need to
		 * make a copy of kf_ops to set its atomic_ग_लिखो_len.
		 */
		अगर (cft->max_ग_लिखो_len && cft->max_ग_लिखो_len != PAGE_SIZE) अणु
			kf_ops = kmemdup(kf_ops, माप(*kf_ops), GFP_KERNEL);
			अगर (!kf_ops) अणु
				cgroup_निकास_cftypes(cfts);
				वापस -ENOMEM;
			पूर्ण
			kf_ops->atomic_ग_लिखो_len = cft->max_ग_लिखो_len;
		पूर्ण

		cft->kf_ops = kf_ops;
		cft->ss = ss;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cgroup_rm_cftypes_locked(काष्ठा cftype *cfts)
अणु
	lockdep_निश्चित_held(&cgroup_mutex);

	अगर (!cfts || !cfts[0].ss)
		वापस -ENOENT;

	list_del(&cfts->node);
	cgroup_apply_cftypes(cfts, false);
	cgroup_निकास_cftypes(cfts);
	वापस 0;
पूर्ण

/**
 * cgroup_rm_cftypes - हटाओ an array of cftypes from a subप्रणाली
 * @cfts: zero-length name terminated array of cftypes
 *
 * Unरेजिस्टर @cfts.  Files described by @cfts are हटाओd from all
 * existing cgroups and all future cgroups won't have them either.  This
 * function can be called anyसमय whether @cfts' subsys is attached or not.
 *
 * Returns 0 on successful unregistration, -ENOENT अगर @cfts is not
 * रेजिस्टरed.
 */
पूर्णांक cgroup_rm_cftypes(काष्ठा cftype *cfts)
अणु
	पूर्णांक ret;

	mutex_lock(&cgroup_mutex);
	ret = cgroup_rm_cftypes_locked(cfts);
	mutex_unlock(&cgroup_mutex);
	वापस ret;
पूर्ण

/**
 * cgroup_add_cftypes - add an array of cftypes to a subप्रणाली
 * @ss: target cgroup subप्रणाली
 * @cfts: zero-length name terminated array of cftypes
 *
 * Register @cfts to @ss.  Files described by @cfts are created क्रम all
 * existing cgroups to which @ss is attached and all future cgroups will
 * have them too.  This function can be called anyसमय whether @ss is
 * attached or not.
 *
 * Returns 0 on successful registration, -त्रुटि_सं on failure.  Note that this
 * function currently वापसs 0 as दीर्घ as @cfts registration is successful
 * even अगर some file creation attempts on existing cgroups fail.
 */
अटल पूर्णांक cgroup_add_cftypes(काष्ठा cgroup_subsys *ss, काष्ठा cftype *cfts)
अणु
	पूर्णांक ret;

	अगर (!cgroup_ssid_enabled(ss->id))
		वापस 0;

	अगर (!cfts || cfts[0].name[0] == '\0')
		वापस 0;

	ret = cgroup_init_cftypes(ss, cfts);
	अगर (ret)
		वापस ret;

	mutex_lock(&cgroup_mutex);

	list_add_tail(&cfts->node, &ss->cfts);
	ret = cgroup_apply_cftypes(cfts, true);
	अगर (ret)
		cgroup_rm_cftypes_locked(cfts);

	mutex_unlock(&cgroup_mutex);
	वापस ret;
पूर्ण

/**
 * cgroup_add_dfl_cftypes - add an array of cftypes क्रम शेष hierarchy
 * @ss: target cgroup subप्रणाली
 * @cfts: zero-length name terminated array of cftypes
 *
 * Similar to cgroup_add_cftypes() but the added files are only used क्रम
 * the शेष hierarchy.
 */
पूर्णांक cgroup_add_dfl_cftypes(काष्ठा cgroup_subsys *ss, काष्ठा cftype *cfts)
अणु
	काष्ठा cftype *cft;

	क्रम (cft = cfts; cft && cft->name[0] != '\0'; cft++)
		cft->flags |= __CFTYPE_ONLY_ON_DFL;
	वापस cgroup_add_cftypes(ss, cfts);
पूर्ण

/**
 * cgroup_add_legacy_cftypes - add an array of cftypes क्रम legacy hierarchies
 * @ss: target cgroup subप्रणाली
 * @cfts: zero-length name terminated array of cftypes
 *
 * Similar to cgroup_add_cftypes() but the added files are only used क्रम
 * the legacy hierarchies.
 */
पूर्णांक cgroup_add_legacy_cftypes(काष्ठा cgroup_subsys *ss, काष्ठा cftype *cfts)
अणु
	काष्ठा cftype *cft;

	क्रम (cft = cfts; cft && cft->name[0] != '\0'; cft++)
		cft->flags |= __CFTYPE_NOT_ON_DFL;
	वापस cgroup_add_cftypes(ss, cfts);
पूर्ण

/**
 * cgroup_file_notअगरy - generate a file modअगरied event क्रम a cgroup_file
 * @cfile: target cgroup_file
 *
 * @cfile must have been obtained by setting cftype->file_offset.
 */
व्योम cgroup_file_notअगरy(काष्ठा cgroup_file *cfile)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cgroup_file_kn_lock, flags);
	अगर (cfile->kn) अणु
		अचिन्हित दीर्घ last = cfile->notअगरied_at;
		अचिन्हित दीर्घ next = last + CGROUP_खाता_NOTIFY_MIN_INTV;

		अगर (समय_in_range(jअगरfies, last, next)) अणु
			समयr_reduce(&cfile->notअगरy_समयr, next);
		पूर्ण अन्यथा अणु
			kernfs_notअगरy(cfile->kn);
			cfile->notअगरied_at = jअगरfies;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&cgroup_file_kn_lock, flags);
पूर्ण

/**
 * css_next_child - find the next child of a given css
 * @pos: the current position (%शून्य to initiate traversal)
 * @parent: css whose children to walk
 *
 * This function वापसs the next child of @parent and should be called
 * under either cgroup_mutex or RCU पढ़ो lock.  The only requirement is
 * that @parent and @pos are accessible.  The next sibling is guaranteed to
 * be वापसed regardless of their states.
 *
 * If a subप्रणाली synchronizes ->css_online() and the start of iteration, a
 * css which finished ->css_online() is guaranteed to be visible in the
 * future iterations and will stay visible until the last reference is put.
 * A css which hasn't finished ->css_online() or alपढ़ोy finished
 * ->css_offline() may show up during traversal.  It's each subsystem's
 * responsibility to synchronize against on/offlining.
 */
काष्ठा cgroup_subsys_state *css_next_child(काष्ठा cgroup_subsys_state *pos,
					   काष्ठा cgroup_subsys_state *parent)
अणु
	काष्ठा cgroup_subsys_state *next;

	cgroup_निश्चित_mutex_or_rcu_locked();

	/*
	 * @pos could alपढ़ोy have been unlinked from the sibling list.
	 * Once a cgroup is हटाओd, its ->sibling.next is no दीर्घer
	 * updated when its next sibling changes.  CSS_RELEASED is set when
	 * @pos is taken off list, at which समय its next poपूर्णांकer is valid,
	 * and, as releases are serialized, the one poपूर्णांकed to by the next
	 * poपूर्णांकer is guaranteed to not have started release yet.  This
	 * implies that अगर we observe !CSS_RELEASED on @pos in this RCU
	 * critical section, the one poपूर्णांकed to by its next poपूर्णांकer is
	 * guaranteed to not have finished its RCU grace period even अगर we
	 * have dropped rcu_पढ़ो_lock() in-between iterations.
	 *
	 * If @pos has CSS_RELEASED set, its next poपूर्णांकer can't be
	 * dereferenced; however, as each css is given a monotonically
	 * increasing unique serial number and always appended to the
	 * sibling list, the next one can be found by walking the parent's
	 * children until the first css with higher serial number than
	 * @pos's.  While this path can be slower, it happens अगरf iteration
	 * races against release and the race winकरोw is very small.
	 */
	अगर (!pos) अणु
		next = list_entry_rcu(parent->children.next, काष्ठा cgroup_subsys_state, sibling);
	पूर्ण अन्यथा अगर (likely(!(pos->flags & CSS_RELEASED))) अणु
		next = list_entry_rcu(pos->sibling.next, काष्ठा cgroup_subsys_state, sibling);
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry_rcu(next, &parent->children, sibling,
					lockdep_is_held(&cgroup_mutex))
			अगर (next->serial_nr > pos->serial_nr)
				अवरोध;
	पूर्ण

	/*
	 * @next, अगर not poपूर्णांकing to the head, can be dereferenced and is
	 * the next sibling.
	 */
	अगर (&next->sibling != &parent->children)
		वापस next;
	वापस शून्य;
पूर्ण

/**
 * css_next_descendant_pre - find the next descendant क्रम pre-order walk
 * @pos: the current position (%शून्य to initiate traversal)
 * @root: css whose descendants to walk
 *
 * To be used by css_क्रम_each_descendant_pre().  Find the next descendant
 * to visit क्रम pre-order traversal of @root's descendants.  @root is
 * included in the iteration and the first node to be visited.
 *
 * While this function requires cgroup_mutex or RCU पढ़ो locking, it
 * करोesn't require the whole traversal to be contained in a single critical
 * section.  This function will वापस the correct next descendant as दीर्घ
 * as both @pos and @root are accessible and @pos is a descendant of @root.
 *
 * If a subप्रणाली synchronizes ->css_online() and the start of iteration, a
 * css which finished ->css_online() is guaranteed to be visible in the
 * future iterations and will stay visible until the last reference is put.
 * A css which hasn't finished ->css_online() or alपढ़ोy finished
 * ->css_offline() may show up during traversal.  It's each subsystem's
 * responsibility to synchronize against on/offlining.
 */
काष्ठा cgroup_subsys_state *
css_next_descendant_pre(काष्ठा cgroup_subsys_state *pos,
			काष्ठा cgroup_subsys_state *root)
अणु
	काष्ठा cgroup_subsys_state *next;

	cgroup_निश्चित_mutex_or_rcu_locked();

	/* अगर first iteration, visit @root */
	अगर (!pos)
		वापस root;

	/* visit the first child अगर exists */
	next = css_next_child(शून्य, pos);
	अगर (next)
		वापस next;

	/* no child, visit my or the बंदst ancestor's next sibling */
	जबतक (pos != root) अणु
		next = css_next_child(pos, pos->parent);
		अगर (next)
			वापस next;
		pos = pos->parent;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(css_next_descendant_pre);

/**
 * css_righपंचांगost_descendant - वापस the righपंचांगost descendant of a css
 * @pos: css of पूर्णांकerest
 *
 * Return the righपंचांगost descendant of @pos.  If there's no descendant, @pos
 * is वापसed.  This can be used during pre-order traversal to skip
 * subtree of @pos.
 *
 * While this function requires cgroup_mutex or RCU पढ़ो locking, it
 * करोesn't require the whole traversal to be contained in a single critical
 * section.  This function will वापस the correct righपंचांगost descendant as
 * दीर्घ as @pos is accessible.
 */
काष्ठा cgroup_subsys_state *
css_righपंचांगost_descendant(काष्ठा cgroup_subsys_state *pos)
अणु
	काष्ठा cgroup_subsys_state *last, *पंचांगp;

	cgroup_निश्चित_mutex_or_rcu_locked();

	करो अणु
		last = pos;
		/* ->prev isn't RCU safe, walk ->next till the end */
		pos = शून्य;
		css_क्रम_each_child(पंचांगp, last)
			pos = पंचांगp;
	पूर्ण जबतक (pos);

	वापस last;
पूर्ण

अटल काष्ठा cgroup_subsys_state *
css_lefपंचांगost_descendant(काष्ठा cgroup_subsys_state *pos)
अणु
	काष्ठा cgroup_subsys_state *last;

	करो अणु
		last = pos;
		pos = css_next_child(शून्य, pos);
	पूर्ण जबतक (pos);

	वापस last;
पूर्ण

/**
 * css_next_descendant_post - find the next descendant क्रम post-order walk
 * @pos: the current position (%शून्य to initiate traversal)
 * @root: css whose descendants to walk
 *
 * To be used by css_क्रम_each_descendant_post().  Find the next descendant
 * to visit क्रम post-order traversal of @root's descendants.  @root is
 * included in the iteration and the last node to be visited.
 *
 * While this function requires cgroup_mutex or RCU पढ़ो locking, it
 * करोesn't require the whole traversal to be contained in a single critical
 * section.  This function will वापस the correct next descendant as दीर्घ
 * as both @pos and @cgroup are accessible and @pos is a descendant of
 * @cgroup.
 *
 * If a subप्रणाली synchronizes ->css_online() and the start of iteration, a
 * css which finished ->css_online() is guaranteed to be visible in the
 * future iterations and will stay visible until the last reference is put.
 * A css which hasn't finished ->css_online() or alपढ़ोy finished
 * ->css_offline() may show up during traversal.  It's each subsystem's
 * responsibility to synchronize against on/offlining.
 */
काष्ठा cgroup_subsys_state *
css_next_descendant_post(काष्ठा cgroup_subsys_state *pos,
			 काष्ठा cgroup_subsys_state *root)
अणु
	काष्ठा cgroup_subsys_state *next;

	cgroup_निश्चित_mutex_or_rcu_locked();

	/* अगर first iteration, visit lefपंचांगost descendant which may be @root */
	अगर (!pos)
		वापस css_lefपंचांगost_descendant(root);

	/* अगर we visited @root, we're करोne */
	अगर (pos == root)
		वापस शून्य;

	/* अगर there's an unvisited sibling, visit its lefपंचांगost descendant */
	next = css_next_child(pos, pos->parent);
	अगर (next)
		वापस css_lefपंचांगost_descendant(next);

	/* no sibling left, visit parent */
	वापस pos->parent;
पूर्ण

/**
 * css_has_online_children - करोes a css have online children
 * @css: the target css
 *
 * Returns %true अगर @css has any online children; otherwise, %false.  This
 * function can be called from any context but the caller is responsible
 * क्रम synchronizing against on/offlining as necessary.
 */
bool css_has_online_children(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा cgroup_subsys_state *child;
	bool ret = false;

	rcu_पढ़ो_lock();
	css_क्रम_each_child(child, css) अणु
		अगर (child->flags & CSS_ONLINE) अणु
			ret = true;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल काष्ठा css_set *css_task_iter_next_css_set(काष्ठा css_task_iter *it)
अणु
	काष्ठा list_head *l;
	काष्ठा cgrp_cset_link *link;
	काष्ठा css_set *cset;

	lockdep_निश्चित_held(&css_set_lock);

	/* find the next thपढ़ोed cset */
	अगर (it->tcset_pos) अणु
		l = it->tcset_pos->next;

		अगर (l != it->tcset_head) अणु
			it->tcset_pos = l;
			वापस container_of(l, काष्ठा css_set,
					    thपढ़ोed_csets_node);
		पूर्ण

		it->tcset_pos = शून्य;
	पूर्ण

	/* find the next cset */
	l = it->cset_pos;
	l = l->next;
	अगर (l == it->cset_head) अणु
		it->cset_pos = शून्य;
		वापस शून्य;
	पूर्ण

	अगर (it->ss) अणु
		cset = container_of(l, काष्ठा css_set, e_cset_node[it->ss->id]);
	पूर्ण अन्यथा अणु
		link = list_entry(l, काष्ठा cgrp_cset_link, cset_link);
		cset = link->cset;
	पूर्ण

	it->cset_pos = l;

	/* initialize thपढ़ोed css_set walking */
	अगर (it->flags & CSS_TASK_ITER_THREADED) अणु
		अगर (it->cur_dcset)
			put_css_set_locked(it->cur_dcset);
		it->cur_dcset = cset;
		get_css_set(cset);

		it->tcset_head = &cset->thपढ़ोed_csets;
		it->tcset_pos = &cset->thपढ़ोed_csets;
	पूर्ण

	वापस cset;
पूर्ण

/**
 * css_task_iter_advance_css_set - advance a task iterator to the next css_set
 * @it: the iterator to advance
 *
 * Advance @it to the next css_set to walk.
 */
अटल व्योम css_task_iter_advance_css_set(काष्ठा css_task_iter *it)
अणु
	काष्ठा css_set *cset;

	lockdep_निश्चित_held(&css_set_lock);

	/* Advance to the next non-empty css_set and find first non-empty tasks list*/
	जबतक ((cset = css_task_iter_next_css_set(it))) अणु
		अगर (!list_empty(&cset->tasks)) अणु
			it->cur_tasks_head = &cset->tasks;
			अवरोध;
		पूर्ण अन्यथा अगर (!list_empty(&cset->mg_tasks)) अणु
			it->cur_tasks_head = &cset->mg_tasks;
			अवरोध;
		पूर्ण अन्यथा अगर (!list_empty(&cset->dying_tasks)) अणु
			it->cur_tasks_head = &cset->dying_tasks;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!cset) अणु
		it->task_pos = शून्य;
		वापस;
	पूर्ण
	it->task_pos = it->cur_tasks_head->next;

	/*
	 * We करोn't keep css_sets locked across iteration steps and thus
	 * need to take steps to ensure that iteration can be resumed after
	 * the lock is re-acquired.  Iteration is perक्रमmed at two levels -
	 * css_sets and tasks in them.
	 *
	 * Once created, a css_set never leaves its cgroup lists, so a
	 * pinned css_set is guaranteed to stay put and we can resume
	 * iteration afterwards.
	 *
	 * Tasks may leave @cset across iteration steps.  This is resolved
	 * by रेजिस्टरing each iterator with the css_set currently being
	 * walked and making css_set_move_task() advance iterators whose
	 * next task is leaving.
	 */
	अगर (it->cur_cset) अणु
		list_del(&it->iters_node);
		put_css_set_locked(it->cur_cset);
	पूर्ण
	get_css_set(cset);
	it->cur_cset = cset;
	list_add(&it->iters_node, &cset->task_iters);
पूर्ण

अटल व्योम css_task_iter_skip(काष्ठा css_task_iter *it,
			       काष्ठा task_काष्ठा *task)
अणु
	lockdep_निश्चित_held(&css_set_lock);

	अगर (it->task_pos == &task->cg_list) अणु
		it->task_pos = it->task_pos->next;
		it->flags |= CSS_TASK_ITER_SKIPPED;
	पूर्ण
पूर्ण

अटल व्योम css_task_iter_advance(काष्ठा css_task_iter *it)
अणु
	काष्ठा task_काष्ठा *task;

	lockdep_निश्चित_held(&css_set_lock);
repeat:
	अगर (it->task_pos) अणु
		/*
		 * Advance iterator to find next entry. We go through cset
		 * tasks, mg_tasks and dying_tasks, when consumed we move onto
		 * the next cset.
		 */
		अगर (it->flags & CSS_TASK_ITER_SKIPPED)
			it->flags &= ~CSS_TASK_ITER_SKIPPED;
		अन्यथा
			it->task_pos = it->task_pos->next;

		अगर (it->task_pos == &it->cur_cset->tasks) अणु
			it->cur_tasks_head = &it->cur_cset->mg_tasks;
			it->task_pos = it->cur_tasks_head->next;
		पूर्ण
		अगर (it->task_pos == &it->cur_cset->mg_tasks) अणु
			it->cur_tasks_head = &it->cur_cset->dying_tasks;
			it->task_pos = it->cur_tasks_head->next;
		पूर्ण
		अगर (it->task_pos == &it->cur_cset->dying_tasks)
			css_task_iter_advance_css_set(it);
	पूर्ण अन्यथा अणु
		/* called from start, proceed to the first cset */
		css_task_iter_advance_css_set(it);
	पूर्ण

	अगर (!it->task_pos)
		वापस;

	task = list_entry(it->task_pos, काष्ठा task_काष्ठा, cg_list);

	अगर (it->flags & CSS_TASK_ITER_PROCS) अणु
		/* अगर PROCS, skip over tasks which aren't group leaders */
		अगर (!thपढ़ो_group_leader(task))
			जाओ repeat;

		/* and dying leaders w/o live member thपढ़ोs */
		अगर (it->cur_tasks_head == &it->cur_cset->dying_tasks &&
		    !atomic_पढ़ो(&task->संकेत->live))
			जाओ repeat;
	पूर्ण अन्यथा अणु
		/* skip all dying ones */
		अगर (it->cur_tasks_head == &it->cur_cset->dying_tasks)
			जाओ repeat;
	पूर्ण
पूर्ण

/**
 * css_task_iter_start - initiate task iteration
 * @css: the css to walk tasks of
 * @flags: CSS_TASK_ITER_* flags
 * @it: the task iterator to use
 *
 * Initiate iteration through the tasks of @css.  The caller can call
 * css_task_iter_next() to walk through the tasks until the function
 * वापसs शून्य.  On completion of iteration, css_task_iter_end() must be
 * called.
 */
व्योम css_task_iter_start(काष्ठा cgroup_subsys_state *css, अचिन्हित पूर्णांक flags,
			 काष्ठा css_task_iter *it)
अणु
	स_रखो(it, 0, माप(*it));

	spin_lock_irq(&css_set_lock);

	it->ss = css->ss;
	it->flags = flags;

	अगर (it->ss)
		it->cset_pos = &css->cgroup->e_csets[css->ss->id];
	अन्यथा
		it->cset_pos = &css->cgroup->cset_links;

	it->cset_head = it->cset_pos;

	css_task_iter_advance(it);

	spin_unlock_irq(&css_set_lock);
पूर्ण

/**
 * css_task_iter_next - वापस the next task क्रम the iterator
 * @it: the task iterator being iterated
 *
 * The "next" function क्रम task iteration.  @it should have been
 * initialized via css_task_iter_start().  Returns शून्य when the iteration
 * reaches the end.
 */
काष्ठा task_काष्ठा *css_task_iter_next(काष्ठा css_task_iter *it)
अणु
	अगर (it->cur_task) अणु
		put_task_काष्ठा(it->cur_task);
		it->cur_task = शून्य;
	पूर्ण

	spin_lock_irq(&css_set_lock);

	/* @it may be half-advanced by skips, finish advancing */
	अगर (it->flags & CSS_TASK_ITER_SKIPPED)
		css_task_iter_advance(it);

	अगर (it->task_pos) अणु
		it->cur_task = list_entry(it->task_pos, काष्ठा task_काष्ठा,
					  cg_list);
		get_task_काष्ठा(it->cur_task);
		css_task_iter_advance(it);
	पूर्ण

	spin_unlock_irq(&css_set_lock);

	वापस it->cur_task;
पूर्ण

/**
 * css_task_iter_end - finish task iteration
 * @it: the task iterator to finish
 *
 * Finish task iteration started by css_task_iter_start().
 */
व्योम css_task_iter_end(काष्ठा css_task_iter *it)
अणु
	अगर (it->cur_cset) अणु
		spin_lock_irq(&css_set_lock);
		list_del(&it->iters_node);
		put_css_set_locked(it->cur_cset);
		spin_unlock_irq(&css_set_lock);
	पूर्ण

	अगर (it->cur_dcset)
		put_css_set(it->cur_dcset);

	अगर (it->cur_task)
		put_task_काष्ठा(it->cur_task);
पूर्ण

अटल व्योम cgroup_procs_release(काष्ठा kernfs_खोलो_file *of)
अणु
	अगर (of->priv) अणु
		css_task_iter_end(of->priv);
		kमुक्त(of->priv);
	पूर्ण
पूर्ण

अटल व्योम *cgroup_procs_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	काष्ठा kernfs_खोलो_file *of = s->निजी;
	काष्ठा css_task_iter *it = of->priv;

	अगर (pos)
		(*pos)++;

	वापस css_task_iter_next(it);
पूर्ण

अटल व्योम *__cgroup_procs_start(काष्ठा seq_file *s, loff_t *pos,
				  अचिन्हित पूर्णांक iter_flags)
अणु
	काष्ठा kernfs_खोलो_file *of = s->निजी;
	काष्ठा cgroup *cgrp = seq_css(s)->cgroup;
	काष्ठा css_task_iter *it = of->priv;

	/*
	 * When a seq_file is seeked, it's always traversed sequentially
	 * from position 0, so we can simply keep iterating on !0 *pos.
	 */
	अगर (!it) अणु
		अगर (WARN_ON_ONCE((*pos)))
			वापस ERR_PTR(-EINVAL);

		it = kzalloc(माप(*it), GFP_KERNEL);
		अगर (!it)
			वापस ERR_PTR(-ENOMEM);
		of->priv = it;
		css_task_iter_start(&cgrp->self, iter_flags, it);
	पूर्ण अन्यथा अगर (!(*pos)) अणु
		css_task_iter_end(it);
		css_task_iter_start(&cgrp->self, iter_flags, it);
	पूर्ण अन्यथा
		वापस it->cur_task;

	वापस cgroup_procs_next(s, शून्य, शून्य);
पूर्ण

अटल व्योम *cgroup_procs_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	काष्ठा cgroup *cgrp = seq_css(s)->cgroup;

	/*
	 * All processes of a thपढ़ोed subtree beदीर्घ to the करोमुख्य cgroup
	 * of the subtree.  Only thपढ़ोs can be distributed across the
	 * subtree.  Reject पढ़ोs on cgroup.procs in the subtree proper.
	 * They're always empty anyway.
	 */
	अगर (cgroup_is_thपढ़ोed(cgrp))
		वापस ERR_PTR(-EOPNOTSUPP);

	वापस __cgroup_procs_start(s, pos, CSS_TASK_ITER_PROCS |
					    CSS_TASK_ITER_THREADED);
पूर्ण

अटल पूर्णांक cgroup_procs_show(काष्ठा seq_file *s, व्योम *v)
अणु
	seq_म_लिखो(s, "%d\n", task_pid_vnr(v));
	वापस 0;
पूर्ण

अटल पूर्णांक cgroup_may_ग_लिखो(स्थिर काष्ठा cgroup *cgrp, काष्ठा super_block *sb)
अणु
	पूर्णांक ret;
	काष्ठा inode *inode;

	lockdep_निश्चित_held(&cgroup_mutex);

	inode = kernfs_get_inode(sb, cgrp->procs_file.kn);
	अगर (!inode)
		वापस -ENOMEM;

	ret = inode_permission(&init_user_ns, inode, MAY_WRITE);
	iput(inode);
	वापस ret;
पूर्ण

अटल पूर्णांक cgroup_procs_ग_लिखो_permission(काष्ठा cgroup *src_cgrp,
					 काष्ठा cgroup *dst_cgrp,
					 काष्ठा super_block *sb)
अणु
	काष्ठा cgroup_namespace *ns = current->nsproxy->cgroup_ns;
	काष्ठा cgroup *com_cgrp = src_cgrp;
	पूर्णांक ret;

	lockdep_निश्चित_held(&cgroup_mutex);

	/* find the common ancestor */
	जबतक (!cgroup_is_descendant(dst_cgrp, com_cgrp))
		com_cgrp = cgroup_parent(com_cgrp);

	/* %current should be authorized to migrate to the common ancestor */
	ret = cgroup_may_ग_लिखो(com_cgrp, sb);
	अगर (ret)
		वापस ret;

	/*
	 * If namespaces are delegation boundaries, %current must be able
	 * to see both source and destination cgroups from its namespace.
	 */
	अगर ((cgrp_dfl_root.flags & CGRP_ROOT_NS_DELEGATE) &&
	    (!cgroup_is_descendant(src_cgrp, ns->root_cset->dfl_cgrp) ||
	     !cgroup_is_descendant(dst_cgrp, ns->root_cset->dfl_cgrp)))
		वापस -ENOENT;

	वापस 0;
पूर्ण

अटल पूर्णांक cgroup_attach_permissions(काष्ठा cgroup *src_cgrp,
				     काष्ठा cgroup *dst_cgrp,
				     काष्ठा super_block *sb, bool thपढ़ोgroup)
अणु
	पूर्णांक ret = 0;

	ret = cgroup_procs_ग_लिखो_permission(src_cgrp, dst_cgrp, sb);
	अगर (ret)
		वापस ret;

	ret = cgroup_migrate_vet_dst(dst_cgrp);
	अगर (ret)
		वापस ret;

	अगर (!thपढ़ोgroup && (src_cgrp->करोm_cgrp != dst_cgrp->करोm_cgrp))
		ret = -EOPNOTSUPP;

	वापस ret;
पूर्ण

अटल sमाप_प्रकार __cgroup_procs_ग_लिखो(काष्ठा kernfs_खोलो_file *of, अक्षर *buf,
				    bool thपढ़ोgroup)
अणु
	काष्ठा cgroup *src_cgrp, *dst_cgrp;
	काष्ठा task_काष्ठा *task;
	sमाप_प्रकार ret;
	bool locked;

	dst_cgrp = cgroup_kn_lock_live(of->kn, false);
	अगर (!dst_cgrp)
		वापस -ENODEV;

	task = cgroup_procs_ग_लिखो_start(buf, thपढ़ोgroup, &locked);
	ret = PTR_ERR_OR_ZERO(task);
	अगर (ret)
		जाओ out_unlock;

	/* find the source cgroup */
	spin_lock_irq(&css_set_lock);
	src_cgrp = task_cgroup_from_root(task, &cgrp_dfl_root);
	spin_unlock_irq(&css_set_lock);

	/* process and thपढ़ो migrations follow same delegation rule */
	ret = cgroup_attach_permissions(src_cgrp, dst_cgrp,
					of->file->f_path.dentry->d_sb, thपढ़ोgroup);
	अगर (ret)
		जाओ out_finish;

	ret = cgroup_attach_task(dst_cgrp, task, thपढ़ोgroup);

out_finish:
	cgroup_procs_ग_लिखो_finish(task, locked);
out_unlock:
	cgroup_kn_unlock(of->kn);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार cgroup_procs_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
				  अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	वापस __cgroup_procs_ग_लिखो(of, buf, true) ?: nbytes;
पूर्ण

अटल व्योम *cgroup_thपढ़ोs_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	वापस __cgroup_procs_start(s, pos, 0);
पूर्ण

अटल sमाप_प्रकार cgroup_thपढ़ोs_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
				    अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	वापस __cgroup_procs_ग_लिखो(of, buf, false) ?: nbytes;
पूर्ण

/* cgroup core पूर्णांकerface files क्रम the शेष hierarchy */
अटल काष्ठा cftype cgroup_base_files[] = अणु
	अणु
		.name = "cgroup.type",
		.flags = CFTYPE_NOT_ON_ROOT,
		.seq_show = cgroup_type_show,
		.ग_लिखो = cgroup_type_ग_लिखो,
	पूर्ण,
	अणु
		.name = "cgroup.procs",
		.flags = CFTYPE_NS_DELEGATABLE,
		.file_offset = दुरत्व(काष्ठा cgroup, procs_file),
		.release = cgroup_procs_release,
		.seq_start = cgroup_procs_start,
		.seq_next = cgroup_procs_next,
		.seq_show = cgroup_procs_show,
		.ग_लिखो = cgroup_procs_ग_लिखो,
	पूर्ण,
	अणु
		.name = "cgroup.threads",
		.flags = CFTYPE_NS_DELEGATABLE,
		.release = cgroup_procs_release,
		.seq_start = cgroup_thपढ़ोs_start,
		.seq_next = cgroup_procs_next,
		.seq_show = cgroup_procs_show,
		.ग_लिखो = cgroup_thपढ़ोs_ग_लिखो,
	पूर्ण,
	अणु
		.name = "cgroup.controllers",
		.seq_show = cgroup_controllers_show,
	पूर्ण,
	अणु
		.name = "cgroup.subtree_control",
		.flags = CFTYPE_NS_DELEGATABLE,
		.seq_show = cgroup_subtree_control_show,
		.ग_लिखो = cgroup_subtree_control_ग_लिखो,
	पूर्ण,
	अणु
		.name = "cgroup.events",
		.flags = CFTYPE_NOT_ON_ROOT,
		.file_offset = दुरत्व(काष्ठा cgroup, events_file),
		.seq_show = cgroup_events_show,
	पूर्ण,
	अणु
		.name = "cgroup.max.descendants",
		.seq_show = cgroup_max_descendants_show,
		.ग_लिखो = cgroup_max_descendants_ग_लिखो,
	पूर्ण,
	अणु
		.name = "cgroup.max.depth",
		.seq_show = cgroup_max_depth_show,
		.ग_लिखो = cgroup_max_depth_ग_लिखो,
	पूर्ण,
	अणु
		.name = "cgroup.stat",
		.seq_show = cgroup_stat_show,
	पूर्ण,
	अणु
		.name = "cgroup.freeze",
		.flags = CFTYPE_NOT_ON_ROOT,
		.seq_show = cgroup_मुक्तze_show,
		.ग_लिखो = cgroup_मुक्तze_ग_लिखो,
	पूर्ण,
	अणु
		.name = "cpu.stat",
		.seq_show = cpu_stat_show,
	पूर्ण,
#अगर_घोषित CONFIG_PSI
	अणु
		.name = "io.pressure",
		.seq_show = cgroup_io_pressure_show,
		.ग_लिखो = cgroup_io_pressure_ग_लिखो,
		.poll = cgroup_pressure_poll,
		.release = cgroup_pressure_release,
	पूर्ण,
	अणु
		.name = "memory.pressure",
		.seq_show = cgroup_memory_pressure_show,
		.ग_लिखो = cgroup_memory_pressure_ग_लिखो,
		.poll = cgroup_pressure_poll,
		.release = cgroup_pressure_release,
	पूर्ण,
	अणु
		.name = "cpu.pressure",
		.seq_show = cgroup_cpu_pressure_show,
		.ग_लिखो = cgroup_cpu_pressure_ग_लिखो,
		.poll = cgroup_pressure_poll,
		.release = cgroup_pressure_release,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_PSI */
	अणु पूर्ण	/* terminate */
पूर्ण;

/*
 * css deकाष्ठाion is four-stage process.
 *
 * 1. Deकाष्ठाion starts.  Killing of the percpu_ref is initiated.
 *    Implemented in समाप्त_css().
 *
 * 2. When the percpu_ref is confirmed to be visible as समाप्तed on all CPUs
 *    and thus css_tryget_online() is guaranteed to fail, the css can be
 *    offlined by invoking offline_css().  After offlining, the base ref is
 *    put.  Implemented in css_समाप्तed_work_fn().
 *
 * 3. When the percpu_ref reaches zero, the only possible reमुख्यing
 *    accessors are inside RCU पढ़ो sections.  css_release() schedules the
 *    RCU callback.
 *
 * 4. After the grace period, the css can be मुक्तd.  Implemented in
 *    css_मुक्त_work_fn().
 *
 * It is actually hairier because both step 2 and 4 require process context
 * and thus involve punting to css->destroy_work adding two additional
 * steps to the alपढ़ोy complex sequence.
 */
अटल व्योम css_मुक्त_rwork_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cgroup_subsys_state *css = container_of(to_rcu_work(work),
				काष्ठा cgroup_subsys_state, destroy_rwork);
	काष्ठा cgroup_subsys *ss = css->ss;
	काष्ठा cgroup *cgrp = css->cgroup;

	percpu_ref_निकास(&css->refcnt);

	अगर (ss) अणु
		/* css मुक्त path */
		काष्ठा cgroup_subsys_state *parent = css->parent;
		पूर्णांक id = css->id;

		ss->css_मुक्त(css);
		cgroup_idr_हटाओ(&ss->css_idr, id);
		cgroup_put(cgrp);

		अगर (parent)
			css_put(parent);
	पूर्ण अन्यथा अणु
		/* cgroup मुक्त path */
		atomic_dec(&cgrp->root->nr_cgrps);
		cgroup1_pidlist_destroy_all(cgrp);
		cancel_work_sync(&cgrp->release_agent_work);

		अगर (cgroup_parent(cgrp)) अणु
			/*
			 * We get a ref to the parent, and put the ref when
			 * this cgroup is being मुक्तd, so it's guaranteed
			 * that the parent won't be destroyed beक्रमe its
			 * children.
			 */
			cgroup_put(cgroup_parent(cgrp));
			kernfs_put(cgrp->kn);
			psi_cgroup_मुक्त(cgrp);
			cgroup_rstat_निकास(cgrp);
			kमुक्त(cgrp);
		पूर्ण अन्यथा अणु
			/*
			 * This is root cgroup's refcnt reaching zero,
			 * which indicates that the root should be
			 * released.
			 */
			cgroup_destroy_root(cgrp->root);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम css_release_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cgroup_subsys_state *css =
		container_of(work, काष्ठा cgroup_subsys_state, destroy_work);
	काष्ठा cgroup_subsys *ss = css->ss;
	काष्ठा cgroup *cgrp = css->cgroup;

	mutex_lock(&cgroup_mutex);

	css->flags |= CSS_RELEASED;
	list_del_rcu(&css->sibling);

	अगर (ss) अणु
		/* css release path */
		अगर (!list_empty(&css->rstat_css_node)) अणु
			cgroup_rstat_flush(cgrp);
			list_del_rcu(&css->rstat_css_node);
		पूर्ण

		cgroup_idr_replace(&ss->css_idr, शून्य, css->id);
		अगर (ss->css_released)
			ss->css_released(css);
	पूर्ण अन्यथा अणु
		काष्ठा cgroup *tcgrp;

		/* cgroup release path */
		TRACE_CGROUP_PATH(release, cgrp);

		cgroup_rstat_flush(cgrp);

		spin_lock_irq(&css_set_lock);
		क्रम (tcgrp = cgroup_parent(cgrp); tcgrp;
		     tcgrp = cgroup_parent(tcgrp))
			tcgrp->nr_dying_descendants--;
		spin_unlock_irq(&css_set_lock);

		/*
		 * There are two control paths which try to determine
		 * cgroup from dentry without going through kernfs -
		 * cgroupstats_build() and css_tryget_online_from_dir().
		 * Those are supported by RCU protecting clearing of
		 * cgrp->kn->priv backpoपूर्णांकer.
		 */
		अगर (cgrp->kn)
			RCU_INIT_POINTER(*(व्योम __rcu __क्रमce **)&cgrp->kn->priv,
					 शून्य);
	पूर्ण

	mutex_unlock(&cgroup_mutex);

	INIT_RCU_WORK(&css->destroy_rwork, css_मुक्त_rwork_fn);
	queue_rcu_work(cgroup_destroy_wq, &css->destroy_rwork);
पूर्ण

अटल व्योम css_release(काष्ठा percpu_ref *ref)
अणु
	काष्ठा cgroup_subsys_state *css =
		container_of(ref, काष्ठा cgroup_subsys_state, refcnt);

	INIT_WORK(&css->destroy_work, css_release_work_fn);
	queue_work(cgroup_destroy_wq, &css->destroy_work);
पूर्ण

अटल व्योम init_and_link_css(काष्ठा cgroup_subsys_state *css,
			      काष्ठा cgroup_subsys *ss, काष्ठा cgroup *cgrp)
अणु
	lockdep_निश्चित_held(&cgroup_mutex);

	cgroup_get_live(cgrp);

	स_रखो(css, 0, माप(*css));
	css->cgroup = cgrp;
	css->ss = ss;
	css->id = -1;
	INIT_LIST_HEAD(&css->sibling);
	INIT_LIST_HEAD(&css->children);
	INIT_LIST_HEAD(&css->rstat_css_node);
	css->serial_nr = css_serial_nr_next++;
	atomic_set(&css->online_cnt, 0);

	अगर (cgroup_parent(cgrp)) अणु
		css->parent = cgroup_css(cgroup_parent(cgrp), ss);
		css_get(css->parent);
	पूर्ण

	अगर (ss->css_rstat_flush)
		list_add_rcu(&css->rstat_css_node, &cgrp->rstat_css_list);

	BUG_ON(cgroup_css(cgrp, ss));
पूर्ण

/* invoke ->css_online() on a new CSS and mark it online अगर successful */
अटल पूर्णांक online_css(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा cgroup_subsys *ss = css->ss;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&cgroup_mutex);

	अगर (ss->css_online)
		ret = ss->css_online(css);
	अगर (!ret) अणु
		css->flags |= CSS_ONLINE;
		rcu_assign_poपूर्णांकer(css->cgroup->subsys[ss->id], css);

		atomic_inc(&css->online_cnt);
		अगर (css->parent)
			atomic_inc(&css->parent->online_cnt);
	पूर्ण
	वापस ret;
पूर्ण

/* अगर the CSS is online, invoke ->css_offline() on it and mark it offline */
अटल व्योम offline_css(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा cgroup_subsys *ss = css->ss;

	lockdep_निश्चित_held(&cgroup_mutex);

	अगर (!(css->flags & CSS_ONLINE))
		वापस;

	अगर (ss->css_offline)
		ss->css_offline(css);

	css->flags &= ~CSS_ONLINE;
	RCU_INIT_POINTER(css->cgroup->subsys[ss->id], शून्य);

	wake_up_all(&css->cgroup->offline_रुकोq);
पूर्ण

/**
 * css_create - create a cgroup_subsys_state
 * @cgrp: the cgroup new css will be associated with
 * @ss: the subsys of new css
 *
 * Create a new css associated with @cgrp - @ss pair.  On success, the new
 * css is online and installed in @cgrp.  This function करोesn't create the
 * पूर्णांकerface files.  Returns 0 on success, -त्रुटि_सं on failure.
 */
अटल काष्ठा cgroup_subsys_state *css_create(काष्ठा cgroup *cgrp,
					      काष्ठा cgroup_subsys *ss)
अणु
	काष्ठा cgroup *parent = cgroup_parent(cgrp);
	काष्ठा cgroup_subsys_state *parent_css = cgroup_css(parent, ss);
	काष्ठा cgroup_subsys_state *css;
	पूर्णांक err;

	lockdep_निश्चित_held(&cgroup_mutex);

	css = ss->css_alloc(parent_css);
	अगर (!css)
		css = ERR_PTR(-ENOMEM);
	अगर (IS_ERR(css))
		वापस css;

	init_and_link_css(css, ss, cgrp);

	err = percpu_ref_init(&css->refcnt, css_release, 0, GFP_KERNEL);
	अगर (err)
		जाओ err_मुक्त_css;

	err = cgroup_idr_alloc(&ss->css_idr, शून्य, 2, 0, GFP_KERNEL);
	अगर (err < 0)
		जाओ err_मुक्त_css;
	css->id = err;

	/* @css is पढ़ोy to be brought online now, make it visible */
	list_add_tail_rcu(&css->sibling, &parent_css->children);
	cgroup_idr_replace(&ss->css_idr, css, css->id);

	err = online_css(css);
	अगर (err)
		जाओ err_list_del;

	वापस css;

err_list_del:
	list_del_rcu(&css->sibling);
err_मुक्त_css:
	list_del_rcu(&css->rstat_css_node);
	INIT_RCU_WORK(&css->destroy_rwork, css_मुक्त_rwork_fn);
	queue_rcu_work(cgroup_destroy_wq, &css->destroy_rwork);
	वापस ERR_PTR(err);
पूर्ण

/*
 * The वापसed cgroup is fully initialized including its control mask, but
 * it isn't associated with its kernfs_node and doesn't have the control
 * mask applied.
 */
अटल काष्ठा cgroup *cgroup_create(काष्ठा cgroup *parent, स्थिर अक्षर *name,
				    umode_t mode)
अणु
	काष्ठा cgroup_root *root = parent->root;
	काष्ठा cgroup *cgrp, *tcgrp;
	काष्ठा kernfs_node *kn;
	पूर्णांक level = parent->level + 1;
	पूर्णांक ret;

	/* allocate the cgroup and its ID, 0 is reserved क्रम the root */
	cgrp = kzalloc(काष्ठा_size(cgrp, ancestor_ids, (level + 1)),
		       GFP_KERNEL);
	अगर (!cgrp)
		वापस ERR_PTR(-ENOMEM);

	ret = percpu_ref_init(&cgrp->self.refcnt, css_release, 0, GFP_KERNEL);
	अगर (ret)
		जाओ out_मुक्त_cgrp;

	ret = cgroup_rstat_init(cgrp);
	अगर (ret)
		जाओ out_cancel_ref;

	/* create the directory */
	kn = kernfs_create_dir(parent->kn, name, mode, cgrp);
	अगर (IS_ERR(kn)) अणु
		ret = PTR_ERR(kn);
		जाओ out_stat_निकास;
	पूर्ण
	cgrp->kn = kn;

	init_cgroup_housekeeping(cgrp);

	cgrp->self.parent = &parent->self;
	cgrp->root = root;
	cgrp->level = level;

	ret = psi_cgroup_alloc(cgrp);
	अगर (ret)
		जाओ out_kernfs_हटाओ;

	ret = cgroup_bpf_inherit(cgrp);
	अगर (ret)
		जाओ out_psi_मुक्त;

	/*
	 * New cgroup inherits effective मुक्तze counter, and
	 * अगर the parent has to be frozen, the child has too.
	 */
	cgrp->मुक्तzer.e_मुक्तze = parent->मुक्तzer.e_मुक्तze;
	अगर (cgrp->मुक्तzer.e_मुक्तze) अणु
		/*
		 * Set the CGRP_FREEZE flag, so when a process will be
		 * attached to the child cgroup, it will become frozen.
		 * At this poपूर्णांक the new cgroup is unpopulated, so we can
		 * consider it frozen immediately.
		 */
		set_bit(CGRP_FREEZE, &cgrp->flags);
		set_bit(CGRP_FROZEN, &cgrp->flags);
	पूर्ण

	spin_lock_irq(&css_set_lock);
	क्रम (tcgrp = cgrp; tcgrp; tcgrp = cgroup_parent(tcgrp)) अणु
		cgrp->ancestor_ids[tcgrp->level] = cgroup_id(tcgrp);

		अगर (tcgrp != cgrp) अणु
			tcgrp->nr_descendants++;

			/*
			 * If the new cgroup is frozen, all ancestor cgroups
			 * get a new frozen descendant, but their state can't
			 * change because of this.
			 */
			अगर (cgrp->मुक्तzer.e_मुक्तze)
				tcgrp->मुक्तzer.nr_frozen_descendants++;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&css_set_lock);

	अगर (notअगरy_on_release(parent))
		set_bit(CGRP_NOTIFY_ON_RELEASE, &cgrp->flags);

	अगर (test_bit(CGRP_CPUSET_CLONE_CHILDREN, &parent->flags))
		set_bit(CGRP_CPUSET_CLONE_CHILDREN, &cgrp->flags);

	cgrp->self.serial_nr = css_serial_nr_next++;

	/* allocation complete, commit to creation */
	list_add_tail_rcu(&cgrp->self.sibling, &cgroup_parent(cgrp)->self.children);
	atomic_inc(&root->nr_cgrps);
	cgroup_get_live(parent);

	/*
	 * On the शेष hierarchy, a child करोesn't स्वतःmatically inherit
	 * subtree_control from the parent.  Each is configured manually.
	 */
	अगर (!cgroup_on_dfl(cgrp))
		cgrp->subtree_control = cgroup_control(cgrp);

	cgroup_propagate_control(cgrp);

	वापस cgrp;

out_psi_मुक्त:
	psi_cgroup_मुक्त(cgrp);
out_kernfs_हटाओ:
	kernfs_हटाओ(cgrp->kn);
out_stat_निकास:
	cgroup_rstat_निकास(cgrp);
out_cancel_ref:
	percpu_ref_निकास(&cgrp->self.refcnt);
out_मुक्त_cgrp:
	kमुक्त(cgrp);
	वापस ERR_PTR(ret);
पूर्ण

अटल bool cgroup_check_hierarchy_limits(काष्ठा cgroup *parent)
अणु
	काष्ठा cgroup *cgroup;
	पूर्णांक ret = false;
	पूर्णांक level = 1;

	lockdep_निश्चित_held(&cgroup_mutex);

	क्रम (cgroup = parent; cgroup; cgroup = cgroup_parent(cgroup)) अणु
		अगर (cgroup->nr_descendants >= cgroup->max_descendants)
			जाओ fail;

		अगर (level > cgroup->max_depth)
			जाओ fail;

		level++;
	पूर्ण

	ret = true;
fail:
	वापस ret;
पूर्ण

पूर्णांक cgroup_सूची_गढ़ो(काष्ठा kernfs_node *parent_kn, स्थिर अक्षर *name, umode_t mode)
अणु
	काष्ठा cgroup *parent, *cgrp;
	पूर्णांक ret;

	/* करो not accept '\n' to prevent making /proc/<pid>/cgroup unparsable */
	अगर (म_अक्षर(name, '\n'))
		वापस -EINVAL;

	parent = cgroup_kn_lock_live(parent_kn, false);
	अगर (!parent)
		वापस -ENODEV;

	अगर (!cgroup_check_hierarchy_limits(parent)) अणु
		ret = -EAGAIN;
		जाओ out_unlock;
	पूर्ण

	cgrp = cgroup_create(parent, name, mode);
	अगर (IS_ERR(cgrp)) अणु
		ret = PTR_ERR(cgrp);
		जाओ out_unlock;
	पूर्ण

	/*
	 * This extra ref will be put in cgroup_मुक्त_fn() and guarantees
	 * that @cgrp->kn is always accessible.
	 */
	kernfs_get(cgrp->kn);

	ret = cgroup_kn_set_ugid(cgrp->kn);
	अगर (ret)
		जाओ out_destroy;

	ret = css_populate_dir(&cgrp->self);
	अगर (ret)
		जाओ out_destroy;

	ret = cgroup_apply_control_enable(cgrp);
	अगर (ret)
		जाओ out_destroy;

	TRACE_CGROUP_PATH(सूची_गढ़ो, cgrp);

	/* let's create and online css's */
	kernfs_activate(cgrp->kn);

	ret = 0;
	जाओ out_unlock;

out_destroy:
	cgroup_destroy_locked(cgrp);
out_unlock:
	cgroup_kn_unlock(parent_kn);
	वापस ret;
पूर्ण

/*
 * This is called when the refcnt of a css is confirmed to be समाप्तed.
 * css_tryget_online() is now guaranteed to fail.  Tell the subप्रणाली to
 * initiate deकाष्ठाion and put the css ref from समाप्त_css().
 */
अटल व्योम css_समाप्तed_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cgroup_subsys_state *css =
		container_of(work, काष्ठा cgroup_subsys_state, destroy_work);

	mutex_lock(&cgroup_mutex);

	करो अणु
		offline_css(css);
		css_put(css);
		/* @css can't go away while we're holding cgroup_mutex */
		css = css->parent;
	पूर्ण जबतक (css && atomic_dec_and_test(&css->online_cnt));

	mutex_unlock(&cgroup_mutex);
पूर्ण

/* css समाप्त confirmation processing requires process context, bounce */
अटल व्योम css_समाप्तed_ref_fn(काष्ठा percpu_ref *ref)
अणु
	काष्ठा cgroup_subsys_state *css =
		container_of(ref, काष्ठा cgroup_subsys_state, refcnt);

	अगर (atomic_dec_and_test(&css->online_cnt)) अणु
		INIT_WORK(&css->destroy_work, css_समाप्तed_work_fn);
		queue_work(cgroup_destroy_wq, &css->destroy_work);
	पूर्ण
पूर्ण

/**
 * समाप्त_css - destroy a css
 * @css: css to destroy
 *
 * This function initiates deकाष्ठाion of @css by removing cgroup पूर्णांकerface
 * files and putting its base reference.  ->css_offline() will be invoked
 * asynchronously once css_tryget_online() is guaranteed to fail and when
 * the reference count reaches zero, @css will be released.
 */
अटल व्योम समाप्त_css(काष्ठा cgroup_subsys_state *css)
अणु
	lockdep_निश्चित_held(&cgroup_mutex);

	अगर (css->flags & CSS_DYING)
		वापस;

	css->flags |= CSS_DYING;

	/*
	 * This must happen beक्रमe css is disassociated with its cgroup.
	 * See seq_css() क्रम details.
	 */
	css_clear_dir(css);

	/*
	 * Killing would put the base ref, but we need to keep it alive
	 * until after ->css_offline().
	 */
	css_get(css);

	/*
	 * cgroup core guarantees that, by the समय ->css_offline() is
	 * invoked, no new css reference will be given out via
	 * css_tryget_online().  We can't simply call percpu_ref_समाप्त() and
	 * proceed to offlining css's because percpu_ref_kill() doesn't
	 * guarantee that the ref is seen as समाप्तed on all CPUs on वापस.
	 *
	 * Use percpu_ref_समाप्त_and_confirm() to get notअगरications as each
	 * css is confirmed to be seen as समाप्तed on all CPUs.
	 */
	percpu_ref_समाप्त_and_confirm(&css->refcnt, css_समाप्तed_ref_fn);
पूर्ण

/**
 * cgroup_destroy_locked - the first stage of cgroup deकाष्ठाion
 * @cgrp: cgroup to be destroyed
 *
 * css's make use of percpu refcnts whose killing latency shouldn't be
 * exposed to userland and are RCU रक्षित.  Also, cgroup core needs to
 * guarantee that css_tryget_online() won't succeed by the समय
 * ->css_offline() is invoked.  To satisfy all the requirements,
 * deकाष्ठाion is implemented in the following two steps.
 *
 * s1. Verअगरy @cgrp can be destroyed and mark it dying.  Remove all
 *     userland visible parts and start समाप्तing the percpu refcnts of
 *     css's.  Set up so that the next stage will be kicked off once all
 *     the percpu refcnts are confirmed to be समाप्तed.
 *
 * s2. Invoke ->css_offline(), mark the cgroup dead and proceed with the
 *     rest of deकाष्ठाion.  Once all cgroup references are gone, the
 *     cgroup is RCU-मुक्तd.
 *
 * This function implements s1.  After this step, @cgrp is gone as far as
 * the userland is concerned and a new cgroup with the same name may be
 * created.  As cgroup करोesn't care about the names पूर्णांकernally, this
 * करोesn't cause any problem.
 */
अटल पूर्णांक cgroup_destroy_locked(काष्ठा cgroup *cgrp)
	__releases(&cgroup_mutex) __acquires(&cgroup_mutex)
अणु
	काष्ठा cgroup *tcgrp, *parent = cgroup_parent(cgrp);
	काष्ठा cgroup_subsys_state *css;
	काष्ठा cgrp_cset_link *link;
	पूर्णांक ssid;

	lockdep_निश्चित_held(&cgroup_mutex);

	/*
	 * Only migration can उठाओ populated from zero and we're alपढ़ोy
	 * holding cgroup_mutex.
	 */
	अगर (cgroup_is_populated(cgrp))
		वापस -EBUSY;

	/*
	 * Make sure there's no live children.  We can't test emptiness of
	 * ->self.children as dead children linger on it जबतक being
	 * drained; otherwise, "rmdir parent/child parent" may fail.
	 */
	अगर (css_has_online_children(&cgrp->self))
		वापस -EBUSY;

	/*
	 * Mark @cgrp and the associated csets dead.  The क्रमmer prevents
	 * further task migration and child creation by disabling
	 * cgroup_lock_live_group().  The latter makes the csets ignored by
	 * the migration path.
	 */
	cgrp->self.flags &= ~CSS_ONLINE;

	spin_lock_irq(&css_set_lock);
	list_क्रम_each_entry(link, &cgrp->cset_links, cset_link)
		link->cset->dead = true;
	spin_unlock_irq(&css_set_lock);

	/* initiate massacre of all css's */
	क्रम_each_css(css, ssid, cgrp)
		समाप्त_css(css);

	/* clear and हटाओ @cgrp dir, @cgrp has an extra ref on its kn */
	css_clear_dir(&cgrp->self);
	kernfs_हटाओ(cgrp->kn);

	अगर (parent && cgroup_is_thपढ़ोed(cgrp))
		parent->nr_thपढ़ोed_children--;

	spin_lock_irq(&css_set_lock);
	क्रम (tcgrp = cgroup_parent(cgrp); tcgrp; tcgrp = cgroup_parent(tcgrp)) अणु
		tcgrp->nr_descendants--;
		tcgrp->nr_dying_descendants++;
		/*
		 * If the dying cgroup is frozen, decrease frozen descendants
		 * counters of ancestor cgroups.
		 */
		अगर (test_bit(CGRP_FROZEN, &cgrp->flags))
			tcgrp->मुक्तzer.nr_frozen_descendants--;
	पूर्ण
	spin_unlock_irq(&css_set_lock);

	cgroup1_check_क्रम_release(parent);

	cgroup_bpf_offline(cgrp);

	/* put the base reference */
	percpu_ref_समाप्त(&cgrp->self.refcnt);

	वापस 0;
पूर्ण;

पूर्णांक cgroup_सूची_हटाओ(काष्ठा kernfs_node *kn)
अणु
	काष्ठा cgroup *cgrp;
	पूर्णांक ret = 0;

	cgrp = cgroup_kn_lock_live(kn, false);
	अगर (!cgrp)
		वापस 0;

	ret = cgroup_destroy_locked(cgrp);
	अगर (!ret)
		TRACE_CGROUP_PATH(सूची_हटाओ, cgrp);

	cgroup_kn_unlock(kn);
	वापस ret;
पूर्ण

अटल काष्ठा kernfs_syscall_ops cgroup_kf_syscall_ops = अणु
	.show_options		= cgroup_show_options,
	.सूची_गढ़ो			= cgroup_सूची_गढ़ो,
	.सूची_हटाओ			= cgroup_सूची_हटाओ,
	.show_path		= cgroup_show_path,
पूर्ण;

अटल व्योम __init cgroup_init_subsys(काष्ठा cgroup_subsys *ss, bool early)
अणु
	काष्ठा cgroup_subsys_state *css;

	pr_debug("Initializing cgroup subsys %s\n", ss->name);

	mutex_lock(&cgroup_mutex);

	idr_init(&ss->css_idr);
	INIT_LIST_HEAD(&ss->cfts);

	/* Create the root cgroup state क्रम this subप्रणाली */
	ss->root = &cgrp_dfl_root;
	css = ss->css_alloc(cgroup_css(&cgrp_dfl_root.cgrp, ss));
	/* We करोn't handle early failures gracefully */
	BUG_ON(IS_ERR(css));
	init_and_link_css(css, ss, &cgrp_dfl_root.cgrp);

	/*
	 * Root csses are never destroyed and we can't initialize
	 * percpu_ref during early init.  Disable refcnting.
	 */
	css->flags |= CSS_NO_REF;

	अगर (early) अणु
		/* allocation can't be करोne safely during early init */
		css->id = 1;
	पूर्ण अन्यथा अणु
		css->id = cgroup_idr_alloc(&ss->css_idr, css, 1, 2, GFP_KERNEL);
		BUG_ON(css->id < 0);
	पूर्ण

	/* Update the init_css_set to contain a subsys
	 * poपूर्णांकer to this state - since the subप्रणाली is
	 * newly रेजिस्टरed, all tasks and hence the
	 * init_css_set is in the subप्रणाली's root cgroup. */
	init_css_set.subsys[ss->id] = css;

	have_विभाजन_callback |= (bool)ss->विभाजन << ss->id;
	have_निकास_callback |= (bool)ss->निकास << ss->id;
	have_release_callback |= (bool)ss->release << ss->id;
	have_canविभाजन_callback |= (bool)ss->can_विभाजन << ss->id;

	/* At प्रणाली boot, beक्रमe all subप्रणालीs have been
	 * रेजिस्टरed, no tasks have been विभाजनed, so we करोn't
	 * need to invoke विभाजन callbacks here. */
	BUG_ON(!list_empty(&init_task.tasks));

	BUG_ON(online_css(css));

	mutex_unlock(&cgroup_mutex);
पूर्ण

/**
 * cgroup_init_early - cgroup initialization at प्रणाली boot
 *
 * Initialize cgroups at प्रणाली boot, and initialize any
 * subप्रणालीs that request early init.
 */
पूर्णांक __init cgroup_init_early(व्योम)
अणु
	अटल काष्ठा cgroup_fs_context __initdata ctx;
	काष्ठा cgroup_subsys *ss;
	पूर्णांक i;

	ctx.root = &cgrp_dfl_root;
	init_cgroup_root(&ctx);
	cgrp_dfl_root.cgrp.self.flags |= CSS_NO_REF;

	RCU_INIT_POINTER(init_task.cgroups, &init_css_set);

	क्रम_each_subsys(ss, i) अणु
		WARN(!ss->css_alloc || !ss->css_मुक्त || ss->name || ss->id,
		     "invalid cgroup_subsys %d:%s css_alloc=%p css_free=%p id:name=%d:%s\n",
		     i, cgroup_subsys_name[i], ss->css_alloc, ss->css_मुक्त,
		     ss->id, ss->name);
		WARN(म_माप(cgroup_subsys_name[i]) > MAX_CGROUP_TYPE_NAMELEN,
		     "cgroup_subsys_name %s too long\n", cgroup_subsys_name[i]);

		ss->id = i;
		ss->name = cgroup_subsys_name[i];
		अगर (!ss->legacy_name)
			ss->legacy_name = cgroup_subsys_name[i];

		अगर (ss->early_init)
			cgroup_init_subsys(ss, true);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * cgroup_init - cgroup initialization
 *
 * Register cgroup fileप्रणाली and /proc file, and initialize
 * any subप्रणालीs that didn't request early init.
 */
पूर्णांक __init cgroup_init(व्योम)
अणु
	काष्ठा cgroup_subsys *ss;
	पूर्णांक ssid;

	BUILD_BUG_ON(CGROUP_SUBSYS_COUNT > 16);
	BUG_ON(cgroup_init_cftypes(शून्य, cgroup_base_files));
	BUG_ON(cgroup_init_cftypes(शून्य, cgroup1_base_files));

	cgroup_rstat_boot();

	/*
	 * The latency of the synchronize_rcu() is too high क्रम cgroups,
	 * aव्योम it at the cost of क्रमcing all पढ़ोers पूर्णांकo the slow path.
	 */
	rcu_sync_enter_start(&cgroup_thपढ़ोgroup_rwsem.rss);

	get_user_ns(init_cgroup_ns.user_ns);

	mutex_lock(&cgroup_mutex);

	/*
	 * Add init_css_set to the hash table so that dfl_root can link to
	 * it during init.
	 */
	hash_add(css_set_table, &init_css_set.hlist,
		 css_set_hash(init_css_set.subsys));

	BUG_ON(cgroup_setup_root(&cgrp_dfl_root, 0));

	mutex_unlock(&cgroup_mutex);

	क्रम_each_subsys(ss, ssid) अणु
		अगर (ss->early_init) अणु
			काष्ठा cgroup_subsys_state *css =
				init_css_set.subsys[ss->id];

			css->id = cgroup_idr_alloc(&ss->css_idr, css, 1, 2,
						   GFP_KERNEL);
			BUG_ON(css->id < 0);
		पूर्ण अन्यथा अणु
			cgroup_init_subsys(ss, false);
		पूर्ण

		list_add_tail(&init_css_set.e_cset_node[ssid],
			      &cgrp_dfl_root.cgrp.e_csets[ssid]);

		/*
		 * Setting dfl_root subsys_mask needs to consider the
		 * disabled flag and cftype registration needs kदो_स्मृति,
		 * both of which aren't available during early_init.
		 */
		अगर (!cgroup_ssid_enabled(ssid))
			जारी;

		अगर (cgroup1_ssid_disabled(ssid))
			prपूर्णांकk(KERN_INFO "Disabling %s control group subsystem in v1 mounts\n",
			       ss->name);

		cgrp_dfl_root.subsys_mask |= 1 << ss->id;

		/* implicit controllers must be thपढ़ोed too */
		WARN_ON(ss->implicit_on_dfl && !ss->thपढ़ोed);

		अगर (ss->implicit_on_dfl)
			cgrp_dfl_implicit_ss_mask |= 1 << ss->id;
		अन्यथा अगर (!ss->dfl_cftypes)
			cgrp_dfl_inhibit_ss_mask |= 1 << ss->id;

		अगर (ss->thपढ़ोed)
			cgrp_dfl_thपढ़ोed_ss_mask |= 1 << ss->id;

		अगर (ss->dfl_cftypes == ss->legacy_cftypes) अणु
			WARN_ON(cgroup_add_cftypes(ss, ss->dfl_cftypes));
		पूर्ण अन्यथा अणु
			WARN_ON(cgroup_add_dfl_cftypes(ss, ss->dfl_cftypes));
			WARN_ON(cgroup_add_legacy_cftypes(ss, ss->legacy_cftypes));
		पूर्ण

		अगर (ss->bind)
			ss->bind(init_css_set.subsys[ssid]);

		mutex_lock(&cgroup_mutex);
		css_populate_dir(init_css_set.subsys[ssid]);
		mutex_unlock(&cgroup_mutex);
	पूर्ण

	/* init_css_set.subsys[] has been updated, re-hash */
	hash_del(&init_css_set.hlist);
	hash_add(css_set_table, &init_css_set.hlist,
		 css_set_hash(init_css_set.subsys));

	WARN_ON(sysfs_create_mount_poपूर्णांक(fs_kobj, "cgroup"));
	WARN_ON(रेजिस्टर_fileप्रणाली(&cgroup_fs_type));
	WARN_ON(रेजिस्टर_fileप्रणाली(&cgroup2_fs_type));
	WARN_ON(!proc_create_single("cgroups", 0, शून्य, proc_cgroupstats_show));
#अगर_घोषित CONFIG_CPUSETS
	WARN_ON(रेजिस्टर_fileप्रणाली(&cpuset_fs_type));
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक __init cgroup_wq_init(व्योम)
अणु
	/*
	 * There isn't much poपूर्णांक in executing deकाष्ठाion path in
	 * parallel.  Good chunk is serialized with cgroup_mutex anyway.
	 * Use 1 क्रम @max_active.
	 *
	 * We would prefer to करो this in cgroup_init() above, but that
	 * is called beक्रमe init_workqueues(): so leave this until after.
	 */
	cgroup_destroy_wq = alloc_workqueue("cgroup_destroy", 0, 1);
	BUG_ON(!cgroup_destroy_wq);
	वापस 0;
पूर्ण
core_initcall(cgroup_wq_init);

व्योम cgroup_path_from_kernfs_id(u64 id, अक्षर *buf, माप_प्रकार buflen)
अणु
	काष्ठा kernfs_node *kn;

	kn = kernfs_find_and_get_node_by_id(cgrp_dfl_root.kf_root, id);
	अगर (!kn)
		वापस;
	kernfs_path(kn, buf, buflen);
	kernfs_put(kn);
पूर्ण

/*
 * proc_cgroup_show()
 *  - Prपूर्णांक task's cgroup paths पूर्णांकo seq_file, one line क्रम each hierarchy
 *  - Used क्रम /proc/<pid>/cgroup.
 */
पूर्णांक proc_cgroup_show(काष्ठा seq_file *m, काष्ठा pid_namespace *ns,
		     काष्ठा pid *pid, काष्ठा task_काष्ठा *tsk)
अणु
	अक्षर *buf;
	पूर्णांक retval;
	काष्ठा cgroup_root *root;

	retval = -ENOMEM;
	buf = kदो_स्मृति(PATH_MAX, GFP_KERNEL);
	अगर (!buf)
		जाओ out;

	mutex_lock(&cgroup_mutex);
	spin_lock_irq(&css_set_lock);

	क्रम_each_root(root) अणु
		काष्ठा cgroup_subsys *ss;
		काष्ठा cgroup *cgrp;
		पूर्णांक ssid, count = 0;

		अगर (root == &cgrp_dfl_root && !cgrp_dfl_visible)
			जारी;

		seq_म_लिखो(m, "%d:", root->hierarchy_id);
		अगर (root != &cgrp_dfl_root)
			क्रम_each_subsys(ss, ssid)
				अगर (root->subsys_mask & (1 << ssid))
					seq_म_लिखो(m, "%s%s", count++ ? "," : "",
						   ss->legacy_name);
		अगर (म_माप(root->name))
			seq_म_लिखो(m, "%sname=%s", count ? "," : "",
				   root->name);
		seq_अ_दो(m, ':');

		cgrp = task_cgroup_from_root(tsk, root);

		/*
		 * On traditional hierarchies, all zombie tasks show up as
		 * beदीर्घing to the root cgroup.  On the शेष hierarchy,
		 * जबतक a zombie करोesn't show up in "cgroup.procs" and
		 * thus can't be migrated, its /proc/PID/cgroup keeps
		 * reporting the cgroup it beदीर्घed to beक्रमe निकासing.  If
		 * the cgroup is हटाओd beक्रमe the zombie is reaped,
		 * " (deleted)" is appended to the cgroup path.
		 */
		अगर (cgroup_on_dfl(cgrp) || !(tsk->flags & PF_EXITING)) अणु
			retval = cgroup_path_ns_locked(cgrp, buf, PATH_MAX,
						current->nsproxy->cgroup_ns);
			अगर (retval >= PATH_MAX)
				retval = -ENAMETOOLONG;
			अगर (retval < 0)
				जाओ out_unlock;

			seq_माला_दो(m, buf);
		पूर्ण अन्यथा अणु
			seq_माला_दो(m, "/");
		पूर्ण

		अगर (cgroup_on_dfl(cgrp) && cgroup_is_dead(cgrp))
			seq_माला_दो(m, " (deleted)\n");
		अन्यथा
			seq_अ_दो(m, '\n');
	पूर्ण

	retval = 0;
out_unlock:
	spin_unlock_irq(&css_set_lock);
	mutex_unlock(&cgroup_mutex);
	kमुक्त(buf);
out:
	वापस retval;
पूर्ण

/**
 * cgroup_विभाजन - initialize cgroup related fields during copy_process()
 * @child: poपूर्णांकer to task_काष्ठा of विभाजनing parent process.
 *
 * A task is associated with the init_css_set until cgroup_post_विभाजन()
 * attaches it to the target css_set.
 */
व्योम cgroup_विभाजन(काष्ठा task_काष्ठा *child)
अणु
	RCU_INIT_POINTER(child->cgroups, &init_css_set);
	INIT_LIST_HEAD(&child->cg_list);
पूर्ण

अटल काष्ठा cgroup *cgroup_get_from_file(काष्ठा file *f)
अणु
	काष्ठा cgroup_subsys_state *css;
	काष्ठा cgroup *cgrp;

	css = css_tryget_online_from_dir(f->f_path.dentry, शून्य);
	अगर (IS_ERR(css))
		वापस ERR_CAST(css);

	cgrp = css->cgroup;
	अगर (!cgroup_on_dfl(cgrp)) अणु
		cgroup_put(cgrp);
		वापस ERR_PTR(-EBADF);
	पूर्ण

	वापस cgrp;
पूर्ण

/**
 * cgroup_css_set_विभाजन - find or create a css_set क्रम a child process
 * @kargs: the arguments passed to create the child process
 *
 * This functions finds or creates a new css_set which the child
 * process will be attached to in cgroup_post_विभाजन(). By शेष,
 * the child process will be given the same css_set as its parent.
 *
 * If CLONE_INTO_CGROUP is specअगरied this function will try to find an
 * existing css_set which includes the requested cgroup and अगर not create
 * a new css_set that the child will be attached to later. If this function
 * succeeds it will hold cgroup_thपढ़ोgroup_rwsem on वापस. If
 * CLONE_INTO_CGROUP is requested this function will grab cgroup mutex
 * beक्रमe grabbing cgroup_thपढ़ोgroup_rwsem and will hold a reference
 * to the target cgroup.
 */
अटल पूर्णांक cgroup_css_set_विभाजन(काष्ठा kernel_clone_args *kargs)
	__acquires(&cgroup_mutex) __acquires(&cgroup_thपढ़ोgroup_rwsem)
अणु
	पूर्णांक ret;
	काष्ठा cgroup *dst_cgrp = शून्य;
	काष्ठा css_set *cset;
	काष्ठा super_block *sb;
	काष्ठा file *f;

	अगर (kargs->flags & CLONE_INTO_CGROUP)
		mutex_lock(&cgroup_mutex);

	cgroup_thपढ़ोgroup_change_begin(current);

	spin_lock_irq(&css_set_lock);
	cset = task_css_set(current);
	get_css_set(cset);
	spin_unlock_irq(&css_set_lock);

	अगर (!(kargs->flags & CLONE_INTO_CGROUP)) अणु
		kargs->cset = cset;
		वापस 0;
	पूर्ण

	f = fget_raw(kargs->cgroup);
	अगर (!f) अणु
		ret = -EBADF;
		जाओ err;
	पूर्ण
	sb = f->f_path.dentry->d_sb;

	dst_cgrp = cgroup_get_from_file(f);
	अगर (IS_ERR(dst_cgrp)) अणु
		ret = PTR_ERR(dst_cgrp);
		dst_cgrp = शून्य;
		जाओ err;
	पूर्ण

	अगर (cgroup_is_dead(dst_cgrp)) अणु
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	/*
	 * Verअगरy that we the target cgroup is writable क्रम us. This is
	 * usually करोne by the vfs layer but since we're not going through
	 * the vfs layer here we need to करो it "manually".
	 */
	ret = cgroup_may_ग_लिखो(dst_cgrp, sb);
	अगर (ret)
		जाओ err;

	ret = cgroup_attach_permissions(cset->dfl_cgrp, dst_cgrp, sb,
					!(kargs->flags & CLONE_THREAD));
	अगर (ret)
		जाओ err;

	kargs->cset = find_css_set(cset, dst_cgrp);
	अगर (!kargs->cset) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	put_css_set(cset);
	fput(f);
	kargs->cgrp = dst_cgrp;
	वापस ret;

err:
	cgroup_thपढ़ोgroup_change_end(current);
	mutex_unlock(&cgroup_mutex);
	अगर (f)
		fput(f);
	अगर (dst_cgrp)
		cgroup_put(dst_cgrp);
	put_css_set(cset);
	अगर (kargs->cset)
		put_css_set(kargs->cset);
	वापस ret;
पूर्ण

/**
 * cgroup_css_set_put_विभाजन - drop references we took during विभाजन
 * @kargs: the arguments passed to create the child process
 *
 * Drop references to the prepared css_set and target cgroup अगर
 * CLONE_INTO_CGROUP was requested.
 */
अटल व्योम cgroup_css_set_put_विभाजन(काष्ठा kernel_clone_args *kargs)
	__releases(&cgroup_thपढ़ोgroup_rwsem) __releases(&cgroup_mutex)
अणु
	cgroup_thपढ़ोgroup_change_end(current);

	अगर (kargs->flags & CLONE_INTO_CGROUP) अणु
		काष्ठा cgroup *cgrp = kargs->cgrp;
		काष्ठा css_set *cset = kargs->cset;

		mutex_unlock(&cgroup_mutex);

		अगर (cset) अणु
			put_css_set(cset);
			kargs->cset = शून्य;
		पूर्ण

		अगर (cgrp) अणु
			cgroup_put(cgrp);
			kargs->cgrp = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * cgroup_can_विभाजन - called on a new task beक्रमe the process is exposed
 * @child: the child process
 *
 * This prepares a new css_set क्रम the child process which the child will
 * be attached to in cgroup_post_विभाजन().
 * This calls the subप्रणाली can_विभाजन() callbacks. If the cgroup_can_विभाजन()
 * callback वापसs an error, the विभाजन पातs with that error code. This
 * allows क्रम a cgroup subप्रणाली to conditionally allow or deny new विभाजनs.
 */
पूर्णांक cgroup_can_विभाजन(काष्ठा task_काष्ठा *child, काष्ठा kernel_clone_args *kargs)
अणु
	काष्ठा cgroup_subsys *ss;
	पूर्णांक i, j, ret;

	ret = cgroup_css_set_विभाजन(kargs);
	अगर (ret)
		वापस ret;

	करो_each_subsys_mask(ss, i, have_canविभाजन_callback) अणु
		ret = ss->can_विभाजन(child, kargs->cset);
		अगर (ret)
			जाओ out_revert;
	पूर्ण जबतक_each_subsys_mask();

	वापस 0;

out_revert:
	क्रम_each_subsys(ss, j) अणु
		अगर (j >= i)
			अवरोध;
		अगर (ss->cancel_विभाजन)
			ss->cancel_विभाजन(child, kargs->cset);
	पूर्ण

	cgroup_css_set_put_विभाजन(kargs);

	वापस ret;
पूर्ण

/**
 * cgroup_cancel_विभाजन - called अगर a विभाजन failed after cgroup_can_विभाजन()
 * @child: the child process
 * @kargs: the arguments passed to create the child process
 *
 * This calls the cancel_विभाजन() callbacks अगर a विभाजन failed *after*
 * cgroup_can_विभाजन() succeeded and cleans up references we took to
 * prepare a new css_set क्रम the child process in cgroup_can_विभाजन().
 */
व्योम cgroup_cancel_विभाजन(काष्ठा task_काष्ठा *child,
			काष्ठा kernel_clone_args *kargs)
अणु
	काष्ठा cgroup_subsys *ss;
	पूर्णांक i;

	क्रम_each_subsys(ss, i)
		अगर (ss->cancel_विभाजन)
			ss->cancel_विभाजन(child, kargs->cset);

	cgroup_css_set_put_विभाजन(kargs);
पूर्ण

/**
 * cgroup_post_विभाजन - finalize cgroup setup क्रम the child process
 * @child: the child process
 *
 * Attach the child process to its css_set calling the subप्रणाली विभाजन()
 * callbacks.
 */
व्योम cgroup_post_विभाजन(काष्ठा task_काष्ठा *child,
		      काष्ठा kernel_clone_args *kargs)
	__releases(&cgroup_thपढ़ोgroup_rwsem) __releases(&cgroup_mutex)
अणु
	काष्ठा cgroup_subsys *ss;
	काष्ठा css_set *cset;
	पूर्णांक i;

	cset = kargs->cset;
	kargs->cset = शून्य;

	spin_lock_irq(&css_set_lock);

	/* init tasks are special, only link regular thपढ़ोs */
	अगर (likely(child->pid)) अणु
		WARN_ON_ONCE(!list_empty(&child->cg_list));
		cset->nr_tasks++;
		css_set_move_task(child, शून्य, cset, false);
	पूर्ण अन्यथा अणु
		put_css_set(cset);
		cset = शून्य;
	पूर्ण

	/*
	 * If the cgroup has to be frozen, the new task has too.  Let's set
	 * the JOBCTL_TRAP_FREEZE jobctl bit to get the task पूर्णांकo the
	 * frozen state.
	 */
	अगर (unlikely(cgroup_task_मुक्तze(child))) अणु
		spin_lock(&child->sighand->siglock);
		WARN_ON_ONCE(child->frozen);
		child->jobctl |= JOBCTL_TRAP_FREEZE;
		spin_unlock(&child->sighand->siglock);

		/*
		 * Calling cgroup_update_frozen() isn't required here,
		 * because it will be called anyway a bit later from
		 * करो_मुक्तzer_trap(). So we aव्योम cgroup's transient चयन
		 * from the frozen state and back.
		 */
	पूर्ण

	spin_unlock_irq(&css_set_lock);

	/*
	 * Call ss->विभाजन().  This must happen after @child is linked on
	 * css_set; otherwise, @child might change state between ->विभाजन()
	 * and addition to css_set.
	 */
	करो_each_subsys_mask(ss, i, have_विभाजन_callback) अणु
		ss->विभाजन(child);
	पूर्ण जबतक_each_subsys_mask();

	/* Make the new cset the root_cset of the new cgroup namespace. */
	अगर (kargs->flags & CLONE_NEWCGROUP) अणु
		काष्ठा css_set *rcset = child->nsproxy->cgroup_ns->root_cset;

		get_css_set(cset);
		child->nsproxy->cgroup_ns->root_cset = cset;
		put_css_set(rcset);
	पूर्ण

	cgroup_css_set_put_विभाजन(kargs);
पूर्ण

/**
 * cgroup_निकास - detach cgroup from निकासing task
 * @tsk: poपूर्णांकer to task_काष्ठा of निकासing process
 *
 * Description: Detach cgroup from @tsk.
 *
 */
व्योम cgroup_निकास(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा cgroup_subsys *ss;
	काष्ठा css_set *cset;
	पूर्णांक i;

	spin_lock_irq(&css_set_lock);

	WARN_ON_ONCE(list_empty(&tsk->cg_list));
	cset = task_css_set(tsk);
	css_set_move_task(tsk, cset, शून्य, false);
	list_add_tail(&tsk->cg_list, &cset->dying_tasks);
	cset->nr_tasks--;

	WARN_ON_ONCE(cgroup_task_frozen(tsk));
	अगर (unlikely(cgroup_task_मुक्तze(tsk)))
		cgroup_update_frozen(task_dfl_cgroup(tsk));

	spin_unlock_irq(&css_set_lock);

	/* see cgroup_post_विभाजन() क्रम details */
	करो_each_subsys_mask(ss, i, have_निकास_callback) अणु
		ss->निकास(tsk);
	पूर्ण जबतक_each_subsys_mask();
पूर्ण

व्योम cgroup_release(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा cgroup_subsys *ss;
	पूर्णांक ssid;

	करो_each_subsys_mask(ss, ssid, have_release_callback) अणु
		ss->release(task);
	पूर्ण जबतक_each_subsys_mask();

	spin_lock_irq(&css_set_lock);
	css_set_skip_task_iters(task_css_set(task), task);
	list_del_init(&task->cg_list);
	spin_unlock_irq(&css_set_lock);
पूर्ण

व्योम cgroup_मुक्त(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा css_set *cset = task_css_set(task);
	put_css_set(cset);
पूर्ण

अटल पूर्णांक __init cgroup_disable(अक्षर *str)
अणु
	काष्ठा cgroup_subsys *ss;
	अक्षर *token;
	पूर्णांक i;

	जबतक ((token = strsep(&str, ",")) != शून्य) अणु
		अगर (!*token)
			जारी;

		क्रम_each_subsys(ss, i) अणु
			अगर (म_भेद(token, ss->name) &&
			    म_भेद(token, ss->legacy_name))
				जारी;

			अटल_branch_disable(cgroup_subsys_enabled_key[i]);
			pr_info("Disabling %s control group subsystem\n",
				ss->name);
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण
__setup("cgroup_disable=", cgroup_disable);

व्योम __init __weak enable_debug_cgroup(व्योम) अणु पूर्ण

अटल पूर्णांक __init enable_cgroup_debug(अक्षर *str)
अणु
	cgroup_debug = true;
	enable_debug_cgroup();
	वापस 1;
पूर्ण
__setup("cgroup_debug", enable_cgroup_debug);

/**
 * css_tryget_online_from_dir - get corresponding css from a cgroup dentry
 * @dentry: directory dentry of पूर्णांकerest
 * @ss: subप्रणाली of पूर्णांकerest
 *
 * If @dentry is a directory क्रम a cgroup which has @ss enabled on it, try
 * to get the corresponding css and वापस it.  If such css करोesn't exist
 * or can't be pinned, an ERR_PTR value is वापसed.
 */
काष्ठा cgroup_subsys_state *css_tryget_online_from_dir(काष्ठा dentry *dentry,
						       काष्ठा cgroup_subsys *ss)
अणु
	काष्ठा kernfs_node *kn = kernfs_node_from_dentry(dentry);
	काष्ठा file_प्रणाली_type *s_type = dentry->d_sb->s_type;
	काष्ठा cgroup_subsys_state *css = शून्य;
	काष्ठा cgroup *cgrp;

	/* is @dentry a cgroup dir? */
	अगर ((s_type != &cgroup_fs_type && s_type != &cgroup2_fs_type) ||
	    !kn || kernfs_type(kn) != KERNFS_सूची)
		वापस ERR_PTR(-EBADF);

	rcu_पढ़ो_lock();

	/*
	 * This path करोesn't originate from kernfs and @kn could alपढ़ोy
	 * have been or be हटाओd at any poपूर्णांक.  @kn->priv is RCU
	 * रक्षित क्रम this access.  See css_release_work_fn() क्रम details.
	 */
	cgrp = rcu_dereference(*(व्योम __rcu __क्रमce **)&kn->priv);
	अगर (cgrp)
		css = cgroup_css(cgrp, ss);

	अगर (!css || !css_tryget_online(css))
		css = ERR_PTR(-ENOENT);

	rcu_पढ़ो_unlock();
	वापस css;
पूर्ण

/**
 * css_from_id - lookup css by id
 * @id: the cgroup id
 * @ss: cgroup subsys to be looked पूर्णांकo
 *
 * Returns the css अगर there's valid one with @id, otherwise वापसs शून्य.
 * Should be called under rcu_पढ़ो_lock().
 */
काष्ठा cgroup_subsys_state *css_from_id(पूर्णांक id, काष्ठा cgroup_subsys *ss)
अणु
	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());
	वापस idr_find(&ss->css_idr, id);
पूर्ण

/**
 * cgroup_get_from_path - lookup and get a cgroup from its शेष hierarchy path
 * @path: path on the शेष hierarchy
 *
 * Find the cgroup at @path on the शेष hierarchy, increment its
 * reference count and वापस it.  Returns poपूर्णांकer to the found cgroup on
 * success, ERR_PTR(-ENOENT) अगर @path करोesn't exist and ERR_PTR(-ENOTसूची)
 * अगर @path poपूर्णांकs to a non-directory.
 */
काष्ठा cgroup *cgroup_get_from_path(स्थिर अक्षर *path)
अणु
	काष्ठा kernfs_node *kn;
	काष्ठा cgroup *cgrp;

	mutex_lock(&cgroup_mutex);

	kn = kernfs_walk_and_get(cgrp_dfl_root.cgrp.kn, path);
	अगर (kn) अणु
		अगर (kernfs_type(kn) == KERNFS_सूची) अणु
			cgrp = kn->priv;
			cgroup_get_live(cgrp);
		पूर्ण अन्यथा अणु
			cgrp = ERR_PTR(-ENOTसूची);
		पूर्ण
		kernfs_put(kn);
	पूर्ण अन्यथा अणु
		cgrp = ERR_PTR(-ENOENT);
	पूर्ण

	mutex_unlock(&cgroup_mutex);
	वापस cgrp;
पूर्ण
EXPORT_SYMBOL_GPL(cgroup_get_from_path);

/**
 * cgroup_get_from_fd - get a cgroup poपूर्णांकer from a fd
 * @fd: fd obtained by खोलो(cgroup2_dir)
 *
 * Find the cgroup from a fd which should be obtained
 * by खोलोing a cgroup directory.  Returns a poपूर्णांकer to the
 * cgroup on success. ERR_PTR is वापसed अगर the cgroup
 * cannot be found.
 */
काष्ठा cgroup *cgroup_get_from_fd(पूर्णांक fd)
अणु
	काष्ठा cgroup *cgrp;
	काष्ठा file *f;

	f = fget_raw(fd);
	अगर (!f)
		वापस ERR_PTR(-EBADF);

	cgrp = cgroup_get_from_file(f);
	fput(f);
	वापस cgrp;
पूर्ण
EXPORT_SYMBOL_GPL(cgroup_get_from_fd);

अटल u64 घातer_of_ten(पूर्णांक घातer)
अणु
	u64 v = 1;
	जबतक (घातer--)
		v *= 10;
	वापस v;
पूर्ण

/**
 * cgroup_parse_भग्न - parse a भग्नing number
 * @input: input string
 * @dec_shअगरt: number of decimal digits to shअगरt
 * @v: output
 *
 * Parse a decimal भग्नing poपूर्णांक number in @input and store the result in
 * @v with decimal poपूर्णांक right shअगरted @dec_shअगरt बार.  For example, अगर
 * @input is "12.3456" and @dec_shअगरt is 3, *@v will be set to 12345.
 * Returns 0 on success, -त्रुटि_सं otherwise.
 *
 * There's nothing cgroup specific about this function except that it's
 * currently the only user.
 */
पूर्णांक cgroup_parse_भग्न(स्थिर अक्षर *input, अचिन्हित dec_shअगरt, s64 *v)
अणु
	s64 whole, frac = 0;
	पूर्णांक fstart = 0, fend = 0, flen;

	अगर (!माला_पूछो(input, "%lld.%n%lld%n", &whole, &fstart, &frac, &fend))
		वापस -EINVAL;
	अगर (frac < 0)
		वापस -EINVAL;

	flen = fend > fstart ? fend - fstart : 0;
	अगर (flen < dec_shअगरt)
		frac *= घातer_of_ten(dec_shअगरt - flen);
	अन्यथा
		frac = DIV_ROUND_CLOSEST_ULL(frac, घातer_of_ten(flen - dec_shअगरt));

	*v = whole * घातer_of_ten(dec_shअगरt) + frac;
	वापस 0;
पूर्ण

/*
 * sock->sk_cgrp_data handling.  For more info, see sock_cgroup_data
 * definition in cgroup-defs.h.
 */
#अगर_घोषित CONFIG_SOCK_CGROUP_DATA

#अगर defined(CONFIG_CGROUP_NET_PRIO) || defined(CONFIG_CGROUP_NET_CLASSID)

DEFINE_SPINLOCK(cgroup_sk_update_lock);
अटल bool cgroup_sk_alloc_disabled __पढ़ो_mostly;

व्योम cgroup_sk_alloc_disable(व्योम)
अणु
	अगर (cgroup_sk_alloc_disabled)
		वापस;
	pr_info("cgroup: disabling cgroup2 socket matching due to net_prio or net_cls activation\n");
	cgroup_sk_alloc_disabled = true;
पूर्ण

#अन्यथा

#घोषणा cgroup_sk_alloc_disabled	false

#पूर्ण_अगर

व्योम cgroup_sk_alloc(काष्ठा sock_cgroup_data *skcd)
अणु
	अगर (cgroup_sk_alloc_disabled) अणु
		skcd->no_refcnt = 1;
		वापस;
	पूर्ण

	/* Don't associate the sock with unrelated interrupted task's cgroup. */
	अगर (in_पूर्णांकerrupt())
		वापस;

	rcu_पढ़ो_lock();

	जबतक (true) अणु
		काष्ठा css_set *cset;

		cset = task_css_set(current);
		अगर (likely(cgroup_tryget(cset->dfl_cgrp))) अणु
			skcd->val = (अचिन्हित दीर्घ)cset->dfl_cgrp;
			cgroup_bpf_get(cset->dfl_cgrp);
			अवरोध;
		पूर्ण
		cpu_relax();
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

व्योम cgroup_sk_clone(काष्ठा sock_cgroup_data *skcd)
अणु
	अगर (skcd->val) अणु
		अगर (skcd->no_refcnt)
			वापस;
		/*
		 * We might be cloning a socket which is left in an empty
		 * cgroup and the cgroup might have alपढ़ोy been सूची_हटाओ'd.
		 * Don't use cgroup_get_live().
		 */
		cgroup_get(sock_cgroup_ptr(skcd));
		cgroup_bpf_get(sock_cgroup_ptr(skcd));
	पूर्ण
पूर्ण

व्योम cgroup_sk_मुक्त(काष्ठा sock_cgroup_data *skcd)
अणु
	काष्ठा cgroup *cgrp = sock_cgroup_ptr(skcd);

	अगर (skcd->no_refcnt)
		वापस;
	cgroup_bpf_put(cgrp);
	cgroup_put(cgrp);
पूर्ण

#पूर्ण_अगर	/* CONFIG_SOCK_CGROUP_DATA */

#अगर_घोषित CONFIG_CGROUP_BPF
पूर्णांक cgroup_bpf_attach(काष्ठा cgroup *cgrp,
		      काष्ठा bpf_prog *prog, काष्ठा bpf_prog *replace_prog,
		      काष्ठा bpf_cgroup_link *link,
		      क्रमागत bpf_attach_type type,
		      u32 flags)
अणु
	पूर्णांक ret;

	mutex_lock(&cgroup_mutex);
	ret = __cgroup_bpf_attach(cgrp, prog, replace_prog, link, type, flags);
	mutex_unlock(&cgroup_mutex);
	वापस ret;
पूर्ण

पूर्णांक cgroup_bpf_detach(काष्ठा cgroup *cgrp, काष्ठा bpf_prog *prog,
		      क्रमागत bpf_attach_type type)
अणु
	पूर्णांक ret;

	mutex_lock(&cgroup_mutex);
	ret = __cgroup_bpf_detach(cgrp, prog, शून्य, type);
	mutex_unlock(&cgroup_mutex);
	वापस ret;
पूर्ण

पूर्णांक cgroup_bpf_query(काष्ठा cgroup *cgrp, स्थिर जोड़ bpf_attr *attr,
		     जोड़ bpf_attr __user *uattr)
अणु
	पूर्णांक ret;

	mutex_lock(&cgroup_mutex);
	ret = __cgroup_bpf_query(cgrp, attr, uattr);
	mutex_unlock(&cgroup_mutex);
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_CGROUP_BPF */

#अगर_घोषित CONFIG_SYSFS
अटल sमाप_प्रकार show_delegatable_files(काष्ठा cftype *files, अक्षर *buf,
				      sमाप_प्रकार size, स्थिर अक्षर *prefix)
अणु
	काष्ठा cftype *cft;
	sमाप_प्रकार ret = 0;

	क्रम (cft = files; cft && cft->name[0] != '\0'; cft++) अणु
		अगर (!(cft->flags & CFTYPE_NS_DELEGATABLE))
			जारी;

		अगर (prefix)
			ret += snम_लिखो(buf + ret, size - ret, "%s.", prefix);

		ret += snम_लिखो(buf + ret, size - ret, "%s\n", cft->name);

		अगर (WARN_ON(ret >= size))
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल sमाप_प्रकार delegate_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा cgroup_subsys *ss;
	पूर्णांक ssid;
	sमाप_प्रकार ret = 0;

	ret = show_delegatable_files(cgroup_base_files, buf, PAGE_SIZE - ret,
				     शून्य);

	क्रम_each_subsys(ss, ssid)
		ret += show_delegatable_files(ss->dfl_cftypes, buf + ret,
					      PAGE_SIZE - ret,
					      cgroup_subsys_name[ssid]);

	वापस ret;
पूर्ण
अटल काष्ठा kobj_attribute cgroup_delegate_attr = __ATTR_RO(delegate);

अटल sमाप_प्रकार features_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			     अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE,
			"nsdelegate\n"
			"memory_localevents\n"
			"memory_recursiveprot\n");
पूर्ण
अटल काष्ठा kobj_attribute cgroup_features_attr = __ATTR_RO(features);

अटल काष्ठा attribute *cgroup_sysfs_attrs[] = अणु
	&cgroup_delegate_attr.attr,
	&cgroup_features_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group cgroup_sysfs_attr_group = अणु
	.attrs = cgroup_sysfs_attrs,
	.name = "cgroup",
पूर्ण;

अटल पूर्णांक __init cgroup_sysfs_init(व्योम)
अणु
	वापस sysfs_create_group(kernel_kobj, &cgroup_sysfs_attr_group);
पूर्ण
subsys_initcall(cgroup_sysfs_init);

#पूर्ण_अगर /* CONFIG_SYSFS */
