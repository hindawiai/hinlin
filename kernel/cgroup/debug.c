<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Debug controller
 *
 * WARNING: This controller is क्रम cgroup core debugging only.
 * Its पूर्णांकerfaces are unstable and subject to changes at any समय.
 */
#समावेश <linux/प्रकार.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>

#समावेश "cgroup-internal.h"

अटल काष्ठा cgroup_subsys_state *
debug_css_alloc(काष्ठा cgroup_subsys_state *parent_css)
अणु
	काष्ठा cgroup_subsys_state *css = kzalloc(माप(*css), GFP_KERNEL);

	अगर (!css)
		वापस ERR_PTR(-ENOMEM);

	वापस css;
पूर्ण

अटल व्योम debug_css_मुक्त(काष्ठा cgroup_subsys_state *css)
अणु
	kमुक्त(css);
पूर्ण

/*
 * debug_taskcount_पढ़ो - वापस the number of tasks in a cgroup.
 * @cgrp: the cgroup in question
 */
अटल u64 debug_taskcount_पढ़ो(काष्ठा cgroup_subsys_state *css,
				काष्ठा cftype *cft)
अणु
	वापस cgroup_task_count(css->cgroup);
पूर्ण

अटल पूर्णांक current_css_set_पढ़ो(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा kernfs_खोलो_file *of = seq->निजी;
	काष्ठा css_set *cset;
	काष्ठा cgroup_subsys *ss;
	काष्ठा cgroup_subsys_state *css;
	पूर्णांक i, refcnt;

	अगर (!cgroup_kn_lock_live(of->kn, false))
		वापस -ENODEV;

	spin_lock_irq(&css_set_lock);
	rcu_पढ़ो_lock();
	cset = task_css_set(current);
	refcnt = refcount_पढ़ो(&cset->refcount);
	seq_म_लिखो(seq, "css_set %pK %d", cset, refcnt);
	अगर (refcnt > cset->nr_tasks)
		seq_म_लिखो(seq, " +%d", refcnt - cset->nr_tasks);
	seq_माला_दो(seq, "\n");

	/*
	 * Prपूर्णांक the css'es stored in the current css_set.
	 */
	क्रम_each_subsys(ss, i) अणु
		css = cset->subsys[ss->id];
		अगर (!css)
			जारी;
		seq_म_लिखो(seq, "%2d: %-4s\t- %p[%d]\n", ss->id, ss->name,
			  css, css->id);
	पूर्ण
	rcu_पढ़ो_unlock();
	spin_unlock_irq(&css_set_lock);
	cgroup_kn_unlock(of->kn);
	वापस 0;
पूर्ण

अटल u64 current_css_set_refcount_पढ़ो(काष्ठा cgroup_subsys_state *css,
					 काष्ठा cftype *cft)
अणु
	u64 count;

	rcu_पढ़ो_lock();
	count = refcount_पढ़ो(&task_css_set(current)->refcount);
	rcu_पढ़ो_unlock();
	वापस count;
पूर्ण

अटल पूर्णांक current_css_set_cg_links_पढ़ो(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा cgrp_cset_link *link;
	काष्ठा css_set *cset;
	अक्षर *name_buf;

	name_buf = kदो_स्मृति(NAME_MAX + 1, GFP_KERNEL);
	अगर (!name_buf)
		वापस -ENOMEM;

	spin_lock_irq(&css_set_lock);
	rcu_पढ़ो_lock();
	cset = task_css_set(current);
	list_क्रम_each_entry(link, &cset->cgrp_links, cgrp_link) अणु
		काष्ठा cgroup *c = link->cgrp;

		cgroup_name(c, name_buf, NAME_MAX + 1);
		seq_म_लिखो(seq, "Root %d group %s\n",
			   c->root->hierarchy_id, name_buf);
	पूर्ण
	rcu_पढ़ो_unlock();
	spin_unlock_irq(&css_set_lock);
	kमुक्त(name_buf);
	वापस 0;
पूर्ण

#घोषणा MAX_TASKS_SHOWN_PER_CSS 25
अटल पूर्णांक cgroup_css_links_पढ़ो(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा cgroup_subsys_state *css = seq_css(seq);
	काष्ठा cgrp_cset_link *link;
	पूर्णांक dead_cnt = 0, extra_refs = 0, thपढ़ोed_csets = 0;

	spin_lock_irq(&css_set_lock);

	list_क्रम_each_entry(link, &css->cgroup->cset_links, cset_link) अणु
		काष्ठा css_set *cset = link->cset;
		काष्ठा task_काष्ठा *task;
		पूर्णांक count = 0;
		पूर्णांक refcnt = refcount_पढ़ो(&cset->refcount);

		/*
		 * Prपूर्णांक out the proc_cset and thपढ़ोed_cset relationship
		 * and highlight dअगरference between refcount and task_count.
		 */
		seq_म_लिखो(seq, "css_set %pK", cset);
		अगर (rcu_dereference_रक्षित(cset->करोm_cset, 1) != cset) अणु
			thपढ़ोed_csets++;
			seq_म_लिखो(seq, "=>%pK", cset->करोm_cset);
		पूर्ण
		अगर (!list_empty(&cset->thपढ़ोed_csets)) अणु
			काष्ठा css_set *tcset;
			पूर्णांक idx = 0;

			list_क्रम_each_entry(tcset, &cset->thपढ़ोed_csets,
					    thपढ़ोed_csets_node) अणु
				seq_माला_दो(seq, idx ? "," : "<=");
				seq_म_लिखो(seq, "%pK", tcset);
				idx++;
			पूर्ण
		पूर्ण अन्यथा अणु
			seq_म_लिखो(seq, " %d", refcnt);
			अगर (refcnt - cset->nr_tasks > 0) अणु
				पूर्णांक extra = refcnt - cset->nr_tasks;

				seq_म_लिखो(seq, " +%d", extra);
				/*
				 * Take out the one additional reference in
				 * init_css_set.
				 */
				अगर (cset == &init_css_set)
					extra--;
				extra_refs += extra;
			पूर्ण
		पूर्ण
		seq_माला_दो(seq, "\n");

		list_क्रम_each_entry(task, &cset->tasks, cg_list) अणु
			अगर (count++ <= MAX_TASKS_SHOWN_PER_CSS)
				seq_म_लिखो(seq, "  task %d\n",
					   task_pid_vnr(task));
		पूर्ण

		list_क्रम_each_entry(task, &cset->mg_tasks, cg_list) अणु
			अगर (count++ <= MAX_TASKS_SHOWN_PER_CSS)
				seq_म_लिखो(seq, "  task %d\n",
					   task_pid_vnr(task));
		पूर्ण
		/* show # of overflowed tasks */
		अगर (count > MAX_TASKS_SHOWN_PER_CSS)
			seq_म_लिखो(seq, "  ... (%d)\n",
				   count - MAX_TASKS_SHOWN_PER_CSS);

		अगर (cset->dead) अणु
			seq_माला_दो(seq, "    [dead]\n");
			dead_cnt++;
		पूर्ण

		WARN_ON(count != cset->nr_tasks);
	पूर्ण
	spin_unlock_irq(&css_set_lock);

	अगर (!dead_cnt && !extra_refs && !thपढ़ोed_csets)
		वापस 0;

	seq_माला_दो(seq, "\n");
	अगर (thपढ़ोed_csets)
		seq_म_लिखो(seq, "threaded css_sets = %d\n", thपढ़ोed_csets);
	अगर (extra_refs)
		seq_म_लिखो(seq, "extra references = %d\n", extra_refs);
	अगर (dead_cnt)
		seq_म_लिखो(seq, "dead css_sets = %d\n", dead_cnt);

	वापस 0;
पूर्ण

अटल पूर्णांक cgroup_subsys_states_पढ़ो(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा kernfs_खोलो_file *of = seq->निजी;
	काष्ठा cgroup *cgrp;
	काष्ठा cgroup_subsys *ss;
	काष्ठा cgroup_subsys_state *css;
	अक्षर pbuf[16];
	पूर्णांक i;

	cgrp = cgroup_kn_lock_live(of->kn, false);
	अगर (!cgrp)
		वापस -ENODEV;

	क्रम_each_subsys(ss, i) अणु
		css = rcu_dereference_check(cgrp->subsys[ss->id], true);
		अगर (!css)
			जारी;

		pbuf[0] = '\0';

		/* Show the parent CSS अगर applicable*/
		अगर (css->parent)
			snम_लिखो(pbuf, माप(pbuf) - 1, " P=%d",
				 css->parent->id);
		seq_म_लिखो(seq, "%2d: %-4s\t- %p[%d] %d%s\n", ss->id, ss->name,
			  css, css->id,
			  atomic_पढ़ो(&css->online_cnt), pbuf);
	पूर्ण

	cgroup_kn_unlock(of->kn);
	वापस 0;
पूर्ण

अटल व्योम cgroup_masks_पढ़ो_one(काष्ठा seq_file *seq, स्थिर अक्षर *name,
				  u16 mask)
अणु
	काष्ठा cgroup_subsys *ss;
	पूर्णांक ssid;
	bool first = true;

	seq_म_लिखो(seq, "%-17s: ", name);
	क्रम_each_subsys(ss, ssid) अणु
		अगर (!(mask & (1 << ssid)))
			जारी;
		अगर (!first)
			seq_माला_दो(seq, ", ");
		seq_माला_दो(seq, ss->name);
		first = false;
	पूर्ण
	seq_अ_दो(seq, '\n');
पूर्ण

अटल पूर्णांक cgroup_masks_पढ़ो(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा kernfs_खोलो_file *of = seq->निजी;
	काष्ठा cgroup *cgrp;

	cgrp = cgroup_kn_lock_live(of->kn, false);
	अगर (!cgrp)
		वापस -ENODEV;

	cgroup_masks_पढ़ो_one(seq, "subtree_control", cgrp->subtree_control);
	cgroup_masks_पढ़ो_one(seq, "subtree_ss_mask", cgrp->subtree_ss_mask);

	cgroup_kn_unlock(of->kn);
	वापस 0;
पूर्ण

अटल u64 releasable_पढ़ो(काष्ठा cgroup_subsys_state *css, काष्ठा cftype *cft)
अणु
	वापस (!cgroup_is_populated(css->cgroup) &&
		!css_has_online_children(&css->cgroup->self));
पूर्ण

अटल काष्ठा cftype debug_legacy_files[] =  अणु
	अणु
		.name = "taskcount",
		.पढ़ो_u64 = debug_taskcount_पढ़ो,
	पूर्ण,

	अणु
		.name = "current_css_set",
		.seq_show = current_css_set_पढ़ो,
		.flags = CFTYPE_ONLY_ON_ROOT,
	पूर्ण,

	अणु
		.name = "current_css_set_refcount",
		.पढ़ो_u64 = current_css_set_refcount_पढ़ो,
		.flags = CFTYPE_ONLY_ON_ROOT,
	पूर्ण,

	अणु
		.name = "current_css_set_cg_links",
		.seq_show = current_css_set_cg_links_पढ़ो,
		.flags = CFTYPE_ONLY_ON_ROOT,
	पूर्ण,

	अणु
		.name = "cgroup_css_links",
		.seq_show = cgroup_css_links_पढ़ो,
	पूर्ण,

	अणु
		.name = "cgroup_subsys_states",
		.seq_show = cgroup_subsys_states_पढ़ो,
	पूर्ण,

	अणु
		.name = "cgroup_masks",
		.seq_show = cgroup_masks_पढ़ो,
	पूर्ण,

	अणु
		.name = "releasable",
		.पढ़ो_u64 = releasable_पढ़ो,
	पूर्ण,

	अणु पूर्ण	/* terminate */
पूर्ण;

अटल काष्ठा cftype debug_files[] =  अणु
	अणु
		.name = "taskcount",
		.पढ़ो_u64 = debug_taskcount_पढ़ो,
	पूर्ण,

	अणु
		.name = "current_css_set",
		.seq_show = current_css_set_पढ़ो,
		.flags = CFTYPE_ONLY_ON_ROOT,
	पूर्ण,

	अणु
		.name = "current_css_set_refcount",
		.पढ़ो_u64 = current_css_set_refcount_पढ़ो,
		.flags = CFTYPE_ONLY_ON_ROOT,
	पूर्ण,

	अणु
		.name = "current_css_set_cg_links",
		.seq_show = current_css_set_cg_links_पढ़ो,
		.flags = CFTYPE_ONLY_ON_ROOT,
	पूर्ण,

	अणु
		.name = "css_links",
		.seq_show = cgroup_css_links_पढ़ो,
	पूर्ण,

	अणु
		.name = "csses",
		.seq_show = cgroup_subsys_states_पढ़ो,
	पूर्ण,

	अणु
		.name = "masks",
		.seq_show = cgroup_masks_पढ़ो,
	पूर्ण,

	अणु पूर्ण	/* terminate */
पूर्ण;

काष्ठा cgroup_subsys debug_cgrp_subsys = अणु
	.css_alloc	= debug_css_alloc,
	.css_मुक्त	= debug_css_मुक्त,
	.legacy_cftypes	= debug_legacy_files,
पूर्ण;

/*
 * On v2, debug is an implicit controller enabled by "cgroup_debug" boot
 * parameter.
 */
व्योम __init enable_debug_cgroup(व्योम)
अणु
	debug_cgrp_subsys.dfl_cftypes = debug_files;
	debug_cgrp_subsys.implicit_on_dfl = true;
	debug_cgrp_subsys.thपढ़ोed = true;
पूर्ण
