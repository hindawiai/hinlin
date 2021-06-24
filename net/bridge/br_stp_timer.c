<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Spanning tree protocol; समयr-related code
 *	Linux ethernet bridge
 *
 *	Authors:
 *	Lennert Buytenhek		<buytenh@gnu.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/बार.h>

#समावेश "br_private.h"
#समावेश "br_private_stp.h"

/* called under bridge lock */
अटल पूर्णांक br_is_designated_क्रम_some_port(स्थिर काष्ठा net_bridge *br)
अणु
	काष्ठा net_bridge_port *p;

	list_क्रम_each_entry(p, &br->port_list, list) अणु
		अगर (p->state != BR_STATE_DISABLED &&
		    !स_भेद(&p->designated_bridge, &br->bridge_id, 8))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम br_hello_समयr_expired(काष्ठा समयr_list *t)
अणु
	काष्ठा net_bridge *br = from_समयr(br, t, hello_समयr);

	br_debug(br, "hello timer expired\n");
	spin_lock(&br->lock);
	अगर (br->dev->flags & IFF_UP) अणु
		br_config_bpdu_generation(br);

		अगर (br->stp_enabled == BR_KERNEL_STP)
			mod_समयr(&br->hello_समयr,
				  round_jअगरfies(jअगरfies + br->hello_समय));
	पूर्ण
	spin_unlock(&br->lock);
पूर्ण

अटल व्योम br_message_age_समयr_expired(काष्ठा समयr_list *t)
अणु
	काष्ठा net_bridge_port *p = from_समयr(p, t, message_age_समयr);
	काष्ठा net_bridge *br = p->br;
	स्थिर bridge_id *id = &p->designated_bridge;
	पूर्णांक was_root;

	अगर (p->state == BR_STATE_DISABLED)
		वापस;

	br_info(br, "port %u(%s) neighbor %.2x%.2x.%pM lost\n",
		(अचिन्हित पूर्णांक) p->port_no, p->dev->name,
		id->prio[0], id->prio[1], &id->addr);

	/*
	 * According to the spec, the message age समयr cannot be
	 * running when we are the root bridge. So..  this was_root
	 * check is redundant. I'm leaving it in क्रम now, though.
	 */
	spin_lock(&br->lock);
	अगर (p->state == BR_STATE_DISABLED)
		जाओ unlock;
	was_root = br_is_root_bridge(br);

	br_become_designated_port(p);
	br_configuration_update(br);
	br_port_state_selection(br);
	अगर (br_is_root_bridge(br) && !was_root)
		br_become_root_bridge(br);
 unlock:
	spin_unlock(&br->lock);
पूर्ण

अटल व्योम br_क्रमward_delay_समयr_expired(काष्ठा समयr_list *t)
अणु
	काष्ठा net_bridge_port *p = from_समयr(p, t, क्रमward_delay_समयr);
	काष्ठा net_bridge *br = p->br;

	br_debug(br, "port %u(%s) forward delay timer\n",
		 (अचिन्हित पूर्णांक) p->port_no, p->dev->name);
	spin_lock(&br->lock);
	अगर (p->state == BR_STATE_LISTENING) अणु
		br_set_state(p, BR_STATE_LEARNING);
		mod_समयr(&p->क्रमward_delay_समयr,
			  jअगरfies + br->क्रमward_delay);
	पूर्ण अन्यथा अगर (p->state == BR_STATE_LEARNING) अणु
		br_set_state(p, BR_STATE_FORWARDING);
		अगर (br_is_designated_क्रम_some_port(br))
			br_topology_change_detection(br);
		netअगर_carrier_on(br->dev);
	पूर्ण
	rcu_पढ़ो_lock();
	br_अगरinfo_notअगरy(RTM_NEWLINK, शून्य, p);
	rcu_पढ़ो_unlock();
	spin_unlock(&br->lock);
पूर्ण

अटल व्योम br_tcn_समयr_expired(काष्ठा समयr_list *t)
अणु
	काष्ठा net_bridge *br = from_समयr(br, t, tcn_समयr);

	br_debug(br, "tcn timer expired\n");
	spin_lock(&br->lock);
	अगर (!br_is_root_bridge(br) && (br->dev->flags & IFF_UP)) अणु
		br_transmit_tcn(br);

		mod_समयr(&br->tcn_समयr, jअगरfies + br->bridge_hello_समय);
	पूर्ण
	spin_unlock(&br->lock);
पूर्ण

अटल व्योम br_topology_change_समयr_expired(काष्ठा समयr_list *t)
अणु
	काष्ठा net_bridge *br = from_समयr(br, t, topology_change_समयr);

	br_debug(br, "topo change timer expired\n");
	spin_lock(&br->lock);
	br->topology_change_detected = 0;
	__br_set_topology_change(br, 0);
	spin_unlock(&br->lock);
पूर्ण

अटल व्योम br_hold_समयr_expired(काष्ठा समयr_list *t)
अणु
	काष्ठा net_bridge_port *p = from_समयr(p, t, hold_समयr);

	br_debug(p->br, "port %u(%s) hold timer expired\n",
		 (अचिन्हित पूर्णांक) p->port_no, p->dev->name);

	spin_lock(&p->br->lock);
	अगर (p->config_pending)
		br_transmit_config(p);
	spin_unlock(&p->br->lock);
पूर्ण

व्योम br_stp_समयr_init(काष्ठा net_bridge *br)
अणु
	समयr_setup(&br->hello_समयr, br_hello_समयr_expired, 0);
	समयr_setup(&br->tcn_समयr, br_tcn_समयr_expired, 0);
	समयr_setup(&br->topology_change_समयr,
		    br_topology_change_समयr_expired, 0);
पूर्ण

व्योम br_stp_port_समयr_init(काष्ठा net_bridge_port *p)
अणु
	समयr_setup(&p->message_age_समयr, br_message_age_समयr_expired, 0);
	समयr_setup(&p->क्रमward_delay_समयr, br_क्रमward_delay_समयr_expired, 0);
	समयr_setup(&p->hold_समयr, br_hold_समयr_expired, 0);
पूर्ण

/* Report ticks left (in USER_HZ) used क्रम API */
अचिन्हित दीर्घ br_समयr_value(स्थिर काष्ठा समयr_list *समयr)
अणु
	वापस समयr_pending(समयr)
		? jअगरfies_delta_to_घड़ी_प्रकार(समयr->expires - jअगरfies) : 0;
पूर्ण
