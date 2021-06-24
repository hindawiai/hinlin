<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/core/netprio_cgroup.c	Priority Control Group
 *
 * Authors:	Neil Horman <nhorman@tuxdriver.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/cgroup.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/atomic.h>
#समावेश <linux/sched/task.h>

#समावेश <net/rtnetlink.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/sock.h>
#समावेश <net/netprio_cgroup.h>

#समावेश <linux/fdtable.h>

/*
 * netprio allocates per-net_device priomap array which is indexed by
 * css->id.  Limiting css ID to 16bits करोesn't lose anything.
 */
#घोषणा NETPRIO_ID_MAX		अच_लघु_उच्च

#घोषणा PRIOMAP_MIN_SZ		128

/*
 * Extend @dev->priomap so that it's large enough to accommodate
 * @target_idx.  @dev->priomap.priomap_len > @target_idx after successful
 * वापस.  Must be called under rtnl lock.
 */
अटल पूर्णांक extend_netdev_table(काष्ठा net_device *dev, u32 target_idx)
अणु
	काष्ठा netprio_map *old, *new;
	माप_प्रकार new_sz, new_len;

	/* is the existing priomap large enough? */
	old = rtnl_dereference(dev->priomap);
	अगर (old && old->priomap_len > target_idx)
		वापस 0;

	/*
	 * Determine the new size.  Let's keep it घातer-of-two.  We start
	 * from PRIOMAP_MIN_SZ and द्विगुन it until it's large enough to
	 * accommodate @target_idx.
	 */
	new_sz = PRIOMAP_MIN_SZ;
	जबतक (true) अणु
		new_len = (new_sz - दुरत्व(काष्ठा netprio_map, priomap)) /
			माप(new->priomap[0]);
		अगर (new_len > target_idx)
			अवरोध;
		new_sz *= 2;
		/* overflowed? */
		अगर (WARN_ON(new_sz < PRIOMAP_MIN_SZ))
			वापस -ENOSPC;
	पूर्ण

	/* allocate & copy */
	new = kzalloc(new_sz, GFP_KERNEL);
	अगर (!new)
		वापस -ENOMEM;

	अगर (old)
		स_नकल(new->priomap, old->priomap,
		       old->priomap_len * माप(old->priomap[0]));

	new->priomap_len = new_len;

	/* install the new priomap */
	rcu_assign_poपूर्णांकer(dev->priomap, new);
	अगर (old)
		kमुक्त_rcu(old, rcu);
	वापस 0;
पूर्ण

/**
 * netprio_prio - वापस the effective netprio of a cgroup-net_device pair
 * @css: css part of the target pair
 * @dev: net_device part of the target pair
 *
 * Should be called under RCU पढ़ो or rtnl lock.
 */
अटल u32 netprio_prio(काष्ठा cgroup_subsys_state *css, काष्ठा net_device *dev)
अणु
	काष्ठा netprio_map *map = rcu_dereference_rtnl(dev->priomap);
	पूर्णांक id = css->id;

	अगर (map && id < map->priomap_len)
		वापस map->priomap[id];
	वापस 0;
पूर्ण

/**
 * netprio_set_prio - set netprio on a cgroup-net_device pair
 * @css: css part of the target pair
 * @dev: net_device part of the target pair
 * @prio: prio to set
 *
 * Set netprio to @prio on @css-@dev pair.  Should be called under rtnl
 * lock and may fail under memory pressure क्रम non-zero @prio.
 */
अटल पूर्णांक netprio_set_prio(काष्ठा cgroup_subsys_state *css,
			    काष्ठा net_device *dev, u32 prio)
अणु
	काष्ठा netprio_map *map;
	पूर्णांक id = css->id;
	पूर्णांक ret;

	/* aव्योम extending priomap क्रम zero ग_लिखोs */
	map = rtnl_dereference(dev->priomap);
	अगर (!prio && (!map || map->priomap_len <= id))
		वापस 0;

	ret = extend_netdev_table(dev, id);
	अगर (ret)
		वापस ret;

	map = rtnl_dereference(dev->priomap);
	map->priomap[id] = prio;
	वापस 0;
पूर्ण

अटल काष्ठा cgroup_subsys_state *
cgrp_css_alloc(काष्ठा cgroup_subsys_state *parent_css)
अणु
	काष्ठा cgroup_subsys_state *css;

	css = kzalloc(माप(*css), GFP_KERNEL);
	अगर (!css)
		वापस ERR_PTR(-ENOMEM);

	वापस css;
पूर्ण

