<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Spanning tree protocol; generic parts
 *	Linux ethernet bridge
 *
 *	Authors:
 *	Lennert Buytenhek		<buytenh@gnu.org>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/rculist.h>
#समावेश <net/चयनdev.h>

#समावेश "br_private.h"
#समावेश "br_private_stp.h"

/* since समय values in bpdu are in jअगरfies and then scaled (1/256)
 * beक्रमe sending, make sure that is at least one STP tick.
 */
#घोषणा MESSAGE_AGE_INCR	((HZ / 256) + 1)

अटल स्थिर अक्षर *स्थिर br_port_state_names[] = अणु
	[BR_STATE_DISABLED] = "disabled",
	[BR_STATE_LISTENING] = "listening",
	[BR_STATE_LEARNING] = "learning",
	[BR_STATE_FORWARDING] = "forwarding",
	[BR_STATE_BLOCKING] = "blocking",
पूर्ण;

व्योम br_set_state(काष्ठा net_bridge_port *p, अचिन्हित पूर्णांक state)
अणु
	काष्ठा चयनdev_attr attr = अणु
		.orig_dev = p->dev,
		.id = SWITCHDEV_ATTR_ID_PORT_STP_STATE,
		.flags = SWITCHDEV_F_DEFER,
		.u.stp_state = state,
	पूर्ण;
	पूर्णांक err;

	/* Don't change the state of the ports अगर they are driven by a dअगरferent
	 * protocol.
	 */
	अगर (p->flags & BR_MRP_AWARE)
		वापस;

	p->state = state;
	err = चयनdev_port_attr_set(p->dev, &attr, शून्य);
	अगर (err && err != -EOPNOTSUPP)
		br_warn(p->br, "error setting offload STP state on port %u(%s)\n",
				(अचिन्हित पूर्णांक) p->port_no, p->dev->name);
	अन्यथा
		br_info(p->br, "port %u(%s) entered %s state\n",
				(अचिन्हित पूर्णांक) p->port_no, p->dev->name,
				br_port_state_names[p->state]);

	अगर (p->br->stp_enabled == BR_KERNEL_STP) अणु
		चयन (p->state) अणु
		हाल BR_STATE_BLOCKING:
			p->stp_xstats.transition_blk++;
			अवरोध;
		हाल BR_STATE_FORWARDING:
			p->stp_xstats.transition_fwd++;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

