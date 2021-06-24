<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Sysfs attributes of bridge ports
 *	Linux ethernet bridge
 *
 *	Authors:
 *	Stephen Hemminger		<shemminger@osdl.org>
 */

#समावेश <linux/capability.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sched/संकेत.स>

#समावेश "br_private.h"

/* IMPORTANT: new bridge port options must be added with netlink support only
 *            please करो not add new sysfs entries
 */

काष्ठा brport_attribute अणु
	काष्ठा attribute	attr;
	sमाप_प्रकार (*show)(काष्ठा net_bridge_port *, अक्षर *);
	पूर्णांक (*store)(काष्ठा net_bridge_port *, अचिन्हित दीर्घ);
	पूर्णांक (*store_raw)(काष्ठा net_bridge_port *, अक्षर *);
पूर्ण;

#घोषणा BRPORT_ATTR_RAW(_name, _mode, _show, _store)			\
स्थिर काष्ठा brport_attribute brport_attr_##_name = अणु			\
	.attr		= अणु.name = __stringअगरy(_name),			\
			   .mode = _mode पूर्ण,				\
	.show		= _show,					\
	.store_raw	= _store,					\
पूर्ण;

#घोषणा BRPORT_ATTR(_name, _mode, _show, _store)		\
स्थिर काष्ठा brport_attribute brport_attr_##_name = अणु 	        \
	.attr = अणु.name = __stringअगरy(_name), 			\
		 .mode = _mode पूर्ण,				\
	.show	= _show,					\
	.store	= _store,					\
पूर्ण;

#घोषणा BRPORT_ATTR_FLAG(_name, _mask)				\
अटल sमाप_प्रकार show_##_name(काष्ठा net_bridge_port *p, अक्षर *buf) \
अणु								\
	वापस प्र_लिखो(buf, "%d\n", !!(p->flags & _mask));	\
पूर्ण								\
अटल पूर्णांक store_##_name(काष्ठा net_bridge_port *p, अचिन्हित दीर्घ v) \
अणु								\
	वापस store_flag(p, v, _mask);				\
