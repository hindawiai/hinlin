<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Ioctl handler
 *	Linux ethernet bridge
 *
 *	Authors:
 *	Lennert Buytenhek		<buytenh@gnu.org>
 */

#समावेश <linux/capability.h>
#समावेश <linux/kernel.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/बार.h>
#समावेश <net/net_namespace.h>
#समावेश <linux/uaccess.h>
#समावेश "br_private.h"

अटल पूर्णांक get_bridge_अगरindices(काष्ठा net *net, पूर्णांक *indices, पूर्णांक num)
अणु
	काष्ठा net_device *dev;
	पूर्णांक i = 0;

	rcu_पढ़ो_lock();
	क्रम_each_netdev_rcu(net, dev) अणु
		अगर (i >= num)
			अवरोध;
		अगर (dev->priv_flags & IFF_EBRIDGE)
			indices[i++] = dev->अगरindex;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस i;
पूर्ण

/* called with RTNL */
अटल व्योम get_port_अगरindices(काष्ठा net_bridge *br, पूर्णांक *अगरindices, पूर्णांक num)
अणु
	काष्ठा net_bridge_port *p;

	list_क्रम_each_entry(p, &br->port_list, list) अणु
		अगर (p->port_no < num)
			अगरindices[p->port_no] = p->dev->अगरindex;
	पूर्ण
पूर्ण

/*
 * Format up to a page worth of क्रमwarding table entries
 * userbuf -- where to copy result
 * maxnum  -- maximum number of entries desired
 *            (limited to a page क्रम sanity)
 * offset  -- number of records to skip
 */
अटल पूर्णांक get_fdb_entries(काष्ठा net_bridge *br, व्योम __user *userbuf,
			   अचिन्हित दीर्घ maxnum, अचिन्हित दीर्घ offset)
अणु
	पूर्णांक num;
	व्योम *buf;
	माप_प्रकार size;

	/* Clamp size to PAGE_SIZE, test maxnum to aव्योम overflow */
	अगर (maxnum > PAGE_SIZE/माप(काष्ठा __fdb_entry))
		maxnum = PAGE_SIZE/माप(काष्ठा __fdb_entry);

	size = maxnum * माप(काष्ठा __fdb_entry);

	buf = kदो_स्मृति(size, GFP_USER);
	अगर (!buf)
		वापस -ENOMEM;

	num = br_fdb_fillbuf(br, buf, maxnum, offset);
	अगर (num > 0) अणु
		अगर (copy_to_user(userbuf, buf, num*माप(काष्ठा __fdb_entry)))
			num = -EFAULT;
	पूर्ण
	kमुक्त(buf);

	वापस num;
पूर्ण

/* called with RTNL */
अटल पूर्णांक add_del_अगर(काष्ठा net_bridge *br, पूर्णांक अगरindex, पूर्णांक isadd)
अणु
	काष्ठा net *net = dev_net(br->dev);
	काष्ठा net_device *dev;
	पूर्णांक ret;

	अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

	dev = __dev_get_by_index(net, अगरindex);
	अगर (dev == शून्य)
		वापस -EINVAL;

	अगर (isadd)
		ret = br_add_अगर(br, dev, शून्य);
	अन्यथा
		ret = br_del_अगर(br, dev);

	वापस ret;
पूर्ण

/*
 * Legacy ioctl's through SIOCDEVPRIVATE
 * This पूर्णांकerface is deprecated because it was too dअगरficult
 * to करो the translation क्रम 32/64bit ioctl compatibility.
 */
