<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * User पूर्णांकerface क्रम Resource Allocation in Resource Director Technology(RDT)
 *
 * Copyright (C) 2016 Intel Corporation
 *
 * Author: Fenghua Yu <fenghua.yu@पूर्णांकel.com>
 *
 * More inक्रमmation about RDT be found in the Intel (R) x86 Architecture
 * Software Developer Manual.
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/cacheinfo.h>
#समावेश <linux/cpu.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/fs.h>
#समावेश <linux/fs_parser.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/kernfs.h>
#समावेश <linux/seq_buf.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/task.h>
#समावेश <linux/slab.h>
#समावेश <linux/task_work.h>
#समावेश <linux/user_namespace.h>

#समावेश <uapi/linux/magic.h>

#समावेश <यंत्र/resctrl.h>
#समावेश "internal.h"

DEFINE_STATIC_KEY_FALSE(rdt_enable_key);
DEFINE_STATIC_KEY_FALSE(rdt_mon_enable_key);
DEFINE_STATIC_KEY_FALSE(rdt_alloc_enable_key);
अटल काष्ठा kernfs_root *rdt_root;
काष्ठा rdtgroup rdtgroup_शेष;
LIST_HEAD(rdt_all_groups);

/* Kernel fs node क्रम "info" directory under root */
अटल काष्ठा kernfs_node *kn_info;

/* Kernel fs node क्रम "mon_groups" directory under root */
अटल काष्ठा kernfs_node *kn_mongrp;

/* Kernel fs node क्रम "mon_data" directory under root */
अटल काष्ठा kernfs_node *kn_mondata;

अटल काष्ठा seq_buf last_cmd_status;
अटल अक्षर last_cmd_status_buf[512];

काष्ठा dentry *debugfs_resctrl;

व्योम rdt_last_cmd_clear(व्योम)
अणु
	lockdep_निश्चित_held(&rdtgroup_mutex);
	seq_buf_clear(&last_cmd_status);
पूर्ण

व्योम rdt_last_cmd_माला_दो(स्थिर अक्षर *s)
अणु
	lockdep_निश्चित_held(&rdtgroup_mutex);
	seq_buf_माला_दो(&last_cmd_status, s);
पूर्ण