u8 br_port_get_stp_state(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा net_bridge_port *p;

	ASSERT_RTNL();

	p = br_port_get_rtnl(dev);
	अगर (!p)
		वापस BR_STATE_DISABLED;

	वापस p->state;
पूर्ण
EXPORT_SYMBOL_GPL(br_port_get_stp_state);

/* called under bridge lock */
काष्ठा net_bridge_port *br_get_port(काष्ठा net_bridge *br, u16 port_no)
अणु
	काष्ठा net_bridge_port *p;

	list_क्रम_each_entry_rcu(p, &br->port_list, list,
				lockdep_is_held(&br->lock)) अणु
		अगर (p->port_no == port_no)
			वापस p;
	पूर्ण

	वापस शून्य;
पूर्ण

/* called under bridge lock */
अटल पूर्णांक br_should_become_root_port(स्थिर काष्ठा net_bridge_port *p,
				      u16 root_port)
अणु
	काष्ठा net_bridge *br;
	काष्ठा net_bridge_port *rp;
	पूर्णांक t;

	br = p->br;
	अगर (p->state == BR_STATE_DISABLED ||
	    br_is_designated_port(p))
		वापस 0;

	अगर (स_भेद(&br->bridge_id, &p->designated_root, 8) <= 0)
		वापस 0;

	अगर (!root_port)
		वापस 1;

	rp = br_get_port(br, root_port);

	t = स_भेद(&p->designated_root, &rp->designated_root, 8);
	अगर (t < 0)
		वापस 1;
	अन्यथा अगर (t > 0)
		वापस 0;

	अगर (p->designated_cost + p->path_cost <
	    rp->designated_cost + rp->path_cost)
		वापस 1;
	अन्यथा अगर (p->designated_cost + p->path_cost >
		 rp->designated_cost + rp->path_cost)
		वापस 0;

	t = स_भेद(&p->designated_bridge, &rp->designated_bridge, 8);
	अगर (t < 0)
		वापस 1;
	अन्यथा अगर (t > 0)
		वापस 0;

	अगर (p->designated_port < rp->designated_port)
		वापस 1;
	अन्यथा अगर (p->designated_port > rp->designated_port)
		वापस 0;

	अगर (p->port_id < rp->port_id)
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम br_root_port_block(स्थिर काष्ठा net_bridge *br,
			       काष्ठा net_bridge_port *p)
अणु

	br_notice(br, "port %u(%s) tried to become root port (blocked)",
		  (अचिन्हित पूर्णांक) p->port_no, p->dev->name);

	br_set_state(p, BR_STATE_LISTENING);
	br_अगरinfo_notअगरy(RTM_NEWLINK, शून्य, p);

	अगर (br->क्रमward_delay > 0)
		mod_समयr(&p->क्रमward_delay_समयr, jअगरfies + br->क्रमward_delay);
पूर्ण

/* called under bridge lock */
अटल व्योम br_root_selection(काष्ठा net_bridge *br)
अणु
	काष्ठा net_bridge_port *p;
	u16 root_port = 0;

	list_क्रम_each_entry(p, &br->port_list, list) अणु
		अगर (!br_should_become_root_port(p, root_port))
			जारी;

		अगर (p->flags & BR_ROOT_BLOCK)
			br_root_port_block(br, p);
		अन्यथा
			root_port = p->port_no;
	पूर्ण

	br->root_port = root_port;

	अगर (!root_port) अणु
		br->designated_root = br->bridge_id;
		br->root_path_cost = 0;
	पूर्ण अन्यथा अणु
		p = br_get_port(br, root_port);
		br->designated_root = p->designated_root;
		br->root_path_cost = p->designated_cost + p->path_cost;
	पूर्ण
पूर्ण

/* called under bridge lock */
व्योम br_become_root_bridge(काष्ठा net_bridge *br)
अणु
	br->max_age = br->bridge_max_age;
	br->hello_समय = br->bridge_hello_समय;
	br->क्रमward_delay = br->bridge_क्रमward_delay;
	br_topology_change_detection(br);
	del_समयr(&br->tcn_समयr);

	अगर (br->dev->flags & IFF_UP) अणु
		br_config_bpdu_generation(br);
		mod_समयr(&br->hello_समयr, jअगरfies + br->hello_समय);
	पूर्ण
पूर्ण

/* called under bridge lock */
व्योम br_transmit_config(काष्ठा net_bridge_port *p)
अणु
	काष्ठा br_config_bpdu bpdu;
	काष्ठा net_bridge *br;

	अगर (समयr_pending(&p->hold_समयr)) अणु
		p->config_pending = 1;
		वापस;
	पूर्ण

	br = p->br;

	bpdu.topology_change = br->topology_change;
	bpdu.topology_change_ack = p->topology_change_ack;
	bpdu.root = br->designated_root;
	bpdu.root_path_cost = br->root_path_cost;
	bpdu.bridge_id = br->bridge_id;
	bpdu.port_id = p->port_id;
	अगर (br_is_root_bridge(br))
		bpdu.message_age = 0;
	अन्यथा अणु
		काष्ठा net_bridge_port *root
			= br_get_port(br, br->root_port);
		bpdu.message_age = (jअगरfies - root->designated_age)
			+ MESSAGE_AGE_INCR;
	पूर्ण
	bpdu.max_age = br->max_age;
	bpdu.hello_समय = br->hello_समय;
	bpdu.क्रमward_delay = br->क्रमward_delay;

	अगर (bpdu.message_age < br->max_age) अणु
		br_send_config_bpdu(p, &bpdu);
		p->topology_change_ack = 0;
		p->config_pending = 0;
		अगर (p->br->stp_enabled == BR_KERNEL_STP)
			mod_समयr(&p->hold_समयr,
				  round_jअगरfies(jअगरfies + BR_HOLD_TIME));
	पूर्ण
पूर्ण

/* called under bridge lock */
अटल व्योम br_record_config_inक्रमmation(काष्ठा net_bridge_port *p,
					 स्थिर काष्ठा br_config_bpdu *bpdu)
अणु
	p->designated_root = bpdu->root;
	p->designated_cost = bpdu->root_path_cost;
	p->designated_bridge = bpdu->bridge_id;
	p->designated_port = bpdu->port_id;
	p->designated_age = jअगरfies - bpdu->message_age;

	mod_समयr(&p->message_age_समयr, jअगरfies
		  + (bpdu->max_age - bpdu->message_age));
पूर्ण

/* called under bridge lock */
अटल व्योम br_record_config_समयout_values(काष्ठा net_bridge *br,
					    स्थिर काष्ठा br_config_bpdu *bpdu)
अणु
	br->max_age = bpdu->max_age;
	br->hello_समय = bpdu->hello_समय;
	br->क्रमward_delay = bpdu->क्रमward_delay;
	__br_set_topology_change(br, bpdu->topology_change);
पूर्ण

/* called under bridge lock */
व्योम br_transmit_tcn(काष्ठा net_bridge *br)
अणु
	काष्ठा net_bridge_port *p;

	p = br_get_port(br, br->root_port);
	अगर (p)
		br_send_tcn_bpdu(p);
	अन्यथा
		br_notice(br, "root port %u not found for topology notice\n",
			  br->root_port);
पूर्ण

/* called under bridge lock */
अटल पूर्णांक br_should_become_designated_port(स्थिर काष्ठा net_bridge_port *p)
अणु
	काष्ठा net_bridge *br;
	पूर्णांक t;

	br = p->br;
	अगर (br_is_designated_port(p))
		वापस 1;

	अगर (स_भेद(&p->designated_root, &br->designated_root, 8))
		वापस 1;

	अगर (br->root_path_cost < p->designated_cost)
		वापस 1;
	अन्यथा अगर (br->root_path_cost > p->designated_cost)
		वापस 0;

	t = स_भेद(&br->bridge_id, &p->designated_bridge, 8);
	अगर (t < 0)
		वापस 1;
	अन्यथा अगर (t > 0)
		वापस 0;

	अगर (p->port_id < p->designated_port)
		वापस 1;

	वापस 0;
पूर्ण

/* called under bridge lock */
अटल व्योम br_designated_port_selection(काष्ठा net_bridge *br)
अणु
	काष्ठा net_bridge_port *p;

	list_क्रम_each_entry(p, &br->port_list, list) अणु
		अगर (p->state != BR_STATE_DISABLED &&
		    br_should_become_designated_port(p))
			br_become_designated_port(p);

	पूर्ण
पूर्ण

/* called under bridge lock */
अटल पूर्णांक br_supersedes_port_info(स्थिर काष्ठा net_bridge_port *p,
				   स्थिर काष्ठा br_config_bpdu *bpdu)
अणु
	पूर्णांक t;

	t = स_भेद(&bpdu->root, &p->designated_root, 8);
	अगर (t < 0)
		वापस 1;
	अन्यथा अगर (t > 0)
		वापस 0;

	अगर (bpdu->root_path_cost < p->designated_cost)
		वापस 1;
	अन्यथा अगर (bpdu->root_path_cost > p->designated_cost)
		वापस 0;

	t = स_भेद(&bpdu->bridge_id, &p->designated_bridge, 8);
	अगर (t < 0)
		वापस 1;
	अन्यथा अगर (t > 0)
		वापस 0;

	अगर (स_भेद(&bpdu->bridge_id, &p->br->bridge_id, 8))
		वापस 1;

	अगर (bpdu->port_id <= p->designated_port)
		वापस 1;

	वापस 0;
पूर्ण

/* called under bridge lock */
अटल व्योम br_topology_change_acknowledged(काष्ठा net_bridge *br)
अणु
	br->topology_change_detected = 0;
	del_समयr(&br->tcn_समयr);
पूर्ण

/* called under bridge lock */
व्योम br_topology_change_detection(काष्ठा net_bridge *br)
अणु
	पूर्णांक isroot = br_is_root_bridge(br);

	अगर (br->stp_enabled != BR_KERNEL_STP)
		वापस;

	br_info(br, "topology change detected, %s\n",
		isroot ? "propagating" : "sending tcn bpdu");

	अगर (isroot) अणु
		__br_set_topology_change(br, 1);
		mod_समयr(&br->topology_change_समयr, jअगरfies
			  + br->bridge_क्रमward_delay + br->bridge_max_age);
	पूर्ण अन्यथा अगर (!br->topology_change_detected) अणु
		br_transmit_tcn(br);
		mod_समयr(&br->tcn_समयr, jअगरfies + br->bridge_hello_समय);
	पूर्ण

	br->topology_change_detected = 1;
पूर्ण

/* called under bridge lock */
व्योम br_config_bpdu_generation(काष्ठा net_bridge *br)
अणु
	काष्ठा net_bridge_port *p;

	list_क्रम_each_entry(p, &br->port_list, list) अणु
		अगर (p->state != BR_STATE_DISABLED &&
		    br_is_designated_port(p))
			br_transmit_config(p);
	पूर्ण
पूर्ण

/* called under bridge lock */
अटल व्योम br_reply(काष्ठा net_bridge_port *p)
अणु
	br_transmit_config(p);
पूर्ण

/* called under bridge lock */
व्योम br_configuration_update(काष्ठा net_bridge *br)
अणु
	br_root_selection(br);
	br_designated_port_selection(br);
पूर्ण

/* called under bridge lock */
व्योम br_become_designated_port(काष्ठा net_bridge_port *p)
अणु
	काष्ठा net_bridge *br;

	br = p->br;
	p->designated_root = br->designated_root;
	p->designated_cost = br->root_path_cost;
	p->designated_bridge = br->bridge_id;
	p->designated_port = p->port_id;
पूर्ण


/* called under bridge lock */
अटल व्योम br_make_blocking(काष्ठा net_bridge_port *p)
अणु
	अगर (p->state != BR_STATE_DISABLED &&
	    p->state != BR_STATE_BLOCKING) अणु
		अगर (p->state == BR_STATE_FORWARDING ||
		    p->state == BR_STATE_LEARNING)
			br_topology_change_detection(p->br);

		br_set_state(p, BR_STATE_BLOCKING);
		br_अगरinfo_notअगरy(RTM_NEWLINK, शून्य, p);

		del_समयr(&p->क्रमward_delay_समयr);
	पूर्ण
पूर्ण

/* called under bridge lock */
अटल व्योम br_make_क्रमwarding(काष्ठा net_bridge_port *p)
अणु
	काष्ठा net_bridge *br = p->br;

	अगर (p->state != BR_STATE_BLOCKING)
		वापस;

	अगर (br->stp_enabled == BR_NO_STP || br->क्रमward_delay == 0) अणु
		br_set_state(p, BR_STATE_FORWARDING);
		br_topology_change_detection(br);
		del_समयr(&p->क्रमward_delay_समयr);
	पूर्ण अन्यथा अगर (br->stp_enabled == BR_KERNEL_STP)
		br_set_state(p, BR_STATE_LISTENING);
	अन्यथा
		br_set_state(p, BR_STATE_LEARNING);

	br_अगरinfo_notअगरy(RTM_NEWLINK, शून्य, p);

	अगर (br->क्रमward_delay != 0)
		mod_समयr(&p->क्रमward_delay_समयr, jअगरfies + br->क्रमward_delay);
पूर्ण

/* called under bridge lock */
व्योम br_port_state_selection(काष्ठा net_bridge *br)
अणु
	काष्ठा net_bridge_port *p;
	अचिन्हित पूर्णांक liveports = 0;

	list_क्रम_each_entry(p, &br->port_list, list) अणु
		अगर (p->state == BR_STATE_DISABLED)
			जारी;

		/* Don't change port states अगर userspace is handling STP */
		अगर (br->stp_enabled != BR_USER_STP) अणु
			अगर (p->port_no == br->root_port) अणु
				p->config_pending = 0;
				p->topology_change_ack = 0;
				br_make_क्रमwarding(p);
			पूर्ण अन्यथा अगर (br_is_designated_port(p)) अणु
				del_समयr(&p->message_age_समयr);
				br_make_क्रमwarding(p);
			पूर्ण अन्यथा अणु
				p->config_pending = 0;
				p->topology_change_ack = 0;
				br_make_blocking(p);
			पूर्ण
		पूर्ण

		अगर (p->state != BR_STATE_BLOCKING)
			br_multicast_enable_port(p);
		/* Multicast is not disabled क्रम the port when it goes in
		 * blocking state because the समयrs will expire and stop by
		 * themselves without sending more queries.
		 */
		अगर (p->state == BR_STATE_FORWARDING)
			++liveports;
	पूर्ण

	अगर (liveports == 0)
		netअगर_carrier_off(br->dev);
	अन्यथा
		netअगर_carrier_on(br->dev);
पूर्ण

/* called under bridge lock */
अटल व्योम br_topology_change_acknowledge(काष्ठा net_bridge_port *p)
अणु
	p->topology_change_ack = 1;
	br_transmit_config(p);
पूर्ण

/* called under bridge lock */
व्योम br_received_config_bpdu(काष्ठा net_bridge_port *p,
			     स्थिर काष्ठा br_config_bpdu *bpdu)
अणु
	काष्ठा net_bridge *br;
	पूर्णांक was_root;

	p->stp_xstats.rx_bpdu++;

	br = p->br;
	was_root = br_is_root_bridge(br);

	अगर (br_supersedes_port_info(p, bpdu)) अणु
		br_record_config_inक्रमmation(p, bpdu);
		br_configuration_update(br);
		br_port_state_selection(br);

		अगर (!br_is_root_bridge(br) && was_root) अणु
			del_समयr(&br->hello_समयr);
			अगर (br->topology_change_detected) अणु
				del_समयr(&br->topology_change_समयr);
				br_transmit_tcn(br);

				mod_समयr(&br->tcn_समयr,
					  jअगरfies + br->bridge_hello_समय);
			पूर्ण
		पूर्ण

		अगर (p->port_no == br->root_port) अणु
			br_record_config_समयout_values(br, bpdu);
			br_config_bpdu_generation(br);
			अगर (bpdu->topology_change_ack)
				br_topology_change_acknowledged(br);
		पूर्ण
	पूर्ण अन्यथा अगर (br_is_designated_port(p)) अणु
		br_reply(p);
	पूर्ण
पूर्ण

/* called under bridge lock */
व्योम br_received_tcn_bpdu(काष्ठा net_bridge_port *p)
अणु
	p->stp_xstats.rx_tcn++;

	अगर (br_is_designated_port(p)) अणु
		br_info(p->br, "port %u(%s) received tcn bpdu\n",
			(अचिन्हित पूर्णांक) p->port_no, p->dev->name);

		br_topology_change_detection(p->br);
		br_topology_change_acknowledge(p);
	पूर्ण
पूर्ण

/* Change bridge STP parameter */
पूर्णांक br_set_hello_समय(काष्ठा net_bridge *br, अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ t = घड़ी_प्रकार_to_jअगरfies(val);

	अगर (t < BR_MIN_HELLO_TIME || t > BR_MAX_HELLO_TIME)
		वापस -दुस्फल;

	spin_lock_bh(&br->lock);
	br->bridge_hello_समय = t;
	अगर (br_is_root_bridge(br))
		br->hello_समय = br->bridge_hello_समय;
	spin_unlock_bh(&br->lock);
	वापस 0;
पूर्ण

पूर्णांक br_set_max_age(काष्ठा net_bridge *br, अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ t = घड़ी_प्रकार_to_jअगरfies(val);

	अगर (t < BR_MIN_MAX_AGE || t > BR_MAX_MAX_AGE)
		वापस -दुस्फल;

	spin_lock_bh(&br->lock);
	br->bridge_max_age = t;
	अगर (br_is_root_bridge(br))
		br->max_age = br->bridge_max_age;
	spin_unlock_bh(&br->lock);
	वापस 0;

पूर्ण

/* called under bridge lock */
पूर्णांक __set_ageing_समय(काष्ठा net_device *dev, अचिन्हित दीर्घ t)
अणु
	काष्ठा चयनdev_attr attr = अणु
		.orig_dev = dev,
		.id = SWITCHDEV_ATTR_ID_BRIDGE_AGEING_TIME,
		.flags = SWITCHDEV_F_SKIP_EOPNOTSUPP | SWITCHDEV_F_DEFER,
		.u.ageing_समय = jअगरfies_to_घड़ी_प्रकार(t),
	पूर्ण;
	पूर्णांक err;

	err = चयनdev_port_attr_set(dev, &attr, शून्य);
	अगर (err && err != -EOPNOTSUPP)
		वापस err;

	वापस 0;
पूर्ण

/* Set समय पूर्णांकerval that dynamic क्रमwarding entries live
 * For pure software bridge, allow values outside the 802.1
 * standard specअगरication क्रम special हालs:
 *  0 - entry never ages (all permanent)
 *  1 - entry disappears (no persistence)
 *
 * Offloaded चयन entries maybe more restrictive
 */
पूर्णांक br_set_ageing_समय(काष्ठा net_bridge *br, घड़ी_प्रकार ageing_समय)
अणु
	अचिन्हित दीर्घ t = घड़ी_प्रकार_to_jअगरfies(ageing_समय);
	पूर्णांक err;

	err = __set_ageing_समय(br->dev, t);
	अगर (err)
		वापस err;

	spin_lock_bh(&br->lock);
	br->bridge_ageing_समय = t;
	br->ageing_समय = t;
	spin_unlock_bh(&br->lock);

	mod_delayed_work(प्रणाली_दीर्घ_wq, &br->gc_work, 0);

	वापस 0;
पूर्ण

घड़ी_प्रकार br_get_ageing_समय(काष्ठा net_device *br_dev)
अणु
	काष्ठा net_bridge *br;

	अगर (!netअगर_is_bridge_master(br_dev))
		वापस 0;

	br = netdev_priv(br_dev);

	वापस jअगरfies_to_घड़ी_प्रकार(br->ageing_समय);
पूर्ण
EXPORT_SYMBOL_GPL(br_get_ageing_समय);

/* called under bridge lock */
व्योम __br_set_topology_change(काष्ठा net_bridge *br, अचिन्हित अक्षर val)
अणु
	अचिन्हित दीर्घ t;
	पूर्णांक err;

	अगर (br->stp_enabled == BR_KERNEL_STP && br->topology_change != val) अणु
		/* On topology change, set the bridge ageing समय to twice the
		 * क्रमward delay. Otherwise, restore its शेष ageing समय.
		 */

		अगर (val) अणु
			t = 2 * br->क्रमward_delay;
			br_debug(br, "decreasing ageing time to %lu\n", t);
		पूर्ण अन्यथा अणु
			t = br->bridge_ageing_समय;
			br_debug(br, "restoring ageing time to %lu\n", t);
		पूर्ण

		err = __set_ageing_समय(br->dev, t);
		अगर (err)
			br_warn(br, "error offloading ageing time\n");
		अन्यथा
			br->ageing_समय = t;
	पूर्ण

	br->topology_change = val;
पूर्ण

व्योम __br_set_क्रमward_delay(काष्ठा net_bridge *br, अचिन्हित दीर्घ t)
अणु
	br->bridge_क्रमward_delay = t;
	अगर (br_is_root_bridge(br))
		br->क्रमward_delay = br->bridge_क्रमward_delay;
पूर्ण

पूर्णांक br_set_क्रमward_delay(काष्ठा net_bridge *br, अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ t = घड़ी_प्रकार_to_jअगरfies(val);
	पूर्णांक err = -दुस्फल;

	spin_lock_bh(&br->lock);
	अगर (br->stp_enabled != BR_NO_STP &&
	    (t < BR_MIN_FORWARD_DELAY || t > BR_MAX_FORWARD_DELAY))
		जाओ unlock;

	__br_set_क्रमward_delay(br, t);
	err = 0;

unlock:
	spin_unlock_bh(&br->lock);
	वापस err;
पूर्ण