अटल पूर्णांक old_dev_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा net_bridge *br = netdev_priv(dev);
	काष्ठा net_bridge_port *p = शून्य;
	अचिन्हित दीर्घ args[4];
	पूर्णांक ret = -EOPNOTSUPP;

	अगर (copy_from_user(args, rq->अगरr_data, माप(args)))
		वापस -EFAULT;

	चयन (args[0]) अणु
	हाल BRCTL_ADD_IF:
	हाल BRCTL_DEL_IF:
		वापस add_del_अगर(br, args[1], args[0] == BRCTL_ADD_IF);

	हाल BRCTL_GET_BRIDGE_INFO:
	अणु
		काष्ठा __bridge_info b;

		स_रखो(&b, 0, माप(काष्ठा __bridge_info));
		rcu_पढ़ो_lock();
		स_नकल(&b.designated_root, &br->designated_root, 8);
		स_नकल(&b.bridge_id, &br->bridge_id, 8);
		b.root_path_cost = br->root_path_cost;
		b.max_age = jअगरfies_to_घड़ी_प्रकार(br->max_age);
		b.hello_समय = jअगरfies_to_घड़ी_प्रकार(br->hello_समय);
		b.क्रमward_delay = br->क्रमward_delay;
		b.bridge_max_age = br->bridge_max_age;
		b.bridge_hello_समय = br->bridge_hello_समय;
		b.bridge_क्रमward_delay = jअगरfies_to_घड़ी_प्रकार(br->bridge_क्रमward_delay);
		b.topology_change = br->topology_change;
		b.topology_change_detected = br->topology_change_detected;
		b.root_port = br->root_port;

		b.stp_enabled = (br->stp_enabled != BR_NO_STP);
		b.ageing_समय = jअगरfies_to_घड़ी_प्रकार(br->ageing_समय);
		b.hello_समयr_value = br_समयr_value(&br->hello_समयr);
		b.tcn_समयr_value = br_समयr_value(&br->tcn_समयr);
		b.topology_change_समयr_value = br_समयr_value(&br->topology_change_समयr);
		b.gc_समयr_value = br_समयr_value(&br->gc_work.समयr);
		rcu_पढ़ो_unlock();

		अगर (copy_to_user((व्योम __user *)args[1], &b, माप(b)))
			वापस -EFAULT;

		वापस 0;
	पूर्ण

	हाल BRCTL_GET_PORT_LIST:
	अणु
		पूर्णांक num, *indices;

		num = args[2];
		अगर (num < 0)
			वापस -EINVAL;
		अगर (num == 0)
			num = 256;
		अगर (num > BR_MAX_PORTS)
			num = BR_MAX_PORTS;

		indices = kसुस्मृति(num, माप(पूर्णांक), GFP_KERNEL);
		अगर (indices == शून्य)
			वापस -ENOMEM;

		get_port_अगरindices(br, indices, num);
		अगर (copy_to_user((व्योम __user *)args[1], indices, num*माप(पूर्णांक)))
			num =  -EFAULT;
		kमुक्त(indices);
		वापस num;
	पूर्ण

	हाल BRCTL_SET_BRIDGE_FORWARD_DELAY:
		अगर (!ns_capable(dev_net(dev)->user_ns, CAP_NET_ADMIN))
			वापस -EPERM;

		ret = br_set_क्रमward_delay(br, args[1]);
		अवरोध;

	हाल BRCTL_SET_BRIDGE_HELLO_TIME:
		अगर (!ns_capable(dev_net(dev)->user_ns, CAP_NET_ADMIN))
			वापस -EPERM;

		ret = br_set_hello_समय(br, args[1]);
		अवरोध;

	हाल BRCTL_SET_BRIDGE_MAX_AGE:
		अगर (!ns_capable(dev_net(dev)->user_ns, CAP_NET_ADMIN))
			वापस -EPERM;

		ret = br_set_max_age(br, args[1]);
		अवरोध;

	हाल BRCTL_SET_AGEING_TIME:
		अगर (!ns_capable(dev_net(dev)->user_ns, CAP_NET_ADMIN))
			वापस -EPERM;

		ret = br_set_ageing_समय(br, args[1]);
		अवरोध;

	हाल BRCTL_GET_PORT_INFO:
	अणु
		काष्ठा __port_info p;
		काष्ठा net_bridge_port *pt;

		rcu_पढ़ो_lock();
		अगर ((pt = br_get_port(br, args[2])) == शून्य) अणु
			rcu_पढ़ो_unlock();
			वापस -EINVAL;
		पूर्ण

		स_रखो(&p, 0, माप(काष्ठा __port_info));
		स_नकल(&p.designated_root, &pt->designated_root, 8);
		स_नकल(&p.designated_bridge, &pt->designated_bridge, 8);
		p.port_id = pt->port_id;
		p.designated_port = pt->designated_port;
		p.path_cost = pt->path_cost;
		p.designated_cost = pt->designated_cost;
		p.state = pt->state;
		p.top_change_ack = pt->topology_change_ack;
		p.config_pending = pt->config_pending;
		p.message_age_समयr_value = br_समयr_value(&pt->message_age_समयr);
		p.क्रमward_delay_समयr_value = br_समयr_value(&pt->क्रमward_delay_समयr);
		p.hold_समयr_value = br_समयr_value(&pt->hold_समयr);

		rcu_पढ़ो_unlock();

		अगर (copy_to_user((व्योम __user *)args[1], &p, माप(p)))
			वापस -EFAULT;

		वापस 0;
	पूर्ण

	हाल BRCTL_SET_BRIDGE_STP_STATE:
		अगर (!ns_capable(dev_net(dev)->user_ns, CAP_NET_ADMIN))
			वापस -EPERM;

		ret = br_stp_set_enabled(br, args[1], शून्य);
		अवरोध;

	हाल BRCTL_SET_BRIDGE_PRIORITY:
		अगर (!ns_capable(dev_net(dev)->user_ns, CAP_NET_ADMIN))
			वापस -EPERM;

		br_stp_set_bridge_priority(br, args[1]);
		ret = 0;
		अवरोध;

	हाल BRCTL_SET_PORT_PRIORITY:
	अणु
		अगर (!ns_capable(dev_net(dev)->user_ns, CAP_NET_ADMIN))
			वापस -EPERM;

		spin_lock_bh(&br->lock);
		अगर ((p = br_get_port(br, args[1])) == शून्य)
			ret = -EINVAL;
		अन्यथा
			ret = br_stp_set_port_priority(p, args[2]);
		spin_unlock_bh(&br->lock);
		अवरोध;
	पूर्ण

	हाल BRCTL_SET_PATH_COST:
	अणु
		अगर (!ns_capable(dev_net(dev)->user_ns, CAP_NET_ADMIN))
			वापस -EPERM;

		spin_lock_bh(&br->lock);
		अगर ((p = br_get_port(br, args[1])) == शून्य)
			ret = -EINVAL;
		अन्यथा
			ret = br_stp_set_path_cost(p, args[2]);
		spin_unlock_bh(&br->lock);
		अवरोध;
	पूर्ण

	हाल BRCTL_GET_FDB_ENTRIES:
		वापस get_fdb_entries(br, (व्योम __user *)args[1],
				       args[2], args[3]);
	पूर्ण

	अगर (!ret) अणु
		अगर (p)
			br_अगरinfo_notअगरy(RTM_NEWLINK, शून्य, p);
		अन्यथा
			netdev_state_change(br->dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक old_deviceless(काष्ठा net *net, व्योम __user *uarg)
अणु
	अचिन्हित दीर्घ args[3];

	अगर (copy_from_user(args, uarg, माप(args)))
		वापस -EFAULT;

	चयन (args[0]) अणु
	हाल BRCTL_GET_VERSION:
		वापस BRCTL_VERSION;

	हाल BRCTL_GET_BRIDGES:
	अणु
		पूर्णांक *indices;
		पूर्णांक ret = 0;

		अगर (args[2] >= 2048)
			वापस -ENOMEM;
		indices = kसुस्मृति(args[2], माप(पूर्णांक), GFP_KERNEL);
		अगर (indices == शून्य)
			वापस -ENOMEM;

		args[2] = get_bridge_अगरindices(net, indices, args[2]);

		ret = copy_to_user((व्योम __user *)args[1], indices, args[2]*माप(पूर्णांक))
			? -EFAULT : args[2];

		kमुक्त(indices);
		वापस ret;
	पूर्ण

	हाल BRCTL_ADD_BRIDGE:
	हाल BRCTL_DEL_BRIDGE:
	अणु
		अक्षर buf[IFNAMSIZ];

		अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			वापस -EPERM;

		अगर (copy_from_user(buf, (व्योम __user *)args[1], IFNAMSIZ))
			वापस -EFAULT;

		buf[IFNAMSIZ-1] = 0;

		अगर (args[0] == BRCTL_ADD_BRIDGE)
			वापस br_add_bridge(net, buf);

		वापस br_del_bridge(net, buf);
	पूर्ण
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

पूर्णांक br_ioctl_deviceless_stub(काष्ठा net *net, अचिन्हित पूर्णांक cmd, व्योम __user *uarg)
अणु
	चयन (cmd) अणु
	हाल SIOCGIFBR:
	हाल SIOCSIFBR:
		वापस old_deviceless(net, uarg);

	हाल SIOCBRADDBR:
	हाल SIOCBRDELBR:
	अणु
		अक्षर buf[IFNAMSIZ];

		अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			वापस -EPERM;

		अगर (copy_from_user(buf, uarg, IFNAMSIZ))
			वापस -EFAULT;

		buf[IFNAMSIZ-1] = 0;
		अगर (cmd == SIOCBRADDBR)
			वापस br_add_bridge(net, buf);

		वापस br_del_bridge(net, buf);
	पूर्ण
	पूर्ण
	वापस -EOPNOTSUPP;
पूर्ण

पूर्णांक br_dev_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा net_bridge *br = netdev_priv(dev);

	चयन (cmd) अणु
	हाल SIOCDEVPRIVATE:
		वापस old_dev_ioctl(dev, rq, cmd);

	हाल SIOCBRADDIF:
	हाल SIOCBRDELIF:
		वापस add_del_अगर(br, rq->अगरr_अगरindex, cmd == SIOCBRADDIF);

	पूर्ण

	br_debug(br, "Bridge does not support ioctl 0x%x\n", cmd);
	वापस -EOPNOTSUPP;
पूर्ण