व्योम rdt_last_cmd_म_लिखो(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	बहु_शुरू(ap, fmt);
	lockdep_निश्चित_held(&rdtgroup_mutex);
	seq_buf_भ_लिखो(&last_cmd_status, fmt, ap);
	बहु_पूर्ण(ap);
पूर्ण

/*
 * Trivial allocator क्रम CLOSIDs. Since h/w only supports a small number,
 * we can keep a biपंचांगap of मुक्त CLOSIDs in a single पूर्णांकeger.
 *
 * Using a global CLOSID across all resources has some advantages and
 * some drawbacks:
 * + We can simply set "current->closid" to assign a task to a resource
 *   group.
 * + Context चयन code can aव्योम extra memory references deciding which
 *   CLOSID to load पूर्णांकo the PQR_ASSOC MSR
 * - We give up some options in configuring resource groups across multi-socket
 *   प्रणालीs.
 * - Our choices on how to configure each resource become progressively more
 *   limited as the number of resources grows.
 */
अटल पूर्णांक closid_मुक्त_map;
अटल पूर्णांक closid_मुक्त_map_len;

पूर्णांक closids_supported(व्योम)
अणु
	वापस closid_मुक्त_map_len;
पूर्ण

अटल व्योम closid_init(व्योम)
अणु
	काष्ठा rdt_resource *r;
	पूर्णांक rdt_min_closid = 32;

	/* Compute rdt_min_closid across all resources */
	क्रम_each_alloc_enabled_rdt_resource(r)
		rdt_min_closid = min(rdt_min_closid, r->num_closid);

	closid_मुक्त_map = BIT_MASK(rdt_min_closid) - 1;

	/* CLOSID 0 is always reserved क्रम the शेष group */
	closid_मुक्त_map &= ~1;
	closid_मुक्त_map_len = rdt_min_closid;
पूर्ण

अटल पूर्णांक closid_alloc(व्योम)
अणु
	u32 closid = ffs(closid_मुक्त_map);

	अगर (closid == 0)
		वापस -ENOSPC;
	closid--;
	closid_मुक्त_map &= ~(1 << closid);

	वापस closid;
पूर्ण

व्योम closid_मुक्त(पूर्णांक closid)
अणु
	closid_मुक्त_map |= 1 << closid;
पूर्ण

/**
 * closid_allocated - test अगर provided closid is in use
 * @closid: closid to be tested
 *
 * Return: true अगर @closid is currently associated with a resource group,
 * false अगर @closid is मुक्त
 */
अटल bool closid_allocated(अचिन्हित पूर्णांक closid)
अणु
	वापस (closid_मुक्त_map & (1 << closid)) == 0;
पूर्ण

/**
 * rdtgroup_mode_by_closid - Return mode of resource group with closid
 * @closid: closid अगर the resource group
 *
 * Each resource group is associated with a @closid. Here the mode
 * of a resource group can be queried by searching क्रम it using its closid.
 *
 * Return: mode as &क्रमागत rdtgrp_mode of resource group with closid @closid
 */
क्रमागत rdtgrp_mode rdtgroup_mode_by_closid(पूर्णांक closid)
अणु
	काष्ठा rdtgroup *rdtgrp;

	list_क्रम_each_entry(rdtgrp, &rdt_all_groups, rdtgroup_list) अणु
		अगर (rdtgrp->closid == closid)
			वापस rdtgrp->mode;
	पूर्ण

	वापस RDT_NUM_MODES;
पूर्ण

अटल स्थिर अक्षर * स्थिर rdt_mode_str[] = अणु
	[RDT_MODE_SHAREABLE]		= "shareable",
	[RDT_MODE_EXCLUSIVE]		= "exclusive",
	[RDT_MODE_PSEUDO_LOCKSETUP]	= "pseudo-locksetup",
	[RDT_MODE_PSEUDO_LOCKED]	= "pseudo-locked",
पूर्ण;

/**
 * rdtgroup_mode_str - Return the string representation of mode
 * @mode: the resource group mode as &क्रमागत rdtgroup_mode
 *
 * Return: string representation of valid mode, "unknown" otherwise
 */
अटल स्थिर अक्षर *rdtgroup_mode_str(क्रमागत rdtgrp_mode mode)
अणु
	अगर (mode < RDT_MODE_SHAREABLE || mode >= RDT_NUM_MODES)
		वापस "unknown";

	वापस rdt_mode_str[mode];
पूर्ण

/* set uid and gid of rdtgroup dirs and files to that of the creator */
अटल पूर्णांक rdtgroup_kn_set_ugid(काष्ठा kernfs_node *kn)
अणु
	काष्ठा iattr iattr = अणु .ia_valid = ATTR_UID | ATTR_GID,
				.ia_uid = current_fsuid(),
				.ia_gid = current_fsgid(), पूर्ण;

	अगर (uid_eq(iattr.ia_uid, GLOBAL_ROOT_UID) &&
	    gid_eq(iattr.ia_gid, GLOBAL_ROOT_GID))
		वापस 0;

	वापस kernfs_setattr(kn, &iattr);
पूर्ण

अटल पूर्णांक rdtgroup_add_file(काष्ठा kernfs_node *parent_kn, काष्ठा rftype *rft)
अणु
	काष्ठा kernfs_node *kn;
	पूर्णांक ret;

	kn = __kernfs_create_file(parent_kn, rft->name, rft->mode,
				  GLOBAL_ROOT_UID, GLOBAL_ROOT_GID,
				  0, rft->kf_ops, rft, शून्य, शून्य);
	अगर (IS_ERR(kn))
		वापस PTR_ERR(kn);

	ret = rdtgroup_kn_set_ugid(kn);
	अगर (ret) अणु
		kernfs_हटाओ(kn);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rdtgroup_seqfile_show(काष्ठा seq_file *m, व्योम *arg)
अणु
	काष्ठा kernfs_खोलो_file *of = m->निजी;
	काष्ठा rftype *rft = of->kn->priv;

	अगर (rft->seq_show)
		वापस rft->seq_show(of, m, arg);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार rdtgroup_file_ग_लिखो(काष्ठा kernfs_खोलो_file *of, अक्षर *buf,
				   माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा rftype *rft = of->kn->priv;

	अगर (rft->ग_लिखो)
		वापस rft->ग_लिखो(of, buf, nbytes, off);

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा kernfs_ops rdtgroup_kf_single_ops = अणु
	.atomic_ग_लिखो_len	= PAGE_SIZE,
	.ग_लिखो			= rdtgroup_file_ग_लिखो,
	.seq_show		= rdtgroup_seqfile_show,
पूर्ण;

अटल स्थिर काष्ठा kernfs_ops kf_mondata_ops = अणु
	.atomic_ग_लिखो_len	= PAGE_SIZE,
	.seq_show		= rdtgroup_mondata_show,
पूर्ण;

अटल bool is_cpu_list(काष्ठा kernfs_खोलो_file *of)
अणु
	काष्ठा rftype *rft = of->kn->priv;

	वापस rft->flags & RFTYPE_FLAGS_CPUS_LIST;
पूर्ण

अटल पूर्णांक rdtgroup_cpus_show(काष्ठा kernfs_खोलो_file *of,
			      काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा rdtgroup *rdtgrp;
	काष्ठा cpumask *mask;
	पूर्णांक ret = 0;

	rdtgrp = rdtgroup_kn_lock_live(of->kn);

	अगर (rdtgrp) अणु
		अगर (rdtgrp->mode == RDT_MODE_PSEUDO_LOCKED) अणु
			अगर (!rdtgrp->plr->d) अणु
				rdt_last_cmd_clear();
				rdt_last_cmd_माला_दो("Cache domain offline\n");
				ret = -ENODEV;
			पूर्ण अन्यथा अणु
				mask = &rdtgrp->plr->d->cpu_mask;
				seq_म_लिखो(s, is_cpu_list(of) ?
					   "%*pbl\n" : "%*pb\n",
					   cpumask_pr_args(mask));
			पूर्ण
		पूर्ण अन्यथा अणु
			seq_म_लिखो(s, is_cpu_list(of) ? "%*pbl\n" : "%*pb\n",
				   cpumask_pr_args(&rdtgrp->cpu_mask));
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = -ENOENT;
	पूर्ण
	rdtgroup_kn_unlock(of->kn);

	वापस ret;
पूर्ण

/*
 * This is safe against resctrl_sched_in() called from __चयन_to()
 * because __चयन_to() is executed with पूर्णांकerrupts disabled. A local call
 * from update_closid_rmid() is रक्षित against __चयन_to() because
 * preemption is disabled.
 */
अटल व्योम update_cpu_closid_rmid(व्योम *info)
अणु
	काष्ठा rdtgroup *r = info;

	अगर (r) अणु
		this_cpu_ग_लिखो(pqr_state.शेष_closid, r->closid);
		this_cpu_ग_लिखो(pqr_state.शेष_rmid, r->mon.rmid);
	पूर्ण

	/*
	 * We cannot unconditionally ग_लिखो the MSR because the current
	 * executing task might have its own closid selected. Just reuse
	 * the context चयन code.
	 */
	resctrl_sched_in();
पूर्ण

/*
 * Update the PGR_ASSOC MSR on all cpus in @cpu_mask,
 *
 * Per task closids/rmids must have been set up beक्रमe calling this function.
 */
अटल व्योम
update_closid_rmid(स्थिर काष्ठा cpumask *cpu_mask, काष्ठा rdtgroup *r)
अणु
	पूर्णांक cpu = get_cpu();

	अगर (cpumask_test_cpu(cpu, cpu_mask))
		update_cpu_closid_rmid(r);
	smp_call_function_many(cpu_mask, update_cpu_closid_rmid, r, 1);
	put_cpu();
पूर्ण

अटल पूर्णांक cpus_mon_ग_लिखो(काष्ठा rdtgroup *rdtgrp, cpumask_var_t newmask,
			  cpumask_var_t पंचांगpmask)
अणु
	काष्ठा rdtgroup *prgrp = rdtgrp->mon.parent, *crgrp;
	काष्ठा list_head *head;

	/* Check whether cpus beदीर्घ to parent ctrl group */
	cpumask_andnot(पंचांगpmask, newmask, &prgrp->cpu_mask);
	अगर (cpumask_weight(पंचांगpmask)) अणु
		rdt_last_cmd_माला_दो("Can only add CPUs to mongroup that belong to parent\n");
		वापस -EINVAL;
	पूर्ण

	/* Check whether cpus are dropped from this group */
	cpumask_andnot(पंचांगpmask, &rdtgrp->cpu_mask, newmask);
	अगर (cpumask_weight(पंचांगpmask)) अणु
		/* Give any dropped cpus to parent rdtgroup */
		cpumask_or(&prgrp->cpu_mask, &prgrp->cpu_mask, पंचांगpmask);
		update_closid_rmid(पंचांगpmask, prgrp);
	पूर्ण

	/*
	 * If we added cpus, हटाओ them from previous group that owned them
	 * and update per-cpu rmid
	 */
	cpumask_andnot(पंचांगpmask, newmask, &rdtgrp->cpu_mask);
	अगर (cpumask_weight(पंचांगpmask)) अणु
		head = &prgrp->mon.crdtgrp_list;
		list_क्रम_each_entry(crgrp, head, mon.crdtgrp_list) अणु
			अगर (crgrp == rdtgrp)
				जारी;
			cpumask_andnot(&crgrp->cpu_mask, &crgrp->cpu_mask,
				       पंचांगpmask);
		पूर्ण
		update_closid_rmid(पंचांगpmask, rdtgrp);
	पूर्ण

	/* Done pushing/pulling - update this group with new mask */
	cpumask_copy(&rdtgrp->cpu_mask, newmask);

	वापस 0;
पूर्ण

अटल व्योम cpumask_rdtgrp_clear(काष्ठा rdtgroup *r, काष्ठा cpumask *m)
अणु
	काष्ठा rdtgroup *crgrp;

	cpumask_andnot(&r->cpu_mask, &r->cpu_mask, m);
	/* update the child mon group masks as well*/
	list_क्रम_each_entry(crgrp, &r->mon.crdtgrp_list, mon.crdtgrp_list)
		cpumask_and(&crgrp->cpu_mask, &r->cpu_mask, &crgrp->cpu_mask);
पूर्ण

अटल पूर्णांक cpus_ctrl_ग_लिखो(काष्ठा rdtgroup *rdtgrp, cpumask_var_t newmask,
			   cpumask_var_t पंचांगpmask, cpumask_var_t पंचांगpmask1)
अणु
	काष्ठा rdtgroup *r, *crgrp;
	काष्ठा list_head *head;

	/* Check whether cpus are dropped from this group */
	cpumask_andnot(पंचांगpmask, &rdtgrp->cpu_mask, newmask);
	अगर (cpumask_weight(पंचांगpmask)) अणु
		/* Can't drop from शेष group */
		अगर (rdtgrp == &rdtgroup_शेष) अणु
			rdt_last_cmd_माला_दो("Can't drop CPUs from default group\n");
			वापस -EINVAL;
		पूर्ण

		/* Give any dropped cpus to rdtgroup_शेष */
		cpumask_or(&rdtgroup_शेष.cpu_mask,
			   &rdtgroup_शेष.cpu_mask, पंचांगpmask);
		update_closid_rmid(पंचांगpmask, &rdtgroup_शेष);
	पूर्ण

	/*
	 * If we added cpus, हटाओ them from previous group and
	 * the prev group's child groups that owned them
	 * and update per-cpu closid/rmid.
	 */
	cpumask_andnot(पंचांगpmask, newmask, &rdtgrp->cpu_mask);
	अगर (cpumask_weight(पंचांगpmask)) अणु
		list_क्रम_each_entry(r, &rdt_all_groups, rdtgroup_list) अणु
			अगर (r == rdtgrp)
				जारी;
			cpumask_and(पंचांगpmask1, &r->cpu_mask, पंचांगpmask);
			अगर (cpumask_weight(पंचांगpmask1))
				cpumask_rdtgrp_clear(r, पंचांगpmask1);
		पूर्ण
		update_closid_rmid(पंचांगpmask, rdtgrp);
	पूर्ण

	/* Done pushing/pulling - update this group with new mask */
	cpumask_copy(&rdtgrp->cpu_mask, newmask);

	/*
	 * Clear child mon group masks since there is a new parent mask
	 * now and update the rmid क्रम the cpus the child lost.
	 */
	head = &rdtgrp->mon.crdtgrp_list;
	list_क्रम_each_entry(crgrp, head, mon.crdtgrp_list) अणु
		cpumask_and(पंचांगpmask, &rdtgrp->cpu_mask, &crgrp->cpu_mask);
		update_closid_rmid(पंचांगpmask, rdtgrp);
		cpumask_clear(&crgrp->cpu_mask);
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार rdtgroup_cpus_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
				   अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	cpumask_var_t पंचांगpmask, newmask, पंचांगpmask1;
	काष्ठा rdtgroup *rdtgrp;
	पूर्णांक ret;

	अगर (!buf)
		वापस -EINVAL;

	अगर (!zalloc_cpumask_var(&पंचांगpmask, GFP_KERNEL))
		वापस -ENOMEM;
	अगर (!zalloc_cpumask_var(&newmask, GFP_KERNEL)) अणु
		मुक्त_cpumask_var(पंचांगpmask);
		वापस -ENOMEM;
	पूर्ण
	अगर (!zalloc_cpumask_var(&पंचांगpmask1, GFP_KERNEL)) अणु
		मुक्त_cpumask_var(पंचांगpmask);
		मुक्त_cpumask_var(newmask);
		वापस -ENOMEM;
	पूर्ण

	rdtgrp = rdtgroup_kn_lock_live(of->kn);
	अगर (!rdtgrp) अणु
		ret = -ENOENT;
		जाओ unlock;
	पूर्ण

	अगर (rdtgrp->mode == RDT_MODE_PSEUDO_LOCKED ||
	    rdtgrp->mode == RDT_MODE_PSEUDO_LOCKSETUP) अणु
		ret = -EINVAL;
		rdt_last_cmd_माला_दो("Pseudo-locking in progress\n");
		जाओ unlock;
	पूर्ण

	अगर (is_cpu_list(of))
		ret = cpulist_parse(buf, newmask);
	अन्यथा
		ret = cpumask_parse(buf, newmask);

	अगर (ret) अणु
		rdt_last_cmd_माला_दो("Bad CPU list/mask\n");
		जाओ unlock;
	पूर्ण

	/* check that user didn't specअगरy any offline cpus */
	cpumask_andnot(पंचांगpmask, newmask, cpu_online_mask);
	अगर (cpumask_weight(पंचांगpmask)) अणु
		ret = -EINVAL;
		rdt_last_cmd_माला_दो("Can only assign online CPUs\n");
		जाओ unlock;
	पूर्ण

	अगर (rdtgrp->type == RDTCTRL_GROUP)
		ret = cpus_ctrl_ग_लिखो(rdtgrp, newmask, पंचांगpmask, पंचांगpmask1);
	अन्यथा अगर (rdtgrp->type == RDTMON_GROUP)
		ret = cpus_mon_ग_लिखो(rdtgrp, newmask, पंचांगpmask);
	अन्यथा
		ret = -EINVAL;

unlock:
	rdtgroup_kn_unlock(of->kn);
	मुक्त_cpumask_var(पंचांगpmask);
	मुक्त_cpumask_var(newmask);
	मुक्त_cpumask_var(पंचांगpmask1);

	वापस ret ?: nbytes;
पूर्ण

/**
 * rdtgroup_हटाओ - the helper to हटाओ resource group safely
 * @rdtgrp: resource group to हटाओ
 *
 * On resource group creation via a सूची_गढ़ो, an extra kernfs_node reference is
 * taken to ensure that the rdtgroup काष्ठाure reमुख्यs accessible क्रम the
 * rdtgroup_kn_unlock() calls where it is हटाओd.
 *
 * Drop the extra reference here, then मुक्त the rdtgroup काष्ठाure.
 *
 * Return: व्योम
 */
अटल व्योम rdtgroup_हटाओ(काष्ठा rdtgroup *rdtgrp)
अणु
	kernfs_put(rdtgrp->kn);
	kमुक्त(rdtgrp);
पूर्ण

अटल व्योम _update_task_closid_rmid(व्योम *task)
अणु
	/*
	 * If the task is still current on this CPU, update PQR_ASSOC MSR.
	 * Otherwise, the MSR is updated when the task is scheduled in.
	 */
	अगर (task == current)
		resctrl_sched_in();
पूर्ण

अटल व्योम update_task_closid_rmid(काष्ठा task_काष्ठा *t)
अणु
	अगर (IS_ENABLED(CONFIG_SMP) && task_curr(t))
		smp_call_function_single(task_cpu(t), _update_task_closid_rmid, t, 1);
	अन्यथा
		_update_task_closid_rmid(t);
पूर्ण

अटल पूर्णांक __rdtgroup_move_task(काष्ठा task_काष्ठा *tsk,
				काष्ठा rdtgroup *rdtgrp)
अणु
	/* If the task is alपढ़ोy in rdtgrp, no need to move the task. */
	अगर ((rdtgrp->type == RDTCTRL_GROUP && tsk->closid == rdtgrp->closid &&
	     tsk->rmid == rdtgrp->mon.rmid) ||
	    (rdtgrp->type == RDTMON_GROUP && tsk->rmid == rdtgrp->mon.rmid &&
	     tsk->closid == rdtgrp->mon.parent->closid))
		वापस 0;

	/*
	 * Set the task's closid/rmid beक्रमe the PQR_ASSOC MSR can be
	 * updated by them.
	 *
	 * For ctrl_mon groups, move both closid and rmid.
	 * For monitor groups, can move the tasks only from
	 * their parent CTRL group.
	 */

	अगर (rdtgrp->type == RDTCTRL_GROUP) अणु
		WRITE_ONCE(tsk->closid, rdtgrp->closid);
		WRITE_ONCE(tsk->rmid, rdtgrp->mon.rmid);
	पूर्ण अन्यथा अगर (rdtgrp->type == RDTMON_GROUP) अणु
		अगर (rdtgrp->mon.parent->closid == tsk->closid) अणु
			WRITE_ONCE(tsk->rmid, rdtgrp->mon.rmid);
		पूर्ण अन्यथा अणु
			rdt_last_cmd_माला_दो("Can't move task to different control group\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/*
	 * Ensure the task's closid and rmid are written beक्रमe determining अगर
	 * the task is current that will decide अगर it will be पूर्णांकerrupted.
	 */
	barrier();

	/*
	 * By now, the task's closid and rmid are set. If the task is current
	 * on a CPU, the PQR_ASSOC MSR needs to be updated to make the resource
	 * group go पूर्णांकo effect. If the task is not current, the MSR will be
	 * updated when the task is scheduled in.
	 */
	update_task_closid_rmid(tsk);

	वापस 0;
पूर्ण

अटल bool is_closid_match(काष्ठा task_काष्ठा *t, काष्ठा rdtgroup *r)
अणु
	वापस (rdt_alloc_capable &&
	       (r->type == RDTCTRL_GROUP) && (t->closid == r->closid));
पूर्ण

अटल bool is_rmid_match(काष्ठा task_काष्ठा *t, काष्ठा rdtgroup *r)
अणु
	वापस (rdt_mon_capable &&
	       (r->type == RDTMON_GROUP) && (t->rmid == r->mon.rmid));
पूर्ण

/**
 * rdtgroup_tasks_asचिन्हित - Test अगर tasks have been asचिन्हित to resource group
 * @r: Resource group
 *
 * Return: 1 अगर tasks have been asचिन्हित to @r, 0 otherwise
 */
पूर्णांक rdtgroup_tasks_asचिन्हित(काष्ठा rdtgroup *r)
अणु
	काष्ठा task_काष्ठा *p, *t;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&rdtgroup_mutex);

	rcu_पढ़ो_lock();
	क्रम_each_process_thपढ़ो(p, t) अणु
		अगर (is_closid_match(t, r) || is_rmid_match(t, r)) अणु
			ret = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल पूर्णांक rdtgroup_task_ग_लिखो_permission(काष्ठा task_काष्ठा *task,
					  काष्ठा kernfs_खोलो_file *of)
अणु
	स्थिर काष्ठा cred *tcred = get_task_cred(task);
	स्थिर काष्ठा cred *cred = current_cred();
	पूर्णांक ret = 0;

	/*
	 * Even अगर we're attaching all tasks in the thपढ़ो group, we only
	 * need to check permissions on one of them.
	 */
	अगर (!uid_eq(cred->euid, GLOBAL_ROOT_UID) &&
	    !uid_eq(cred->euid, tcred->uid) &&
	    !uid_eq(cred->euid, tcred->suid)) अणु
		rdt_last_cmd_म_लिखो("No permission to move task %d\n", task->pid);
		ret = -EPERM;
	पूर्ण

	put_cred(tcred);
	वापस ret;
पूर्ण

अटल पूर्णांक rdtgroup_move_task(pid_t pid, काष्ठा rdtgroup *rdtgrp,
			      काष्ठा kernfs_खोलो_file *of)
अणु
	काष्ठा task_काष्ठा *tsk;
	पूर्णांक ret;

	rcu_पढ़ो_lock();
	अगर (pid) अणु
		tsk = find_task_by_vpid(pid);
		अगर (!tsk) अणु
			rcu_पढ़ो_unlock();
			rdt_last_cmd_म_लिखो("No task %d\n", pid);
			वापस -ESRCH;
		पूर्ण
	पूर्ण अन्यथा अणु
		tsk = current;
	पूर्ण

	get_task_काष्ठा(tsk);
	rcu_पढ़ो_unlock();

	ret = rdtgroup_task_ग_लिखो_permission(tsk, of);
	अगर (!ret)
		ret = __rdtgroup_move_task(tsk, rdtgrp);

	put_task_काष्ठा(tsk);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार rdtgroup_tasks_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
				    अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा rdtgroup *rdtgrp;
	पूर्णांक ret = 0;
	pid_t pid;

	अगर (kstrtoपूर्णांक(म_मालाip(buf), 0, &pid) || pid < 0)
		वापस -EINVAL;
	rdtgrp = rdtgroup_kn_lock_live(of->kn);
	अगर (!rdtgrp) अणु
		rdtgroup_kn_unlock(of->kn);
		वापस -ENOENT;
	पूर्ण
	rdt_last_cmd_clear();

	अगर (rdtgrp->mode == RDT_MODE_PSEUDO_LOCKED ||
	    rdtgrp->mode == RDT_MODE_PSEUDO_LOCKSETUP) अणु
		ret = -EINVAL;
		rdt_last_cmd_माला_दो("Pseudo-locking in progress\n");
		जाओ unlock;
	पूर्ण

	ret = rdtgroup_move_task(pid, rdtgrp, of);

unlock:
	rdtgroup_kn_unlock(of->kn);

	वापस ret ?: nbytes;
पूर्ण

अटल व्योम show_rdt_tasks(काष्ठा rdtgroup *r, काष्ठा seq_file *s)
अणु
	काष्ठा task_काष्ठा *p, *t;

	rcu_पढ़ो_lock();
	क्रम_each_process_thपढ़ो(p, t) अणु
		अगर (is_closid_match(t, r) || is_rmid_match(t, r))
			seq_म_लिखो(s, "%d\n", t->pid);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक rdtgroup_tasks_show(काष्ठा kernfs_खोलो_file *of,
			       काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा rdtgroup *rdtgrp;
	पूर्णांक ret = 0;

	rdtgrp = rdtgroup_kn_lock_live(of->kn);
	अगर (rdtgrp)
		show_rdt_tasks(rdtgrp, s);
	अन्यथा
		ret = -ENOENT;
	rdtgroup_kn_unlock(of->kn);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PROC_CPU_RESCTRL

/*
 * A task can only be part of one resctrl control group and of one monitor
 * group which is associated to that control group.
 *
 * 1)   res:
 *      mon:
 *
 *    resctrl is not available.
 *
 * 2)   res:/
 *      mon:
 *
 *    Task is part of the root resctrl control group, and it is not associated
 *    to any monitor group.
 *
 * 3)  res:/
 *     mon:mon0
 *
 *    Task is part of the root resctrl control group and monitor group mon0.
 *
 * 4)  res:group0
 *     mon:
 *
 *    Task is part of resctrl control group group0, and it is not associated
 *    to any monitor group.
 *
 * 5) res:group0
 *    mon:mon1
 *
 *    Task is part of resctrl control group group0 and monitor group mon1.
 */
पूर्णांक proc_resctrl_show(काष्ठा seq_file *s, काष्ठा pid_namespace *ns,
		      काष्ठा pid *pid, काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा rdtgroup *rdtg;
	पूर्णांक ret = 0;

	mutex_lock(&rdtgroup_mutex);

	/* Return empty अगर resctrl has not been mounted. */
	अगर (!अटल_branch_unlikely(&rdt_enable_key)) अणु
		seq_माला_दो(s, "res:\nmon:\n");
		जाओ unlock;
	पूर्ण

	list_क्रम_each_entry(rdtg, &rdt_all_groups, rdtgroup_list) अणु
		काष्ठा rdtgroup *crg;

		/*
		 * Task inक्रमmation is only relevant क्रम shareable
		 * and exclusive groups.
		 */
		अगर (rdtg->mode != RDT_MODE_SHAREABLE &&
		    rdtg->mode != RDT_MODE_EXCLUSIVE)
			जारी;

		अगर (rdtg->closid != tsk->closid)
			जारी;

		seq_म_लिखो(s, "res:%s%s\n", (rdtg == &rdtgroup_शेष) ? "/" : "",
			   rdtg->kn->name);
		seq_माला_दो(s, "mon:");
		list_क्रम_each_entry(crg, &rdtg->mon.crdtgrp_list,
				    mon.crdtgrp_list) अणु
			अगर (tsk->rmid != crg->mon.rmid)
				जारी;
			seq_म_लिखो(s, "%s", crg->kn->name);
			अवरोध;
		पूर्ण
		seq_अ_दो(s, '\n');
		जाओ unlock;
	पूर्ण
	/*
	 * The above search should succeed. Otherwise वापस
	 * with an error.
	 */
	ret = -ENOENT;
unlock:
	mutex_unlock(&rdtgroup_mutex);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक rdt_last_cmd_status_show(काष्ठा kernfs_खोलो_file *of,
				    काष्ठा seq_file *seq, व्योम *v)
अणु
	पूर्णांक len;

	mutex_lock(&rdtgroup_mutex);
	len = seq_buf_used(&last_cmd_status);
	अगर (len)
		seq_म_लिखो(seq, "%.*s", len, last_cmd_status_buf);
	अन्यथा
		seq_माला_दो(seq, "ok\n");
	mutex_unlock(&rdtgroup_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक rdt_num_closids_show(काष्ठा kernfs_खोलो_file *of,
				काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा rdt_resource *r = of->kn->parent->priv;

	seq_म_लिखो(seq, "%d\n", r->num_closid);
	वापस 0;
पूर्ण

अटल पूर्णांक rdt_शेष_ctrl_show(काष्ठा kernfs_खोलो_file *of,
			     काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा rdt_resource *r = of->kn->parent->priv;

	seq_म_लिखो(seq, "%x\n", r->शेष_ctrl);
	वापस 0;
पूर्ण

अटल पूर्णांक rdt_min_cbm_bits_show(काष्ठा kernfs_खोलो_file *of,
			     काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा rdt_resource *r = of->kn->parent->priv;

	seq_म_लिखो(seq, "%u\n", r->cache.min_cbm_bits);
	वापस 0;
पूर्ण

अटल पूर्णांक rdt_shareable_bits_show(काष्ठा kernfs_खोलो_file *of,
				   काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा rdt_resource *r = of->kn->parent->priv;

	seq_म_लिखो(seq, "%x\n", r->cache.shareable_bits);
	वापस 0;
पूर्ण

/**
 * rdt_bit_usage_show - Display current usage of resources
 *
 * A करोमुख्य is a shared resource that can now be allocated dअगरferently. Here
 * we display the current regions of the करोमुख्य as an annotated biपंचांगask.
 * For each करोमुख्य of this resource its allocation biपंचांगask
 * is annotated as below to indicate the current usage of the corresponding bit:
 *   0 - currently unused
 *   X - currently available क्रम sharing and used by software and hardware
 *   H - currently used by hardware only but available क्रम software use
 *   S - currently used and shareable by software only
 *   E - currently used exclusively by one resource group
 *   P - currently pseuकरो-locked by one resource group
 */
अटल पूर्णांक rdt_bit_usage_show(काष्ठा kernfs_खोलो_file *of,
			      काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा rdt_resource *r = of->kn->parent->priv;
	/*
	 * Use अचिन्हित दीर्घ even though only 32 bits are used to ensure
	 * test_bit() is used safely.
	 */
	अचिन्हित दीर्घ sw_shareable = 0, hw_shareable = 0;
	अचिन्हित दीर्घ exclusive = 0, pseuकरो_locked = 0;
	काष्ठा rdt_करोमुख्य *करोm;
	पूर्णांक i, hwb, swb, excl, psl;
	क्रमागत rdtgrp_mode mode;
	bool sep = false;
	u32 *ctrl;

	mutex_lock(&rdtgroup_mutex);
	hw_shareable = r->cache.shareable_bits;
	list_क्रम_each_entry(करोm, &r->करोमुख्यs, list) अणु
		अगर (sep)
			seq_अ_दो(seq, ';');
		ctrl = करोm->ctrl_val;
		sw_shareable = 0;
		exclusive = 0;
		seq_म_लिखो(seq, "%d=", करोm->id);
		क्रम (i = 0; i < closids_supported(); i++, ctrl++) अणु
			अगर (!closid_allocated(i))
				जारी;
			mode = rdtgroup_mode_by_closid(i);
			चयन (mode) अणु
			हाल RDT_MODE_SHAREABLE:
				sw_shareable |= *ctrl;
				अवरोध;
			हाल RDT_MODE_EXCLUSIVE:
				exclusive |= *ctrl;
				अवरोध;
			हाल RDT_MODE_PSEUDO_LOCKSETUP:
			/*
			 * RDT_MODE_PSEUDO_LOCKSETUP is possible
			 * here but not included since the CBM
			 * associated with this CLOSID in this mode
			 * is not initialized and no task or cpu can be
			 * asचिन्हित this CLOSID.
			 */
				अवरोध;
			हाल RDT_MODE_PSEUDO_LOCKED:
			हाल RDT_NUM_MODES:
				WARN(1,
				     "invalid mode for closid %d\n", i);
				अवरोध;
			पूर्ण
		पूर्ण
		क्रम (i = r->cache.cbm_len - 1; i >= 0; i--) अणु
			pseuकरो_locked = करोm->plr ? करोm->plr->cbm : 0;
			hwb = test_bit(i, &hw_shareable);
			swb = test_bit(i, &sw_shareable);
			excl = test_bit(i, &exclusive);
			psl = test_bit(i, &pseuकरो_locked);
			अगर (hwb && swb)
				seq_अ_दो(seq, 'X');
			अन्यथा अगर (hwb && !swb)
				seq_अ_दो(seq, 'H');
			अन्यथा अगर (!hwb && swb)
				seq_अ_दो(seq, 'S');
			अन्यथा अगर (excl)
				seq_अ_दो(seq, 'E');
			अन्यथा अगर (psl)
				seq_अ_दो(seq, 'P');
			अन्यथा /* Unused bits reमुख्य */
				seq_अ_दो(seq, '0');
		पूर्ण
		sep = true;
	पूर्ण
	seq_अ_दो(seq, '\n');
	mutex_unlock(&rdtgroup_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक rdt_min_bw_show(काष्ठा kernfs_खोलो_file *of,
			     काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा rdt_resource *r = of->kn->parent->priv;

	seq_म_लिखो(seq, "%u\n", r->membw.min_bw);
	वापस 0;
पूर्ण

अटल पूर्णांक rdt_num_rmids_show(काष्ठा kernfs_खोलो_file *of,
			      काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा rdt_resource *r = of->kn->parent->priv;

	seq_म_लिखो(seq, "%d\n", r->num_rmid);

	वापस 0;
पूर्ण

अटल पूर्णांक rdt_mon_features_show(काष्ठा kernfs_खोलो_file *of,
				 काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा rdt_resource *r = of->kn->parent->priv;
	काष्ठा mon_evt *mevt;

	list_क्रम_each_entry(mevt, &r->evt_list, list)
		seq_म_लिखो(seq, "%s\n", mevt->name);

	वापस 0;
पूर्ण

अटल पूर्णांक rdt_bw_gran_show(काष्ठा kernfs_खोलो_file *of,
			     काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा rdt_resource *r = of->kn->parent->priv;

	seq_म_लिखो(seq, "%u\n", r->membw.bw_gran);
	वापस 0;
पूर्ण

अटल पूर्णांक rdt_delay_linear_show(काष्ठा kernfs_खोलो_file *of,
			     काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा rdt_resource *r = of->kn->parent->priv;

	seq_म_लिखो(seq, "%u\n", r->membw.delay_linear);
	वापस 0;
पूर्ण

अटल पूर्णांक max_threshold_occ_show(काष्ठा kernfs_खोलो_file *of,
				  काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा rdt_resource *r = of->kn->parent->priv;

	seq_म_लिखो(seq, "%u\n", resctrl_cqm_threshold * r->mon_scale);

	वापस 0;
पूर्ण

अटल पूर्णांक rdt_thपढ़ो_throttle_mode_show(काष्ठा kernfs_खोलो_file *of,
					 काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा rdt_resource *r = of->kn->parent->priv;

	अगर (r->membw.throttle_mode == THREAD_THROTTLE_PER_THREAD)
		seq_माला_दो(seq, "per-thread\n");
	अन्यथा
		seq_माला_दो(seq, "max\n");

	वापस 0;
पूर्ण

अटल sमाप_प्रकार max_threshold_occ_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
				       अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा rdt_resource *r = of->kn->parent->priv;
	अचिन्हित पूर्णांक bytes;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक(buf, 0, &bytes);
	अगर (ret)
		वापस ret;

	अगर (bytes > (boot_cpu_data.x86_cache_size * 1024))
		वापस -EINVAL;

	resctrl_cqm_threshold = bytes / r->mon_scale;

	वापस nbytes;
पूर्ण

/*
 * rdtgroup_mode_show - Display mode of this resource group
 */
अटल पूर्णांक rdtgroup_mode_show(काष्ठा kernfs_खोलो_file *of,
			      काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा rdtgroup *rdtgrp;

	rdtgrp = rdtgroup_kn_lock_live(of->kn);
	अगर (!rdtgrp) अणु
		rdtgroup_kn_unlock(of->kn);
		वापस -ENOENT;
	पूर्ण

	seq_म_लिखो(s, "%s\n", rdtgroup_mode_str(rdtgrp->mode));

	rdtgroup_kn_unlock(of->kn);
	वापस 0;
पूर्ण

/**
 * rdt_cdp_peer_get - Retrieve CDP peer अगर it exists
 * @r: RDT resource to which RDT करोमुख्य @d beदीर्घs
 * @d: Cache instance क्रम which a CDP peer is requested
 * @r_cdp: RDT resource that shares hardware with @r (RDT resource peer)
 *         Used to वापस the result.
 * @d_cdp: RDT करोमुख्य that shares hardware with @d (RDT करोमुख्य peer)
 *         Used to वापस the result.
 *
 * RDT resources are managed independently and by extension the RDT करोमुख्यs
 * (RDT resource instances) are managed independently also. The Code and
 * Data Prioritization (CDP) RDT resources, जबतक managed independently,
 * could refer to the same underlying hardware. For example,
 * RDT_RESOURCE_L2CODE and RDT_RESOURCE_L2DATA both refer to the L2 cache.
 *
 * When provided with an RDT resource @r and an instance of that RDT
 * resource @d rdt_cdp_peer_get() will वापस अगर there is a peer RDT
 * resource and the exact instance that shares the same hardware.
 *
 * Return: 0 अगर a CDP peer was found, <0 on error or अगर no CDP peer exists.
 *         If a CDP peer was found, @r_cdp will poपूर्णांक to the peer RDT resource
 *         and @d_cdp will poपूर्णांक to the peer RDT करोमुख्य.
 */
अटल पूर्णांक rdt_cdp_peer_get(काष्ठा rdt_resource *r, काष्ठा rdt_करोमुख्य *d,
			    काष्ठा rdt_resource **r_cdp,
			    काष्ठा rdt_करोमुख्य **d_cdp)
अणु
	काष्ठा rdt_resource *_r_cdp = शून्य;
	काष्ठा rdt_करोमुख्य *_d_cdp = शून्य;
	पूर्णांक ret = 0;

	चयन (r->rid) अणु
	हाल RDT_RESOURCE_L3DATA:
		_r_cdp = &rdt_resources_all[RDT_RESOURCE_L3CODE];
		अवरोध;
	हाल RDT_RESOURCE_L3CODE:
		_r_cdp =  &rdt_resources_all[RDT_RESOURCE_L3DATA];
		अवरोध;
	हाल RDT_RESOURCE_L2DATA:
		_r_cdp =  &rdt_resources_all[RDT_RESOURCE_L2CODE];
		अवरोध;
	हाल RDT_RESOURCE_L2CODE:
		_r_cdp =  &rdt_resources_all[RDT_RESOURCE_L2DATA];
		अवरोध;
	शेष:
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	/*
	 * When a new CPU comes online and CDP is enabled then the new
	 * RDT करोमुख्यs (अगर any) associated with both CDP RDT resources
	 * are added in the same CPU online routine जबतक the
	 * rdtgroup_mutex is held. It should thus not happen क्रम one
	 * RDT करोमुख्य to exist and be associated with its RDT CDP
	 * resource but there is no RDT करोमुख्य associated with the
	 * peer RDT CDP resource. Hence the WARN.
	 */
	_d_cdp = rdt_find_करोमुख्य(_r_cdp, d->id, शून्य);
	अगर (WARN_ON(IS_ERR_OR_शून्य(_d_cdp))) अणु
		_r_cdp = शून्य;
		_d_cdp = शून्य;
		ret = -EINVAL;
	पूर्ण

out:
	*r_cdp = _r_cdp;
	*d_cdp = _d_cdp;

	वापस ret;
पूर्ण

/**
 * __rdtgroup_cbm_overlaps - Does CBM क्रम पूर्णांकended closid overlap with other
 * @r: Resource to which करोमुख्य instance @d beदीर्घs.
 * @d: The करोमुख्य instance क्रम which @closid is being tested.
 * @cbm: Capacity biपंचांगask being tested.
 * @closid: Intended closid क्रम @cbm.
 * @exclusive: Only check अगर overlaps with exclusive resource groups
 *
 * Checks अगर provided @cbm पूर्णांकended to be used क्रम @closid on करोमुख्य
 * @d overlaps with any other closids or other hardware usage associated
 * with this करोमुख्य. If @exclusive is true then only overlaps with
 * resource groups in exclusive mode will be considered. If @exclusive
 * is false then overlaps with any resource group or hardware entities
 * will be considered.
 *
 * @cbm is अचिन्हित दीर्घ, even अगर only 32 bits are used, to make the
 * biपंचांगap functions work correctly.
 *
 * Return: false अगर CBM करोes not overlap, true अगर it करोes.
 */
अटल bool __rdtgroup_cbm_overlaps(काष्ठा rdt_resource *r, काष्ठा rdt_करोमुख्य *d,
				    अचिन्हित दीर्घ cbm, पूर्णांक closid, bool exclusive)
अणु
	क्रमागत rdtgrp_mode mode;
	अचिन्हित दीर्घ ctrl_b;
	u32 *ctrl;
	पूर्णांक i;

	/* Check क्रम any overlap with regions used by hardware directly */
	अगर (!exclusive) अणु
		ctrl_b = r->cache.shareable_bits;
		अगर (biपंचांगap_पूर्णांकersects(&cbm, &ctrl_b, r->cache.cbm_len))
			वापस true;
	पूर्ण

	/* Check क्रम overlap with other resource groups */
	ctrl = d->ctrl_val;
	क्रम (i = 0; i < closids_supported(); i++, ctrl++) अणु
		ctrl_b = *ctrl;
		mode = rdtgroup_mode_by_closid(i);
		अगर (closid_allocated(i) && i != closid &&
		    mode != RDT_MODE_PSEUDO_LOCKSETUP) अणु
			अगर (biपंचांगap_पूर्णांकersects(&cbm, &ctrl_b, r->cache.cbm_len)) अणु
				अगर (exclusive) अणु
					अगर (mode == RDT_MODE_EXCLUSIVE)
						वापस true;
					जारी;
				पूर्ण
				वापस true;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

/**
 * rdtgroup_cbm_overlaps - Does CBM overlap with other use of hardware
 * @r: Resource to which करोमुख्य instance @d beदीर्घs.
 * @d: The करोमुख्य instance क्रम which @closid is being tested.
 * @cbm: Capacity biपंचांगask being tested.
 * @closid: Intended closid क्रम @cbm.
 * @exclusive: Only check अगर overlaps with exclusive resource groups
 *
 * Resources that can be allocated using a CBM can use the CBM to control
 * the overlap of these allocations. rdtgroup_cmb_overlaps() is the test
 * क्रम overlap. Overlap test is not limited to the specअगरic resource क्रम
 * which the CBM is पूर्णांकended though - when dealing with CDP resources that
 * share the underlying hardware the overlap check should be perक्रमmed on
 * the CDP resource sharing the hardware also.
 *
 * Refer to description of __rdtgroup_cbm_overlaps() क्रम the details of the
 * overlap test.
 *
 * Return: true अगर CBM overlap detected, false अगर there is no overlap
 */
bool rdtgroup_cbm_overlaps(काष्ठा rdt_resource *r, काष्ठा rdt_करोमुख्य *d,
			   अचिन्हित दीर्घ cbm, पूर्णांक closid, bool exclusive)
अणु
	काष्ठा rdt_resource *r_cdp;
	काष्ठा rdt_करोमुख्य *d_cdp;

	अगर (__rdtgroup_cbm_overlaps(r, d, cbm, closid, exclusive))
		वापस true;

	अगर (rdt_cdp_peer_get(r, d, &r_cdp, &d_cdp) < 0)
		वापस false;

	वापस  __rdtgroup_cbm_overlaps(r_cdp, d_cdp, cbm, closid, exclusive);
पूर्ण

/**
 * rdtgroup_mode_test_exclusive - Test अगर this resource group can be exclusive
 *
 * An exclusive resource group implies that there should be no sharing of
 * its allocated resources. At the समय this group is considered to be
 * exclusive this test can determine अगर its current schemata supports this
 * setting by testing क्रम overlap with all other resource groups.
 *
 * Return: true अगर resource group can be exclusive, false अगर there is overlap
 * with allocations of other resource groups and thus this resource group
 * cannot be exclusive.
 */
अटल bool rdtgroup_mode_test_exclusive(काष्ठा rdtgroup *rdtgrp)
अणु
	पूर्णांक closid = rdtgrp->closid;
	काष्ठा rdt_resource *r;
	bool has_cache = false;
	काष्ठा rdt_करोमुख्य *d;

	क्रम_each_alloc_enabled_rdt_resource(r) अणु
		अगर (r->rid == RDT_RESOURCE_MBA)
			जारी;
		has_cache = true;
		list_क्रम_each_entry(d, &r->करोमुख्यs, list) अणु
			अगर (rdtgroup_cbm_overlaps(r, d, d->ctrl_val[closid],
						  rdtgrp->closid, false)) अणु
				rdt_last_cmd_माला_दो("Schemata overlaps\n");
				वापस false;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!has_cache) अणु
		rdt_last_cmd_माला_दो("Cannot be exclusive without CAT/CDP\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/**
 * rdtgroup_mode_ग_लिखो - Modअगरy the resource group's mode
 *
 */
अटल sमाप_प्रकार rdtgroup_mode_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
				   अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा rdtgroup *rdtgrp;
	क्रमागत rdtgrp_mode mode;
	पूर्णांक ret = 0;

	/* Valid input requires a trailing newline */
	अगर (nbytes == 0 || buf[nbytes - 1] != '\n')
		वापस -EINVAL;
	buf[nbytes - 1] = '\0';

	rdtgrp = rdtgroup_kn_lock_live(of->kn);
	अगर (!rdtgrp) अणु
		rdtgroup_kn_unlock(of->kn);
		वापस -ENOENT;
	पूर्ण

	rdt_last_cmd_clear();

	mode = rdtgrp->mode;

	अगर ((!म_भेद(buf, "shareable") && mode == RDT_MODE_SHAREABLE) ||
	    (!म_भेद(buf, "exclusive") && mode == RDT_MODE_EXCLUSIVE) ||
	    (!म_भेद(buf, "pseudo-locksetup") &&
	     mode == RDT_MODE_PSEUDO_LOCKSETUP) ||
	    (!म_भेद(buf, "pseudo-locked") && mode == RDT_MODE_PSEUDO_LOCKED))
		जाओ out;

	अगर (mode == RDT_MODE_PSEUDO_LOCKED) अणु
		rdt_last_cmd_माला_दो("Cannot change pseudo-locked group\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!म_भेद(buf, "shareable")) अणु
		अगर (rdtgrp->mode == RDT_MODE_PSEUDO_LOCKSETUP) अणु
			ret = rdtgroup_locksetup_निकास(rdtgrp);
			अगर (ret)
				जाओ out;
		पूर्ण
		rdtgrp->mode = RDT_MODE_SHAREABLE;
	पूर्ण अन्यथा अगर (!म_भेद(buf, "exclusive")) अणु
		अगर (!rdtgroup_mode_test_exclusive(rdtgrp)) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		अगर (rdtgrp->mode == RDT_MODE_PSEUDO_LOCKSETUP) अणु
			ret = rdtgroup_locksetup_निकास(rdtgrp);
			अगर (ret)
				जाओ out;
		पूर्ण
		rdtgrp->mode = RDT_MODE_EXCLUSIVE;
	पूर्ण अन्यथा अगर (!म_भेद(buf, "pseudo-locksetup")) अणु
		ret = rdtgroup_locksetup_enter(rdtgrp);
		अगर (ret)
			जाओ out;
		rdtgrp->mode = RDT_MODE_PSEUDO_LOCKSETUP;
	पूर्ण अन्यथा अणु
		rdt_last_cmd_माला_दो("Unknown or unsupported mode\n");
		ret = -EINVAL;
	पूर्ण

out:
	rdtgroup_kn_unlock(of->kn);
	वापस ret ?: nbytes;
पूर्ण

/**
 * rdtgroup_cbm_to_size - Translate CBM to size in bytes
 * @r: RDT resource to which @d beदीर्घs.
 * @d: RDT करोमुख्य instance.
 * @cbm: biपंचांगask क्रम which the size should be computed.
 *
 * The biपंचांगask provided associated with the RDT करोमुख्य instance @d will be
 * translated पूर्णांकo how many bytes it represents. The size in bytes is
 * computed by first भागiding the total cache size by the CBM length to
 * determine how many bytes each bit in the biपंचांगask represents. The result
 * is multiplied with the number of bits set in the biपंचांगask.
 *
 * @cbm is अचिन्हित दीर्घ, even अगर only 32 bits are used to make the
 * biपंचांगap functions work correctly.
 */
अचिन्हित पूर्णांक rdtgroup_cbm_to_size(काष्ठा rdt_resource *r,
				  काष्ठा rdt_करोमुख्य *d, अचिन्हित दीर्घ cbm)
अणु
	काष्ठा cpu_cacheinfo *ci;
	अचिन्हित पूर्णांक size = 0;
	पूर्णांक num_b, i;

	num_b = biपंचांगap_weight(&cbm, r->cache.cbm_len);
	ci = get_cpu_cacheinfo(cpumask_any(&d->cpu_mask));
	क्रम (i = 0; i < ci->num_leaves; i++) अणु
		अगर (ci->info_list[i].level == r->cache_level) अणु
			size = ci->info_list[i].size / r->cache.cbm_len * num_b;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस size;
पूर्ण

/**
 * rdtgroup_size_show - Display size in bytes of allocated regions
 *
 * The "size" file mirrors the layout of the "schemata" file, prपूर्णांकing the
 * size in bytes of each region instead of the capacity biपंचांगask.
 *
 */
अटल पूर्णांक rdtgroup_size_show(काष्ठा kernfs_खोलो_file *of,
			      काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा rdtgroup *rdtgrp;
	काष्ठा rdt_resource *r;
	काष्ठा rdt_करोमुख्य *d;
	अचिन्हित पूर्णांक size;
	पूर्णांक ret = 0;
	bool sep;
	u32 ctrl;

	rdtgrp = rdtgroup_kn_lock_live(of->kn);
	अगर (!rdtgrp) अणु
		rdtgroup_kn_unlock(of->kn);
		वापस -ENOENT;
	पूर्ण

	अगर (rdtgrp->mode == RDT_MODE_PSEUDO_LOCKED) अणु
		अगर (!rdtgrp->plr->d) अणु
			rdt_last_cmd_clear();
			rdt_last_cmd_माला_दो("Cache domain offline\n");
			ret = -ENODEV;
		पूर्ण अन्यथा अणु
			seq_म_लिखो(s, "%*s:", max_name_width,
				   rdtgrp->plr->r->name);
			size = rdtgroup_cbm_to_size(rdtgrp->plr->r,
						    rdtgrp->plr->d,
						    rdtgrp->plr->cbm);
			seq_म_लिखो(s, "%d=%u\n", rdtgrp->plr->d->id, size);
		पूर्ण
		जाओ out;
	पूर्ण

	क्रम_each_alloc_enabled_rdt_resource(r) अणु
		sep = false;
		seq_म_लिखो(s, "%*s:", max_name_width, r->name);
		list_क्रम_each_entry(d, &r->करोमुख्यs, list) अणु
			अगर (sep)
				seq_अ_दो(s, ';');
			अगर (rdtgrp->mode == RDT_MODE_PSEUDO_LOCKSETUP) अणु
				size = 0;
			पूर्ण अन्यथा अणु
				ctrl = (!is_mba_sc(r) ?
						d->ctrl_val[rdtgrp->closid] :
						d->mbps_val[rdtgrp->closid]);
				अगर (r->rid == RDT_RESOURCE_MBA)
					size = ctrl;
				अन्यथा
					size = rdtgroup_cbm_to_size(r, d, ctrl);
			पूर्ण
			seq_म_लिखो(s, "%d=%u", d->id, size);
			sep = true;
		पूर्ण
		seq_अ_दो(s, '\n');
	पूर्ण

out:
	rdtgroup_kn_unlock(of->kn);

	वापस ret;
पूर्ण

/* rdtgroup inक्रमmation files क्रम one cache resource. */
अटल काष्ठा rftype res_common_files[] = अणु
	अणु
		.name		= "last_cmd_status",
		.mode		= 0444,
		.kf_ops		= &rdtgroup_kf_single_ops,
		.seq_show	= rdt_last_cmd_status_show,
		.fflags		= RF_TOP_INFO,
	पूर्ण,
	अणु
		.name		= "num_closids",
		.mode		= 0444,
		.kf_ops		= &rdtgroup_kf_single_ops,
		.seq_show	= rdt_num_closids_show,
		.fflags		= RF_CTRL_INFO,
	पूर्ण,
	अणु
		.name		= "mon_features",
		.mode		= 0444,
		.kf_ops		= &rdtgroup_kf_single_ops,
		.seq_show	= rdt_mon_features_show,
		.fflags		= RF_MON_INFO,
	पूर्ण,
	अणु
		.name		= "num_rmids",
		.mode		= 0444,
		.kf_ops		= &rdtgroup_kf_single_ops,
		.seq_show	= rdt_num_rmids_show,
		.fflags		= RF_MON_INFO,
	पूर्ण,
	अणु
		.name		= "cbm_mask",
		.mode		= 0444,
		.kf_ops		= &rdtgroup_kf_single_ops,
		.seq_show	= rdt_शेष_ctrl_show,
		.fflags		= RF_CTRL_INFO | RFTYPE_RES_CACHE,
	पूर्ण,
	अणु
		.name		= "min_cbm_bits",
		.mode		= 0444,
		.kf_ops		= &rdtgroup_kf_single_ops,
		.seq_show	= rdt_min_cbm_bits_show,
		.fflags		= RF_CTRL_INFO | RFTYPE_RES_CACHE,
	पूर्ण,
	अणु
		.name		= "shareable_bits",
		.mode		= 0444,
		.kf_ops		= &rdtgroup_kf_single_ops,
		.seq_show	= rdt_shareable_bits_show,
		.fflags		= RF_CTRL_INFO | RFTYPE_RES_CACHE,
	पूर्ण,
	अणु
		.name		= "bit_usage",
		.mode		= 0444,
		.kf_ops		= &rdtgroup_kf_single_ops,
		.seq_show	= rdt_bit_usage_show,
		.fflags		= RF_CTRL_INFO | RFTYPE_RES_CACHE,
	पूर्ण,
	अणु
		.name		= "min_bandwidth",
		.mode		= 0444,
		.kf_ops		= &rdtgroup_kf_single_ops,
		.seq_show	= rdt_min_bw_show,
		.fflags		= RF_CTRL_INFO | RFTYPE_RES_MB,
	पूर्ण,
	अणु
		.name		= "bandwidth_gran",
		.mode		= 0444,
		.kf_ops		= &rdtgroup_kf_single_ops,
		.seq_show	= rdt_bw_gran_show,
		.fflags		= RF_CTRL_INFO | RFTYPE_RES_MB,
	पूर्ण,
	अणु
		.name		= "delay_linear",
		.mode		= 0444,
		.kf_ops		= &rdtgroup_kf_single_ops,
		.seq_show	= rdt_delay_linear_show,
		.fflags		= RF_CTRL_INFO | RFTYPE_RES_MB,
	पूर्ण,
	/*
	 * Platक्रमm specअगरic which (अगर any) capabilities are provided by
	 * thपढ़ो_throttle_mode. Defer "fflags" initialization to platक्रमm
	 * discovery.
	 */
	अणु
		.name		= "thread_throttle_mode",
		.mode		= 0444,
		.kf_ops		= &rdtgroup_kf_single_ops,
		.seq_show	= rdt_thपढ़ो_throttle_mode_show,
	पूर्ण,
	अणु
		.name		= "max_threshold_occupancy",
		.mode		= 0644,
		.kf_ops		= &rdtgroup_kf_single_ops,
		.ग_लिखो		= max_threshold_occ_ग_लिखो,
		.seq_show	= max_threshold_occ_show,
		.fflags		= RF_MON_INFO | RFTYPE_RES_CACHE,
	पूर्ण,
	अणु
		.name		= "cpus",
		.mode		= 0644,
		.kf_ops		= &rdtgroup_kf_single_ops,
		.ग_लिखो		= rdtgroup_cpus_ग_लिखो,
		.seq_show	= rdtgroup_cpus_show,
		.fflags		= RFTYPE_BASE,
	पूर्ण,
	अणु
		.name		= "cpus_list",
		.mode		= 0644,
		.kf_ops		= &rdtgroup_kf_single_ops,
		.ग_लिखो		= rdtgroup_cpus_ग_लिखो,
		.seq_show	= rdtgroup_cpus_show,
		.flags		= RFTYPE_FLAGS_CPUS_LIST,
		.fflags		= RFTYPE_BASE,
	पूर्ण,
	अणु
		.name		= "tasks",
		.mode		= 0644,
		.kf_ops		= &rdtgroup_kf_single_ops,
		.ग_लिखो		= rdtgroup_tasks_ग_लिखो,
		.seq_show	= rdtgroup_tasks_show,
		.fflags		= RFTYPE_BASE,
	पूर्ण,
	अणु
		.name		= "schemata",
		.mode		= 0644,
		.kf_ops		= &rdtgroup_kf_single_ops,
		.ग_लिखो		= rdtgroup_schemata_ग_लिखो,
		.seq_show	= rdtgroup_schemata_show,
		.fflags		= RF_CTRL_BASE,
	पूर्ण,
	अणु
		.name		= "mode",
		.mode		= 0644,
		.kf_ops		= &rdtgroup_kf_single_ops,
		.ग_लिखो		= rdtgroup_mode_ग_लिखो,
		.seq_show	= rdtgroup_mode_show,
		.fflags		= RF_CTRL_BASE,
	पूर्ण,
	अणु
		.name		= "size",
		.mode		= 0444,
		.kf_ops		= &rdtgroup_kf_single_ops,
		.seq_show	= rdtgroup_size_show,
		.fflags		= RF_CTRL_BASE,
	पूर्ण,

पूर्ण;

अटल पूर्णांक rdtgroup_add_files(काष्ठा kernfs_node *kn, अचिन्हित दीर्घ fflags)
अणु
	काष्ठा rftype *rfts, *rft;
	पूर्णांक ret, len;

	rfts = res_common_files;
	len = ARRAY_SIZE(res_common_files);

	lockdep_निश्चित_held(&rdtgroup_mutex);

	क्रम (rft = rfts; rft < rfts + len; rft++) अणु
		अगर (rft->fflags && ((fflags & rft->fflags) == rft->fflags)) अणु
			ret = rdtgroup_add_file(kn, rft);
			अगर (ret)
				जाओ error;
		पूर्ण
	पूर्ण

	वापस 0;
error:
	pr_warn("Failed to add %s, err=%d\n", rft->name, ret);
	जबतक (--rft >= rfts) अणु
		अगर ((fflags & rft->fflags) == rft->fflags)
			kernfs_हटाओ_by_name(kn, rft->name);
	पूर्ण
	वापस ret;
पूर्ण

अटल काष्ठा rftype *rdtgroup_get_rftype_by_name(स्थिर अक्षर *name)
अणु
	काष्ठा rftype *rfts, *rft;
	पूर्णांक len;

	rfts = res_common_files;
	len = ARRAY_SIZE(res_common_files);

	क्रम (rft = rfts; rft < rfts + len; rft++) अणु
		अगर (!म_भेद(rft->name, name))
			वापस rft;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम __init thपढ़ो_throttle_mode_init(व्योम)
अणु
	काष्ठा rftype *rft;

	rft = rdtgroup_get_rftype_by_name("thread_throttle_mode");
	अगर (!rft)
		वापस;

	rft->fflags = RF_CTRL_INFO | RFTYPE_RES_MB;
पूर्ण

/**
 * rdtgroup_kn_mode_restrict - Restrict user access to named resctrl file
 * @r: The resource group with which the file is associated.
 * @name: Name of the file
 *
 * The permissions of named resctrl file, directory, or link are modअगरied
 * to not allow पढ़ो, ग_लिखो, or execute by any user.
 *
 * WARNING: This function is पूर्णांकended to communicate to the user that the
 * resctrl file has been locked करोwn - that it is not relevant to the
 * particular state the प्रणाली finds itself in. It should not be relied
 * on to protect from user access because after the file's permissions
 * are restricted the user can still change the permissions using chmod
 * from the command line.
 *
 * Return: 0 on success, <0 on failure.
 */
पूर्णांक rdtgroup_kn_mode_restrict(काष्ठा rdtgroup *r, स्थिर अक्षर *name)
अणु
	काष्ठा iattr iattr = अणु.ia_valid = ATTR_MODE,पूर्ण;
	काष्ठा kernfs_node *kn;
	पूर्णांक ret = 0;

	kn = kernfs_find_and_get_ns(r->kn, name, शून्य);
	अगर (!kn)
		वापस -ENOENT;

	चयन (kernfs_type(kn)) अणु
	हाल KERNFS_सूची:
		iattr.ia_mode = S_IFसूची;
		अवरोध;
	हाल KERNFS_खाता:
		iattr.ia_mode = S_IFREG;
		अवरोध;
	हाल KERNFS_LINK:
		iattr.ia_mode = S_IFLNK;
		अवरोध;
	पूर्ण

	ret = kernfs_setattr(kn, &iattr);
	kernfs_put(kn);
	वापस ret;
पूर्ण

/**
 * rdtgroup_kn_mode_restore - Restore user access to named resctrl file
 * @r: The resource group with which the file is associated.
 * @name: Name of the file
 * @mask: Mask of permissions that should be restored
 *
 * Restore the permissions of the named file. If @name is a directory the
 * permissions of its parent will be used.
 *
 * Return: 0 on success, <0 on failure.
 */
पूर्णांक rdtgroup_kn_mode_restore(काष्ठा rdtgroup *r, स्थिर अक्षर *name,
			     umode_t mask)
अणु
	काष्ठा iattr iattr = अणु.ia_valid = ATTR_MODE,पूर्ण;
	काष्ठा kernfs_node *kn, *parent;
	काष्ठा rftype *rfts, *rft;
	पूर्णांक ret, len;

	rfts = res_common_files;
	len = ARRAY_SIZE(res_common_files);

	क्रम (rft = rfts; rft < rfts + len; rft++) अणु
		अगर (!म_भेद(rft->name, name))
			iattr.ia_mode = rft->mode & mask;
	पूर्ण

	kn = kernfs_find_and_get_ns(r->kn, name, शून्य);
	अगर (!kn)
		वापस -ENOENT;

	चयन (kernfs_type(kn)) अणु
	हाल KERNFS_सूची:
		parent = kernfs_get_parent(kn);
		अगर (parent) अणु
			iattr.ia_mode |= parent->mode;
			kernfs_put(parent);
		पूर्ण
		iattr.ia_mode |= S_IFसूची;
		अवरोध;
	हाल KERNFS_खाता:
		iattr.ia_mode |= S_IFREG;
		अवरोध;
	हाल KERNFS_LINK:
		iattr.ia_mode |= S_IFLNK;
		अवरोध;
	पूर्ण

	ret = kernfs_setattr(kn, &iattr);
	kernfs_put(kn);
	वापस ret;
पूर्ण

अटल पूर्णांक rdtgroup_सूची_गढ़ो_info_resdir(काष्ठा rdt_resource *r, अक्षर *name,
				      अचिन्हित दीर्घ fflags)
अणु
	काष्ठा kernfs_node *kn_subdir;
	पूर्णांक ret;

	kn_subdir = kernfs_create_dir(kn_info, name,
				      kn_info->mode, r);
	अगर (IS_ERR(kn_subdir))
		वापस PTR_ERR(kn_subdir);

	ret = rdtgroup_kn_set_ugid(kn_subdir);
	अगर (ret)
		वापस ret;

	ret = rdtgroup_add_files(kn_subdir, fflags);
	अगर (!ret)
		kernfs_activate(kn_subdir);

	वापस ret;
पूर्ण

अटल पूर्णांक rdtgroup_create_info_dir(काष्ठा kernfs_node *parent_kn)
अणु
	काष्ठा rdt_resource *r;
	अचिन्हित दीर्घ fflags;
	अक्षर name[32];
	पूर्णांक ret;

	/* create the directory */
	kn_info = kernfs_create_dir(parent_kn, "info", parent_kn->mode, शून्य);
	अगर (IS_ERR(kn_info))
		वापस PTR_ERR(kn_info);

	ret = rdtgroup_add_files(kn_info, RF_TOP_INFO);
	अगर (ret)
		जाओ out_destroy;

	क्रम_each_alloc_enabled_rdt_resource(r) अणु
		fflags =  r->fflags | RF_CTRL_INFO;
		ret = rdtgroup_सूची_गढ़ो_info_resdir(r, r->name, fflags);
		अगर (ret)
			जाओ out_destroy;
	पूर्ण

	क्रम_each_mon_enabled_rdt_resource(r) अणु
		fflags =  r->fflags | RF_MON_INFO;
		प्र_लिखो(name, "%s_MON", r->name);
		ret = rdtgroup_सूची_गढ़ो_info_resdir(r, name, fflags);
		अगर (ret)
			जाओ out_destroy;
	पूर्ण

	ret = rdtgroup_kn_set_ugid(kn_info);
	अगर (ret)
		जाओ out_destroy;

	kernfs_activate(kn_info);

	वापस 0;

out_destroy:
	kernfs_हटाओ(kn_info);
	वापस ret;
पूर्ण

अटल पूर्णांक
mongroup_create_dir(काष्ठा kernfs_node *parent_kn, काष्ठा rdtgroup *prgrp,
		    अक्षर *name, काष्ठा kernfs_node **dest_kn)
अणु
	काष्ठा kernfs_node *kn;
	पूर्णांक ret;

	/* create the directory */
	kn = kernfs_create_dir(parent_kn, name, parent_kn->mode, prgrp);
	अगर (IS_ERR(kn))
		वापस PTR_ERR(kn);

	अगर (dest_kn)
		*dest_kn = kn;

	ret = rdtgroup_kn_set_ugid(kn);
	अगर (ret)
		जाओ out_destroy;

	kernfs_activate(kn);

	वापस 0;

out_destroy:
	kernfs_हटाओ(kn);
	वापस ret;
पूर्ण

अटल व्योम l3_qos_cfg_update(व्योम *arg)
अणु
	bool *enable = arg;

	wrmsrl(MSR_IA32_L3_QOS_CFG, *enable ? L3_QOS_CDP_ENABLE : 0ULL);
पूर्ण

अटल व्योम l2_qos_cfg_update(व्योम *arg)
अणु
	bool *enable = arg;

	wrmsrl(MSR_IA32_L2_QOS_CFG, *enable ? L2_QOS_CDP_ENABLE : 0ULL);
पूर्ण

अटल अंतरभूत bool is_mba_linear(व्योम)
अणु
	वापस rdt_resources_all[RDT_RESOURCE_MBA].membw.delay_linear;
पूर्ण

अटल पूर्णांक set_cache_qos_cfg(पूर्णांक level, bool enable)
अणु
	व्योम (*update)(व्योम *arg);
	काष्ठा rdt_resource *r_l;
	cpumask_var_t cpu_mask;
	काष्ठा rdt_करोमुख्य *d;
	पूर्णांक cpu;

	अगर (level == RDT_RESOURCE_L3)
		update = l3_qos_cfg_update;
	अन्यथा अगर (level == RDT_RESOURCE_L2)
		update = l2_qos_cfg_update;
	अन्यथा
		वापस -EINVAL;

	अगर (!zalloc_cpumask_var(&cpu_mask, GFP_KERNEL))
		वापस -ENOMEM;

	r_l = &rdt_resources_all[level];
	list_क्रम_each_entry(d, &r_l->करोमुख्यs, list) अणु
		अगर (r_l->cache.arch_has_per_cpu_cfg)
			/* Pick all the CPUs in the करोमुख्य instance */
			क्रम_each_cpu(cpu, &d->cpu_mask)
				cpumask_set_cpu(cpu, cpu_mask);
		अन्यथा
			/* Pick one CPU from each करोमुख्य instance to update MSR */
			cpumask_set_cpu(cpumask_any(&d->cpu_mask), cpu_mask);
	पूर्ण
	cpu = get_cpu();
	/* Update QOS_CFG MSR on this cpu अगर it's in cpu_mask. */
	अगर (cpumask_test_cpu(cpu, cpu_mask))
		update(&enable);
	/* Update QOS_CFG MSR on all other cpus in cpu_mask. */
	smp_call_function_many(cpu_mask, update, &enable, 1);
	put_cpu();

	मुक्त_cpumask_var(cpu_mask);

	वापस 0;
पूर्ण

/* Restore the qos cfg state when a करोमुख्य comes online */
व्योम rdt_करोमुख्य_reconfigure_cdp(काष्ठा rdt_resource *r)
अणु
	अगर (!r->alloc_capable)
		वापस;

	अगर (r == &rdt_resources_all[RDT_RESOURCE_L2DATA])
		l2_qos_cfg_update(&r->alloc_enabled);

	अगर (r == &rdt_resources_all[RDT_RESOURCE_L3DATA])
		l3_qos_cfg_update(&r->alloc_enabled);
पूर्ण

/*
 * Enable or disable the MBA software controller
 * which helps user specअगरy bandwidth in MBps.
 * MBA software controller is supported only अगर
 * MBM is supported and MBA is in linear scale.
 */
अटल पूर्णांक set_mba_sc(bool mba_sc)
अणु
	काष्ठा rdt_resource *r = &rdt_resources_all[RDT_RESOURCE_MBA];
	काष्ठा rdt_करोमुख्य *d;

	अगर (!is_mbm_enabled() || !is_mba_linear() ||
	    mba_sc == is_mba_sc(r))
		वापस -EINVAL;

	r->membw.mba_sc = mba_sc;
	list_क्रम_each_entry(d, &r->करोमुख्यs, list)
		setup_शेष_ctrlval(r, d->ctrl_val, d->mbps_val);

	वापस 0;
पूर्ण

अटल पूर्णांक cdp_enable(पूर्णांक level, पूर्णांक data_type, पूर्णांक code_type)
अणु
	काष्ठा rdt_resource *r_ldata = &rdt_resources_all[data_type];
	काष्ठा rdt_resource *r_lcode = &rdt_resources_all[code_type];
	काष्ठा rdt_resource *r_l = &rdt_resources_all[level];
	पूर्णांक ret;

	अगर (!r_l->alloc_capable || !r_ldata->alloc_capable ||
	    !r_lcode->alloc_capable)
		वापस -EINVAL;

	ret = set_cache_qos_cfg(level, true);
	अगर (!ret) अणु
		r_l->alloc_enabled = false;
		r_ldata->alloc_enabled = true;
		r_lcode->alloc_enabled = true;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक cdpl3_enable(व्योम)
अणु
	वापस cdp_enable(RDT_RESOURCE_L3, RDT_RESOURCE_L3DATA,
			  RDT_RESOURCE_L3CODE);
पूर्ण

अटल पूर्णांक cdpl2_enable(व्योम)
अणु
	वापस cdp_enable(RDT_RESOURCE_L2, RDT_RESOURCE_L2DATA,
			  RDT_RESOURCE_L2CODE);
पूर्ण

अटल व्योम cdp_disable(पूर्णांक level, पूर्णांक data_type, पूर्णांक code_type)
अणु
	काष्ठा rdt_resource *r = &rdt_resources_all[level];

	r->alloc_enabled = r->alloc_capable;

	अगर (rdt_resources_all[data_type].alloc_enabled) अणु
		rdt_resources_all[data_type].alloc_enabled = false;
		rdt_resources_all[code_type].alloc_enabled = false;
		set_cache_qos_cfg(level, false);
	पूर्ण
पूर्ण

अटल व्योम cdpl3_disable(व्योम)
अणु
	cdp_disable(RDT_RESOURCE_L3, RDT_RESOURCE_L3DATA, RDT_RESOURCE_L3CODE);
पूर्ण

अटल व्योम cdpl2_disable(व्योम)
अणु
	cdp_disable(RDT_RESOURCE_L2, RDT_RESOURCE_L2DATA, RDT_RESOURCE_L2CODE);
पूर्ण

अटल व्योम cdp_disable_all(व्योम)
अणु
	अगर (rdt_resources_all[RDT_RESOURCE_L3DATA].alloc_enabled)
		cdpl3_disable();
	अगर (rdt_resources_all[RDT_RESOURCE_L2DATA].alloc_enabled)
		cdpl2_disable();
पूर्ण

/*
 * We करोn't allow rdtgroup directories to be created anywhere
 * except the root directory. Thus when looking क्रम the rdtgroup
 * काष्ठाure क्रम a kernfs node we are either looking at a directory,
 * in which हाल the rdtgroup काष्ठाure is poपूर्णांकed at by the "priv"
 * field, otherwise we have a file, and need only look to the parent
 * to find the rdtgroup.
 */
अटल काष्ठा rdtgroup *kernfs_to_rdtgroup(काष्ठा kernfs_node *kn)
अणु
	अगर (kernfs_type(kn) == KERNFS_सूची) अणु
		/*
		 * All the resource directories use "kn->priv"
		 * to poपूर्णांक to the "struct rdtgroup" क्रम the
		 * resource. "info" and its subdirectories करोn't
		 * have rdtgroup काष्ठाures, so वापस शून्य here.
		 */
		अगर (kn == kn_info || kn->parent == kn_info)
			वापस शून्य;
		अन्यथा
			वापस kn->priv;
	पूर्ण अन्यथा अणु
		वापस kn->parent->priv;
	पूर्ण
पूर्ण

काष्ठा rdtgroup *rdtgroup_kn_lock_live(काष्ठा kernfs_node *kn)
अणु
	काष्ठा rdtgroup *rdtgrp = kernfs_to_rdtgroup(kn);

	अगर (!rdtgrp)
		वापस शून्य;

	atomic_inc(&rdtgrp->रुकोcount);
	kernfs_अवरोध_active_protection(kn);

	mutex_lock(&rdtgroup_mutex);

	/* Was this group deleted जबतक we रुकोed? */
	अगर (rdtgrp->flags & RDT_DELETED)
		वापस शून्य;

	वापस rdtgrp;
पूर्ण

व्योम rdtgroup_kn_unlock(काष्ठा kernfs_node *kn)
अणु
	काष्ठा rdtgroup *rdtgrp = kernfs_to_rdtgroup(kn);

	अगर (!rdtgrp)
		वापस;

	mutex_unlock(&rdtgroup_mutex);

	अगर (atomic_dec_and_test(&rdtgrp->रुकोcount) &&
	    (rdtgrp->flags & RDT_DELETED)) अणु
		अगर (rdtgrp->mode == RDT_MODE_PSEUDO_LOCKSETUP ||
		    rdtgrp->mode == RDT_MODE_PSEUDO_LOCKED)
			rdtgroup_pseuकरो_lock_हटाओ(rdtgrp);
		kernfs_unअवरोध_active_protection(kn);
		rdtgroup_हटाओ(rdtgrp);
	पूर्ण अन्यथा अणु
		kernfs_unअवरोध_active_protection(kn);
	पूर्ण
पूर्ण

अटल पूर्णांक सूची_गढ़ो_mondata_all(काष्ठा kernfs_node *parent_kn,
			     काष्ठा rdtgroup *prgrp,
			     काष्ठा kernfs_node **mon_data_kn);

अटल पूर्णांक rdt_enable_ctx(काष्ठा rdt_fs_context *ctx)
अणु
	पूर्णांक ret = 0;

	अगर (ctx->enable_cdpl2)
		ret = cdpl2_enable();

	अगर (!ret && ctx->enable_cdpl3)
		ret = cdpl3_enable();

	अगर (!ret && ctx->enable_mba_mbps)
		ret = set_mba_sc(true);

	वापस ret;
पूर्ण

अटल पूर्णांक rdt_get_tree(काष्ठा fs_context *fc)
अणु
	काष्ठा rdt_fs_context *ctx = rdt_fc2context(fc);
	काष्ठा rdt_करोमुख्य *करोm;
	काष्ठा rdt_resource *r;
	पूर्णांक ret;

	cpus_पढ़ो_lock();
	mutex_lock(&rdtgroup_mutex);
	/*
	 * resctrl file प्रणाली can only be mounted once.
	 */
	अगर (अटल_branch_unlikely(&rdt_enable_key)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	ret = rdt_enable_ctx(ctx);
	अगर (ret < 0)
		जाओ out_cdp;

	closid_init();

	ret = rdtgroup_create_info_dir(rdtgroup_शेष.kn);
	अगर (ret < 0)
		जाओ out_mba;

	अगर (rdt_mon_capable) अणु
		ret = mongroup_create_dir(rdtgroup_शेष.kn,
					  &rdtgroup_शेष, "mon_groups",
					  &kn_mongrp);
		अगर (ret < 0)
			जाओ out_info;

		ret = सूची_गढ़ो_mondata_all(rdtgroup_शेष.kn,
					&rdtgroup_शेष, &kn_mondata);
		अगर (ret < 0)
			जाओ out_mongrp;
		rdtgroup_शेष.mon.mon_data_kn = kn_mondata;
	पूर्ण

	ret = rdt_pseuकरो_lock_init();
	अगर (ret)
		जाओ out_mondata;

	ret = kernfs_get_tree(fc);
	अगर (ret < 0)
		जाओ out_psl;

	अगर (rdt_alloc_capable)
		अटल_branch_enable_cpuslocked(&rdt_alloc_enable_key);
	अगर (rdt_mon_capable)
		अटल_branch_enable_cpuslocked(&rdt_mon_enable_key);

	अगर (rdt_alloc_capable || rdt_mon_capable)
		अटल_branch_enable_cpuslocked(&rdt_enable_key);

	अगर (is_mbm_enabled()) अणु
		r = &rdt_resources_all[RDT_RESOURCE_L3];
		list_क्रम_each_entry(करोm, &r->करोमुख्यs, list)
			mbm_setup_overflow_handler(करोm, MBM_OVERFLOW_INTERVAL);
	पूर्ण

	जाओ out;

out_psl:
	rdt_pseuकरो_lock_release();
out_mondata:
	अगर (rdt_mon_capable)
		kernfs_हटाओ(kn_mondata);
out_mongrp:
	अगर (rdt_mon_capable)
		kernfs_हटाओ(kn_mongrp);
out_info:
	kernfs_हटाओ(kn_info);
out_mba:
	अगर (ctx->enable_mba_mbps)
		set_mba_sc(false);
out_cdp:
	cdp_disable_all();
out:
	rdt_last_cmd_clear();
	mutex_unlock(&rdtgroup_mutex);
	cpus_पढ़ो_unlock();
	वापस ret;
पूर्ण

क्रमागत rdt_param अणु
	Opt_cdp,
	Opt_cdpl2,
	Opt_mba_mbps,
	nr__rdt_params
पूर्ण;

अटल स्थिर काष्ठा fs_parameter_spec rdt_fs_parameters[] = अणु
	fsparam_flag("cdp",		Opt_cdp),
	fsparam_flag("cdpl2",		Opt_cdpl2),
	fsparam_flag("mba_MBps",	Opt_mba_mbps),
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक rdt_parse_param(काष्ठा fs_context *fc, काष्ठा fs_parameter *param)
अणु
	काष्ठा rdt_fs_context *ctx = rdt_fc2context(fc);
	काष्ठा fs_parse_result result;
	पूर्णांक opt;

	opt = fs_parse(fc, rdt_fs_parameters, param, &result);
	अगर (opt < 0)
		वापस opt;

	चयन (opt) अणु
	हाल Opt_cdp:
		ctx->enable_cdpl3 = true;
		वापस 0;
	हाल Opt_cdpl2:
		ctx->enable_cdpl2 = true;
		वापस 0;
	हाल Opt_mba_mbps:
		अगर (boot_cpu_data.x86_venकरोr != X86_VENDOR_INTEL)
			वापस -EINVAL;
		ctx->enable_mba_mbps = true;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम rdt_fs_context_मुक्त(काष्ठा fs_context *fc)
अणु
	काष्ठा rdt_fs_context *ctx = rdt_fc2context(fc);

	kernfs_मुक्त_fs_context(fc);
	kमुक्त(ctx);
पूर्ण

अटल स्थिर काष्ठा fs_context_operations rdt_fs_context_ops = अणु
	.मुक्त		= rdt_fs_context_मुक्त,
	.parse_param	= rdt_parse_param,
	.get_tree	= rdt_get_tree,
पूर्ण;

अटल पूर्णांक rdt_init_fs_context(काष्ठा fs_context *fc)
अणु
	काष्ठा rdt_fs_context *ctx;

	ctx = kzalloc(माप(काष्ठा rdt_fs_context), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->kfc.root = rdt_root;
	ctx->kfc.magic = RDTGROUP_SUPER_MAGIC;
	fc->fs_निजी = &ctx->kfc;
	fc->ops = &rdt_fs_context_ops;
	put_user_ns(fc->user_ns);
	fc->user_ns = get_user_ns(&init_user_ns);
	fc->global = true;
	वापस 0;
पूर्ण

अटल पूर्णांक reset_all_ctrls(काष्ठा rdt_resource *r)
अणु
	काष्ठा msr_param msr_param;
	cpumask_var_t cpu_mask;
	काष्ठा rdt_करोमुख्य *d;
	पूर्णांक i, cpu;

	अगर (!zalloc_cpumask_var(&cpu_mask, GFP_KERNEL))
		वापस -ENOMEM;

	msr_param.res = r;
	msr_param.low = 0;
	msr_param.high = r->num_closid;

	/*
	 * Disable resource control क्रम this resource by setting all
	 * CBMs in all करोमुख्यs to the maximum mask value. Pick one CPU
	 * from each करोमुख्य to update the MSRs below.
	 */
	list_क्रम_each_entry(d, &r->करोमुख्यs, list) अणु
		cpumask_set_cpu(cpumask_any(&d->cpu_mask), cpu_mask);

		क्रम (i = 0; i < r->num_closid; i++)
			d->ctrl_val[i] = r->शेष_ctrl;
	पूर्ण
	cpu = get_cpu();
	/* Update CBM on this cpu अगर it's in cpu_mask. */
	अगर (cpumask_test_cpu(cpu, cpu_mask))
		rdt_ctrl_update(&msr_param);
	/* Update CBM on all other cpus in cpu_mask. */
	smp_call_function_many(cpu_mask, rdt_ctrl_update, &msr_param, 1);
	put_cpu();

	मुक्त_cpumask_var(cpu_mask);

	वापस 0;
पूर्ण

/*
 * Move tasks from one to the other group. If @from is शून्य, then all tasks
 * in the प्रणालीs are moved unconditionally (used क्रम tearकरोwn).
 *
 * If @mask is not शून्य the cpus on which moved tasks are running are set
 * in that mask so the update smp function call is restricted to affected
 * cpus.
 */
अटल व्योम rdt_move_group_tasks(काष्ठा rdtgroup *from, काष्ठा rdtgroup *to,
				 काष्ठा cpumask *mask)
अणु
	काष्ठा task_काष्ठा *p, *t;

	पढ़ो_lock(&tasklist_lock);
	क्रम_each_process_thपढ़ो(p, t) अणु
		अगर (!from || is_closid_match(t, from) ||
		    is_rmid_match(t, from)) अणु
			WRITE_ONCE(t->closid, to->closid);
			WRITE_ONCE(t->rmid, to->mon.rmid);

			/*
			 * If the task is on a CPU, set the CPU in the mask.
			 * The detection is inaccurate as tasks might move or
			 * schedule beक्रमe the smp function call takes place.
			 * In such a हाल the function call is poपूर्णांकless, but
			 * there is no other side effect.
			 */
			अगर (IS_ENABLED(CONFIG_SMP) && mask && task_curr(t))
				cpumask_set_cpu(task_cpu(t), mask);
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&tasklist_lock);
पूर्ण

अटल व्योम मुक्त_all_child_rdtgrp(काष्ठा rdtgroup *rdtgrp)
अणु
	काष्ठा rdtgroup *sentry, *sपंचांगp;
	काष्ठा list_head *head;

	head = &rdtgrp->mon.crdtgrp_list;
	list_क्रम_each_entry_safe(sentry, sपंचांगp, head, mon.crdtgrp_list) अणु
		मुक्त_rmid(sentry->mon.rmid);
		list_del(&sentry->mon.crdtgrp_list);

		अगर (atomic_पढ़ो(&sentry->रुकोcount) != 0)
			sentry->flags = RDT_DELETED;
		अन्यथा
			rdtgroup_हटाओ(sentry);
	पूर्ण
पूर्ण

/*
 * Forcibly हटाओ all of subdirectories under root.
 */
अटल व्योम सूची_हटाओ_all_sub(व्योम)
अणु
	काष्ठा rdtgroup *rdtgrp, *पंचांगp;

	/* Move all tasks to the शेष resource group */
	rdt_move_group_tasks(शून्य, &rdtgroup_शेष, शून्य);

	list_क्रम_each_entry_safe(rdtgrp, पंचांगp, &rdt_all_groups, rdtgroup_list) अणु
		/* Free any child rmids */
		मुक्त_all_child_rdtgrp(rdtgrp);

		/* Remove each rdtgroup other than root */
		अगर (rdtgrp == &rdtgroup_शेष)
			जारी;

		अगर (rdtgrp->mode == RDT_MODE_PSEUDO_LOCKSETUP ||
		    rdtgrp->mode == RDT_MODE_PSEUDO_LOCKED)
			rdtgroup_pseuकरो_lock_हटाओ(rdtgrp);

		/*
		 * Give any CPUs back to the शेष group. We cannot copy
		 * cpu_online_mask because a CPU might have executed the
		 * offline callback alपढ़ोy, but is still marked online.
		 */
		cpumask_or(&rdtgroup_शेष.cpu_mask,
			   &rdtgroup_शेष.cpu_mask, &rdtgrp->cpu_mask);

		मुक्त_rmid(rdtgrp->mon.rmid);

		kernfs_हटाओ(rdtgrp->kn);
		list_del(&rdtgrp->rdtgroup_list);

		अगर (atomic_पढ़ो(&rdtgrp->रुकोcount) != 0)
			rdtgrp->flags = RDT_DELETED;
		अन्यथा
			rdtgroup_हटाओ(rdtgrp);
	पूर्ण
	/* Notअगरy online CPUs to update per cpu storage and PQR_ASSOC MSR */
	update_closid_rmid(cpu_online_mask, &rdtgroup_शेष);

	kernfs_हटाओ(kn_info);
	kernfs_हटाओ(kn_mongrp);
	kernfs_हटाओ(kn_mondata);
पूर्ण

अटल व्योम rdt_समाप्त_sb(काष्ठा super_block *sb)
अणु
	काष्ठा rdt_resource *r;

	cpus_पढ़ो_lock();
	mutex_lock(&rdtgroup_mutex);

	set_mba_sc(false);

	/*Put everything back to शेष values. */
	क्रम_each_alloc_enabled_rdt_resource(r)
		reset_all_ctrls(r);
	cdp_disable_all();
	सूची_हटाओ_all_sub();
	rdt_pseuकरो_lock_release();
	rdtgroup_शेष.mode = RDT_MODE_SHAREABLE;
	अटल_branch_disable_cpuslocked(&rdt_alloc_enable_key);
	अटल_branch_disable_cpuslocked(&rdt_mon_enable_key);
	अटल_branch_disable_cpuslocked(&rdt_enable_key);
	kernfs_समाप्त_sb(sb);
	mutex_unlock(&rdtgroup_mutex);
	cpus_पढ़ो_unlock();
पूर्ण

अटल काष्ठा file_प्रणाली_type rdt_fs_type = अणु
	.name			= "resctrl",
	.init_fs_context	= rdt_init_fs_context,
	.parameters		= rdt_fs_parameters,
	.समाप्त_sb		= rdt_समाप्त_sb,
पूर्ण;

अटल पूर्णांक mon_addfile(काष्ठा kernfs_node *parent_kn, स्थिर अक्षर *name,
		       व्योम *priv)
अणु
	काष्ठा kernfs_node *kn;
	पूर्णांक ret = 0;

	kn = __kernfs_create_file(parent_kn, name, 0444,
				  GLOBAL_ROOT_UID, GLOBAL_ROOT_GID, 0,
				  &kf_mondata_ops, priv, शून्य, शून्य);
	अगर (IS_ERR(kn))
		वापस PTR_ERR(kn);

	ret = rdtgroup_kn_set_ugid(kn);
	अगर (ret) अणु
		kernfs_हटाओ(kn);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Remove all subdirectories of mon_data of ctrl_mon groups
 * and monitor groups with given करोमुख्य id.
 */
व्योम सूची_हटाओ_mondata_subdir_allrdtgrp(काष्ठा rdt_resource *r, अचिन्हित पूर्णांक करोm_id)
अणु
	काष्ठा rdtgroup *prgrp, *crgrp;
	अक्षर name[32];

	अगर (!r->mon_enabled)
		वापस;

	list_क्रम_each_entry(prgrp, &rdt_all_groups, rdtgroup_list) अणु
		प्र_लिखो(name, "mon_%s_%02d", r->name, करोm_id);
		kernfs_हटाओ_by_name(prgrp->mon.mon_data_kn, name);

		list_क्रम_each_entry(crgrp, &prgrp->mon.crdtgrp_list, mon.crdtgrp_list)
			kernfs_हटाओ_by_name(crgrp->mon.mon_data_kn, name);
	पूर्ण
पूर्ण

अटल पूर्णांक सूची_गढ़ो_mondata_subdir(काष्ठा kernfs_node *parent_kn,
				काष्ठा rdt_करोमुख्य *d,
				काष्ठा rdt_resource *r, काष्ठा rdtgroup *prgrp)
अणु
	जोड़ mon_data_bits priv;
	काष्ठा kernfs_node *kn;
	काष्ठा mon_evt *mevt;
	काष्ठा rmid_पढ़ो rr;
	अक्षर name[32];
	पूर्णांक ret;

	प्र_लिखो(name, "mon_%s_%02d", r->name, d->id);
	/* create the directory */
	kn = kernfs_create_dir(parent_kn, name, parent_kn->mode, prgrp);
	अगर (IS_ERR(kn))
		वापस PTR_ERR(kn);

	ret = rdtgroup_kn_set_ugid(kn);
	अगर (ret)
		जाओ out_destroy;

	अगर (WARN_ON(list_empty(&r->evt_list))) अणु
		ret = -EPERM;
		जाओ out_destroy;
	पूर्ण

	priv.u.rid = r->rid;
	priv.u.करोmid = d->id;
	list_क्रम_each_entry(mevt, &r->evt_list, list) अणु
		priv.u.evtid = mevt->evtid;
		ret = mon_addfile(kn, mevt->name, priv.priv);
		अगर (ret)
			जाओ out_destroy;

		अगर (is_mbm_event(mevt->evtid))
			mon_event_पढ़ो(&rr, r, d, prgrp, mevt->evtid, true);
	पूर्ण
	kernfs_activate(kn);
	वापस 0;

out_destroy:
	kernfs_हटाओ(kn);
	वापस ret;
पूर्ण

/*
 * Add all subdirectories of mon_data क्रम "ctrl_mon" groups
 * and "monitor" groups with given करोमुख्य id.
 */
व्योम सूची_गढ़ो_mondata_subdir_allrdtgrp(काष्ठा rdt_resource *r,
				    काष्ठा rdt_करोमुख्य *d)
अणु
	काष्ठा kernfs_node *parent_kn;
	काष्ठा rdtgroup *prgrp, *crgrp;
	काष्ठा list_head *head;

	अगर (!r->mon_enabled)
		वापस;

	list_क्रम_each_entry(prgrp, &rdt_all_groups, rdtgroup_list) अणु
		parent_kn = prgrp->mon.mon_data_kn;
		सूची_गढ़ो_mondata_subdir(parent_kn, d, r, prgrp);

		head = &prgrp->mon.crdtgrp_list;
		list_क्रम_each_entry(crgrp, head, mon.crdtgrp_list) अणु
			parent_kn = crgrp->mon.mon_data_kn;
			सूची_गढ़ो_mondata_subdir(parent_kn, d, r, crgrp);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक सूची_गढ़ो_mondata_subdir_allकरोm(काष्ठा kernfs_node *parent_kn,
				       काष्ठा rdt_resource *r,
				       काष्ठा rdtgroup *prgrp)
अणु
	काष्ठा rdt_करोमुख्य *करोm;
	पूर्णांक ret;

	list_क्रम_each_entry(करोm, &r->करोमुख्यs, list) अणु
		ret = सूची_गढ़ो_mondata_subdir(parent_kn, करोm, r, prgrp);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This creates a directory mon_data which contains the monitored data.
 *
 * mon_data has one directory क्रम each करोमुख्य which are named
 * in the क्रमmat mon_<करोमुख्य_name>_<करोमुख्य_id>. For ex: A mon_data
 * with L3 करोमुख्य looks as below:
 * ./mon_data:
 * mon_L3_00
 * mon_L3_01
 * mon_L3_02
 * ...
 *
 * Each करोमुख्य directory has one file per event:
 * ./mon_L3_00/:
 * llc_occupancy
 *
 */
अटल पूर्णांक सूची_गढ़ो_mondata_all(काष्ठा kernfs_node *parent_kn,
			     काष्ठा rdtgroup *prgrp,
			     काष्ठा kernfs_node **dest_kn)
अणु
	काष्ठा rdt_resource *r;
	काष्ठा kernfs_node *kn;
	पूर्णांक ret;

	/*
	 * Create the mon_data directory first.
	 */
	ret = mongroup_create_dir(parent_kn, prgrp, "mon_data", &kn);
	अगर (ret)
		वापस ret;

	अगर (dest_kn)
		*dest_kn = kn;

	/*
	 * Create the subdirectories क्रम each करोमुख्य. Note that all events
	 * in a करोमुख्य like L3 are grouped पूर्णांकo a resource whose करोमुख्य is L3
	 */
	क्रम_each_mon_enabled_rdt_resource(r) अणु
		ret = सूची_गढ़ो_mondata_subdir_allकरोm(kn, r, prgrp);
		अगर (ret)
			जाओ out_destroy;
	पूर्ण

	वापस 0;

out_destroy:
	kernfs_हटाओ(kn);
	वापस ret;
पूर्ण

/**
 * cbm_ensure_valid - Enक्रमce validity on provided CBM
 * @_val:	Candidate CBM
 * @r:		RDT resource to which the CBM beदीर्घs
 *
 * The provided CBM represents all cache portions available क्रम use. This
 * may be represented by a biपंचांगap that करोes not consist of contiguous ones
 * and thus be an invalid CBM.
 * Here the provided CBM is क्रमced to be a valid CBM by only considering
 * the first set of contiguous bits as valid and clearing all bits.
 * The पूर्णांकention here is to provide a valid शेष CBM with which a new
 * resource group is initialized. The user can follow this with a
 * modअगरication to the CBM अगर the शेष करोes not satisfy the
 * requirements.
 */
अटल u32 cbm_ensure_valid(u32 _val, काष्ठा rdt_resource *r)
अणु
	अचिन्हित पूर्णांक cbm_len = r->cache.cbm_len;
	अचिन्हित दीर्घ first_bit, zero_bit;
	अचिन्हित दीर्घ val = _val;

	अगर (!val)
		वापस 0;

	first_bit = find_first_bit(&val, cbm_len);
	zero_bit = find_next_zero_bit(&val, cbm_len, first_bit);

	/* Clear any reमुख्यing bits to ensure contiguous region */
	biपंचांगap_clear(&val, zero_bit, cbm_len - zero_bit);
	वापस (u32)val;
पूर्ण

/*
 * Initialize cache resources per RDT करोमुख्य
 *
 * Set the RDT करोमुख्य up to start off with all usable allocations. That is,
 * all shareable and unused bits. All-zero CBM is invalid.
 */
अटल पूर्णांक __init_one_rdt_करोमुख्य(काष्ठा rdt_करोमुख्य *d, काष्ठा rdt_resource *r,
				 u32 closid)
अणु
	काष्ठा rdt_resource *r_cdp = शून्य;
	काष्ठा rdt_करोमुख्य *d_cdp = शून्य;
	u32 used_b = 0, unused_b = 0;
	अचिन्हित दीर्घ पंचांगp_cbm;
	क्रमागत rdtgrp_mode mode;
	u32 peer_ctl, *ctrl;
	पूर्णांक i;

	rdt_cdp_peer_get(r, d, &r_cdp, &d_cdp);
	d->have_new_ctrl = false;
	d->new_ctrl = r->cache.shareable_bits;
	used_b = r->cache.shareable_bits;
	ctrl = d->ctrl_val;
	क्रम (i = 0; i < closids_supported(); i++, ctrl++) अणु
		अगर (closid_allocated(i) && i != closid) अणु
			mode = rdtgroup_mode_by_closid(i);
			अगर (mode == RDT_MODE_PSEUDO_LOCKSETUP)
				/*
				 * ctrl values क्रम locksetup aren't relevant
				 * until the schemata is written, and the mode
				 * becomes RDT_MODE_PSEUDO_LOCKED.
				 */
				जारी;
			/*
			 * If CDP is active include peer करोमुख्य's
			 * usage to ensure there is no overlap
			 * with an exclusive group.
			 */
			अगर (d_cdp)
				peer_ctl = d_cdp->ctrl_val[i];
			अन्यथा
				peer_ctl = 0;
			used_b |= *ctrl | peer_ctl;
			अगर (mode == RDT_MODE_SHAREABLE)
				d->new_ctrl |= *ctrl | peer_ctl;
		पूर्ण
	पूर्ण
	अगर (d->plr && d->plr->cbm > 0)
		used_b |= d->plr->cbm;
	unused_b = used_b ^ (BIT_MASK(r->cache.cbm_len) - 1);
	unused_b &= BIT_MASK(r->cache.cbm_len) - 1;
	d->new_ctrl |= unused_b;
	/*
	 * Force the initial CBM to be valid, user can
	 * modअगरy the CBM based on प्रणाली availability.
	 */
	d->new_ctrl = cbm_ensure_valid(d->new_ctrl, r);
	/*
	 * Assign the u32 CBM to an अचिन्हित दीर्घ to ensure that
	 * biपंचांगap_weight() करोes not access out-of-bound memory.
	 */
	पंचांगp_cbm = d->new_ctrl;
	अगर (biपंचांगap_weight(&पंचांगp_cbm, r->cache.cbm_len) < r->cache.min_cbm_bits) अणु
		rdt_last_cmd_म_लिखो("No space on %s:%d\n", r->name, d->id);
		वापस -ENOSPC;
	पूर्ण
	d->have_new_ctrl = true;

	वापस 0;
पूर्ण

/*
 * Initialize cache resources with शेष values.
 *
 * A new RDT group is being created on an allocation capable (CAT)
 * supporting प्रणाली. Set this group up to start off with all usable
 * allocations.
 *
 * If there are no more shareable bits available on any करोमुख्य then
 * the entire allocation will fail.
 */
अटल पूर्णांक rdtgroup_init_cat(काष्ठा rdt_resource *r, u32 closid)
अणु
	काष्ठा rdt_करोमुख्य *d;
	पूर्णांक ret;

	list_क्रम_each_entry(d, &r->करोमुख्यs, list) अणु
		ret = __init_one_rdt_करोमुख्य(d, r, closid);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* Initialize MBA resource with शेष values. */
अटल व्योम rdtgroup_init_mba(काष्ठा rdt_resource *r)
अणु
	काष्ठा rdt_करोमुख्य *d;

	list_क्रम_each_entry(d, &r->करोमुख्यs, list) अणु
		d->new_ctrl = is_mba_sc(r) ? MBA_MAX_MBPS : r->शेष_ctrl;
		d->have_new_ctrl = true;
	पूर्ण
पूर्ण

/* Initialize the RDT group's allocations. */
अटल पूर्णांक rdtgroup_init_alloc(काष्ठा rdtgroup *rdtgrp)
अणु
	काष्ठा rdt_resource *r;
	पूर्णांक ret;

	क्रम_each_alloc_enabled_rdt_resource(r) अणु
		अगर (r->rid == RDT_RESOURCE_MBA) अणु
			rdtgroup_init_mba(r);
		पूर्ण अन्यथा अणु
			ret = rdtgroup_init_cat(r, rdtgrp->closid);
			अगर (ret < 0)
				वापस ret;
		पूर्ण

		ret = update_करोमुख्यs(r, rdtgrp->closid);
		अगर (ret < 0) अणु
			rdt_last_cmd_माला_दो("Failed to initialize allocations\n");
			वापस ret;
		पूर्ण

	पूर्ण

	rdtgrp->mode = RDT_MODE_SHAREABLE;

	वापस 0;
पूर्ण

अटल पूर्णांक सूची_गढ़ो_rdt_prepare(काष्ठा kernfs_node *parent_kn,
			     स्थिर अक्षर *name, umode_t mode,
			     क्रमागत rdt_group_type rtype, काष्ठा rdtgroup **r)
अणु
	काष्ठा rdtgroup *prdtgrp, *rdtgrp;
	काष्ठा kernfs_node *kn;
	uपूर्णांक files = 0;
	पूर्णांक ret;

	prdtgrp = rdtgroup_kn_lock_live(parent_kn);
	अगर (!prdtgrp) अणु
		ret = -ENODEV;
		जाओ out_unlock;
	पूर्ण

	अगर (rtype == RDTMON_GROUP &&
	    (prdtgrp->mode == RDT_MODE_PSEUDO_LOCKSETUP ||
	     prdtgrp->mode == RDT_MODE_PSEUDO_LOCKED)) अणु
		ret = -EINVAL;
		rdt_last_cmd_माला_दो("Pseudo-locking in progress\n");
		जाओ out_unlock;
	पूर्ण

	/* allocate the rdtgroup. */
	rdtgrp = kzalloc(माप(*rdtgrp), GFP_KERNEL);
	अगर (!rdtgrp) अणु
		ret = -ENOSPC;
		rdt_last_cmd_माला_दो("Kernel out of memory\n");
		जाओ out_unlock;
	पूर्ण
	*r = rdtgrp;
	rdtgrp->mon.parent = prdtgrp;
	rdtgrp->type = rtype;
	INIT_LIST_HEAD(&rdtgrp->mon.crdtgrp_list);

	/* kernfs creates the directory क्रम rdtgrp */
	kn = kernfs_create_dir(parent_kn, name, mode, rdtgrp);
	अगर (IS_ERR(kn)) अणु
		ret = PTR_ERR(kn);
		rdt_last_cmd_माला_दो("kernfs create error\n");
		जाओ out_मुक्त_rgrp;
	पूर्ण
	rdtgrp->kn = kn;

	/*
	 * kernfs_हटाओ() will drop the reference count on "kn" which
	 * will मुक्त it. But we still need it to stick around क्रम the
	 * rdtgroup_kn_unlock(kn) call. Take one extra reference here,
	 * which will be dropped by kernfs_put() in rdtgroup_हटाओ().
	 */
	kernfs_get(kn);

	ret = rdtgroup_kn_set_ugid(kn);
	अगर (ret) अणु
		rdt_last_cmd_माला_दो("kernfs perm error\n");
		जाओ out_destroy;
	पूर्ण

	files = RFTYPE_BASE | BIT(RF_CTRLSHIFT + rtype);
	ret = rdtgroup_add_files(kn, files);
	अगर (ret) अणु
		rdt_last_cmd_माला_दो("kernfs fill error\n");
		जाओ out_destroy;
	पूर्ण

	अगर (rdt_mon_capable) अणु
		ret = alloc_rmid();
		अगर (ret < 0) अणु
			rdt_last_cmd_माला_दो("Out of RMIDs\n");
			जाओ out_destroy;
		पूर्ण
		rdtgrp->mon.rmid = ret;

		ret = सूची_गढ़ो_mondata_all(kn, rdtgrp, &rdtgrp->mon.mon_data_kn);
		अगर (ret) अणु
			rdt_last_cmd_माला_दो("kernfs subdir error\n");
			जाओ out_idमुक्त;
		पूर्ण
	पूर्ण
	kernfs_activate(kn);

	/*
	 * The caller unlocks the parent_kn upon success.
	 */
	वापस 0;

out_idमुक्त:
	मुक्त_rmid(rdtgrp->mon.rmid);
out_destroy:
	kernfs_put(rdtgrp->kn);
	kernfs_हटाओ(rdtgrp->kn);
out_मुक्त_rgrp:
	kमुक्त(rdtgrp);
out_unlock:
	rdtgroup_kn_unlock(parent_kn);
	वापस ret;
पूर्ण

अटल व्योम सूची_गढ़ो_rdt_prepare_clean(काष्ठा rdtgroup *rgrp)
अणु
	kernfs_हटाओ(rgrp->kn);
	मुक्त_rmid(rgrp->mon.rmid);
	rdtgroup_हटाओ(rgrp);
पूर्ण

/*
 * Create a monitor group under "mon_groups" directory of a control
 * and monitor group(ctrl_mon). This is a resource group
 * to monitor a subset of tasks and cpus in its parent ctrl_mon group.
 */
अटल पूर्णांक rdtgroup_सूची_गढ़ो_mon(काष्ठा kernfs_node *parent_kn,
			      स्थिर अक्षर *name, umode_t mode)
अणु
	काष्ठा rdtgroup *rdtgrp, *prgrp;
	पूर्णांक ret;

	ret = सूची_गढ़ो_rdt_prepare(parent_kn, name, mode, RDTMON_GROUP, &rdtgrp);
	अगर (ret)
		वापस ret;

	prgrp = rdtgrp->mon.parent;
	rdtgrp->closid = prgrp->closid;

	/*
	 * Add the rdtgrp to the list of rdtgrps the parent
	 * ctrl_mon group has to track.
	 */
	list_add_tail(&rdtgrp->mon.crdtgrp_list, &prgrp->mon.crdtgrp_list);

	rdtgroup_kn_unlock(parent_kn);
	वापस ret;
पूर्ण

/*
 * These are rdtgroups created under the root directory. Can be used
 * to allocate and monitor resources.
 */
अटल पूर्णांक rdtgroup_सूची_गढ़ो_ctrl_mon(काष्ठा kernfs_node *parent_kn,
				   स्थिर अक्षर *name, umode_t mode)
अणु
	काष्ठा rdtgroup *rdtgrp;
	काष्ठा kernfs_node *kn;
	u32 closid;
	पूर्णांक ret;

	ret = सूची_गढ़ो_rdt_prepare(parent_kn, name, mode, RDTCTRL_GROUP, &rdtgrp);
	अगर (ret)
		वापस ret;

	kn = rdtgrp->kn;
	ret = closid_alloc();
	अगर (ret < 0) अणु
		rdt_last_cmd_माला_दो("Out of CLOSIDs\n");
		जाओ out_common_fail;
	पूर्ण
	closid = ret;
	ret = 0;

	rdtgrp->closid = closid;
	ret = rdtgroup_init_alloc(rdtgrp);
	अगर (ret < 0)
		जाओ out_id_मुक्त;

	list_add(&rdtgrp->rdtgroup_list, &rdt_all_groups);

	अगर (rdt_mon_capable) अणु
		/*
		 * Create an empty mon_groups directory to hold the subset
		 * of tasks and cpus to monitor.
		 */
		ret = mongroup_create_dir(kn, rdtgrp, "mon_groups", शून्य);
		अगर (ret) अणु
			rdt_last_cmd_माला_दो("kernfs subdir error\n");
			जाओ out_del_list;
		पूर्ण
	पूर्ण

	जाओ out_unlock;

out_del_list:
	list_del(&rdtgrp->rdtgroup_list);
out_id_मुक्त:
	closid_मुक्त(closid);
out_common_fail:
	सूची_गढ़ो_rdt_prepare_clean(rdtgrp);
out_unlock:
	rdtgroup_kn_unlock(parent_kn);
	वापस ret;
पूर्ण

/*
 * We allow creating mon groups only with in a directory called "mon_groups"
 * which is present in every ctrl_mon group. Check अगर this is a valid
 * "mon_groups" directory.
 *
 * 1. The directory should be named "mon_groups".
 * 2. The mon group itself should "not" be named "mon_groups".
 *   This makes sure "mon_groups" directory always has a ctrl_mon group
 *   as parent.
 */
अटल bool is_mon_groups(काष्ठा kernfs_node *kn, स्थिर अक्षर *name)
अणु
	वापस (!म_भेद(kn->name, "mon_groups") &&
		म_भेद(name, "mon_groups"));
पूर्ण

अटल पूर्णांक rdtgroup_सूची_गढ़ो(काष्ठा kernfs_node *parent_kn, स्थिर अक्षर *name,
			  umode_t mode)
अणु
	/* Do not accept '\n' to aव्योम unparsable situation. */
	अगर (म_अक्षर(name, '\n'))
		वापस -EINVAL;

	/*
	 * If the parent directory is the root directory and RDT
	 * allocation is supported, add a control and monitoring
	 * subdirectory
	 */
	अगर (rdt_alloc_capable && parent_kn == rdtgroup_शेष.kn)
		वापस rdtgroup_सूची_गढ़ो_ctrl_mon(parent_kn, name, mode);

	/*
	 * If RDT monitoring is supported and the parent directory is a valid
	 * "mon_groups" directory, add a monitoring subdirectory.
	 */
	अगर (rdt_mon_capable && is_mon_groups(parent_kn, name))
		वापस rdtgroup_सूची_गढ़ो_mon(parent_kn, name, mode);

	वापस -EPERM;
पूर्ण

अटल पूर्णांक rdtgroup_सूची_हटाओ_mon(काष्ठा rdtgroup *rdtgrp, cpumask_var_t पंचांगpmask)
अणु
	काष्ठा rdtgroup *prdtgrp = rdtgrp->mon.parent;
	पूर्णांक cpu;

	/* Give any tasks back to the parent group */
	rdt_move_group_tasks(rdtgrp, prdtgrp, पंचांगpmask);

	/* Update per cpu rmid of the moved CPUs first */
	क्रम_each_cpu(cpu, &rdtgrp->cpu_mask)
		per_cpu(pqr_state.शेष_rmid, cpu) = prdtgrp->mon.rmid;
	/*
	 * Update the MSR on moved CPUs and CPUs which have moved
	 * task running on them.
	 */
	cpumask_or(पंचांगpmask, पंचांगpmask, &rdtgrp->cpu_mask);
	update_closid_rmid(पंचांगpmask, शून्य);

	rdtgrp->flags = RDT_DELETED;
	मुक्त_rmid(rdtgrp->mon.rmid);

	/*
	 * Remove the rdtgrp from the parent ctrl_mon group's list
	 */
	WARN_ON(list_empty(&prdtgrp->mon.crdtgrp_list));
	list_del(&rdtgrp->mon.crdtgrp_list);

	kernfs_हटाओ(rdtgrp->kn);

	वापस 0;
पूर्ण

अटल पूर्णांक rdtgroup_ctrl_हटाओ(काष्ठा rdtgroup *rdtgrp)
अणु
	rdtgrp->flags = RDT_DELETED;
	list_del(&rdtgrp->rdtgroup_list);

	kernfs_हटाओ(rdtgrp->kn);
	वापस 0;
पूर्ण

अटल पूर्णांक rdtgroup_सूची_हटाओ_ctrl(काष्ठा rdtgroup *rdtgrp, cpumask_var_t पंचांगpmask)
अणु
	पूर्णांक cpu;

	/* Give any tasks back to the शेष group */
	rdt_move_group_tasks(rdtgrp, &rdtgroup_शेष, पंचांगpmask);

	/* Give any CPUs back to the शेष group */
	cpumask_or(&rdtgroup_शेष.cpu_mask,
		   &rdtgroup_शेष.cpu_mask, &rdtgrp->cpu_mask);

	/* Update per cpu closid and rmid of the moved CPUs first */
	क्रम_each_cpu(cpu, &rdtgrp->cpu_mask) अणु
		per_cpu(pqr_state.शेष_closid, cpu) = rdtgroup_शेष.closid;
		per_cpu(pqr_state.शेष_rmid, cpu) = rdtgroup_शेष.mon.rmid;
	पूर्ण

	/*
	 * Update the MSR on moved CPUs and CPUs which have moved
	 * task running on them.
	 */
	cpumask_or(पंचांगpmask, पंचांगpmask, &rdtgrp->cpu_mask);
	update_closid_rmid(पंचांगpmask, शून्य);

	closid_मुक्त(rdtgrp->closid);
	मुक्त_rmid(rdtgrp->mon.rmid);

	rdtgroup_ctrl_हटाओ(rdtgrp);

	/*
	 * Free all the child monitor group rmids.
	 */
	मुक्त_all_child_rdtgrp(rdtgrp);

	वापस 0;
पूर्ण

अटल पूर्णांक rdtgroup_सूची_हटाओ(काष्ठा kernfs_node *kn)
अणु
	काष्ठा kernfs_node *parent_kn = kn->parent;
	काष्ठा rdtgroup *rdtgrp;
	cpumask_var_t पंचांगpmask;
	पूर्णांक ret = 0;

	अगर (!zalloc_cpumask_var(&पंचांगpmask, GFP_KERNEL))
		वापस -ENOMEM;

	rdtgrp = rdtgroup_kn_lock_live(kn);
	अगर (!rdtgrp) अणु
		ret = -EPERM;
		जाओ out;
	पूर्ण

	/*
	 * If the rdtgroup is a ctrl_mon group and parent directory
	 * is the root directory, हटाओ the ctrl_mon group.
	 *
	 * If the rdtgroup is a mon group and parent directory
	 * is a valid "mon_groups" directory, हटाओ the mon group.
	 */
	अगर (rdtgrp->type == RDTCTRL_GROUP && parent_kn == rdtgroup_शेष.kn &&
	    rdtgrp != &rdtgroup_शेष) अणु
		अगर (rdtgrp->mode == RDT_MODE_PSEUDO_LOCKSETUP ||
		    rdtgrp->mode == RDT_MODE_PSEUDO_LOCKED) अणु
			ret = rdtgroup_ctrl_हटाओ(rdtgrp);
		पूर्ण अन्यथा अणु
			ret = rdtgroup_सूची_हटाओ_ctrl(rdtgrp, पंचांगpmask);
		पूर्ण
	पूर्ण अन्यथा अगर (rdtgrp->type == RDTMON_GROUP &&
		 is_mon_groups(parent_kn, kn->name)) अणु
		ret = rdtgroup_सूची_हटाओ_mon(rdtgrp, पंचांगpmask);
	पूर्ण अन्यथा अणु
		ret = -EPERM;
	पूर्ण

out:
	rdtgroup_kn_unlock(kn);
	मुक्त_cpumask_var(पंचांगpmask);
	वापस ret;
पूर्ण

अटल पूर्णांक rdtgroup_show_options(काष्ठा seq_file *seq, काष्ठा kernfs_root *kf)
अणु
	अगर (rdt_resources_all[RDT_RESOURCE_L3DATA].alloc_enabled)
		seq_माला_दो(seq, ",cdp");

	अगर (rdt_resources_all[RDT_RESOURCE_L2DATA].alloc_enabled)
		seq_माला_दो(seq, ",cdpl2");

	अगर (is_mba_sc(&rdt_resources_all[RDT_RESOURCE_MBA]))
		seq_माला_दो(seq, ",mba_MBps");

	वापस 0;
पूर्ण

अटल काष्ठा kernfs_syscall_ops rdtgroup_kf_syscall_ops = अणु
	.सूची_गढ़ो		= rdtgroup_सूची_गढ़ो,
	.सूची_हटाओ		= rdtgroup_सूची_हटाओ,
	.show_options	= rdtgroup_show_options,
पूर्ण;

अटल पूर्णांक __init rdtgroup_setup_root(व्योम)
अणु
	पूर्णांक ret;

	rdt_root = kernfs_create_root(&rdtgroup_kf_syscall_ops,
				      KERNFS_ROOT_CREATE_DEACTIVATED |
				      KERNFS_ROOT_EXTRA_OPEN_PERM_CHECK,
				      &rdtgroup_शेष);
	अगर (IS_ERR(rdt_root))
		वापस PTR_ERR(rdt_root);

	mutex_lock(&rdtgroup_mutex);

	rdtgroup_शेष.closid = 0;
	rdtgroup_शेष.mon.rmid = 0;
	rdtgroup_शेष.type = RDTCTRL_GROUP;
	INIT_LIST_HEAD(&rdtgroup_शेष.mon.crdtgrp_list);

	list_add(&rdtgroup_शेष.rdtgroup_list, &rdt_all_groups);

	ret = rdtgroup_add_files(rdt_root->kn, RF_CTRL_BASE);
	अगर (ret) अणु
		kernfs_destroy_root(rdt_root);
		जाओ out;
	पूर्ण

	rdtgroup_शेष.kn = rdt_root->kn;
	kernfs_activate(rdtgroup_शेष.kn);

out:
	mutex_unlock(&rdtgroup_mutex);

	वापस ret;
पूर्ण

/*
 * rdtgroup_init - rdtgroup initialization
 *
 * Setup resctrl file प्रणाली including set up root, create mount poपूर्णांक,
 * रेजिस्टर rdtgroup fileप्रणाली, and initialize files under root directory.
 *
 * Return: 0 on success or -त्रुटि_सं
 */
पूर्णांक __init rdtgroup_init(व्योम)
अणु
	पूर्णांक ret = 0;

	seq_buf_init(&last_cmd_status, last_cmd_status_buf,
		     माप(last_cmd_status_buf));

	ret = rdtgroup_setup_root();
	अगर (ret)
		वापस ret;

	ret = sysfs_create_mount_poपूर्णांक(fs_kobj, "resctrl");
	अगर (ret)
		जाओ cleanup_root;

	ret = रेजिस्टर_fileप्रणाली(&rdt_fs_type);
	अगर (ret)
		जाओ cleanup_mountpoपूर्णांक;

	/*
	 * Adding the resctrl debugfs directory here may not be ideal since
	 * it would let the resctrl debugfs directory appear on the debugfs
	 * fileप्रणाली beक्रमe the resctrl fileप्रणाली is mounted.
	 * It may also be ok since that would enable debugging of RDT beक्रमe
	 * resctrl is mounted.
	 * The reason why the debugfs directory is created here and not in
	 * rdt_get_tree() is because rdt_get_tree() takes rdtgroup_mutex and
	 * during the debugfs directory creation also &sb->s_type->i_mutex_key
	 * (the lockdep class of inode->i_rwsem). Other fileप्रणाली
	 * पूर्णांकeractions (eg. SyS_getdents) have the lock ordering:
	 * &sb->s_type->i_mutex_key --> &mm->mmap_lock
	 * During mmap(), called with &mm->mmap_lock, the rdtgroup_mutex
	 * is taken, thus creating dependency:
	 * &mm->mmap_lock --> rdtgroup_mutex क्रम the latter that can cause
	 * issues considering the other two lock dependencies.
	 * By creating the debugfs directory here we aव्योम a dependency
	 * that may cause deadlock (even though file operations cannot
	 * occur until the fileप्रणाली is mounted, but I करो not know how to
	 * tell lockdep that).
	 */
	debugfs_resctrl = debugfs_create_dir("resctrl", शून्य);

	वापस 0;

cleanup_mountpoपूर्णांक:
	sysfs_हटाओ_mount_poपूर्णांक(fs_kobj, "resctrl");
cleanup_root:
	kernfs_destroy_root(rdt_root);

	वापस ret;
पूर्ण

व्योम __निकास rdtgroup_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(debugfs_resctrl);
	unरेजिस्टर_fileप्रणाली(&rdt_fs_type);
	sysfs_हटाओ_mount_poपूर्णांक(fs_kobj, "resctrl");
	kernfs_destroy_root(rdt_root);
पूर्ण
