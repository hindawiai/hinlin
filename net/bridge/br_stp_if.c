<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Spanning tree protocol; पूर्णांकerface code
 *	Linux ethernet bridge
 *
 *	Authors:
 *	Lennert Buytenhek		<buytenh@gnu.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/kmod.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <net/चयनdev.h>

#समावेश "br_private.h"
#समावेश "br_private_stp.h"


/* Port id is composed of priority and port number.
 * NB: some bits of priority are dropped to
 *     make room क्रम more ports.
 */
अटल अंतरभूत port_id br_make_port_id(__u8 priority, __u16 port_no)
अणु
	वापस ((u16)priority << BR_PORT_BITS)
		| (port_no & ((1<<BR_PORT_BITS)-1));
पूर्ण

#घोषणा BR_MAX_PORT_PRIORITY ((u16)~0 >> BR_PORT_BITS)

/* called under bridge lock */
व्योम br_init_port(काष्ठा net_bridge_port *p)
अणु
	पूर्णांक err;

	p->port_id = br_make_port_id(p->priority, p->port_no);
	br_become_designated_port(p);
	br_set_state(p, BR_STATE_BLOCKING);
	p->topology_change_ack = 0;
	p->config_pending = 0;

	err = __set_ageing_समय(p->dev, p->br->ageing_समय);
	अगर (err)
		netdev_err(p->dev, "failed to offload ageing time\n");
पूर्ण

/* NO locks held */
व्योम br_stp_enable_bridge(काष्ठा net_bridge *br)
अणु
	काष्ठा net_bridge_port *p;

	spin_lock_bh(&br->lock);
	अगर (br->stp_enabled == BR_KERNEL_STP)
		mod_समयr(&br->hello_समयr, jअगरfies + br->hello_समय);
	mod_delayed_work(प्रणाली_दीर्घ_wq, &br->gc_work, HZ / 10);

	br_config_bpdu_generation(br);

	list_क्रम_each_entry(p, &br->port_list, list) अणु
		अगर (netअगर_running(p->dev) && netअगर_oper_up(p->dev))
			br_stp_enable_port(p);

	पूर्ण
	spin_unlock_bh(&br->lock);
पूर्ण

/* NO locks held */
व्योम br_stp_disable_bridge(काष्ठा net_bridge *br)
अणु
	काष्ठा net_bridge_port *p;

	spin_lock_bh(&br->lock);
	list_क्रम_each_entry(p, &br->port_list, list) अणु
		अगर (p->state != BR_STATE_DISABLED)
			br_stp_disable_port(p);

	पूर्ण

	__br_set_topology_change(br, 0);
	br->topology_change_detected = 0;
	spin_unlock_bh(&br->lock);

	del_समयr_sync(&br->hello_समयr);
	del_समयr_sync(&br->topology_change_समयr);
	del_समयr_sync(&br->tcn_समयr);
	cancel_delayed_work_sync(&br->gc_work);
पूर्ण

/* called under bridge lock */
व्योम br_stp_enable_port(काष्ठा net_bridge_port *p)
अणु
	br_init_port(p);
	br_port_state_selection(p->br);
	br_अगरinfo_notअगरy(RTM_NEWLINK, शून्य, p);
पूर्ण

/* called under bridge lock */
व्योम br_stp_disable_port(काष्ठा net_bridge_port *p)
अणु
	काष्ठा net_bridge *br = p->br;
	पूर्णांक wasroot;

	wasroot = br_is_root_bridge(br);
	br_become_designated_port(p);
	br_set_state(p, BR_STATE_DISABLED);
	p->topology_change_ack = 0;
	p->config_pending = 0;

	br_अगरinfo_notअगरy(RTM_NEWLINK, शून्य, p);

	del_समयr(&p->message_age_समयr);
	del_समयr(&p->क्रमward_delay_समयr);
	del_समयr(&p->hold_समयr);

	अगर (!rcu_access_poपूर्णांकer(p->backup_port))
		br_fdb_delete_by_port(br, p, 0, 0);
	br_multicast_disable_port(p);

	br_configuration_update(br);

	br_port_state_selection(br);

	अगर (br_is_root_bridge(br) && !wasroot)
		br_become_root_bridge(br);
पूर्ण