अटल पूर्णांक cgrp_css_online(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा cgroup_subsys_state *parent_css = css->parent;
	काष्ठा net_device *dev;
	पूर्णांक ret = 0;

	अगर (css->id > NETPRIO_ID_MAX)
		वापस -ENOSPC;

	अगर (!parent_css)
		वापस 0;

	rtnl_lock();
	/*
	 * Inherit prios from the parent.  As all prios are set during
	 * onlining, there is no need to clear them on offline.
	 */
	क्रम_each_netdev(&init_net, dev) अणु
		u32 prio = netprio_prio(parent_css, dev);

		ret = netprio_set_prio(css, dev, prio);
		अगर (ret)
			अवरोध;
	पूर्ण
	rtnl_unlock();
	वापस ret;
पूर्ण

अटल व्योम cgrp_css_मुक्त(काष्ठा cgroup_subsys_state *css)
अणु
	kमुक्त(css);
पूर्ण

अटल u64 पढ़ो_prioidx(काष्ठा cgroup_subsys_state *css, काष्ठा cftype *cft)
अणु
	वापस css->id;
पूर्ण

अटल पूर्णांक पढ़ो_priomap(काष्ठा seq_file *sf, व्योम *v)
अणु
	काष्ठा net_device *dev;

	rcu_पढ़ो_lock();
	क्रम_each_netdev_rcu(&init_net, dev)
		seq_म_लिखो(sf, "%s %u\n", dev->name,
			   netprio_prio(seq_css(sf), dev));
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

अटल sमाप_प्रकार ग_लिखो_priomap(काष्ठा kernfs_खोलो_file *of,
			     अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	अक्षर devname[IFNAMSIZ + 1];
	काष्ठा net_device *dev;
	u32 prio;
	पूर्णांक ret;

	अगर (माला_पूछो(buf, "%"__stringअगरy(IFNAMSIZ)"s %u", devname, &prio) != 2)
		वापस -EINVAL;

	dev = dev_get_by_name(&init_net, devname);
	अगर (!dev)
		वापस -ENODEV;

	cgroup_sk_alloc_disable();

	rtnl_lock();

	ret = netprio_set_prio(of_css(of), dev, prio);

	rtnl_unlock();
	dev_put(dev);
	वापस ret ?: nbytes;
पूर्ण

अटल पूर्णांक update_netprio(स्थिर व्योम *v, काष्ठा file *file, अचिन्हित n)
अणु
	काष्ठा socket *sock = sock_from_file(file);
	अगर (sock) अणु
		spin_lock(&cgroup_sk_update_lock);
		sock_cgroup_set_prioidx(&sock->sk->sk_cgrp_data,
					(अचिन्हित दीर्घ)v);
		spin_unlock(&cgroup_sk_update_lock);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम net_prio_attach(काष्ठा cgroup_taskset *tset)
अणु
	काष्ठा task_काष्ठा *p;
	काष्ठा cgroup_subsys_state *css;

	cgroup_sk_alloc_disable();

	cgroup_taskset_क्रम_each(p, css, tset) अणु
		व्योम *v = (व्योम *)(अचिन्हित दीर्घ)css->id;

		task_lock(p);
		iterate_fd(p->files, 0, update_netprio, v);
		task_unlock(p);
	पूर्ण
पूर्ण

अटल काष्ठा cftype ss_files[] = अणु
	अणु
		.name = "prioidx",
		.पढ़ो_u64 = पढ़ो_prioidx,
	पूर्ण,
	अणु
		.name = "ifpriomap",
		.seq_show = पढ़ो_priomap,
		.ग_लिखो = ग_लिखो_priomap,
	पूर्ण,
	अणु पूर्ण	/* terminate */
पूर्ण;

काष्ठा cgroup_subsys net_prio_cgrp_subsys = अणु
	.css_alloc	= cgrp_css_alloc,
	.css_online	= cgrp_css_online,
	.css_मुक्त	= cgrp_css_मुक्त,
	.attach		= net_prio_attach,
	.legacy_cftypes	= ss_files,
पूर्ण;

अटल पूर्णांक netprio_device_event(काष्ठा notअगरier_block *unused,
				अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा netprio_map *old;

	/*
	 * Note this is called with rtnl_lock held so we have update side
	 * protection on our rcu assignments
	 */

	चयन (event) अणु
	हाल NETDEV_UNREGISTER:
		old = rtnl_dereference(dev->priomap);
		RCU_INIT_POINTER(dev->priomap, शून्य);
		अगर (old)
			kमुक्त_rcu(old, rcu);
		अवरोध;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block netprio_device_notअगरier = अणु
	.notअगरier_call = netprio_device_event
पूर्ण;

अटल पूर्णांक __init init_cgroup_netprio(व्योम)
अणु
	रेजिस्टर_netdevice_notअगरier(&netprio_device_notअगरier);
	वापस 0;
पूर्ण
subsys_initcall(init_cgroup_netprio);