पूर्ण								\
अटल BRPORT_ATTR(_name, 0644,					\
		   show_##_name, store_##_name)

अटल पूर्णांक store_flag(काष्ठा net_bridge_port *p, अचिन्हित दीर्घ v,
		      अचिन्हित दीर्घ mask)
अणु
	काष्ठा netlink_ext_ack extack = अणु0पूर्ण;
	अचिन्हित दीर्घ flags = p->flags;
	पूर्णांक err;

	अगर (v)
		flags |= mask;
	अन्यथा
		flags &= ~mask;

	अगर (flags != p->flags) अणु
		err = br_चयनdev_set_port_flag(p, flags, mask, &extack);
		अगर (err) अणु
			netdev_err(p->dev, "%s\n", extack._msg);
			वापस err;
		पूर्ण

		p->flags = flags;
		br_port_flags_change(p, mask);
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार show_path_cost(काष्ठा net_bridge_port *p, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", p->path_cost);
पूर्ण

अटल BRPORT_ATTR(path_cost, 0644,
		   show_path_cost, br_stp_set_path_cost);

अटल sमाप_प्रकार show_priority(काष्ठा net_bridge_port *p, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", p->priority);
पूर्ण

अटल BRPORT_ATTR(priority, 0644,
			 show_priority, br_stp_set_port_priority);

अटल sमाप_प्रकार show_designated_root(काष्ठा net_bridge_port *p, अक्षर *buf)
अणु
	वापस br_show_bridge_id(buf, &p->designated_root);
पूर्ण
अटल BRPORT_ATTR(designated_root, 0444, show_designated_root, शून्य);

अटल sमाप_प्रकार show_designated_bridge(काष्ठा net_bridge_port *p, अक्षर *buf)
अणु
	वापस br_show_bridge_id(buf, &p->designated_bridge);
पूर्ण
अटल BRPORT_ATTR(designated_bridge, 0444, show_designated_bridge, शून्य);

अटल sमाप_प्रकार show_designated_port(काष्ठा net_bridge_port *p, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", p->designated_port);
पूर्ण
अटल BRPORT_ATTR(designated_port, 0444, show_designated_port, शून्य);

अटल sमाप_प्रकार show_designated_cost(काष्ठा net_bridge_port *p, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", p->designated_cost);
पूर्ण
अटल BRPORT_ATTR(designated_cost, 0444, show_designated_cost, शून्य);

अटल sमाप_प्रकार show_port_id(काष्ठा net_bridge_port *p, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "0x%x\n", p->port_id);
पूर्ण
अटल BRPORT_ATTR(port_id, 0444, show_port_id, शून्य);

अटल sमाप_प्रकार show_port_no(काष्ठा net_bridge_port *p, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "0x%x\n", p->port_no);
पूर्ण

अटल BRPORT_ATTR(port_no, 0444, show_port_no, शून्य);

अटल sमाप_प्रकार show_change_ack(काष्ठा net_bridge_port *p, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", p->topology_change_ack);
पूर्ण
अटल BRPORT_ATTR(change_ack, 0444, show_change_ack, शून्य);

अटल sमाप_प्रकार show_config_pending(काष्ठा net_bridge_port *p, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", p->config_pending);
पूर्ण
अटल BRPORT_ATTR(config_pending, 0444, show_config_pending, शून्य);

अटल sमाप_प्रकार show_port_state(काष्ठा net_bridge_port *p, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", p->state);
पूर्ण
अटल BRPORT_ATTR(state, 0444, show_port_state, शून्य);

अटल sमाप_प्रकार show_message_age_समयr(काष्ठा net_bridge_port *p,
					    अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%ld\n", br_समयr_value(&p->message_age_समयr));
पूर्ण
अटल BRPORT_ATTR(message_age_समयr, 0444, show_message_age_समयr, शून्य);

अटल sमाप_प्रकार show_क्रमward_delay_समयr(काष्ठा net_bridge_port *p,
					    अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%ld\n", br_समयr_value(&p->क्रमward_delay_समयr));
पूर्ण
अटल BRPORT_ATTR(क्रमward_delay_समयr, 0444, show_क्रमward_delay_समयr, शून्य);

अटल sमाप_प्रकार show_hold_समयr(काष्ठा net_bridge_port *p,
					    अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%ld\n", br_समयr_value(&p->hold_समयr));
पूर्ण
अटल BRPORT_ATTR(hold_समयr, 0444, show_hold_समयr, शून्य);

अटल पूर्णांक store_flush(काष्ठा net_bridge_port *p, अचिन्हित दीर्घ v)
अणु
	br_fdb_delete_by_port(p->br, p, 0, 0); // Don't delete local entry
	वापस 0;
पूर्ण
अटल BRPORT_ATTR(flush, 0200, शून्य, store_flush);

अटल sमाप_प्रकार show_group_fwd_mask(काष्ठा net_bridge_port *p, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%#x\n", p->group_fwd_mask);
पूर्ण

अटल पूर्णांक store_group_fwd_mask(काष्ठा net_bridge_port *p,
				अचिन्हित दीर्घ v)
अणु
	अगर (v & BR_GROUPFWD_MACPAUSE)
		वापस -EINVAL;
	p->group_fwd_mask = v;

	वापस 0;
पूर्ण
अटल BRPORT_ATTR(group_fwd_mask, 0644, show_group_fwd_mask,
		   store_group_fwd_mask);

अटल sमाप_प्रकार show_backup_port(काष्ठा net_bridge_port *p, अक्षर *buf)
अणु
	काष्ठा net_bridge_port *backup_p;
	पूर्णांक ret = 0;

	rcu_पढ़ो_lock();
	backup_p = rcu_dereference(p->backup_port);
	अगर (backup_p)
		ret = प्र_लिखो(buf, "%s\n", backup_p->dev->name);
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल पूर्णांक store_backup_port(काष्ठा net_bridge_port *p, अक्षर *buf)
अणु
	काष्ठा net_device *backup_dev = शून्य;
	अक्षर *nl = म_अक्षर(buf, '\n');

	अगर (nl)
		*nl = '\0';

	अगर (म_माप(buf) > 0) अणु
		backup_dev = __dev_get_by_name(dev_net(p->dev), buf);
		अगर (!backup_dev)
			वापस -ENOENT;
	पूर्ण

	वापस nbp_backup_change(p, backup_dev);
पूर्ण
अटल BRPORT_ATTR_RAW(backup_port, 0644, show_backup_port, store_backup_port);

BRPORT_ATTR_FLAG(hairpin_mode, BR_HAIRPIN_MODE);
BRPORT_ATTR_FLAG(bpdu_guard, BR_BPDU_GUARD);
BRPORT_ATTR_FLAG(root_block, BR_ROOT_BLOCK);
BRPORT_ATTR_FLAG(learning, BR_LEARNING);
BRPORT_ATTR_FLAG(unicast_flood, BR_FLOOD);
BRPORT_ATTR_FLAG(proxyarp, BR_PROXYARP);
BRPORT_ATTR_FLAG(proxyarp_wअगरi, BR_PROXYARP_WIFI);
BRPORT_ATTR_FLAG(multicast_flood, BR_MCAST_FLOOD);
BRPORT_ATTR_FLAG(broadcast_flood, BR_BCAST_FLOOD);
BRPORT_ATTR_FLAG(neigh_suppress, BR_NEIGH_SUPPRESS);
BRPORT_ATTR_FLAG(isolated, BR_ISOLATED);

#अगर_घोषित CONFIG_BRIDGE_IGMP_SNOOPING
अटल sमाप_प्रकार show_multicast_router(काष्ठा net_bridge_port *p, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", p->multicast_router);
पूर्ण

अटल पूर्णांक store_multicast_router(काष्ठा net_bridge_port *p,
				      अचिन्हित दीर्घ v)
अणु
	वापस br_multicast_set_port_router(p, v);
पूर्ण
अटल BRPORT_ATTR(multicast_router, 0644, show_multicast_router,
		   store_multicast_router);

BRPORT_ATTR_FLAG(multicast_fast_leave, BR_MULTICAST_FAST_LEAVE);
BRPORT_ATTR_FLAG(multicast_to_unicast, BR_MULTICAST_TO_UNICAST);
#पूर्ण_अगर

अटल स्थिर काष्ठा brport_attribute *brport_attrs[] = अणु
	&brport_attr_path_cost,
	&brport_attr_priority,
	&brport_attr_port_id,
	&brport_attr_port_no,
	&brport_attr_designated_root,
	&brport_attr_designated_bridge,
	&brport_attr_designated_port,
	&brport_attr_designated_cost,
	&brport_attr_state,
	&brport_attr_change_ack,
	&brport_attr_config_pending,
	&brport_attr_message_age_समयr,
	&brport_attr_क्रमward_delay_समयr,
	&brport_attr_hold_समयr,
	&brport_attr_flush,
	&brport_attr_hairpin_mode,
	&brport_attr_bpdu_guard,
	&brport_attr_root_block,
	&brport_attr_learning,
	&brport_attr_unicast_flood,
#अगर_घोषित CONFIG_BRIDGE_IGMP_SNOOPING
	&brport_attr_multicast_router,
	&brport_attr_multicast_fast_leave,
	&brport_attr_multicast_to_unicast,
#पूर्ण_अगर
	&brport_attr_proxyarp,
	&brport_attr_proxyarp_wअगरi,
	&brport_attr_multicast_flood,
	&brport_attr_broadcast_flood,
	&brport_attr_group_fwd_mask,
	&brport_attr_neigh_suppress,
	&brport_attr_isolated,
	&brport_attr_backup_port,
	शून्य
पूर्ण;

#घोषणा to_brport_attr(_at) container_of(_at, काष्ठा brport_attribute, attr)

अटल sमाप_प्रकार brport_show(काष्ठा kobject *kobj,
			   काष्ठा attribute *attr, अक्षर *buf)
अणु
	काष्ठा brport_attribute *brport_attr = to_brport_attr(attr);
	काष्ठा net_bridge_port *p = kobj_to_brport(kobj);

	अगर (!brport_attr->show)
		वापस -EINVAL;

	वापस brport_attr->show(p, buf);
पूर्ण

अटल sमाप_प्रकार brport_store(काष्ठा kobject *kobj,
			    काष्ठा attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा brport_attribute *brport_attr = to_brport_attr(attr);
	काष्ठा net_bridge_port *p = kobj_to_brport(kobj);
	sमाप_प्रकार ret = -EINVAL;
	अचिन्हित दीर्घ val;
	अक्षर *endp;

	अगर (!ns_capable(dev_net(p->dev)->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (!rtnl_trylock())
		वापस restart_syscall();

	अगर (brport_attr->store_raw) अणु
		अक्षर *buf_copy;

		buf_copy = kstrndup(buf, count, GFP_KERNEL);
		अगर (!buf_copy) अणु
			ret = -ENOMEM;
			जाओ out_unlock;
		पूर्ण
		spin_lock_bh(&p->br->lock);
		ret = brport_attr->store_raw(p, buf_copy);
		spin_unlock_bh(&p->br->lock);
		kमुक्त(buf_copy);
	पूर्ण अन्यथा अगर (brport_attr->store) अणु
		val = simple_म_से_अदीर्घ(buf, &endp, 0);
		अगर (endp == buf)
			जाओ out_unlock;
		spin_lock_bh(&p->br->lock);
		ret = brport_attr->store(p, val);
		spin_unlock_bh(&p->br->lock);
	पूर्ण

	अगर (!ret) अणु
		br_अगरinfo_notअगरy(RTM_NEWLINK, शून्य, p);
		ret = count;
	पूर्ण
out_unlock:
	rtnl_unlock();

	वापस ret;
पूर्ण

स्थिर काष्ठा sysfs_ops brport_sysfs_ops = अणु
	.show = brport_show,
	.store = brport_store,
पूर्ण;

/*
 * Add sysfs entries to ethernet device added to a bridge.
 * Creates a brport subdirectory with bridge attributes.
 * Puts symlink in bridge's brअगर subdirectory
 */
पूर्णांक br_sysfs_addअगर(काष्ठा net_bridge_port *p)
अणु
	काष्ठा net_bridge *br = p->br;
	स्थिर काष्ठा brport_attribute **a;
	पूर्णांक err;

	err = sysfs_create_link(&p->kobj, &br->dev->dev.kobj,
				SYSFS_BRIDGE_PORT_LINK);
	अगर (err)
		वापस err;

	क्रम (a = brport_attrs; *a; ++a) अणु
		err = sysfs_create_file(&p->kobj, &((*a)->attr));
		अगर (err)
			वापस err;
	पूर्ण

	strlcpy(p->sysfs_name, p->dev->name, IFNAMSIZ);
	वापस sysfs_create_link(br->अगरobj, &p->kobj, p->sysfs_name);
पूर्ण

/* Rename bridge's brअगर symlink */
पूर्णांक br_sysfs_नामअगर(काष्ठा net_bridge_port *p)
अणु
	काष्ठा net_bridge *br = p->br;
	पूर्णांक err;

	/* If a नाम fails, the rollback will cause another
	 * नाम call with the existing name.
	 */
	अगर (!म_भेदन(p->sysfs_name, p->dev->name, IFNAMSIZ))
		वापस 0;

	err = sysfs_नाम_link(br->अगरobj, &p->kobj,
				p->sysfs_name, p->dev->name);
	अगर (err)
		netdev_notice(br->dev, "unable to rename link %s to %s",
			      p->sysfs_name, p->dev->name);
	अन्यथा
		strlcpy(p->sysfs_name, p->dev->name, IFNAMSIZ);

	वापस err;
पूर्ण