अटल पूर्णांक br_stp_call_user(काष्ठा net_bridge *br, अक्षर *arg)
अणु
	अक्षर *argv[] = अणु BR_STP_PROG, br->dev->name, arg, शून्य पूर्ण;
	अक्षर *envp[] = अणु शून्य पूर्ण;
	पूर्णांक rc;

	/* call userspace STP and report program errors */
	rc = call_usermodehelper(BR_STP_PROG, argv, envp, UMH_WAIT_PROC);
	अगर (rc > 0) अणु
		अगर (rc & 0xff)
			br_debug(br, BR_STP_PROG " received signal %d\n",
				 rc & 0x7f);
		अन्यथा
			br_debug(br, BR_STP_PROG " exited with code %d\n",
				 (rc >> 8) & 0xff);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम br_stp_start(काष्ठा net_bridge *br)
अणु
	पूर्णांक err = -ENOENT;

	अगर (net_eq(dev_net(br->dev), &init_net))
		err = br_stp_call_user(br, "start");

	अगर (err && err != -ENOENT)
		br_err(br, "failed to start userspace STP (%d)\n", err);

	spin_lock_bh(&br->lock);

	अगर (br->bridge_क्रमward_delay < BR_MIN_FORWARD_DELAY)
		__br_set_क्रमward_delay(br, BR_MIN_FORWARD_DELAY);
	अन्यथा अगर (br->bridge_क्रमward_delay > BR_MAX_FORWARD_DELAY)
		__br_set_क्रमward_delay(br, BR_MAX_FORWARD_DELAY);

	अगर (!err) अणु
		br->stp_enabled = BR_USER_STP;
		br_debug(br, "userspace STP started\n");
	पूर्ण अन्यथा अणु
		br->stp_enabled = BR_KERNEL_STP;
		br_debug(br, "using kernel STP\n");

		/* To start समयrs on any ports left in blocking */
		अगर (br->dev->flags & IFF_UP)
			mod_समयr(&br->hello_समयr, jअगरfies + br->hello_समय);
		br_port_state_selection(br);
	पूर्ण

	spin_unlock_bh(&br->lock);
पूर्ण

अटल व्योम br_stp_stop(काष्ठा net_bridge *br)
अणु
	पूर्णांक err;

	अगर (br->stp_enabled == BR_USER_STP) अणु
		err = br_stp_call_user(br, "stop");
		अगर (err)
			br_err(br, "failed to stop userspace STP (%d)\n", err);

		/* To start समयrs on any ports left in blocking */
		spin_lock_bh(&br->lock);
		br_port_state_selection(br);
		spin_unlock_bh(&br->lock);
	पूर्ण

	br->stp_enabled = BR_NO_STP;
पूर्ण

पूर्णांक br_stp_set_enabled(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
		       काष्ठा netlink_ext_ack *extack)
अणु
	ASSERT_RTNL();

	अगर (br_mrp_enabled(br)) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "STP can't be enabled if MRP is already enabled");
		वापस -EINVAL;
	पूर्ण

	अगर (val) अणु
		अगर (br->stp_enabled == BR_NO_STP)
			br_stp_start(br);
	पूर्ण अन्यथा अणु
		अगर (br->stp_enabled != BR_NO_STP)
			br_stp_stop(br);
	पूर्ण

	वापस 0;
पूर्ण

/* called under bridge lock */
व्योम br_stp_change_bridge_id(काष्ठा net_bridge *br, स्थिर अचिन्हित अक्षर *addr)
अणु
	/* should be aligned on 2 bytes क्रम ether_addr_equal() */
	अचिन्हित लघु oldaddr_aligned[ETH_ALEN >> 1];
	अचिन्हित अक्षर *oldaddr = (अचिन्हित अक्षर *)oldaddr_aligned;
	काष्ठा net_bridge_port *p;
	पूर्णांक wasroot;

	wasroot = br_is_root_bridge(br);

	br_fdb_change_mac_address(br, addr);

	स_नकल(oldaddr, br->bridge_id.addr, ETH_ALEN);
	स_नकल(br->bridge_id.addr, addr, ETH_ALEN);
	स_नकल(br->dev->dev_addr, addr, ETH_ALEN);

	list_क्रम_each_entry(p, &br->port_list, list) अणु
		अगर (ether_addr_equal(p->designated_bridge.addr, oldaddr))
			स_नकल(p->designated_bridge.addr, addr, ETH_ALEN);

		अगर (ether_addr_equal(p->designated_root.addr, oldaddr))
			स_नकल(p->designated_root.addr, addr, ETH_ALEN);
	पूर्ण

	br_configuration_update(br);
	br_port_state_selection(br);
	अगर (br_is_root_bridge(br) && !wasroot)
		br_become_root_bridge(br);
