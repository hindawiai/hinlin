<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/core/netclassid_cgroup.c	Classid Cgroupfs Handling
 *
 * Authors:	Thomas Graf <tgraf@suug.ch>
 */

#समावेश <linux/slab.h>
#समावेश <linux/cgroup.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/sched/task.h>

#समावेश <net/cls_cgroup.h>
#समावेश <net/sock.h>

अटल अंतरभूत काष्ठा cgroup_cls_state *css_cls_state(काष्ठा cgroup_subsys_state *css)
अणु
	वापस css ? container_of(css, काष्ठा cgroup_cls_state, css) : शून्य;
पूर्ण

काष्ठा cgroup_cls_state *task_cls_state(काष्ठा task_काष्ठा *p)
अणु
	वापस css_cls_state(task_css_check(p, net_cls_cgrp_id,
					    rcu_पढ़ो_lock_bh_held()));
पूर्ण
EXPORT_SYMBOL_GPL(task_cls_state);

अटल काष्ठा cgroup_subsys_state *
cgrp_css_alloc(काष्ठा cgroup_subsys_state *parent_css)
अणु
	काष्ठा cgroup_cls_state *cs;

	cs = kzalloc(माप(*cs), GFP_KERNEL);
	अगर (!cs)
		वापस ERR_PTR(-ENOMEM);

	वापस &cs->css;
पूर्ण

अटल पूर्णांक cgrp_css_online(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा cgroup_cls_state *cs = css_cls_state(css);
	काष्ठा cgroup_cls_state *parent = css_cls_state(css->parent);

	अगर (parent)
		cs->classid = parent->classid;

	वापस 0;
पूर्ण

अटल व्योम cgrp_css_मुक्त(काष्ठा cgroup_subsys_state *css)
अणु
	kमुक्त(css_cls_state(css));
पूर्ण

/*
 * To aव्योम मुक्तzing of sockets creation क्रम tasks with big number of thपढ़ोs
 * and खोलोed sockets lets release file_lock every 1000 iterated descriptors.
 * New sockets will alपढ़ोy have been created with new classid.
 */

काष्ठा update_classid_context अणु
	u32 classid;
	अचिन्हित पूर्णांक batch;
पूर्ण;

#घोषणा UPDATE_CLASSID_BATCH 1000

अटल पूर्णांक update_classid_sock(स्थिर व्योम *v, काष्ठा file *file, अचिन्हित n)
अणु
	काष्ठा update_classid_context *ctx = (व्योम *)v;
	काष्ठा socket *sock = sock_from_file(file);

	अगर (sock) अणु
		spin_lock(&cgroup_sk_update_lock);
		sock_cgroup_set_classid(&sock->sk->sk_cgrp_data, ctx->classid);
		spin_unlock(&cgroup_sk_update_lock);
	पूर्ण
	अगर (--ctx->batch == 0) अणु
		ctx->batch = UPDATE_CLASSID_BATCH;
		वापस n + 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम update_classid_task(काष्ठा task_काष्ठा *p, u32 classid)
अणु
	काष्ठा update_classid_context ctx = अणु
		.classid = classid,
		.batch = UPDATE_CLASSID_BATCH
	पूर्ण;
	अचिन्हित पूर्णांक fd = 0;

	करो अणु
		task_lock(p);
		fd = iterate_fd(p->files, fd, update_classid_sock, &ctx);
		task_unlock(p);
		cond_resched();
	पूर्ण जबतक (fd);
पूर्ण

अटल व्योम cgrp_attach(काष्ठा cgroup_taskset *tset)
अणु
	काष्ठा cgroup_subsys_state *css;
	काष्ठा task_काष्ठा *p;

	cgroup_taskset_क्रम_each(p, css, tset) अणु
		update_classid_task(p, css_cls_state(css)->classid);
	पूर्ण
पूर्ण

अटल u64 पढ़ो_classid(काष्ठा cgroup_subsys_state *css, काष्ठा cftype *cft)
अणु
	वापस css_cls_state(css)->classid;
पूर्ण

अटल पूर्णांक ग_लिखो_classid(काष्ठा cgroup_subsys_state *css, काष्ठा cftype *cft,
			 u64 value)
अणु
	काष्ठा cgroup_cls_state *cs = css_cls_state(css);
	काष्ठा css_task_iter it;
	काष्ठा task_काष्ठा *p;

	cgroup_sk_alloc_disable();

	cs->classid = (u32)value;

	css_task_iter_start(css, 0, &it);
	जबतक ((p = css_task_iter_next(&it)))
		update_classid_task(p, cs->classid);
	css_task_iter_end(&it);

	वापस 0;
पूर्ण

अटल काष्ठा cftype ss_files[] = अणु
	अणु
		.name		= "classid",
		.पढ़ो_u64	= पढ़ो_classid,
		.ग_लिखो_u64	= ग_लिखो_classid,
	पूर्ण,
	अणु पूर्ण	/* terminate */
पूर्ण;

काष्ठा cgroup_subsys net_cls_cgrp_subsys = अणु
	.css_alloc		= cgrp_css_alloc,
	.css_online		= cgrp_css_online,
	.css_मुक्त		= cgrp_css_मुक्त,
	.attach			= cgrp_attach,
	.legacy_cftypes		= ss_files,
पूर्ण;