पूर्ण

/* should be aligned on 2 bytes क्रम ether_addr_equal() */
अटल स्थिर अचिन्हित लघु br_mac_zero_aligned[ETH_ALEN >> 1];

/* called under bridge lock */
bool br_stp_recalculate_bridge_id(काष्ठा net_bridge *br)
अणु
	स्थिर अचिन्हित अक्षर *br_mac_zero =
			(स्थिर अचिन्हित अक्षर *)br_mac_zero_aligned;
	स्थिर अचिन्हित अक्षर *addr = br_mac_zero;
	काष्ठा net_bridge_port *p;

	/* user has chosen a value so keep it */
	अगर (br->dev->addr_assign_type == NET_ADDR_SET)
		वापस false;

	list_क्रम_each_entry(p, &br->port_list, list) अणु
		अगर (addr == br_mac_zero ||
		    स_भेद(p->dev->dev_addr, addr, ETH_ALEN) < 0)
			addr = p->dev->dev_addr;

	पूर्ण

	अगर (ether_addr_equal(br->bridge_id.addr, addr))
		वापस false;	/* no change */

	br_stp_change_bridge_id(br, addr);
	वापस true;
पूर्ण

/* Acquires and releases bridge lock */
व्योम br_stp_set_bridge_priority(काष्ठा net_bridge *br, u16 newprio)
अणु
	काष्ठा net_bridge_port *p;
	पूर्णांक wasroot;

	spin_lock_bh(&br->lock);
	wasroot = br_is_root_bridge(br);

	list_क्रम_each_entry(p, &br->port_list, list) अणु
		अगर (p->state != BR_STATE_DISABLED &&
		    br_is_designated_port(p)) अणु
			p->designated_bridge.prio[0] = (newprio >> 8) & 0xFF;
			p->designated_bridge.prio[1] = newprio & 0xFF;
		पूर्ण

	पूर्ण

	br->bridge_id.prio[0] = (newprio >> 8) & 0xFF;
	br->bridge_id.prio[1] = newprio & 0xFF;
	br_configuration_update(br);
	br_port_state_selection(br);
	अगर (br_is_root_bridge(br) && !wasroot)
		br_become_root_bridge(br);
	spin_unlock_bh(&br->lock);
पूर्ण

/* called under bridge lock */
पूर्णांक br_stp_set_port_priority(काष्ठा net_bridge_port *p, अचिन्हित दीर्घ newprio)
अणु
	port_id new_port_id;

	अगर (newprio > BR_MAX_PORT_PRIORITY)
		वापस -दुस्फल;

	new_port_id = br_make_port_id(newprio, p->port_no);
	अगर (br_is_designated_port(p))
		p->designated_port = new_port_id;

	p->port_id = new_port_id;
	p->priority = newprio;
	अगर (!स_भेद(&p->br->bridge_id, &p->designated_bridge, 8) &&
	    p->port_id < p->designated_port) अणु
		br_become_designated_port(p);
		br_port_state_selection(p->br);
	पूर्ण

	वापस 0;
पूर्ण

/* called under bridge lock */
पूर्णांक br_stp_set_path_cost(काष्ठा net_bridge_port *p, अचिन्हित दीर्घ path_cost)
अणु
	अगर (path_cost < BR_MIN_PATH_COST ||
	    path_cost > BR_MAX_PATH_COST)
		वापस -दुस्फल;

	p->flags |= BR_ADMIN_COST;
	p->path_cost = path_cost;
	br_configuration_update(p->br);
	br_port_state_selection(p->br);
	वापस 0;
पूर्ण

sमाप_प्रकार br_show_bridge_id(अक्षर *buf, स्थिर काष्ठा bridge_id *id)
अणु
	वापस प्र_लिखो(buf, "%.2x%.2x.%.2x%.2x%.2x%.2x%.2x%.2x\n",
	       id->prio[0], id->prio[1],
	       id->addr[0], id->addr[1], id->addr[2],
	       id->addr[3], id->addr[4], id->addr[5]);
पूर्ण
